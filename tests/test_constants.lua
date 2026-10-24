-- Enum constants generated from raylib.h (tools/gen_constants.py).
local T = ...
local r = T.raylib

-- Spot values that must match raylib.h
T.assert_eq("KEY_A", r.KEY_A, 65)
T.assert_eq("KEY_SPACE", r.KEY_SPACE, 32)
T.assert_eq("MOUSE_BUTTON_LEFT", r.MOUSE_BUTTON_LEFT, 0)
T.assert_eq("MOUSE_BUTTON_RIGHT", r.MOUSE_BUTTON_RIGHT, 1)
T.assert_eq("FLAG_VSYNC_HINT", r.FLAG_VSYNC_HINT, 0x00000040)
T.assert_eq("FLAG_WINDOW_RESIZABLE", r.FLAG_WINDOW_RESIZABLE, 0x00000004)
T.assert_eq("PIXELFORMAT_UNCOMPRESSED_R8G8B8A8", r.PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 7)
T.assert_eq("LOG_WARNING", r.LOG_WARNING, 4)
T.assert_eq("BLEND_ALPHA", r.BLEND_ALPHA, 0)

-- #define aliases resolve to the enum value
T.assert_eq("MOUSE_LEFT_BUTTON alias", r.MOUSE_LEFT_BUTTON, r.MOUSE_BUTTON_LEFT)

-- Flags combine with bitwise or
T.assert_eq("flags or", r.FLAG_VSYNC_HINT | r.FLAG_WINDOW_RESIZABLE, 0x44)

-- Math constants
T.assert_approx("PI", r.PI, math.pi, 1e-12)
T.assert_approx("DEG2RAD", r.DEG2RAD * 180, math.pi, 1e-12)
T.assert_approx("RAD2DEG", r.RAD2DEG * math.pi, 180, 1e-12)

-- Version
T.assert_eq("RAYLIB_VERSION_MAJOR", r.RAYLIB_VERSION_MAJOR, 6)
T.assert_eq("RAYLIB_VERSION is string", type(r.RAYLIB_VERSION), "string")
T.assert_eq("RAYLIB_VERSION matches parts",
    r.RAYLIB_VERSION, ("%d.%d"):format(r.RAYLIB_VERSION_MAJOR, r.RAYLIB_VERSION_MINOR))

-- Every UPPER_CASE entry is a number, a string (version), or a color table
local bad = {}
local count = 0
for k, v in pairs(r) do
    if k:match("^[A-Z][A-Z0-9_]*$") then
        local tv = type(v)
        if tv == "number" then count = count + 1
        elseif tv ~= "string" and tv ~= "table" then bad[#bad + 1] = k end
    end
end
T.assert_eq("no non-constant upper-case exports", #bad, 0)
T.assert_true("at least 300 numeric constants", count >= 300)
