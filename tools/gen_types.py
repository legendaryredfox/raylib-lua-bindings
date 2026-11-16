#!/usr/bin/env python3
"""Generate types/raylib.lua (LuaLS definitions) from the raylib headers.

Signatures are derived from raylib.h / raymath.h / rlgl.h, then adjusted to the
Lua API:
  * `T *items, int count` pairs collapse to one `T[]` parameter
  * `int *out` result parameters become extra return values
  * structs are tables (`Vector2`, `Color`, ...) or userdata (`Image`, `Sound`, ...)
OVERRIDES holds the functions whose Lua signature differs from the header in a
way the rules above cannot express; each entry was checked against its C wrapper.

Only functions registered in src/lua_raylib*.c are emitted, so the file cannot
list something the module does not export. The script fails if a registered
function has no signature, so a raylib upgrade cannot leave one untyped.

Usage (from the repo root):  python3 tools/gen_types.py
"""
import glob
import re
import sys
from pathlib import Path

OUT = Path("types/raylib.lua")
RAYLIB_H = Path("raylib/src/raylib.h")
RAYMATH_H = Path("raylib/src/raymath.h")
RLGL_H = Path("raylib/src/rlgl.h")

# ---------------------------------------------------------------------------
# Types
# ---------------------------------------------------------------------------
# Opaque resources: userdata with a named metatable. alias -> canonical class
USERDATA = {
    "Image": "Image", "Texture2D": "Texture2D", "Texture": "Texture2D",
    "TextureCubemap": "Texture2D", "RenderTexture2D": "RenderTexture2D",
    "RenderTexture": "RenderTexture2D", "Font": "Font", "Sound": "Sound",
    "Music": "Music", "AudioStream": "AudioStream", "Wave": "Wave",
    "Model": "Model", "Mesh": "Mesh", "Material": "Material",
    "ModelAnimation": "ModelAnimation", "Shader": "Shader", "Camera": "Camera",
    "Camera3D": "Camera", "AutomationEventList": "AutomationEventList",
    "VrStereoConfig": "VrStereoConfig", "rlRenderBatch": "rlRenderBatch",
}
# Plain tables with named fields
TABLES = {
    "Vector2", "Vector3", "Vector4", "Color", "Rectangle", "Matrix", "Ray",
    "RayCollision", "BoundingBox", "NPatchInfo", "Camera2D", "VrDeviceInfo",
}
ALIAS = {"Quaternion": "Vector4"}
SCALARS = {
    "int": "integer", "unsigned int": "integer", "unsigned char": "integer",
    "short": "integer", "unsigned short": "integer", "long": "integer",
    "float": "number", "double": "number", "bool": "boolean",
}
STRINGS = {"const char *", "char *"}
OPAQUE_PTR = {"void *", "const void *", "unsigned char *", "const unsigned char *"}

# Manual class docs for userdata (they carry no readable fields)
USERDATA_DOC = {
    "Image": "CPU image. Released with UnloadImage (or `<close>`).",
    "Texture2D": "GPU texture. Released with UnloadTexture (or `<close>`).",
    "RenderTexture2D": "Framebuffer. Released with UnloadRenderTexture (or `<close>`).",
    "Font": "Font. Released with UnloadFont (or `<close>`).",
    "Sound": "Sound. Released with UnloadSound (or `<close>`).",
    "Music": "Music stream. Released with UnloadMusicStream (or `<close>`).",
    "AudioStream": "Audio stream. Released with UnloadAudioStream (or `<close>`).",
    "Wave": "Wave data. Released with UnloadWave (or `<close>`).",
    "Model": "3D model. Released with UnloadModel (or `<close>`).",
    "Mesh": "Mesh. Released with UnloadMesh (or `<close>`).",
    "Material": "Material. Released with UnloadMaterial (or `<close>`).",
    "ModelAnimation": "Model animation. Released with UnloadModelAnimation (or `<close>`).",
    "Shader": "Shader. Released with UnloadShader (or `<close>`).",
    "Camera": "3D camera userdata from CreateCamera3D; UpdateCamera mutates it.",
    "AutomationEventList": "Automation event list. Released with UnloadAutomationEventList (or `<close>`).",
    "VrStereoConfig": "VR stereo config. Released with UnloadVrStereoConfig (or `<close>`).",
    "rlRenderBatch": "rlgl render batch. Released with rlUnloadRenderBatch (or `<close>`).",
}

