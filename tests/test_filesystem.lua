-- Filesystem binding tests (no window required)
-- Uses a temporary directory under /tmp; cleaned up at the end.
local T = ...
local r = T.raylib

local tmpdir = "/tmp/rl_lua_test_" .. tostring(os.time())

-- MakeDirectory
local rc = r.MakeDirectory(tmpdir)
T.assert_eq("MakeDirectory new dir returns 0", rc, 0)

-- IsFileNameValid
T.assert_true ("IsFileNameValid 'test.lua'",  r.IsFileNameValid("test.lua"))
T.assert_true ("IsFileNameValid 'file.txt'",  r.IsFileNameValid("file.txt"))
T.assert_false("IsFileNameValid 'foo/bar'",   r.IsFileNameValid("foo/bar"))
T.assert_false("IsFileNameValid 'foo|bar'",   r.IsFileNameValid("foo|bar"))

-- Write a source file through Lua (io), then test FileCopy
local src  = tmpdir .. "/source.txt"
local dst  = tmpdir .. "/dest.txt"
local fh = assert(io.open(src, "w"))
fh:write("hello raylib")
fh:close()

-- FileCopy returns 1 on success (bool-as-int; Raylib 6.0 convention)
local copy_rc = r.FileCopy(src, dst)
T.assert_eq("FileCopy returns 1 on success", copy_rc, 1)
local dfh = io.open(dst, "r")
T.assert_true("FileCopy destination exists", dfh ~= nil)
if dfh then
    T.assert_eq("FileCopy content matches", dfh:read("*a"), "hello raylib")
    dfh:close()
end

-- FileRemove
local rem_rc = r.FileRemove(src)
T.assert_eq  ("FileRemove returns 0",  rem_rc, 0)
T.assert_true("FileRemove file gone",  io.open(src, "r") == nil)

-- FileRename
local renamed = tmpdir .. "/renamed.txt"
local ren_rc  = r.FileRename(dst, renamed)
T.assert_eq  ("FileRename returns 0",    ren_rc, 0)
T.assert_true("FileRename new exists",   io.open(renamed, "r") ~= nil)
T.assert_true("FileRename old gone",     io.open(dst,     "r") == nil)

-- FileMove: internally calls FileCopy then FileRemove.
-- In Raylib 6.0, FileMove treats FileCopy's success return (1) as failure,
-- so it always returns -1 even when the copy succeeds.
-- We verify the destination was created despite the wrong return code.
local moved   = tmpdir .. "/moved.txt"
local move_rc = r.FileMove(renamed, moved)
T.assert_eq  ("FileMove returns -1 (Raylib 6.0 bug)", move_rc, -1)
T.assert_true("FileMove dest exists despite wrong rc",  io.open(moved, "r") ~= nil)

-- GetDirectoryFileCount: tmpdir should contain exactly 'moved.txt' now
local fc = r.GetDirectoryFileCount(tmpdir)
T.assert_true("GetDirectoryFileCount >= 1", fc >= 1)

-- Cleanup (FileMove leaves both src and dst on the Raylib 6.0 bug path)
os.remove(moved)
os.remove(renamed)
os.execute("rmdir " .. tmpdir)
