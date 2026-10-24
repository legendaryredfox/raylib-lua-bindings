-- Raylib 6.2 additions and behavior changes (no window required).
--   * new path queries;
--   * ImageDraw* family: ImageDrawImage/Ex/Pro/Rec, gradients, line strip,
--     rectangle Pro/Lines forms, plus the legacy ImageDraw / ImageDrawTriangleEx;
--   * renamed GetSplinePointBezierQuadratic (old name kept as alias);
--   * bindings that need a GL context are only checked for presence.
local T = ...
local r = T.raylib

local BLACK = {r = 0, g = 0, b = 0, a = 255}
local RED   = {r = 255, g = 0, b = 0, a = 255}
local GREEN = {r = 0, g = 255, b = 0, a = 255}
local BLUE  = {r = 0, g = 0, b = 255, a = 255}
local WHITE = {r = 255, g = 255, b = 255, a = 255}

local function px(img, x, y) return r.GetImageColor(img, x, y) end
local function is(c, ref) return c.r == ref.r and c.g == ref.g and c.b == ref.b end

-- Path queries ---------------------------------------------------------------
T.assert_true ("IsPathAbsolute absolute",   r.IsPathAbsolute("/tmp"))
T.assert_false("IsPathAbsolute relative",   r.IsPathAbsolute("tests/runner.lua"))
T.assert_true ("IsPathDirectory directory", r.IsPathDirectory("tests"))
T.assert_false("IsPathDirectory file",      r.IsPathDirectory("tests/runner.lua"))
T.assert_false("IsFileHidden normal file",  r.IsFileHidden("tests/runner.lua"))

-- Spline rename ----------------------------------------------------------------
local p = r.GetSplinePointBezierQuadratic({x = 0, y = 0}, {x = 2, y = 2}, {x = 4, y = 0}, 0.5)
T.assert_approx("GetSplinePointBezierQuadratic x", p.x, 2)
T.assert_approx("GetSplinePointBezierQuadratic y", p.y, 1)
T.assert_eq("GetSplinePointBezierQuad alias", r.GetSplinePointBezierQuad, r.GetSplinePointBezierQuadratic)

-- Registered bindings (some need a GL context to run) -----------------------------
for _, name in ipairs({
    "DrawCircleLinesEx", "DrawCircleSectorLinesEx", "DrawEllipseLinesEx", "DrawRingLinesEx",
    "DrawTriangleGradient", "DrawTriangleLinesEx", "LoadRenderTextureEx", "ImageDrawTextPro",
}) do
    T.assert_eq("binding " .. name .. " exists", type(r[name]), "function")
end

-- ImageDrawImage family ----------------------------------------------------------
local dst = r.GenImageColor(8, 8, BLACK)
local src = r.GenImageColor(2, 2, RED)

r.ImageDrawImage(dst, src, 1, 1, WHITE)
T.assert_true ("ImageDrawImage draws source", is(px(dst, 1, 1), RED))
T.assert_true ("ImageDrawImage leaves outside", is(px(dst, 4, 4), BLACK))

r.ImageDrawImageRec(dst, src, {x = 0, y = 0, width = 1, height = 1}, {x = 5, y = 5}, WHITE)
T.assert_true ("ImageDrawImageRec draws region", is(px(dst, 5, 5), RED))
T.assert_true ("ImageDrawImageRec single pixel",  is(px(dst, 6, 6), BLACK))

local dst2 = r.GenImageColor(8, 8, BLACK)
r.ImageDrawImageEx(dst2, src, {x = 0, y = 0}, 0, 2, WHITE)
T.assert_true ("ImageDrawImageEx scaled covers 4x4", is(px(dst2, 3, 3), RED))
T.assert_true ("ImageDrawImageEx scaled stops",      is(px(dst2, 5, 5), BLACK))

local dst3 = r.GenImageColor(8, 8, BLACK)
r.ImageDrawImagePro(dst3, src, {x = 0, y = 0, width = 2, height = 2},
    {x = 2, y = 2, width = 4, height = 4}, {x = 0, y = 0}, 0, WHITE)
T.assert_true ("ImageDrawImagePro stretched", is(px(dst3, 4, 4), RED))

-- legacy ImageDraw (rectangle form) still works
local dst4 = r.GenImageColor(8, 8, BLACK)
r.ImageDraw(dst4, src, {x = 0, y = 0, width = 2, height = 2},
    {x = 2, y = 2, width = 2, height = 2}, WHITE)
