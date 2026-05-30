-- Text utility binding tests (no window required)
local T = ...
local r = T.raylib

-- TextLength
T.assert_eq("TextLength empty",   r.TextLength(""), 0)
T.assert_eq("TextLength 'hello'", r.TextLength("hello"), 5)
T.assert_eq("TextLength spaces",  r.TextLength("a b"), 3)

-- TextIsEqual
T.assert_true ("TextIsEqual same strings",    r.TextIsEqual("hello", "hello"))
T.assert_false("TextIsEqual different strings", r.TextIsEqual("hello", "world"))
T.assert_true ("TextIsEqual both empty",      r.TextIsEqual("", ""))
T.assert_false("TextIsEqual empty vs non",    r.TextIsEqual("", "x"))

-- TextToUpper / TextToLower
T.assert_eq("TextToUpper lowercase",  r.TextToUpper("hello world"), "HELLO WORLD")
T.assert_eq("TextToLower uppercase",  r.TextToLower("HELLO WORLD"), "hello world")
T.assert_eq("TextToUpper idempotent", r.TextToUpper("HELLO"), "HELLO")
T.assert_eq("TextToLower idempotent", r.TextToLower("hello"), "hello")

-- TextSubtext (0-based position, length bytes)
T.assert_eq("TextSubtext suffix", r.TextSubtext("hello world", 6, 5), "world")
T.assert_eq("TextSubtext prefix", r.TextSubtext("hello world", 0, 5), "hello")

-- TextReplace (static buffer) / TextReplaceAlloc (heap)
T.assert_eq("TextReplace match",         r.TextReplace("hello world", "world", "lua"), "hello lua")
T.assert_eq("TextReplace no match",      r.TextReplace("hello world", "xyz",   "abc"), "hello world")
T.assert_eq("TextReplaceAlloc match",    r.TextReplaceAlloc("hello world", "world", "lua"), "hello lua")
T.assert_eq("TextReplaceAlloc no match", r.TextReplaceAlloc("hello world", "xyz",   "abc"), "hello world")

-- TextReplaceBetween: replaces content between delimiters, keeping them
T.assert_eq("TextReplaceBetween",      r.TextReplaceBetween("say [X] here", "[", "]", "hello"), "say [hello] here")
T.assert_eq("TextReplaceBetweenAlloc", r.TextReplaceBetweenAlloc("say [X] here", "[", "]", "hello"), "say [hello] here")

-- TextInsert (0-based position) / TextInsertAlloc
T.assert_eq("TextInsert at end",       r.TextInsert("hello", "_LUA_", 5),      "hello_LUA_")
T.assert_eq("TextInsertAlloc at end",  r.TextInsertAlloc("hello", "_LUA_", 5), "hello_LUA_")

-- TextJoin
T.assert_eq("TextJoin with comma",  r.TextJoin({"a", "b", "c"}, ","),  "a,b,c")
T.assert_eq("TextJoin with space",  r.TextJoin({"hello", "world"}, " "), "hello world")
T.assert_eq("TextJoin single item", r.TextJoin({"only"}, ","),          "only")

