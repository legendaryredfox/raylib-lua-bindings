-- Color utility binding tests (no window required)
local T = ...
local r = T.raylib

-- ColorToInt: packs {r,g,b,a} as (r<<24)|(g<<16)|(b<<8)|a, returned as signed int
T.assert_eq("ColorToInt all zeros",    r.ColorToInt({r=0, g=0, b=0, a=0}),   0)
T.assert_eq("ColorToInt alpha only",   r.ColorToInt({r=0, g=0, b=0, a=255}), 255)
T.assert_eq("ColorToInt 1,2,3,4",      r.ColorToInt({r=1, g=2, b=3, a=4}),   16909060)  -- 0x01020304

-- ColorNormalize: maps channel [0,255] -> [0.0,1.0]
local norm = r.ColorNormalize({r=255, g=128, b=0, a=255})
T.assert_approx("ColorNormalize x (255->1.0)",  norm.x, 1.0,   0.001)
T.assert_approx("ColorNormalize y (128->0.502)", norm.y, 0.502, 0.002)
T.assert_approx("ColorNormalize z (0->0.0)",    norm.z, 0.0,   0.001)
T.assert_approx("ColorNormalize w (255->1.0)",  norm.w, 1.0,   0.001)

-- ColorFromNormalized: maps [0.0,1.0] -> channel [0,255]
local c = r.ColorFromNormalized({x=1.0, y=0.0, z=0.0, w=1.0})
T.assert_eq("ColorFromNormalized r", c.r, 255)
T.assert_eq("ColorFromNormalized g", c.g, 0)
T.assert_eq("ColorFromNormalized b", c.b, 0)
T.assert_eq("ColorFromNormalized a", c.a, 255)

-- ColorNormalize -> ColorFromNormalized round-trip (±1 rounding tolerance)
local orig = {r=80, g=160, b=240, a=255}
local n2   = r.ColorNormalize(orig)
local back = r.ColorFromNormalized(n2)
T.assert_true("ColorNormalize round-trip r", math.abs(back.r - orig.r) <= 1)
T.assert_true("ColorNormalize round-trip g", math.abs(back.g - orig.g) <= 1)
T.assert_true("ColorNormalize round-trip b", math.abs(back.b - orig.b) <= 1)

-- ColorToHSV: pure red = hue 0, saturation 1, value 1
local hsv = r.ColorToHSV({r=255, g=0, b=0, a=255})
T.assert_approx("ColorToHSV red hue",        hsv.x, 0.0, 0.001)
T.assert_approx("ColorToHSV red saturation", hsv.y, 1.0, 0.001)
T.assert_approx("ColorToHSV red value",      hsv.z, 1.0, 0.001)

-- ColorFromHSV: hue 0, sat 1, val 1 => pure red
local fromHSV = r.ColorFromHSV(0.0, 1.0, 1.0)
T.assert_eq("ColorFromHSV r", fromHSV.r, 255)
T.assert_eq("ColorFromHSV g", fromHSV.g, 0)
T.assert_eq("ColorFromHSV b", fromHSV.b, 0)
T.assert_eq("ColorFromHSV a", fromHSV.a, 255)

-- ColorToHSV -> ColorFromHSV round-trip (green)
local hsvG  = r.ColorToHSV({r=0, g=255, b=0, a=255})
local green = r.ColorFromHSV(hsvG.x, hsvG.y, hsvG.z)
T.assert_eq  ("HSV round-trip g",   green.g, 255)
T.assert_true("HSV round-trip r~0", green.r <= 1)
T.assert_true("HSV round-trip b~0", green.b <= 1)

-- ColorTint: white tinted with red => red
local tinted = r.ColorTint({r=255, g=255, b=255, a=255}, {r=255, g=0, b=0, a=255})
T.assert_eq("ColorTint white+red => r=255", tinted.r, 255)
T.assert_eq("ColorTint white+red => g=0",   tinted.g, 0)
T.assert_eq("ColorTint white+red => b=0",   tinted.b, 0)

-- ColorAlpha: sets alpha to (int)(255 * factor), rgb unchanged
-- The original alpha is replaced, not scaled.
local half = r.ColorAlpha({r=200, g=100, b=50, a=255}, 0.5)
T.assert_eq  ("ColorAlpha r unchanged",      half.r, 200)
T.assert_eq  ("ColorAlpha g unchanged",      half.g, 100)
T.assert_eq  ("ColorAlpha b unchanged",      half.b, 50)
T.assert_true("ColorAlpha 0.5 => a~127",     math.abs(half.a - 127) <= 1)

-- ColorAlpha: factor 0.0 => a=0
local zero = r.ColorAlpha({r=255, g=255, b=255, a=255}, 0.0)
T.assert_eq("ColorAlpha factor 0 => a=0", zero.a, 0)

-- ColorAlpha: factor 1.0 => a=255 (independent of original alpha)
local full = r.ColorAlpha({r=128, g=128, b=128, a=200}, 1.0)
T.assert_eq("ColorAlpha factor 1 => a=255", full.a, 255)

-- ColorBrightness: factor 0.0 => no change
local bright0 = r.ColorBrightness({r=100, g=100, b=100, a=255}, 0.0)
T.assert_eq("ColorBrightness factor 0 r", bright0.r, 100)
T.assert_eq("ColorBrightness factor 0 g", bright0.g, 100)
T.assert_eq("ColorBrightness factor 0 b", bright0.b, 100)

-- ColorBrightness: factor 1.0 => clamps to white
local bright1 = r.ColorBrightness({r=100, g=100, b=100, a=255}, 1.0)
T.assert_eq("ColorBrightness factor 1 r=255", bright1.r, 255)
T.assert_eq("ColorBrightness factor 1 g=255", bright1.g, 255)
T.assert_eq("ColorBrightness factor 1 b=255", bright1.b, 255)

-- GetRandomValue: always in [min, max]
for _ = 1, 20 do
    local v = r.GetRandomValue(0, 100)
    T.assert_true("GetRandomValue in [0,100]", v >= 0 and v <= 100)
end
T.assert_true("GetRandomValue exact range [5,5]", r.GetRandomValue(5, 5) == 5)