# Extra, non-header classes
EXTRA_CLASSES = """\
---Samples handed to an audio handler. Only valid during the call.
---@class AudioSampleBuffer
---@field [integer] number sample, 1-based
---@operator len: integer

---Opaque glyph array from LoadFontData, consumed by GenImageFontAtlas / UnloadFontData.
---@class GlyphInfoArray

---Opaque glyph info returned by GetGlyphInfo.
---@class GlyphInfo

---Packed `0xRRGGBBAA` color (accepted by ClearBackground and DrawRectangle only).
---@alias PackedColor integer

---Audio handler: runs on raylib's audio thread from a private Lua state, so it may only
---use `_ENV` and its arguments (no upvalues, script globals or the raylib module).
---@alias AudioHandler fun(samples: AudioSampleBuffer, frames: integer, channels: integer)
"""


def lua_type(ctype, fallback="any"):
    """Header C type -> LuaLS type (None when it must be dropped by the caller)."""
    t = re.sub(r"\s+", " ", ctype.replace("const ", "")).strip()
    t = t.replace(" *", "*").replace("* ", "*")
    if t in SCALARS:
        return SCALARS[t]
    if t in ("char*",):
        return "string"
    if t in ALIAS:
        return ALIAS[t]
    if t in USERDATA:
        return USERDATA[t]
    if t in TABLES:
        return t
    if t.endswith("*") and t[:-1] in USERDATA:
        return USERDATA[t[:-1]]
    if t in ("void*", "unsigned char*"):
        return "string"
    if t.endswith("Callback"):
        return "function"
    return fallback


def split_params(p):
    p = p.strip()
    if p in ("", "void"):
        return []
    return [x.strip() for x in p.split(",")]


def parse_param(p):
    """'const Vector2 *points' -> (ctype, name). Handles '...' and 'char **x'."""
    if p == "...":
        return ("...", "...")
    m = re.match(r"^(.*?)(\*{0,2})\s*(\w+)$", p)
    ctype = (m.group(1).strip() + (" " + m.group(2) if m.group(2) else "")).strip()
    return (ctype, m.group(3))


COUNT_NAMES = re.compile(r"(count|size|length|len|num|instances|frames)$", re.I)

LUA_KEYWORDS = {"end", "function", "local", "repeat", "until", "then", "not", "and", "or",
                "in", "do", "nil", "true", "false", "while", "for", "if", "else", "elseif",
                "return", "break", "goto"}


def safe(n):
    return n + "_" if n in LUA_KEYWORDS else n


def default_signature(ret, params):
    """Return (params[(name,type)], returns[type]) from a C prototype."""
    ps = [parse_param(p) for p in params]
    out_params, rets = [], []
    r = lua_type(ret, "any") if ret.strip() != "void" else None
    rn = re.sub(r"\s+", " ", ret.replace("const ", "")).strip()
    if params and rn.endswith("*") and parse_param(params[-1])[0].replace("const ", "").strip() == "int *":
        base = {"char **": "string", "unsigned char *": None}.get(rn, rn[:-1].strip())
        r = "string" if base is None else lua_type(base, "any") + "[]"
    if r:
        rets.append(r)
    i = 0
    while i < len(ps):
        ctype, name = ps[i]
        if ctype == "...":
            out_params.append(("...", "any"))
            i += 1
            continue
        norm = re.sub(r"\s+", " ", ctype.replace("const ", "")).strip()
        # int *outParam: the wrapper returns table/string lengths itself, so drop it
        if norm == "int *" and i == len(ps) - 1:
            i += 1
            continue
        if norm.endswith("*") and norm not in ("char *",):
            base = norm[:-1].strip()
            has_count = i + 1 < len(ps) and ps[i + 1][0] == "int" and COUNT_NAMES.search(ps[i + 1][1])
            if base in ("void", "unsigned char"):
                # raw data buffer: Lua string; the size argument is derived from it
                out_params.append((safe(name), "string"))
                i += 2 if has_count else 1
                continue
            if has_count and (base not in USERDATA or re.search(r"count$", ps[i + 1][1], re.I)):
                out_params.append((safe(name), lua_type(base, "any") + "[]"))
                i += 2
                continue
        out_params.append((safe(name), lua_type(ctype)))
        i += 1
    return out_params, rets


