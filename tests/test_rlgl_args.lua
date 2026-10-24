-- rlgl bindings that are checkable without a GL context: registration, constants
-- and argument validation (errors are raised before any GL call is made).
local T = ...
local r = T.raylib

-- Every rlgl function in rlgl.h is either bound or deliberately unsupported
local unsupported = {
    rlglInit = true, rlglClose = true, rlLoadExtensions = true, rlGetProcAddress = true,
    rlGetShaderLocsDefault = true, rlSetShader = true, rlEnableStatePointer = true,
}
local header = assert(io.open("raylib/src/rlgl.h", "r"))
local text = header:read("*a")
header:close()
text = text:match("^(.-)#if defined%(RLGL_IMPLEMENTATION%)") or text
local declared, bound_count = 0, 0
for name in text:gmatch("\nRLAPI [^\n;]-%f[%w_](rl%w+)%(") do
    declared = declared + 1
    if unsupported[name] then
        T.assert_eq(name .. " is not exposed", r[name], nil)
    else
        bound_count = bound_count + 1
        if type(r[name]) ~= "function" then T.assert_eq(name .. " is bound", type(r[name]), "function") end
    end
end
T.assert_eq("rlgl functions found in header", declared, 163)
T.assert_eq("rlgl functions bound", bound_count, 156)

-- Constants
T.assert_eq("RL_TRIANGLES", r.RL_TRIANGLES, 0x0004)
T.assert_eq("RL_QUADS", r.RL_QUADS, 0x0007)
T.assert_eq("RL_MODELVIEW", r.RL_MODELVIEW, 0x1700)
T.assert_eq("RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8", r.RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 7)
T.assert_eq("RL_OPENGL_33", type(r.RL_OPENGL_33), "number")
T.assert_eq("RL_SHADER_UNIFORM_VEC3", r.RL_SHADER_UNIFORM_VEC3, 2)

-- Argument validation (these must raise before touching OpenGL)
local RGBA = r.RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
local function fails(desc, f, ...) T.assert_false(desc, (pcall(f, ...))) end

fails("rlUpdateTexture rejects a short buffer", r.rlUpdateTexture, 1, 0, 0, 2, 2, RGBA, "too short")
fails("rlUpdateTexture rejects non-positive size", r.rlUpdateTexture, 1, 0, 0, 0, 2, RGBA, string.rep("x", 64))
fails("rlLoadTexture rejects a short buffer", r.rlLoadTexture, "abc", 4, 4, RGBA, 1)
fails("rlLoadTexture rejects a short mip chain", r.rlLoadTexture, string.rep("x", 64), 4, 4, RGBA, 3)
fails("rlLoadTextureCubemap needs six faces", r.rlLoadTextureCubemap, string.rep("x", 16 * 4), 4, RGBA, 1)
fails("rlLoadVertexBuffer rejects a short buffer", r.rlLoadVertexBuffer, "abc", 64, false)
fails("rlUpdateVertexBuffer rejects a short buffer", r.rlUpdateVertexBuffer, 1, "abc", 64, 0)
fails("rlUpdateVertexBufferElements rejects a short buffer", r.rlUpdateVertexBufferElements, 1, "abc", 64, 0)
fails("rlLoadShaderBuffer rejects a short buffer", r.rlLoadShaderBuffer, 64, "abc", 0)
fails("rlUpdateShaderBuffer rejects a short buffer", r.rlUpdateShaderBuffer, 1, "abc", 64, 0)
fails("rlDrawVertexArrayElements rejects a short index buffer", r.rlDrawVertexArrayElements, 0, 6, "abc")
fails("rlSetUniform rejects a short table", r.rlSetUniform, 0, {1.0}, r.RL_SHADER_UNIFORM_VEC3, 1)
fails("rlSetUniform rejects an unknown type", r.rlSetUniform, 0, {1.0}, 99, 1)
fails("rlSetUniformMatrices rejects an empty table", r.rlSetUniformMatrices, 0, {})
fails("rlSetVertexAttributeDefault rejects count 5", r.rlSetVertexAttributeDefault, 0, {1, 2, 3, 4, 5}, 0, 5)
fails("rlSetVertexAttributeDefault rejects a short table", r.rlSetVertexAttributeDefault, 0, {1}, 0, 3)
fails("rlColor4ub rejects out-of-range bytes", r.rlColor4ub, 300, 0, 0, 255)
fails("rlColor4ub rejects negative bytes", r.rlColor4ub, -1, 0, 0, 255)
fails("rlEnableTexture rejects negative ids", r.rlEnableTexture, -5)
fails("rlMultMatrixf rejects a non-table", r.rlMultMatrixf, 5)
fails("rlDrawRenderBatch rejects non-batches", r.rlDrawRenderBatch, {})
fails("rlGenTextureMipmaps rejects bad sizes", r.rlGenTextureMipmaps, 1, 0, 4, RGBA)
fails("rlReadScreenPixels rejects bad sizes", r.rlReadScreenPixels, 0, 4)
fails("rlCopyFramebuffer rejects unknown formats", r.rlCopyFramebuffer, 0, 0, 4, 4, 9999)
