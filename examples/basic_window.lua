local raylib = require("raylib")
-- Raylib Lua Example - Basic window

-- Initialization
----------------------------------------------------------------------------------------
local screenWidth = 800
local screenHeight = 450

raylib.InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window")

raylib.SetTargetFPS(60)  -- Set our game to run at 60 frames-per-second
----------------------------------------------------------------------------------------

-- Main game loop
while not raylib.WindowShouldClose() do  -- Detect window close button or ESC key
    -- Update

    raylib.BeginDrawing()

    raylib.ClearBackground(0xFFFFFFFF)
    local text = "Hello Raylib + Lua!"
    local posX = 100
    local posY = 150
    local fontSize = 20
    local color = {r = 0, g = 0, b = 0, a = 100} -- Gray
    
    raylib.DrawText(text, posX, posY, fontSize, color)
    raylib.EndDrawing()
    ------------------------------------------------------------------------------------
end

-- De-Initialization
----------------------------------------------------------------------------------------
raylib.CloseWindow()  -- Close window and OpenGL context
----------------------------------------------------------------------------------------
