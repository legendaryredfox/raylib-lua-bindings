-- Audio streaming demo: generate a 440 Hz tone in Lua and feed it to an
-- AudioStream as 16-bit signed stereo PCM. This exercises UpdateAudioStream
-- with a Lua binary string (the supported way to pass sample data).
--
-- Note: AttachAudioStreamProcessor is intentionally not used here — its callback
-- receives a raw buffer pointer rather than an indexable sample table, so it
-- cannot process audio from pure Lua (see README "Known Issues").
local raylib = require("raylib")

local SAMPLE_RATE = 44100
local CHANNELS    = 2
local FRAMES      = 4096          -- frames generated per buffer refill

raylib.InitWindow(800, 450, "raylib [audio] example - stream a generated tone")
raylib.InitAudioDevice()
raylib.SetTargetFPS(60)

local stream = raylib.LoadAudioStream(SAMPLE_RATE, 16, CHANNELS)
raylib.PlayAudioStream(stream)

local frequency = 440.0          -- A4
local phase     = 0.0
local twoPi     = 2.0 * math.pi
local step      = twoPi * frequency / SAMPLE_RATE

-- Build one buffer of 16-bit signed stereo PCM as a binary string.
local function generateTone()
    local samples = {}
    for i = 1, FRAMES do
        local s = math.floor(math.sin(phase) * 16000)
        phase = phase + step
        if phase >= twoPi then phase = phase - twoPi end
        samples[i] = string.pack("<i2i2", s, s)   -- left, right
    end
    return table.concat(samples)
end

local BLACK    = {r = 0,   g = 0,   b = 0,   a = 255}
local RAYWHITE = {r = 245, g = 245, b = 245, a = 255}

while not raylib.WindowShouldClose() do
    if raylib.IsAudioStreamProcessed(stream) then
        raylib.UpdateAudioStream(stream, generateTone(), FRAMES)
    end

    raylib.BeginDrawing()
    raylib.ClearBackground(RAYWHITE)
    raylib.DrawText("Streaming a 440 Hz tone via UpdateAudioStream", 120, 200, 20, BLACK)
    raylib.DrawText("Close the window to stop.", 120, 240, 20, BLACK)
    raylib.EndDrawing()
end

raylib.UnloadAudioStream(stream)
raylib.CloseAudioDevice()
raylib.CloseWindow()
