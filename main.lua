local raylib = require("raylib")

raylib.InitWindow(1280, 720, "Lua Raylib Audio Processing Example")
raylib.InitAudioDevice()

local stream = raylib.LoadAudioStream(44100, 16, 2) -- 44.1kHz, 16-bit, stereo

-- Define a simple audio processor function
local function audioProcessor(samples)
    for i = 1, #samples do
        samples[i] = -samples[i]
    end
    return samples
end

raylib.AttachAudioStreamProcessor(stream, audioProcessor)

raylib.PlayAudioStream(stream)

-- Main loop
while not raylib.WindowShouldClose() do
    local dummyData = string.rep("\0", 44100 * 2 * 2) -- 1 second of silence
    raylib.UpdateAudioStream(stream, dummyData, 44100)

    raylib.BeginDrawing()
    raylib.ClearBackground(0xFFFFFFFF)
    raylib.DrawText("Playing audio stream with processor", 200, 200, 20, 0xFF0000FF)
    raylib.EndDrawing()
end

raylib.UnloadAudioStream(stream)
raylib.CloseAudioDevice()
raylib.CloseWindow()