# ---------------------------------------------------------------------------
# Overrides: name -> (params [(name, type)], returns [type]). Each one was checked
# against its C wrapper in src/. Optional extras live in OVERLOADS / DOCS.
# ---------------------------------------------------------------------------
DATA = "string|lightuserdata"        # get_data_buffer: Lua string or raw pointer
V2, V3, MAT, REC, COL = "Vector2", "Vector3", "Matrix", "Rectangle", "Color"
I, N, S, B = "integer", "number", "string", "boolean"


def P(*items):
    """P("a:integer", "b:string?") -> [(name, type)]"""
    return [tuple(x.split(":", 1)) for x in items]


OVERRIDES = {
    # -- shapes / draw: the wrapper takes integers or numbers where the header has floats
    "CheckCollisionLines": (P("startPos1:Vector2", "endPos1:Vector2", "startPos2:Vector2", "endPos2:Vector2"), [B, "Vector2"]),
    "DrawCircle": (P("centerX:integer", "centerY:integer", "radius:integer", "color:Color"), []),
    "DrawEllipse": (P("centerX:integer", "centerY:integer", "radiusH:integer", "radiusV:integer", "color:Color"), []),
    "DrawRectangleGradientEx": (P("rec:Rectangle", "topLeft:Color", "bottomLeft:Color", "bottomRight:Color", "topRight:Color"), []),
    "DrawRectangleLines": (P("posX:integer", "posY:integer", "width:integer", "height:integer", "color:Color"), []),
    "DrawRectangleRounded": (P("rec:Rectangle", "roundness:number", "segments:integer", "color:Color"), []),
    "ClearBackground": (P("color:Color|PackedColor"), []),
    "DrawRectangle": (P("posX:integer", "posY:integer", "width:integer", "height:integer", "color:Color|PackedColor"), []),
    # -- text / codepoints: sizes come back as extra results
    "CodepointToUTF8": (P("codepoint:integer"), [S, I]),
    "GetCodepoint": (P("text:string"), [I, I]),
    "GetCodepointNext": (P("text:string"), [I, I]),
    "GetCodepointPrevious": (P("text:string", "pos:integer?"), ["integer?", I]),
    "TextAppend": (P("text:string", "append:string", "position:integer"), [S, I]),
    "TextCopy": (P("src:string"), [S, I]),
    "TextFormat": (P("text:string", "...:any"), [S]),
    "TextSplit": (P("text:string", "delimiter:string"), ["string[]"]),
    "TraceLog": (P("logLevel:integer", "text:string"), []),
    "LoadCodepoints": (P("text:string"), ["integer[]"]),
    "UnloadCodepoints": (P("codepoints:integer[]"), []),
    "LoadTextLines": (P("text:string"), ["string[]"]),
    "UnloadTextLines": (P("lines:string[]"), []),
    # -- fonts
    "LoadFontData": (P("fileData:string", "fontSize:integer", "codepoints:integer[]?", "type:integer?"), ["GlyphInfoArray"]),
    "GenImageFontAtlas": (P("glyphs:GlyphInfoArray", "fontSize:integer", "padding:integer", "packMethod:integer"), ["Image", "Rectangle[]"]),
    "UnloadFontData": (P("glyphs:GlyphInfoArray"), []),
    "GetGlyphInfo": (P("font:Font", "codepoint:integer"), ["GlyphInfo"]),
    # -- images / waves / music from memory (explicit dataSize) and animation frame counts
    "LoadImageFromMemory": (P("fileType:string", "fileData:string", "dataSize:integer"), ["Image"]),
    "LoadImageAnim": (P("fileName:string"), ["Image", I]),
    "LoadImageAnimFromMemory": (P("fileType:string", "fileData:string", "dataSize:integer"), ["Image", I]),
    "LoadWaveFromMemory": (P("fileType:string", "fileData:string", "dataSize:integer"), ["Wave"]),
    "LoadImageColors": (P("image:Image"), ["lightuserdata"]),
    "LoadImagePalette": (P("image:Image", "maxPaletteSize:integer"), ["lightuserdata", I]),
    "UnloadImageColors": (P("colors:lightuserdata"), []),
    "UnloadImagePalette": (P("colors:lightuserdata"), []),
    "LoadWaveSamples": (P("wave:Wave"), ["lightuserdata"]),
    "UnloadWaveSamples": (P("samples:lightuserdata"), []),
    "UpdateTextureRec": (P("texture:Texture2D", "rec:Rectangle", "pixels:" + DATA), []),
    # -- models
    "LoadMaterials": (P("fileName:string"), ["Material[]"]),
    "LoadModelAnimations": (P("fileName:string"), ["ModelAnimation[]"]),
    "UpdateMeshBuffer": (P("mesh:Mesh", "index:integer", "data:" + DATA, "dataSize:integer", "offset:integer"), []),
    # -- audio
    "UpdateSound": (P("sound:Sound", "data:" + DATA, "sampleCount:integer"), []),
    "UpdateAudioStream": (P("stream:AudioStream", "data:" + DATA, "frameCount:integer"), []),
    "SetAudioStreamCallback": (P("stream:AudioStream", "callback:AudioHandler?"), []),
    "AttachAudioStreamProcessor": (P("stream:AudioStream", "processor:AudioHandler"), []),
    "DetachAudioStreamProcessor": (P("stream:AudioStream", "processor:AudioHandler"), []),
    "AttachAudioMixedProcessor": (P("processor:AudioHandler"), []),
    "DetachAudioMixedProcessor": (P("processor:AudioHandler"), []),
    # -- files, hashes, random, automation
    "LoadFileData": (P("fileName:string"), ["string?"]),
    "UnloadFileData": (P("data:string"), []),
    "UnloadFileText": (P("text:string"), []),
    "SaveFileData": (P("fileName:string", "data:string"), [B]),
    "ExportDataAsCode": (P("data:string", "fileName:string"), [B]),
    "LoadDirectoryFiles": (P("dirPath:string"), ["string[]"]),
    "LoadDirectoryFilesEx": (P("basePath:string", "filter:string", "scanSubdirs:boolean"), ["string[]"]),
    "UnloadDirectoryFiles": (P("files:string[]"), []),
    "LoadDroppedFiles": ([], ["string[]"]),
    "UnloadDroppedFiles": (P("files:string[]"), []),
    "ComputeMD5": (P("data:string"), ["integer[]"]),
    "ComputeSHA1": (P("data:string"), ["integer[]"]),
    "ComputeSHA256": (P("data:string"), ["integer[]"]),
    "LoadRandomSequence": (P("count:integer", "min:integer", "max:integer"), ["integer[]"]),
    "UnloadRandomSequence": (P("sequence:integer[]"), []),
    "PlayAutomationEvent": (P("list:AutomationEventList", "index:integer"), []),
    "SetShaderValue": (P("shader:Shader", "locIndex:integer", "value:number|integer|number[]|integer[]", "uniformType:integer"), []),
    # -- callbacks (nil clears)
    "SetTraceLogCallback": (P("callback:(fun(logLevel: integer, text: string))?"), []),
    "SetLoadFileDataCallback": (P("callback:(fun(fileName: string): string?)?"), []),
    "SetLoadFileTextCallback": (P("callback:(fun(fileName: string): string?)?"), []),
    "SetSaveFileDataCallback": (P("callback:(fun(fileName: string, data: string): boolean)?"), []),
    "SetSaveFileTextCallback": (P("callback:(fun(fileName: string, text: string): boolean)?"), []),
    # -- raymath: out-pointers become results, float arrays become tables
    "Vector3OrthoNormalize": (P("v1:Vector3", "v2:Vector3"), [V3, V3]),
    "Vector3ToFloatV": (P("v:Vector3"), ["number[]"]),
    "MatrixToFloatV": (P("mat:Matrix"), ["number[]"]),
    "QuaternionToAxisAngle": (P("q:Vector4"), [V3, N]),
    "MatrixDecompose": (P("mat:Matrix"), [V3, "Vector4", V3]),
    # -- rlgl buffer functions (src/lua_raylib_rlgl_buffers.c)
    "rlMultMatrixf": (P("matf:Matrix|number[]"), []),
    "rlSetRenderBatchActive": (P("batch:rlRenderBatch?"), []),
    "rlLoadVertexBuffer": (P("data:string?", "size:integer", "dynamic:boolean"), [I]),
    "rlLoadVertexBufferElement": (P("data:string?", "size:integer", "dynamic:boolean"), [I]),
    "rlUpdateVertexBuffer": (P("bufferId:integer", "data:" + DATA, "dataSize:integer", "offset:integer"), []),
    "rlUpdateVertexBufferElements": (P("id:integer", "data:" + DATA, "dataSize:integer", "offset:integer"), []),
    "rlSetVertexAttributeDefault": (P("locIndex:integer", "value:number[]", "attribType:integer", "count:integer"), []),
    "rlDrawVertexArrayElements": (P("offset:integer", "count:integer", "buffer:string?"), []),
    "rlDrawVertexArrayElementsInstanced": (P("offset:integer", "count:integer", "buffer:string?", "instances:integer"), []),
    "rlLoadTexture": (P("data:string?", "width:integer", "height:integer", "format:integer", "mipmapCount:integer"), [I]),
    "rlLoadTextureCubemap": (P("data:string?", "size:integer", "format:integer", "mipmapCount:integer"), [I]),
    "rlUpdateTexture": (P("id:integer", "offsetX:integer", "offsetY:integer", "width:integer", "height:integer", "format:integer", "data:" + DATA), []),
    "rlGetGlTextureFormats": (P("format:integer"), [I, I, I]),
    "rlGenTextureMipmaps": (P("id:integer", "width:integer", "height:integer", "format:integer"), [I]),
    "rlReadTexturePixels": (P("id:integer", "width:integer", "height:integer", "format:integer"), ["string?"]),
    "rlReadScreenPixels": (P("width:integer", "height:integer"), ["string?"]),
    "rlCopyFramebuffer": (P("x:integer", "y:integer", "width:integer", "height:integer", "format:integer"), [S]),
    "rlSetUniform": (P("locIndex:integer", "value:number|number[]", "uniformType:integer", "count:integer"), []),
    "rlSetUniformMatrices": (P("locIndex:integer", "matrices:Matrix[]"), []),
    "rlLoadShaderBuffer": (P("size:integer", "data:string?", "usageHint:integer"), [I]),
    "rlUpdateShaderBuffer": (P("id:integer", "data:" + DATA, "dataSize:integer", "offset:integer"), []),
    "rlReadShaderBuffer": (P("id:integer", "count:integer", "offset:integer"), [S]),
}

