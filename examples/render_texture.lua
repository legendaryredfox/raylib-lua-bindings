-- Render to a texture, then draw it scaled and rotated.
-- GetRenderTextureTexture exposes the RenderTexture2D's color attachment.
-- EXAMPLE_FRAMES=N exits after N frames (used for automated runs).
local raylib = require("raylib")

raylib.InitWindow(800, 450, "raylib [textures] example - render texture")
raylib.SetTargetFPS(60)

local SIZE = 128
local target = raylib.LoadRenderTexture(SIZE, SIZE)
local texture = raylib.GetRenderTextureTexture(target)   -- shared with `target`; never UnloadTexture it

local max_frames = tonumber(os.getenv("EXAMPLE_FRAMES"))
local frame = 0
local angle = 0

while not raylib.WindowShouldClose() do
    angle = angle + 60 * raylib.GetFrameTime()

    -- Draw into the render texture
    raylib.BeginTextureMode(target)
    raylib.ClearBackground(raylib.SKYBLUE)
    raylib.DrawCircleGradient({x = SIZE / 2, y = SIZE / 2}, 48, raylib.WHITE, raylib.BLUE)
    raylib.DrawTriangleGradient({x = 64, y = 8}, {x = 24, y = 80}, {x = 104, y = 80}, raylib.RED, raylib.GREEN, raylib.YELLOW)
    raylib.EndTextureMode()

    raylib.BeginDrawing()
    raylib.ClearBackground(raylib.RAYWHITE)
    -- Render textures are stored upside down: a negative source height flips them
    raylib.DrawTextureRec(texture, {x = 0, y = 0, width = SIZE, height = -SIZE}, {x = 40, y = 40}, raylib.WHITE)
    raylib.DrawTexturePro(texture,
        {x = 0, y = 0, width = SIZE, height = -SIZE},
        {x = 520, y = 225, width = SIZE * 2, height = SIZE * 2},
        {x = SIZE, y = SIZE}, angle, raylib.WHITE)
    raylib.DrawText("Rendered once per frame into a 128x128 texture", 10, 420, 20, raylib.DARKGRAY)
    raylib.EndDrawing()

    frame = frame + 1
    if max_frames and frame >= max_frames then break end
end

raylib.UnloadRenderTexture(target)
raylib.CloseWindow()
