-- Fragment shader compiled from a Lua string, with a time uniform.
-- EXAMPLE_FRAMES=N exits after N frames (used for automated runs).
local raylib = require("raylib")

raylib.InitWindow(800, 450, "raylib [shaders] example - animated fragment shader")
raylib.SetTargetFPS(60)

local fragment = [[
#version 330
in vec2 fragTexCoord;
out vec4 finalColor;
uniform float time;
void main() {
    vec2 p = fragTexCoord * 8.0;
    float v = sin(p.x + time) + sin(p.y + time * 1.3) + sin((p.x + p.y) * 0.5 + time * 0.7);
    finalColor = vec4(0.5 + 0.5 * sin(v + vec3(0.0, 2.0, 4.0)), 1.0);
}
]]

local shader = raylib.LoadShaderFromMemory(nil, fragment)
assert(raylib.IsShaderValid(shader), "shader failed to compile (see log above)")
local time_loc = raylib.GetShaderLocation(shader, "time")

local max_frames = tonumber(os.getenv("EXAMPLE_FRAMES"))
local frame = 0

while not raylib.WindowShouldClose() do
    raylib.SetShaderValue(shader, time_loc, raylib.GetTime(), raylib.SHADER_UNIFORM_FLOAT)

    raylib.BeginDrawing()
    raylib.ClearBackground(raylib.RAYWHITE)
    raylib.BeginShaderMode(shader)
    raylib.DrawRectangle(0, 0, 800, 450, raylib.WHITE)   -- the shader colours this rectangle
    raylib.EndShaderMode()
    raylib.DrawText("Fragment shader loaded with LoadShaderFromMemory", 10, 10, 20, raylib.WHITE)
    raylib.EndDrawing()

    frame = frame + 1
    if max_frames and frame >= max_frames then break end
end

raylib.UnloadShader(shader)
raylib.CloseWindow()