T.assert_true ("legacy ImageDraw draws", is(px(dst4, 2, 2), RED))

-- Gradients, strips and rectangles ---------------------------------------------------
local g = r.GenImageColor(16, 16, BLACK)
r.ImageDrawCircleGradient(g, {x = 8, y = 8}, 6, WHITE, BLACK)
local center = px(g, 8, 8)
T.assert_true ("ImageDrawCircleGradient center bright", center.r > 200)
T.assert_true ("ImageDrawCircleGradient outside untouched", is(px(g, 0, 0), BLACK))

local rg = r.GenImageColor(16, 16, BLACK)
r.ImageDrawRectangleGradientEx(rg, {x = 0, y = 0, width = 16, height = 16}, RED, GREEN, BLUE, WHITE)
T.assert_true ("ImageDrawRectangleGradientEx changes pixels", not is(px(rg, 8, 8), BLACK))

local ls = r.GenImageColor(10, 10, BLACK)
r.ImageDrawLineStrip(ls, {{x = 0, y = 0}, {x = 9, y = 0}, {x = 9, y = 9}}, RED)
T.assert_true ("ImageDrawLineStrip horizontal", is(px(ls, 4, 0), RED))
T.assert_true ("ImageDrawLineStrip vertical",   is(px(ls, 9, 5), RED))
T.assert_true ("ImageDrawLineStrip untouched",  is(px(ls, 3, 6), BLACK))

local rp = r.GenImageColor(16, 16, BLACK)
r.ImageDrawRectanglePro(rp, {x = 4, y = 4, width = 6, height = 6}, {x = 0, y = 0}, 0, RED)
T.assert_true ("ImageDrawRectanglePro fills", is(px(rp, 6, 6), RED))

-- Rectangle outlines: both signatures -------------------------------------------------------
local o1 = r.GenImageColor(16, 16, BLACK)
r.ImageDrawRectangleLines(o1, {x = 2, y = 2, width = 10, height = 10}, 1, RED)   -- table form
T.assert_true ("RectangleLines (rec) edge",     is(px(o1, 2, 5), RED))
T.assert_true ("RectangleLines (rec) interior", is(px(o1, 6, 6), BLACK))

local o2 = r.GenImageColor(16, 16, BLACK)
r.ImageDrawRectangleLines(o2, 2, 2, 10, 10, RED)                                  -- 6.2 number form
T.assert_true ("RectangleLines (x,y,w,h) edge",     is(px(o2, 2, 5), RED))
T.assert_true ("RectangleLines (x,y,w,h) interior", is(px(o2, 6, 6), BLACK))

local o3 = r.GenImageColor(16, 16, BLACK)
r.ImageDrawRectangleLinesEx(o3, {x = 2, y = 2, width = 10, height = 10}, 1, RED)
T.assert_true ("RectangleLinesEx edge", is(px(o3, 2, 5), RED))

-- Triangle gradient and its legacy name -------------------------------------------------------
T.assert_eq("ImageDrawTriangleEx alias", r.ImageDrawTriangleEx, r.ImageDrawTriangleGradient)
local tg = r.GenImageColor(16, 16, BLACK)
r.ImageDrawTriangleGradient(tg, {x = 0, y = 0}, {x = 0, y = 15}, {x = 15, y = 15}, RED, GREEN, BLUE)
T.assert_true ("ImageDrawTriangleGradient fills", not is(px(tg, 3, 12), BLACK))

-- ImageColorContrast takes an integer in 6.2 --------------------------------------------------
local cc = r.GenImageColor(2, 2, {r = 100, g = 100, b = 100, a = 255})
T.assert_true ("ImageColorContrast integer", (pcall(r.ImageColorContrast, cc, 50)))

-- Argument validation ---------------------------------------------------------------------------
T.assert_false("ImageDrawImage rejects non-image", (pcall(r.ImageDrawImage, dst, {}, 0, 0, WHITE)))
T.assert_false("ImageDrawLineStrip rejects non-table", (pcall(r.ImageDrawLineStrip, dst, 5, RED)))

for _, im in ipairs({dst, src, dst2, dst3, dst4, g, rg, ls, rp, o1, o2, o3, tg, cc}) do r.UnloadImage(im) end
