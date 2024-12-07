#include <stdlib.h>
#include "raylib_wrappers.h"
#include "lua_raylib_shapes.h"

int lua_SetShapesTexture(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture2D");
    Rectangle source = get_rectangle_from_table(L, 2);
    SetShapesTexture(*texture, source);
    return 0;
}

int lua_GetShapesTexture(lua_State *L) {
    Texture2D texture = GetShapesTexture();
    Texture2D *pTexture = lua_newuserdata(L, sizeof(Texture2D));
    *pTexture = texture;
    luaL_setmetatable(L, "Texture2D");
    return 1;
}

int lua_GetShapesTextureRectangle(lua_State *L) {
    Rectangle rect = GetShapesTextureRectangle();
    push_rectangle_to_table(L, rect);
    return 1;
}

int lua_DrawPixel(lua_State *L) {
    int posX = luaL_checkinteger(L, 1);
    int posY = luaL_checkinteger(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawPixel(posX, posY, color);
    return 0;
}

int lua_DrawPixelV(lua_State *L) {
    Vector2 position = get_vector2_from_table(L, 1);
    Color color = get_color_from_table(L, 2);
    DrawPixelV(position, color);
    return 0;
}

int lua_DrawLineV(lua_State *L) {
    Vector2 startPos = get_vector2_from_table(L, 1);
    Vector2 endPos = get_vector2_from_table(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawLineV(startPos, endPos, color);
    return 0;
}

int lua_DrawCircleV(lua_State *L) {
    Vector2 center = get_vector2_from_table(L, 1);
    float radius = luaL_checknumber(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawCircleV(center, radius, color);
    return 0;
}

int lua_DrawCircleLines(lua_State *L) {
    int centerX = luaL_checkinteger(L, 1);
    int centerY = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);
    Color color = get_color_from_table(L, 4);
    DrawCircleLines(centerX, centerY, radius, color);
    return 0;
}

int lua_DrawCircleLinesV(lua_State *L) {
    Vector2 center = get_vector2_from_table(L, 1);
    float radius = luaL_checknumber(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawCircleLinesV(center, radius, color);
    return 0;
}

int lua_DrawEllipseLines(lua_State *L) {
    int centerX = luaL_checkinteger(L, 1);
    int centerY = luaL_checkinteger(L, 2);
    float radiusH = luaL_checknumber(L, 3);
    float radiusV = luaL_checknumber(L, 4);
    Color color = get_color_from_table(L, 5);
    DrawEllipseLines(centerX, centerY, radiusH, radiusV, color);
    return 0;
}

int lua_DrawRectangleV(lua_State *L) {
    Vector2 position = get_vector2_from_table(L, 1);
    Vector2 size = get_vector2_from_table(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawRectangleV(position, size, color);
    return 0;
}

int lua_DrawRectangleRec(lua_State *L) {
    Rectangle rec = get_rectangle_from_table(L, 1);
    Color color = get_color_from_table(L, 2);
    DrawRectangleRec(rec, color);
    return 0;
}

int lua_DrawRectanglePro(lua_State *L) {
    Rectangle rec = get_rectangle_from_table(L, 1);
    Vector2 origin = get_vector2_from_table(L, 2);
    float rotation = luaL_checknumber(L, 3);
    Color color = get_color_from_table(L, 4);
    DrawRectanglePro(rec, origin, rotation, color);
    return 0;
}

int lua_DrawRectangleGradientH(lua_State *L) {
    int posX = luaL_checkinteger(L, 1);
    int posY = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    Color left = get_color_from_table(L, 5);
    Color right = get_color_from_table(L, 6);
    DrawRectangleGradientH(posX, posY, width, height, left, right);
    return 0;
}

int lua_DrawRectangleLinesEx(lua_State *L) {
    Rectangle rec = get_rectangle_from_table(L, 1);
    float lineThick = luaL_checknumber(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawRectangleLinesEx(rec, lineThick, color);
    return 0;
}

int lua_DrawSplineLinear(lua_State *L) {
    Vector2 *points = get_vector2_array_from_table(L, 1);
    int pointCount = luaL_len(L, 1);
    float thick = luaL_checknumber(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawSplineLinear(points, pointCount, thick, color);
    free(points);
    return 0;
}

int lua_DrawSplineBasis(lua_State *L) {
    Vector2 *points = get_vector2_array_from_table(L, 1);
    int pointCount = luaL_len(L, 1);
    float thick = luaL_checknumber(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawSplineBasis(points, pointCount, thick, color);
    free(points);
    return 0;
}

int lua_DrawSplineCatmullRom(lua_State *L) {
    Vector2 *points = get_vector2_array_from_table(L, 1);
    int pointCount = luaL_len(L, 1);
    float thick = luaL_checknumber(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawSplineCatmullRom(points, pointCount, thick, color);
    free(points);
    return 0;
}

int lua_DrawSplineBezierQuadratic(lua_State *L) {
    Vector2 *points = get_vector2_array_from_table(L, 1);
    int pointCount = luaL_len(L, 1);
    float thick = luaL_checknumber(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawSplineBezierQuadratic(points, pointCount, thick, color);
    free(points);
    return 0;
}

int lua_DrawSplineBezierCubic(lua_State *L) {
    Vector2 *points = get_vector2_array_from_table(L, 1);
    int pointCount = luaL_len(L, 1);
    float thick = luaL_checknumber(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawSplineBezierCubic(points, pointCount, thick, color);
    free(points);
    return 0;
}

int lua_DrawSplineSegmentLinear(lua_State *L) {
    Vector2 p1 = get_vector2_from_table(L, 1);
    Vector2 p2 = get_vector2_from_table(L, 2);
    float thick = luaL_checknumber(L, 3);
    Color color = get_color_from_table(L, 4);
    DrawSplineSegmentLinear(p1, p2, thick, color);
    return 0;
}

int lua_DrawSplineSegmentBasis(lua_State *L) {
    Vector2 p1 = get_vector2_from_table(L, 1);
    Vector2 p2 = get_vector2_from_table(L, 2);
    Vector2 p3 = get_vector2_from_table(L, 3);
    Vector2 p4 = get_vector2_from_table(L, 4);
    float thick = luaL_checknumber(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawSplineSegmentBasis(p1, p2, p3, p4, thick, color);
    return 0;
}

int lua_DrawSplineSegmentCatmullRom(lua_State *L) {
    Vector2 p1 = get_vector2_from_table(L, 1);
    Vector2 p2 = get_vector2_from_table(L, 2);
    Vector2 p3 = get_vector2_from_table(L, 3);
    Vector2 p4 = get_vector2_from_table(L, 4);
    float thick = luaL_checknumber(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawSplineSegmentCatmullRom(p1, p2, p3, p4, thick, color);
    return 0;
}

int lua_DrawSplineSegmentBezierQuadratic(lua_State *L) {
    Vector2 p1 = get_vector2_from_table(L, 1);
    Vector2 c2 = get_vector2_from_table(L, 2);
    Vector2 p3 = get_vector2_from_table(L, 3);
    float thick = luaL_checknumber(L, 4);
    Color color = get_color_from_table(L, 5);
    DrawSplineSegmentBezierQuadratic(p1, c2, p3, thick, color);
    return 0;
}

int lua_DrawSplineSegmentBezierCubic(lua_State *L) {
    Vector2 p1 = get_vector2_from_table(L, 1);
    Vector2 c2 = get_vector2_from_table(L, 2);
    Vector2 c3 = get_vector2_from_table(L, 3);
    Vector2 p4 = get_vector2_from_table(L, 4);
    float thick = luaL_checknumber(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawSplineSegmentBezierCubic(p1, c2, c3, p4, thick, color);
    return 0;
}

int lua_GetSplinePointLinear(lua_State *L) {
    Vector2 startPos = get_vector2_from_table(L, 1);
    Vector2 endPos = get_vector2_from_table(L, 2);
    float t = luaL_checknumber(L, 3);
    Vector2 point = GetSplinePointLinear(startPos, endPos, t);
    push_vector2_to_table(L, point);
    return 1;
}

int lua_GetSplinePointBasis(lua_State *L) {
    Vector2 p1 = get_vector2_from_table(L, 1);
    Vector2 p2 = get_vector2_from_table(L, 2);
    Vector2 p3 = get_vector2_from_table(L, 3);
    Vector2 p4 = get_vector2_from_table(L, 4);
    float t = luaL_checknumber(L, 5);
    Vector2 point = GetSplinePointBasis(p1, p2, p3, p4, t);
    push_vector2_to_table(L, point);
    return 1;
}

int lua_GetSplinePointCatmullRom(lua_State *L) {
    Vector2 p1 = get_vector2_from_table(L, 1);
    Vector2 p2 = get_vector2_from_table(L, 2);
    Vector2 p3 = get_vector2_from_table(L, 3);
    Vector2 p4 = get_vector2_from_table(L, 4);
    float t = luaL_checknumber(L, 5);
    Vector2 point = GetSplinePointCatmullRom(p1, p2, p3, p4, t);
    push_vector2_to_table(L, point);
    return 1;
}

int lua_GetSplinePointBezierQuad(lua_State *L) {
    Vector2 p1 = get_vector2_from_table(L, 1);
    Vector2 c2 = get_vector2_from_table(L, 2);
    Vector2 p3 = get_vector2_from_table(L, 3);
    float t = luaL_checknumber(L, 4);
    Vector2 point = GetSplinePointBezierQuad(p1, c2, p3, t);
    push_vector2_to_table(L, point);
    return 1;
}

int lua_GetSplinePointBezierCubic(lua_State *L) {
    Vector2 p1 = get_vector2_from_table(L, 1);
    Vector2 c2 = get_vector2_from_table(L, 2);
    Vector2 c3 = get_vector2_from_table(L, 3);
    Vector2 p4 = get_vector2_from_table(L, 4);
    float t = luaL_checknumber(L, 5);
    Vector2 point = GetSplinePointBezierCubic(p1, c2, c3, p4, t);
    push_vector2_to_table(L, point);
    return 1;
}

int lua_CheckCollisionRecs(lua_State *L) {
    Rectangle rec1 = get_rectangle_from_table(L, 1);
    Rectangle rec2 = get_rectangle_from_table(L, 2);
    bool result = CheckCollisionRecs(rec1, rec2);
    lua_pushboolean(L, result);
    return 1;
}

int lua_CheckCollisionCircles(lua_State *L) {
    Vector2 center1 = get_vector2_from_table(L, 1);
    float radius1 = luaL_checknumber(L, 2);
    Vector2 center2 = get_vector2_from_table(L, 3);
    float radius2 = luaL_checknumber(L, 4);
    bool result = CheckCollisionCircles(center1, radius1, center2, radius2);
    lua_pushboolean(L, result);
    return 1;
}

int lua_CheckCollisionCircleRec(lua_State *L) {
    Vector2 center = get_vector2_from_table(L, 1);
    float radius = luaL_checknumber(L, 2);
    Rectangle rec = get_rectangle_from_table(L, 3);
    bool result = CheckCollisionCircleRec(center, radius, rec);
    lua_pushboolean(L, result);
    return 1;
}

int lua_CheckCollisionCircleLine(lua_State *L) {
    Vector2 center = get_vector2_from_table(L, 1);
    float radius = luaL_checknumber(L, 2);
    Vector2 p1 = get_vector2_from_table(L, 3);
    Vector2 p2 = get_vector2_from_table(L, 4);
    bool result = CheckCollisionCircleLine(center, radius, p1, p2);
    lua_pushboolean(L, result);
    return 1;
}

int lua_CheckCollisionPointRec(lua_State *L) {
    Vector2 point = get_vector2_from_table(L, 1);
    Rectangle rec = get_rectangle_from_table(L, 2);
    bool result = CheckCollisionPointRec(point, rec);
    lua_pushboolean(L, result);
    return 1;
}

int lua_CheckCollisionPointCircle(lua_State *L) {
    Vector2 point = get_vector2_from_table(L, 1);
    Vector2 center = get_vector2_from_table(L, 2);
    float radius = luaL_checknumber(L, 3);
    bool result = CheckCollisionPointCircle(point, center, radius);
    lua_pushboolean(L, result);
    return 1;
}

int lua_CheckCollisionPointTriangle(lua_State *L) {
    Vector2 point = get_vector2_from_table(L, 1);
    Vector2 p1 = get_vector2_from_table(L, 2);
    Vector2 p2 = get_vector2_from_table(L, 3);
    Vector2 p3 = get_vector2_from_table(L, 4);
    bool result = CheckCollisionPointTriangle(point, p1, p2, p3);
    lua_pushboolean(L, result);
    return 1;
}

int lua_CheckCollisionPointLine(lua_State *L) {
    Vector2 point = get_vector2_from_table(L, 1);
    Vector2 p1 = get_vector2_from_table(L, 2);
    Vector2 p2 = get_vector2_from_table(L, 3);
    int threshold = luaL_checkinteger(L, 4);
    bool result = CheckCollisionPointLine(point, p1, p2, threshold);
    lua_pushboolean(L, result);
    return 1;
}

int lua_CheckCollisionPointPoly(lua_State *L) {
    Vector2 point = get_vector2_from_table(L, 1);
    Vector2 *points = get_vector2_array_from_table(L, 2);
    int pointCount = luaL_len(L, 2);
    bool result = CheckCollisionPointPoly(point, points, pointCount);
    lua_pushboolean(L, result);
    return 1;
}

int lua_CheckCollisionLines(lua_State *L) {
    Vector2 startPos1 = get_vector2_from_table(L, 1);
    Vector2 endPos1 = get_vector2_from_table(L, 2);
    Vector2 startPos2 = get_vector2_from_table(L, 3);
    Vector2 endPos2 = get_vector2_from_table(L, 4);
    Vector2 collisionPoint;
    bool result = CheckCollisionLines(startPos1, endPos1, startPos2, endPos2, &collisionPoint);
    lua_pushboolean(L, result);
    push_vector2_to_table(L, collisionPoint);
    return 2;
}

int lua_GetCollisionRec(lua_State *L) {
    Rectangle rec1 = get_rectangle_from_table(L, 1);
    Rectangle rec2 = get_rectangle_from_table(L, 2);
    Rectangle collisionRec = GetCollisionRec(rec1, rec2);
    push_rectangle_to_table(L, collisionRec);
    return 1;
}
