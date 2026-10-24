-- `local x <close> = ...` releases raylib resources through the matching Unload*.
local T = ...
local r = T.raylib

-- Image is released when the scope ends
local kept
do
    local img <close> = r.GenImageColor(4, 4, {r = 1, g = 2, b = 3, a = 255})
    T.assert_true("image valid inside scope", r.IsImageValid(img))
    kept = img
end
T.assert_false("image invalid after scope", r.IsImageValid(kept))

-- Released even when the scope is left by an error
local escaped
local ok = pcall(function()
    local img <close> = r.GenImageColor(2, 2, {r = 0, g = 0, b = 0, a = 255})
    escaped = img
    error("boom")
end)
T.assert_false("error propagates", ok)
T.assert_false("image released on error", r.IsImageValid(escaped))

-- Manual Unload before the scope ends is safe (zero-on-unload makes close a no-op)
local ok_double = pcall(function()
    local img <close> = r.GenImageColor(2, 2, {r = 0, g = 0, b = 0, a = 255})
    r.UnloadImage(img)
end)
T.assert_true("close after manual unload is safe", ok_double)

-- Every resource metatable has a __close
for _, name in ipairs({"Image", "Texture2D", "RenderTexture2D", "Model", "Mesh", "Material",
                       "Sound", "Music", "AudioStream", "Wave", "Shader", "Font"}) do
    local mt = debug.getregistry()[name]
    T.assert_eq(name .. " has __close", type(mt and mt.__close), "function")
end
