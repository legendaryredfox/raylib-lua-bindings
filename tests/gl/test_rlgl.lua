-- rlgl against a real GL context (run by `make test-gl` under xvfb-run).
local T = ...
local r = T.raylib

r.SetTraceLogLevel(r.LOG_WARNING)
r.InitWindow(64, 64, "rlgl tests")
local RGBA = r.RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8

local function pixel(data, w, x, y)
    local i = (y * w + x) * 4 + 1
    return data:byte(i, i + 3)
end

T.assert_eq("rlGetVersion is OpenGL 3.3", r.rlGetVersion(), r.RL_OPENGL_33)
T.assert_eq("rlGetPixelFormatName is a string", type(r.rlGetPixelFormatName(RGBA)), "string")
local internal, format, gltype = r.rlGetGlTextureFormats(RGBA)
T.assert_true("rlGetGlTextureFormats returns GL enums", internal > 0 and format > 0 and gltype > 0)

-- Immediate mode: draw a red triangle and read the framebuffer back
r.BeginDrawing()
r.ClearBackground(r.BLACK)
r.rlBegin(r.RL_TRIANGLES)
r.rlColor4ub(255, 0, 0, 255)
r.rlVertex2f(32, 0)
r.rlVertex2f(0, 64)
r.rlVertex2f(64, 64)
r.rlEnd()
r.rlDrawRenderBatchActive()
local screen = r.rlReadScreenPixels(64, 64)
r.EndDrawing()
T.assert_eq("rlReadScreenPixels size", #screen, 64 * 64 * 4)
local pr, pg, pb = pixel(screen, 64, 32, 48)
T.assert_eq("triangle red", pr, 255)
T.assert_eq("triangle green", pg, 0)
T.assert_eq("triangle blue", pb, 0)
local br, bg = pixel(screen, 64, 1, 1)
T.assert_true("outside the triangle stays black", br == 0 and bg == 0)

-- Matrix stack helpers
local ok = pcall(function()
    r.rlMatrixMode(r.RL_MODELVIEW)
    r.rlPushMatrix()
    r.rlLoadIdentity()
    r.rlTranslatef(1, 2, 3)
    r.rlRotatef(90, 0, 0, 1)
    r.rlScalef(2, 2, 2)
    r.rlMultMatrixf({1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1})
    r.rlMultMatrixf(r.MatrixIdentity())
    local m = r.rlGetMatrixTransform()
    assert(type(m.m0) == "number")
    r.rlPopMatrix()
end)
T.assert_true("matrix stack calls", ok)

-- Texture upload / readback / update
do
    local data = string.rep("\255\0\0\255", 4)                 -- 2x2 red
    local id = r.rlLoadTexture(data, 2, 2, RGBA, 1)
    T.assert_true("rlLoadTexture returns an id", id > 0)
    T.assert_eq("texture round trip", r.rlReadTexturePixels(id, 2, 2, RGBA), data)
    local green = string.rep("\0\255\0\255", 4)
    r.rlUpdateTexture(id, 0, 0, 2, 2, RGBA, green)
    T.assert_eq("rlUpdateTexture", r.rlReadTexturePixels(id, 2, 2, RGBA), green)
    r.rlUnloadTexture(id)
end

-- Mipmaps
do
    local id = r.rlLoadTexture(string.rep("\255\255\255\255", 16), 4, 4, RGBA, 1)
    T.assert_true("rlGenTextureMipmaps count", r.rlGenTextureMipmaps(id, 4, 4, RGBA) >= 2)
    r.rlUnloadTexture(id)
end

-- Cubemap needs six faces of data
do
    local face = string.rep("\0\0\255\255", 4)
    local id = r.rlLoadTextureCubemap(string.rep(face, 6), 2, RGBA, 1)
    T.assert_true("rlLoadTextureCubemap", id > 0)
    r.rlUnloadTexture(id)
end

-- Framebuffer with a color attachment
do
    local tex = r.rlLoadTexture(nil, 8, 8, RGBA, 1)
    local fbo = r.rlLoadFramebuffer()
    r.rlFramebufferAttach(fbo, tex, r.RL_ATTACHMENT_COLOR_CHANNEL0, r.RL_ATTACHMENT_TEXTURE2D, 0)
    T.assert_true("framebuffer complete", r.rlFramebufferComplete(fbo))
    r.rlUnloadFramebuffer(fbo)
    r.rlUnloadTexture(tex)
end

-- Vertex buffers
do
    local vao = r.rlLoadVertexArray()
    r.rlEnableVertexArray(vao)
    local vbo = r.rlLoadVertexBuffer(string.rep("\0", 48), 48, true)
    T.assert_true("rlLoadVertexBuffer", vbo > 0)
    r.rlUpdateVertexBuffer(vbo, string.rep("\1", 16), 16, 0)
    local ebo = r.rlLoadVertexBufferElement(string.rep("\0", 12), 12, false)
    T.assert_true("rlLoadVertexBufferElement", ebo > 0)
    r.rlSetVertexAttributeDefault(1, {1, 0.5, 0.25, 1}, r.RL_SHADER_ATTRIB_VEC4, 4)
    r.rlDisableVertexArray()
    r.rlUnloadVertexBuffer(vbo)
    r.rlUnloadVertexBuffer(ebo)
    r.rlUnloadVertexArray(vao)
end

-- Shader program and uniforms
do
    local vs = "#version 330\nin vec3 vertexPosition;\nuniform mat4 mvp;\nvoid main(){ gl_Position = mvp*vec4(vertexPosition,1.0); }\n"
    local fs = "#version 330\nout vec4 c;\nuniform vec3 tint;\nuniform float amount;\nvoid main(){ c = vec4(tint*amount, 1.0); }\n"
    local prog = r.rlLoadShaderProgram(vs, fs)
    T.assert_true("rlLoadShaderProgram", prog > 0)
    local tint = r.rlGetLocationUniform(prog, "tint")
    local amount = r.rlGetLocationUniform(prog, "amount")
    local mvp = r.rlGetLocationUniform(prog, "mvp")
    T.assert_true("uniform locations", tint >= 0 and amount >= 0 and mvp >= 0)
    r.rlEnableShader(prog)
    r.rlSetUniform(tint, {1, 0.5, 0.25}, r.RL_SHADER_UNIFORM_VEC3, 1)
    r.rlSetUniform(amount, 0.5, r.RL_SHADER_UNIFORM_FLOAT, 1)
    r.rlSetUniformMatrix(mvp, r.MatrixIdentity())
    r.rlSetUniformMatrices(mvp, {r.MatrixIdentity()})
    r.rlDisableShader()
    r.rlUnloadShaderProgram(prog)
end

-- Render batches: <close>, activation, and unloading the active batch
do
    local batch <close> = r.rlLoadRenderBatch(1, 256)
    r.rlSetRenderBatchActive(batch)
    r.rlSetRenderBatchActive(nil)
    r.rlSetRenderBatchActive(batch)
    r.rlUnloadRenderBatch(batch)                 -- unloading the active batch deactivates it first
    T.assert_false("unloaded batch cannot be drawn", (pcall(r.rlDrawRenderBatch, batch)))
    r.rlUnloadRenderBatch(batch)                 -- second unload is a no-op
end
r.BeginDrawing()
r.ClearBackground(r.RAYWHITE)
r.rlBegin(r.RL_QUADS); r.rlVertex2f(0, 0); r.rlVertex2f(0, 8); r.rlVertex2f(8, 8); r.rlVertex2f(8, 0); r.rlEnd()
r.EndDrawing()                                   -- default batch still works afterwards

-- State toggles do not raise
T.assert_true("state toggles", pcall(function()
    r.rlEnableDepthTest(); r.rlDisableDepthTest()
    r.rlEnableBackfaceCulling(); r.rlDisableBackfaceCulling()
    r.rlEnableScissorTest(); r.rlScissor(0, 0, 8, 8); r.rlDisableScissorTest()
    r.rlSetBlendMode(r.RL_BLEND_ALPHA); r.rlSetLineWidth(2); r.rlSetPointSize(3)
    r.rlColorMask(true, true, true, true)
    assert(r.rlGetLineWidth() > 0)
end))

r.CloseWindow()
