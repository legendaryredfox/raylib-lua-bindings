local raylib = require("raylib")

-- Raylib Lua Example - Basic window
local RAYWHITE = raylib.ColorToInt({r = 245, g = 245, b = 245, a = 255})-- Initialization
local BLACK = {r = 0, g = 0, b = 0, a = 255}
----------------------------------------------------------------------------------------
local screenWidth = 800
local screenHeight = 450

raylib.InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window")

raylib.SetTargetFPS(60)  -- Set our game to run at 60 frames-per-second
----------------------------------------------------------------------------------------

-- EXAMPLE_FRAMES=N exits after N frames (used for automated runs)
local max_frames = tonumber(os.getenv("EXAMPLE_FRAMES"))
local frame = 0

-- Main game loop
while not raylib.WindowShouldClose() do  -- Detect window close button or ESC key
    -- Update

    raylib.BeginDrawing()
    raylib.ClearBackground(RAYWHITE)
    raylib.DrawText("Hello Raylib + Lua!", 100, 150, 20, BLACK)
    raylib.EndDrawing()
    ------------------------------------------------------------------------------------
    frame = frame + 1
    if max_frames and frame >= max_frames then break end
end

-- De-Initialization
----------------------------------------------------------------------------------------
raylib.CloseWindow()  -- Close window and OpenGL context
----------------------------------------------------------------------------------------