# Parameters the wrapper treats as optional (nil / absent): name -> {param}
OPTIONAL = {
    "LoadAutomationEventList": {"fileName"},
    "LoadDirectoryFilesEx": {"filter"},
    "LoadFontEx": {"codepoints"},
    "LoadFontFromMemory": {"codepoints"},
    "LoadShader": {"vsFileName", "fsFileName"},
    "LoadShaderFromMemory": {"vsCode", "fsCode"},
    "SetGamepadVibration": {"duration"},
}

# Alternative call shapes the wrapper also accepts: name -> LuaLS `fun(...)` strings
OVERLOADS = {
    "DrawRectangleGradientEx": ["fun(x: number, y: number, width: number, height: number, topLeft: Color, bottomLeft: Color, bottomRight: Color, topRight: Color)"],
    "DrawRectangleRounded": ["fun(x: number, y: number, width: number, height: number, roundness: number, segments: integer, color: Color)"],
    "DrawRectangleLines": ["fun(posX: integer, posY: integer, width: integer, height: integer, lineThick: integer, color: Color)"],
    "UpdateTextureRec": ["fun(texture: Texture2D, x: number, y: number, width: number, height: number, pixels: string|lightuserdata)"],
}

# Functions that exist only in the Lua module (no raylib.h prototype): name -> (params, returns, doc)
LUA_ONLY = {
    "CreateCamera3D": (P("position:Vector3", "target:Vector3", "up:Vector3", "fovy:number", "projection:integer"), ["Camera"],
                       "Builds a 3D camera userdata (UpdateCamera mutates it)."),
    "DrawRectangleGradient": (P("posX:integer", "posY:integer", "width:integer", "height:integer", "color1:Color", "color2:Color"), [],
                              "Horizontal gradient rectangle (maps to DrawRectangleGradientH)."),
    "GetAutomationEventCount": (P("list:AutomationEventList"), [I], "Number of events in a list."),
    "GetClipboardTextLength": ([], [I], "Byte length of the clipboard text (0 when empty)."),
    "GetRenderTextureTexture": (P("renderTexture:RenderTexture2D"), ["Texture2D"],
                                "Texture view sharing the render texture's GL id. Never UnloadTexture it."),
    "GetSplinePointBezierQuad": (P("p1:Vector2", "c2:Vector2", "p3:Vector2", "t:number"), [V2],
                                 "Old name of GetSplinePointBezierQuadratic."),
    "GetTargetFPS": ([], [I], "Delegates to GetFPS()."),
    "ImageDraw": (P("dst:Image", "src:Image", "srcRec:Rectangle", "dstRec:Rectangle", "tint:Color"), [],
                  "Maps to ImageDrawImagePro."),
    "ImageDrawTriangleEx": (P("dst:Image", "v1:Vector2", "v2:Vector2", "v3:Vector2", "c1:Color", "c2:Color", "c3:Color"), [],
                            "Old name of ImageDrawTriangleGradient."),
    "UnloadModelAnimation": (P("animation:ModelAnimation"), [], "Release one animation (never the plural raylib call)."),
}


