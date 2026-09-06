-- Memory-safety and robustness tests (no window required).
-- These exercise the hardened array readers, zero-on-unload, the Base64
-- round-trip, and error paths that previously leaked or crashed.
local T = ...
local r = T.raylib

-- ---------------------------------------------------------------------------
-- Array readers: valid input works, bad input raises instead of crashing.
-- Reaching the assertions at all proves the process did not crash on the
-- error path (a crash would abort the whole test runner).
-- ---------------------------------------------------------------------------

-- CheckCollisionPointPoly reads a Lua array of Vector2 via the hardened reader.
local square = { {x=0,y=0}, {x=10,y=0}, {x=10,y=10}, {x=0,y=10} }
T.assert_true("point inside polygon",  r.CheckCollisionPointPoly({x=5,y=5},  square))
T.assert_false("point outside polygon", r.CheckCollisionPointPoly({x=99,y=99}, square))

-- Bad element mid-array must raise a Lua error (not crash / not leak).
local ok_bad = pcall(r.CheckCollisionPointPoly, {x=0,y=0},
                     { {x=0,y=0}, {x=1,y=0}, "not a vector" })
T.assert_false("malformed polygon element raises", ok_bad)

-- Empty array must be handled without crashing.
local ok_empty = pcall(r.CheckCollisionPointPoly, {x=0,y=0}, {})
T.assert_true("empty polygon does not crash", ok_empty)

-- ---------------------------------------------------------------------------
-- LoadUTF8: table of codepoints -> string (hardened int-array reader).
-- ---------------------------------------------------------------------------
T.assert_eq("LoadUTF8 encodes codepoints", r.LoadUTF8({72, 105}), "Hi")

local ok_utf8 = pcall(r.LoadUTF8, {72, {}, 105})
T.assert_false("LoadUTF8 rejects non-integer element", ok_utf8)

-- ---------------------------------------------------------------------------
-- Base64 round-trip (DecodeDataBase64 signedness fix, raylib 6.0 signature).
-- ---------------------------------------------------------------------------
local original = "raylib-lua safety \0 binary"     -- embedded NUL on purpose
local encoded  = r.EncodeDataBase64(original)
T.assert_true("EncodeDataBase64 returns a string", type(encoded) == "string")
T.assert_eq("Base64 round-trips binary data", r.DecodeDataBase64(encoded), original)

-- ---------------------------------------------------------------------------
-- Zero-on-unload: using a resource after Unload* must be a safe no-op, not a
-- use-after-free. GenImageColor is CPU-side, so no window is required.
-- ---------------------------------------------------------------------------
local img = r.GenImageColor(4, 4, {r=255, g=0, b=0, a=255})
T.assert_true("GenImageColor produces a valid image", r.IsImageValid(img))
r.UnloadImage(img)
T.assert_false("image is invalid (not UAF) after UnloadImage", r.IsImageValid(img))

-- Double unload must not crash (struct already zeroed).
local ok_double = pcall(r.UnloadImage, img)
T.assert_true("double UnloadImage is safe", ok_double)