-- TextSplit
local parts = r.TextSplit("a,b,c", ",")
T.assert_eq("TextSplit count",     #parts,   3)
T.assert_eq("TextSplit[1]",        parts[1], "a")
T.assert_eq("TextSplit[2]",        parts[2], "b")
T.assert_eq("TextSplit[3]",        parts[3], "c")
local single = r.TextSplit("hello", ",")
T.assert_eq("TextSplit no-delim count", #single,   1)
T.assert_eq("TextSplit no-delim[1]",    single[1], "hello")

-- TextFindIndex (returns 0-based index, or -1 if not found)
T.assert_eq("TextFindIndex mid",   r.TextFindIndex("hello world", "world"), 6)
T.assert_eq("TextFindIndex start", r.TextFindIndex("hello world", "hello"), 0)
T.assert_eq("TextFindIndex miss",  r.TextFindIndex("hello world", "xyz"),  -1)

-- TextFormat: delegates to Lua string.format (printf-style specifiers)
T.assert_eq("TextFormat int+str", r.TextFormat("%d-%s", 42, "x"), "42-x")
T.assert_eq("TextFormat plain",   r.TextFormat("no specifiers"),  "no specifiers")
T.assert_eq("TextFormat padded",  r.TextFormat("%03d", 7),        "007")

-- LoadUTF8: codepoints -> UTF-8 string; UnloadUTF8 is a safe no-op
T.assert_eq("LoadUTF8 'AB'", r.LoadUTF8({65, 66}), "AB")
T.assert_true("UnloadUTF8 no-op is safe", (pcall(r.UnloadUTF8, "AB")))

-- TextToInteger
T.assert_eq("TextToInteger positive", r.TextToInteger("42"),  42)
T.assert_eq("TextToInteger negative", r.TextToInteger("-10"), -10)
T.assert_eq("TextToInteger zero",     r.TextToInteger("0"),   0)

-- TextToFloat
T.assert_approx("TextToFloat 3.14", r.TextToFloat("3.14"), 3.14, 0.001)

-- TextToPascal / TextToSnake / TextToCamel
T.assert_eq("TextToPascal", r.TextToPascal("hello_world"), "HelloWorld")
T.assert_eq("TextToSnake",  r.TextToSnake("HelloWorld"),   "hello_world")
T.assert_eq("TextToCamel",  r.TextToCamel("hello_world"),  "helloWorld")

-- TextRemoveSpaces
T.assert_eq("TextRemoveSpaces leading+trailing", r.TextRemoveSpaces("  hi  there  "), "hithere")
T.assert_eq("TextRemoveSpaces internal",         r.TextRemoveSpaces("a b  c"),         "abc")

-- GetTextBetween (returns content between two delimiter strings)
T.assert_eq("GetTextBetween brackets", r.GetTextBetween("[hello]", "[", "]"), "hello")

-- LoadTextLines (splits on \n)
local lines = r.LoadTextLines("line1\nline2\nline3")
T.assert_eq("LoadTextLines count", #lines,   3)
T.assert_eq("LoadTextLines[1]",    lines[1], "line1")
T.assert_eq("LoadTextLines[2]",    lines[2], "line2")
T.assert_eq("LoadTextLines[3]",    lines[3], "line3")

-- GetCodepointCount
T.assert_eq("GetCodepointCount 'hello'", r.GetCodepointCount("hello"), 5)
T.assert_eq("GetCodepointCount empty",   r.GetCodepointCount(""),      0)

-- LoadCodepoints: returns array of Unicode codepoints
local pts = r.LoadCodepoints("AB")
T.assert_eq("LoadCodepoints count",  #pts,   2)
T.assert_eq("LoadCodepoints[1] = A", pts[1], 65)
T.assert_eq("LoadCodepoints[2] = B", pts[2], 66)

-- GetCodepoint: returns (codepoint, byte_size) for first char in string
local cp, sz = r.GetCodepoint("A")
T.assert_eq("GetCodepoint value of A", cp, 65)
T.assert_eq("GetCodepoint byte size",  sz, 1)

-- CodepointToUTF8: returns (utf8_string, byte_size)
local u, s = r.CodepointToUTF8(65)
T.assert_eq("CodepointToUTF8 65 -> 'A'", u, "A")
T.assert_eq("CodepointToUTF8 byte size", s, 1)

-- TextCopy: returns (copy, bytes_copied)
local cpy, n = r.TextCopy("hello")
T.assert_eq("TextCopy text",  cpy, "hello")
T.assert_eq("TextCopy bytes", n,   5)

-- TextAppend: appends to a string at position, returns (result, new_position)
local app, pos = r.TextAppend("hello", "_world", 5)
T.assert_eq("TextAppend result",       app, "hello_world")
T.assert_eq("TextAppend new position", pos, 11)
