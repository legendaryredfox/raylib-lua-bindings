-- 3D camera: orbit a cube with the mouse wheel / arrow keys.
-- EXAMPLE_FRAMES=N exits after N frames (used for automated runs).
local raylib = require("raylib")

raylib.InitWindow(800, 450, "raylib [models] example - 3D camera")
raylib.SetTargetFPS(60)

local camera = raylib.CreateCamera3D(
    {x = 8, y = 6, z = 8},   -- position
    {x = 0, y = 1, z = 0},   -- target
    {x = 0, y = 1, z = 0},   -- up
    45, raylib.CAMERA_PERSPECTIVE)

local max_frames = tonumber(os.getenv("EXAMPLE_FRAMES"))
local frame = 0

while not raylib.WindowShouldClose() do
    raylib.UpdateCamera(camera, raylib.CAMERA_ORBITAL)

    raylib.BeginDrawing()
    raylib.ClearBackground(raylib.RAYWHITE)

    raylib.BeginMode3D(camera)
    raylib.DrawCube({x = 0, y = 1, z = 0}, 2, 2, 2, raylib.RED)
    raylib.DrawCubeWires({x = 0, y = 1, z = 0}, 2, 2, 2, raylib.MAROON)
    raylib.DrawSphere({x = 4, y = 1, z = 0}, 1, raylib.BLUE)
    raylib.DrawGrid(20, 1)
    raylib.EndMode3D()

    raylib.DrawText("Orbital camera (CAMERA_ORBITAL)", 10, 10, 20, raylib.DARKGRAY)
    raylib.DrawFPS(10, 40)
    raylib.EndDrawing()

    frame = frame + 1
    if max_frames and frame >= max_frames then break end
end

raylib.CloseWindow()