# ---------------------------------------------------------------------------
# Registered names
# ---------------------------------------------------------------------------
def registered_names():
    names = set()
    for f in glob.glob("src/lua_raylib*.c"):
        for m in re.finditer(r'\{"(\w+)",\s*\w+\}', Path(f).read_text()):
            if not m.group(1).startswith("__"):
                names.add(m.group(1))
    return names


def constant_names():
    """(integers, floats, strings) exported by the generated constants file."""
    text = Path("src/lua_raylib_constants.c").read_text()
    ints = re.findall(r'\{"(\w+)",\s*\(lua_Integer\)', text)
    ints += re.findall(r'lua_pushinteger\(L, \w+\);\s*lua_setfield\(L, -2, "(\w+)"\)', text)
    nums = re.findall(r'lua_pushnumber\(L, [^;]+\);\s*lua_setfield\(L, -2, "(\w+)"\)', text)
    strs = re.findall(r'lua_pushstring\(L, [^;]+\);\s*lua_setfield\(L, -2, "(\w+)"\)', text)
    return ints, nums, strs


def color_names():
    return re.findall(r'^\s*\{\s*"(\w+)",\s*\{\s*\d+', Path("src/lua_raylib.c").read_text(), flags=re.M)


def comment_of(line):
    m = re.search(r"//\s*(.+?)\s*$", line)
    return m.group(1) if m else ""


