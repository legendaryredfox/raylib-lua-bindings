-- Image / userdata binding tests (no window required).
--
-- These exercise the userdata fixes:
--   * named metatables are registered, so luaL_checkudata accepts objects;
--   * every Image-returning function yields an Image *userdata* (the GenImage*
--     / LoadImage*FromMemory family previously returned a plain table that no
--     other function would accept);
--   * distinct types carry distinct metatables, so a mismatched object is
--     rejected rather than silently reinterpreted.
--
-- CPU-side image generation/inspection needs no GL context, so all of this
-- runs without InitWindow.
local T = ...
local r = T.raylib

local RED = {r = 255, g = 0, b = 0, a = 255}

-- GenImageColor must return an Image userdata (was a plain table before).
local img = r.GenImageColor(4, 3, RED)
T.assert_eq  ("GenImageColor returns userdata", type(img), "userdata")
T.assert_true("GenImageColor produces a valid image", r.IsImageValid(img))

-- Pixels read back through the same userdata.
local c = r.GetImageColor(img, 0, 0)
T.assert_eq("GetImageColor r", c.r, 255)
T.assert_eq("GetImageColor g", c.g, 0)
T.assert_eq("GetImageColor b", c.b, 0)
T.assert_eq("GetImageColor a", c.a, 255)

-- ImageCopy accepts the userdata and returns an independent Image userdata.
local copy = r.ImageCopy(img)
T.assert_eq  ("ImageCopy returns userdata", type(copy), "userdata")
T.assert_true("ImageCopy is valid", r.IsImageValid(copy))

-- In-place mutation affects only the copy. Inverting red (255,0,0) yields
-- cyan (0,255,255); alpha is left untouched by ImageColorInvert.
r.ImageColorInvert(copy)
local ic = r.GetImageColor(copy, 0, 0)
T.assert_eq("inverted copy r", ic.r, 0)
T.assert_eq("inverted copy g", ic.g, 255)
T.assert_eq("inverted copy b", ic.b, 255)
local oc = r.GetImageColor(img, 0, 0)
T.assert_eq("original image untouched after copy invert", oc.r, 255)

-- A second generator (different code path) also returns a usable userdata.
local checked = r.GenImageChecked(8, 8, 2, 2, RED, {r=0, g=0, b=0, a=255})
T.assert_eq  ("GenImageChecked returns userdata", type(checked), "userdata")
T.assert_true("GenImageChecked is valid", r.IsImageValid(checked))

-- Distinct type tags: an Image must be rejected where a Wave is expected,
-- proving the metatables are registered AND distinct (not a shared/nil one).
T.assert_false("Image rejected where Wave expected", (pcall(r.IsWaveValid, img)))

-- Unloading via the matching Unload* accepts the userdata without error.
T.assert_true("UnloadImage accepts copy",     (pcall(r.UnloadImage, copy)))
T.assert_true("UnloadImage accepts checked",  (pcall(r.UnloadImage, checked)))
T.assert_true("UnloadImage accepts original", (pcall(r.UnloadImage, img)))
