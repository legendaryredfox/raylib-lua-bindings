-- Audio handler validation tests (no audio device required: every case is
-- rejected before raylib is called)
local T = ...
local r = T.raylib

local function rejects(desc, fn, ...)
    local ok, err = pcall(fn, ...)
    T.assert_false(desc .. " fails", ok)
    return tostring(err)
end

local err = rejects("AttachAudioMixedProcessor(C function)", r.AttachAudioMixedProcessor, print)
T.assert_true("C function error message", err:find("must be a Lua function", 1, true) ~= nil)

local captured = 0
err = rejects("AttachAudioMixedProcessor(closure)", r.AttachAudioMixedProcessor,
    function(buf) captured = captured + 1 end)
T.assert_true("closure error names the captured local", err:find("'captured'", 1, true) ~= nil)

rejects("AttachAudioMixedProcessor(non-function)", r.AttachAudioMixedProcessor, 42)

-- Detaching something never attached is a no-op
T.assert_true("DetachAudioMixedProcessor(unknown) is a no-op",
    pcall(r.DetachAudioMixedProcessor, function() end))
