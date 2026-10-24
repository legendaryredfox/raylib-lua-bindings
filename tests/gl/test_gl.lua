-- Windowed checks (need a GL context): run with `make test-gl` (uses xvfb-run).
local T = ...
local r = T.raylib

r.SetTraceLogLevel(r.LOG_WARNING)
r.InitWindow(64, 64, "gl tests")

-- RenderTexture: draw into it, read the pixels back through GetRenderTextureTexture
do
    local rt <close> = r.LoadRenderTexture(16, 16)
    r.BeginTextureMode(rt)
    r.ClearBackground({r = 230, g = 41, b = 55, a = 255})
    r.EndTextureMode()
    local tex = r.GetRenderTextureTexture(rt)
    T.assert_eq("GetRenderTextureTexture is Texture2D", type(tex), "userdata")
    local img = r.LoadImageFromTexture(tex)
    local c = r.GetImageColor(img, 8, 8)
    T.assert_eq("render texture red", c.r, 230)
    T.assert_eq("render texture green", c.g, 41)
    r.UnloadImage(img)
end

-- LoadRenderTextureEx accepts a pixel format
do
    local rt <close> = r.LoadRenderTextureEx(8, 8, r.PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)
    T.assert_true("LoadRenderTextureEx valid", r.IsRenderTextureValid(rt))
end

-- Draw*Ex variants run without error inside a frame
local ok = pcall(function()
    r.BeginDrawing()
    r.ClearBackground(r.RAYWHITE)
    r.DrawCircleLinesEx({x = 32, y = 32}, 10, 2, r.RED)
    r.DrawCircleSectorLinesEx({x = 32, y = 32}, 10, 0, 90, 8, 2, r.RED)
    r.DrawEllipseLinesEx({x = 32, y = 32}, 10, 5, 2, r.RED)
    r.DrawRingLinesEx({x = 32, y = 32}, 5, 10, 0, 180, 8, 2, r.RED)
    r.DrawTriangleGradient({x = 0, y = 0}, {x = 0, y = 10}, {x = 10, y = 10}, r.RED, r.GREEN, r.BLUE)
    r.DrawTriangleLinesEx({x = 0, y = 0}, {x = 0, y = 10}, {x = 10, y = 10}, 2, r.RED)
    r.EndDrawing()
end)
T.assert_true("Draw*Ex variants run", ok)

-- Shader compile + <close>
do
    local fs = "#version 330\nout vec4 c;\nvoid main(){ c = vec4(1.0); }\n"
    local sh <close> = r.LoadShaderFromMemory(nil, fs)
    T.assert_true("shader compiles", r.IsShaderValid(sh))
end

-- Image from screen / texture from image with <close>
do
    local img <close> = r.GenImageChecked(8, 8, 2, 2, r.BLACK, r.WHITE)
    local tex <close> = r.LoadTextureFromImage(img)
    T.assert_true("texture valid", r.IsTextureValid(tex))
end

r.CloseWindow()
