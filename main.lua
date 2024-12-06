local raylib = require("raylib")

raylib.InitWindow(1280, 720, "Lua Raylib Example")

while not raylib.WindowShouldClose() do
    raylib.BeginDrawing()
    raylib.ClearBackground(0xFFFFFFFF) -- White background
    raylib.DrawRectangle(200, 200, 400, 200, 0xFF0000FF) -- Red rectangle
    raylib.EndDrawing()
end

raylib.CloseWindow()
