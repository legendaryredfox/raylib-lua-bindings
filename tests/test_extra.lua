-- Tests for the window-free bindings added in lua_raylib_extra.c
-- (text parsing, path utilities, file/data I/O, compression, base64, random).
local T = ...
local r = T.raylib

-- ---------------------------------------------------------------------------
-- Text parsing helpers
-- ---------------------------------------------------------------------------
T.assert_eq("TextToInteger '42'",     r.TextToInteger("42"), 42)
T.assert_eq("TextToInteger '-7'",     r.TextToInteger("-7"), -7)
T.assert_eq("TextToInteger '0'",      r.TextToInteger("0"), 0)
T.assert_approx("TextToFloat '3.5'",  r.TextToFloat("3.5"), 3.5)
T.assert_approx("TextToFloat '-2.25'",r.TextToFloat("-2.25"), -2.25)

-- ---------------------------------------------------------------------------
-- Path string utilities (pure string ops, no filesystem access)
-- ---------------------------------------------------------------------------
T.assert_eq("GetFileExtension",       r.GetFileExtension("a/b/c.png"), ".png")
T.assert_eq("GetFileName",            r.GetFileName("a/b/c.png"), "c.png")
T.assert_eq("GetFileNameWithoutExt",  r.GetFileNameWithoutExt("a/b/c.png"), "c")
T.assert_true("GetDirectoryPath ends b",
    r.GetDirectoryPath("a/b/c.png"):sub(-1) == "b")
T.assert_true("IsFileExtension true",  r.IsFileExtension("hello.PNG", ".png"))
T.assert_false("IsFileExtension false", r.IsFileExtension("hello.txt", ".png"))

-- ---------------------------------------------------------------------------
-- Working directory: query + ChangeDirectory round-trip
-- ---------------------------------------------------------------------------
local cwd = r.GetWorkingDirectory()
T.assert_true("GetWorkingDirectory non-empty", type(cwd) == "string" and #cwd > 0)
T.assert_true("GetApplicationDirectory non-empty",
    type(r.GetApplicationDirectory()) == "string" and #r.GetApplicationDirectory() > 0)
T.assert_true("ChangeDirectory to /tmp", r.ChangeDirectory("/tmp"))
T.assert_true("ChangeDirectory back", r.ChangeDirectory(cwd))

-- ---------------------------------------------------------------------------
-- File data / text round-trips + existence + length (in a temp dir)
-- ---------------------------------------------------------------------------
local tmpdir = "/tmp/rl_lua_extra_" .. tostring(os.time())
r.ChangeDirectory("/tmp")           -- MakeDirectory is relative-safe here
local _ = os.execute("mkdir -p " .. tmpdir)

local binPath = tmpdir .. "/data.bin"
local binData = "ab\0cd\255ef"       -- 8 bytes, embedded NUL + high byte
T.assert_true("SaveFileData ok", r.SaveFileData(binPath, binData))
T.assert_true("FileExists after save", r.FileExists(binPath))
T.assert_false("FileExists missing", r.FileExists(tmpdir .. "/nope.bin"))
T.assert_true("IsPathFile on file", r.IsPathFile(binPath))
T.assert_false("IsPathFile on dir", r.IsPathFile(tmpdir))
T.assert_true("DirectoryExists", r.DirectoryExists(tmpdir))
T.assert_eq("GetFileLength", r.GetFileLength(binPath), #binData)
T.assert_eq("LoadFileData round-trip", r.LoadFileData(binPath), binData)
-- UnloadFileData is a safe no-op (data already owned by Lua as a string)
r.UnloadFileData(binData)

local txtPath = tmpdir .. "/data.txt"
local txtData = "line1\nline2\n"
T.assert_true("SaveFileText ok", r.SaveFileText(txtPath, txtData))
T.assert_eq("LoadFileText round-trip", r.LoadFileText(txtPath), txtData)
r.UnloadFileText(txtData)            -- safe no-op

-- ---------------------------------------------------------------------------
-- Compression round-trip
-- ---------------------------------------------------------------------------
local original = string.rep("raylib-lua ", 64)
local comp = r.CompressData(original)
T.assert_true("CompressData returns string", type(comp) == "string" and #comp > 0)
T.assert_eq("DecompressData round-trip", r.DecompressData(comp), original)

-- ---------------------------------------------------------------------------
-- Base64: known vector + round-trip with binary
-- ---------------------------------------------------------------------------
T.assert_eq("EncodeDataBase64 'Man'", r.EncodeDataBase64("Man"), "TWFu")
local raw = "\0\1\2\3\255\254"
T.assert_eq("base64 binary round-trip",
    r.DecodeDataBase64(r.EncodeDataBase64(raw)), raw)

-- ---------------------------------------------------------------------------
-- Random: SetRandomSeed determinism + LoadRandomSequence range/count
-- ---------------------------------------------------------------------------
r.SetRandomSeed(1234)
local a = r.GetRandomValue(1, 1000000)
r.SetRandomSeed(1234)
local b = r.GetRandomValue(1, 1000000)
T.assert_eq("SetRandomSeed determinism", a, b)

local seq = r.LoadRandomSequence(6, 10, 20)
T.assert_eq("LoadRandomSequence count", #seq, 6)
local in_range = true
for i = 1, #seq do
    if type(seq[i]) ~= "number" or seq[i] < 10 or seq[i] > 20 then in_range = false end
end
T.assert_true("LoadRandomSequence values in [10,20]", in_range)
r.UnloadRandomSequence(seq)          -- safe no-op

-- ---------------------------------------------------------------------------
-- Directory listing + ExportDataAsCode (tmpdir still has data.bin & data.txt)
-- ---------------------------------------------------------------------------
local listing = r.LoadDirectoryFiles(tmpdir)
T.assert_true("LoadDirectoryFiles count >= 2", #listing >= 2)
T.assert_true("LoadDirectoryFiles entries are strings", type(listing[1]) == "string")
r.UnloadDirectoryFiles(listing)      -- safe no-op

local codePath = tmpdir .. "/data_code.h"
T.assert_true("ExportDataAsCode", r.ExportDataAsCode("abc", codePath))
T.assert_true("ExportDataAsCode wrote file", r.FileExists(codePath))

-- ---------------------------------------------------------------------------
-- Automation events (window-free: empty list create / count / export / unload)
-- ---------------------------------------------------------------------------
local evlist = r.LoadAutomationEventList()          -- no arg => empty list
T.assert_eq("GetAutomationEventCount empty", r.GetAutomationEventCount(evlist), 0)
r.SetAutomationEventBaseFrame(0)                    -- just exercise the binding
local evPath = tmpdir .. "/events.rae"
T.assert_true("ExportAutomationEventList", r.ExportAutomationEventList(evlist, evPath))
T.assert_true("ExportAutomationEventList wrote file", r.FileExists(evPath))
r.UnloadAutomationEventList(evlist)
os.remove(evPath)

-- ---------------------------------------------------------------------------
-- Cleanup
-- ---------------------------------------------------------------------------
os.remove(codePath)
os.remove(binPath)
os.remove(txtPath)
os.execute("rmdir " .. tmpdir)
r.ChangeDirectory(cwd)               -- restore for any later suites
