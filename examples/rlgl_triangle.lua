-- Immediate-mode drawing with rlgl: a gradient triangle and a spinning quad built
-- from rlBegin/rlVertex2f/rlColor4ub under the matrix stack.
-- EXAMPLE_FRAMES=N exits after N frames (used for automated runs).
local raylib = require("raylib")

raylib.InitWindow(800, 450, "raylib [rlgl] example - immediate mode")
raylib.SetTargetFPS(60)

local max_frames = tonumber(os.getenv("EXAMPLE_FRAMES"))
local frame = 0
local angle = 0

while not raylib.WindowShouldClose() do
    angle = angle + 90 * raylib.GetFrameTime()

    raylib.BeginDrawing()
    raylib.ClearBackground(raylib.RAYWHITE)

    -- Gradient triangle (counter-clockwise, in screen pixels)
    raylib.rlBegin(raylib.RL_TRIANGLES)
    raylib.rlColor4ub(255, 0, 0, 255);  raylib.rlVertex2f(200, 80)
    raylib.rlColor4ub(0, 255, 0, 255);  raylib.rlVertex2f(100, 300)
    raylib.rlColor4ub(0, 0, 255, 255);  raylib.rlVertex2f(300, 300)
    raylib.rlEnd()

    -- Spinning quad around its center, using the matrix stack
    raylib.rlPushMatrix()
    raylib.rlTranslatef(580, 190, 0)
    raylib.rlRotatef(angle, 0, 0, 1)
    raylib.rlBegin(raylib.RL_QUADS)
    raylib.rlColor4ub(255, 161, 0, 255)
    raylib.rlVertex2f(-70, -70)
    raylib.rlVertex2f(-70, 70)
    raylib.rlColor4ub(255, 109, 194, 255)
    raylib.rlVertex2f(70, 70)
    raylib.rlVertex2f(70, -70)
    raylib.rlEnd()
    raylib.rlPopMatrix()

    raylib.DrawText("rlgl immediate mode", 10, 10, 20, raylib.DARKGRAY)
    raylib.EndDrawing()

    frame = frame + 1
    if max_frames and frame >= max_frames then break end
end

raylib.CloseWindow()
