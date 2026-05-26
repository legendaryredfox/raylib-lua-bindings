-- Hashing function binding tests (no window required)
-- Expected values verified against standard implementations.
local T = ...
local r = T.raylib

-- ComputeCRC32
T.assert_eq("ComputeCRC32 empty string",     r.ComputeCRC32(""),      0)
T.assert_eq("ComputeCRC32 'hello'",          r.ComputeCRC32("hello"), 907060870)  -- 0x3610A686
T.assert_eq("ComputeCRC32 deterministic",    r.ComputeCRC32("test"),  r.ComputeCRC32("test"))
T.assert_true("ComputeCRC32 distinct inputs", r.ComputeCRC32("hello") ~= r.ComputeCRC32("world"))

-- ComputeMD5 ("hello")
-- Standard MD5: 5d41402abc4b2a76b9719d911017c592
-- Stored as 4 little-endian uint32 words:
--   5d41402a -> 0x2A40415D   bc4b2a76 -> 0x762A4BBC
--   b9719d91 -> 0x919D71B9   1017c592 -> 0x92C51710
local md5 = r.ComputeMD5("hello")
T.assert_eq("ComputeMD5 returns 4 words", #md5,   4)
T.assert_eq("ComputeMD5 'hello' word[1]", md5[1], 0x2A40415D)
T.assert_eq("ComputeMD5 'hello' word[2]", md5[2], 0x762A4BBC)
T.assert_eq("ComputeMD5 'hello' word[3]", md5[3], 0x919D71B9)
T.assert_eq("ComputeMD5 'hello' word[4]", md5[4], 0x92C51710)
T.assert_eq("ComputeMD5 deterministic",   r.ComputeMD5("hello")[1], md5[1])

-- ComputeSHA1 ("hello")
-- Standard SHA1: aaf4c61ddcc5e8a2dabede0f3b482cd9aea9434d
-- Stored as 5 big-endian uint32 words.
local sha1 = r.ComputeSHA1("hello")
T.assert_eq("ComputeSHA1 returns 5 words", #sha1,   5)
T.assert_eq("ComputeSHA1 'hello' word[1]", sha1[1], 0xAAF4C61D)
T.assert_eq("ComputeSHA1 'hello' word[2]", sha1[2], 0xDCC5E8A2)
T.assert_eq("ComputeSHA1 'hello' word[3]", sha1[3], 0xDABEDE0F)
T.assert_eq("ComputeSHA1 'hello' word[4]", sha1[4], 0x3B482CD9)
T.assert_eq("ComputeSHA1 'hello' word[5]", sha1[5], 0xAEA9434D)
T.assert_eq("ComputeSHA1 deterministic",   r.ComputeSHA1("hello")[1], sha1[1])
T.assert_true("ComputeSHA1 distinct inputs", r.ComputeSHA1("hello")[1] ~= r.ComputeSHA1("world")[1])

-- ComputeSHA256 ("hello")
-- Standard SHA256: 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824
-- Stored as 8 big-endian uint32 words.
local sha256 = r.ComputeSHA256("hello")
T.assert_eq("ComputeSHA256 returns 8 words", #sha256,   8)
T.assert_eq("ComputeSHA256 'hello' word[1]", sha256[1], 0x2CF24DBA)
T.assert_eq("ComputeSHA256 'hello' word[2]", sha256[2], 0x5FB0A30E)
T.assert_eq("ComputeSHA256 'hello' word[3]", sha256[3], 0x26E83B2A)
T.assert_eq("ComputeSHA256 'hello' word[4]", sha256[4], 0xC5B9E29E)
T.assert_eq("ComputeSHA256 'hello' word[5]", sha256[5], 0x1B161E5C)
T.assert_eq("ComputeSHA256 'hello' word[6]", sha256[6], 0x1FA7425E)
T.assert_eq("ComputeSHA256 'hello' word[7]", sha256[7], 0x73043362)
T.assert_eq("ComputeSHA256 'hello' word[8]", sha256[8], 0x938B9824)
T.assert_eq("ComputeSHA256 deterministic",   r.ComputeSHA256("hello")[1], sha256[1])
T.assert_true("ComputeSHA256 distinct inputs", r.ComputeSHA256("hello")[1] ~= r.ComputeSHA256("world")[1])