def parse_protos(path, macro):
    protos = {}
    text = path.read_text()
    if macro == "RLAPI" and path == RLGL_H:
        text = text.split("#if defined(RLGL_IMPLEMENTATION)")[0]
    for line in text.splitlines():
        m = re.match(rf"^{macro}\s+(.+?)\b(\w+)\(([^)]*)\)\s*(?:;|\{{|$)", line)
        if m:
            protos[m.group(2)] = (m.group(1).strip(), split_params(m.group(3)), comment_of(line))
    return protos


def parse_structs():
    """struct name -> [(field, ctype)] for TABLES (from raylib.h and raymath.h)."""
    out = {}
    text = RAYLIB_H.read_text()
    for m in re.finditer(r"typedef struct (\w+) \{(.*?)\} \1;", text, flags=re.S):
        name = m.group(1)
        if name not in TABLES:
            continue
        fields = []
        for line in m.group(2).splitlines():
            line = line.strip()
            fm = re.match(r"^([\w ]+?)\s+(\w+(?:\s*,\s*\w+)*)\s*;\s*(?://\s*(.*))?$", line)
            if not fm:
                continue
            ctype = fm.group(1).strip()
            for fname in [x.strip() for x in fm.group(2).split(",")]:
                fields.append((fname, ctype, fm.group(3) or ""))
        out[name] = fields
    return out


