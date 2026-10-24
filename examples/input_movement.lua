-- Keyboard / mouse input with key constants and raymath vectors.
-- Move with WASD or the arrow keys; click to teleport the ball to the cursor.
-- EXAMPLE_FRAMES=N exits after N frames (used for automated runs).
local raylib = require("raylib")

local WIDTH, HEIGHT, RADIUS, SPEED = 800, 450, 24, 260

raylib.InitWindow(WIDTH, HEIGHT, "raylib [core] example - input and movement")
raylib.SetTargetFPS(60)

local pos = {x = WIDTH / 2, y = HEIGHT / 2}
local max_frames = tonumber(os.getenv("EXAMPLE_FRAMES"))
local frame = 0

while not raylib.WindowShouldClose() do
    local dir = raylib.Vector2Zero()
    if raylib.IsKeyDown(raylib.KEY_D) or raylib.IsKeyDown(raylib.KEY_RIGHT) then dir.x = dir.x + 1 end
    if raylib.IsKeyDown(raylib.KEY_A) or raylib.IsKeyDown(raylib.KEY_LEFT)  then dir.x = dir.x - 1 end
    if raylib.IsKeyDown(raylib.KEY_S) or raylib.IsKeyDown(raylib.KEY_DOWN)  then dir.y = dir.y + 1 end
    if raylib.IsKeyDown(raylib.KEY_W) or raylib.IsKeyDown(raylib.KEY_UP)    then dir.y = dir.y - 1 end

    -- Normalize so diagonal movement is not faster
    pos = raylib.Vector2Add(pos, raylib.Vector2Scale(raylib.Vector2Normalize(dir), SPEED * raylib.GetFrameTime()))
    pos.x = raylib.Clamp(pos.x, RADIUS, WIDTH - RADIUS)
    pos.y = raylib.Clamp(pos.y, RADIUS, HEIGHT - RADIUS)

    if raylib.IsMouseButtonPressed(raylib.MOUSE_BUTTON_LEFT) then
        pos = raylib.GetMousePosition()
    end

    raylib.BeginDrawing()
    raylib.ClearBackground(raylib.RAYWHITE)
    raylib.DrawCircleV(pos, RADIUS, raylib.MAROON)
    raylib.DrawCircleLinesEx(pos, RADIUS + 6, 2, raylib.DARKGRAY)
    raylib.DrawText("WASD / arrows to move, left click to teleport", 10, 10, 20, raylib.DARKGRAY)
    raylib.EndDrawing()

    frame = frame + 1
    if max_frames and frame >= max_frames then break end
end

raylib.CloseWindow()
