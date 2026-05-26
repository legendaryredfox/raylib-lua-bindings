-- Run from the repo root:
--   LUA_CPATH="./?.so" lua tests/runner.lua
-- Or via:
--   make test

local raylib = require("raylib")

local passed = 0
local failed = 0
local errors = {}

local function assert_eq(desc, got, expected)
    if got == expected then
        passed = passed + 1
    else
        failed = failed + 1
        table.insert(errors, string.format(
            "FAIL [%s]\n  expected: %s\n  got:      %s",
            desc, tostring(expected), tostring(got)))
    end
end

local function assert_true(desc, v)
    assert_eq(desc, v, true)
end

local function assert_false(desc, v)
    assert_eq(desc, v, false)
end

local function assert_approx(desc, got, expected, tol)
    tol = tol or 1e-4
    assert_true(
        string.format("%s (%.6g ≈ %.6g, tol %.6g)", desc, got, expected, tol),
        math.abs(got - expected) <= tol)
end

local T = {
    raylib       = raylib,
    assert_eq    = assert_eq,
    assert_true  = assert_true,
    assert_false = assert_false,
    assert_approx = assert_approx,
}

local suite_files = {
    "tests/test_text.lua",
    "tests/test_hashing.lua",
    "tests/test_color.lua",
    "tests/test_filesystem.lua",
}

for _, path in ipairs(suite_files) do
    local chunk, load_err = loadfile(path)
    if not chunk then
        failed = failed + 1
        table.insert(errors, "LOAD ERROR " .. path .. ": " .. tostring(load_err))
    else
        local ok, run_err = pcall(chunk, T)
        if not ok then
            failed = failed + 1
            table.insert(errors, "RUNTIME ERROR " .. path .. ": " .. tostring(run_err))
        end
    end
end

io.write(string.format("\n=== %d passed, %d failed ===\n", passed, failed))
for _, msg in ipairs(errors) do
    io.write(msg .. "\n")
end

os.exit(failed == 0 and 0 or 1)