def render_class(name, fields):
    lines = [f"---@class {name}"]
    for fname, ctype, doc in fields:
        t = lua_type(ctype)
        lines.append(f"---@field {fname} {t}" + (f" {doc}" if doc else ""))
    return "\n".join(lines)


def main():
    reg = registered_names()
    raylib = parse_protos(RAYLIB_H, "RLAPI")
    rlgl = parse_protos(RLGL_H, "RLAPI")
    rmath = parse_protos(RAYMATH_H, "RMAPI")
    structs = parse_structs()

    emitted, missing = {}, []
    for source, protos in (("raylib", raylib), ("raymath", rmath), ("rlgl", rlgl)):
        for name, (ret, params, doc) in protos.items():
            if name not in reg:
                continue
            if name in OVERRIDES:
                p, r = OVERRIDES[name]
            else:
                p, r = default_signature(ret, params)
            emitted[name] = (source, doc, p, r)
        for name, opt in OPTIONAL.items():
            if name in emitted:
                src_, doc_, p_, r_ = emitted[name]
                emitted[name] = (src_, doc_, [(n, t + "?" if n in opt and not t.endswith("?") else t) for n, t in p_], r_)
    for name, (p, r, doc) in LUA_ONLY.items():
        emitted[name] = ("lua", doc, p, r)
    for name, (p, r) in OVERRIDES.items():
        if name in reg and name not in emitted:
            emitted[name] = ("lua", "", p, r)
    for name in sorted(reg):
        if name not in emitted:
            missing.append(name)
    if missing:
        sys.exit("no signature for: " + ", ".join(missing))

    out = ["---@meta raylib", "---Generated by tools/gen_types.py. Do not edit by hand.", "", "---@class raylib", "local raylib = {}", ""]
    out.append(EXTRA_CLASSES)
    for name in sorted(TABLES):
        if name == "Camera2D" or name in structs:
            out.append(render_class(name, structs[name]))
            out.append("")
    out.append("---@alias Quaternion Vector4\n")
    for cls, doc in USERDATA_DOC.items():
        out.append(f"---{doc}\n---@class {cls}\n")
    for name in sorted(emitted, key=lambda n: (emitted[n][0], n)):
        source, doc, p, r = emitted[name]
        lines = [f"---{doc}"] if doc else []
        for pname, ptype in p:
            lines.append(f"---@param {pname} {ptype}")
        for ov in OVERLOADS.get(name, []):
            lines.append(f"---@overload {ov}")
        for rt in r:
            lines.append(f"---@return {rt}")
        args = ", ".join(pn for pn, _ in p)
        lines.append(f"function raylib.{name}({args}) end")
        out.append("\n".join(lines))
        out.append("")
    ints, nums, strs = constant_names()
    for n in sorted(set(ints)):
        out.append(f"---@type integer\nraylib.{n} = 0\n")
    for n in sorted(set(nums)):
        out.append(f"---@type number\nraylib.{n} = 0\n")
    for n in sorted(set(strs)):
        out.append(f"---@type string\nraylib.{n} = \"\"\n")
    for n in color_names():
        out.append(f"---@type Color\nraylib.{n} = nil\n")
    out.append("-- Named colors are also globals")
    for n in color_names():
        out.append(f"---@type Color\n{n} = nil\n")
    out.append("return raylib")
    OUT.parent.mkdir(exist_ok=True)
    OUT.write_text("\n".join(out) + "\n")
    print(f"wrote {OUT}: {len(emitted)} functions")


if __name__ == "__main__":
    main()
