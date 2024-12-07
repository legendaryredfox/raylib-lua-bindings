#ifndef LUA_RAYLIB_SHAPES_H
#define LUA_RAYLIB_SHAPES_H

#include "lua.h"
#include "lauxlib.h"
#include "raylib.h"

int lua_SetShapesTexture(lua_State *L);
int lua_GetShapesTexture(lua_State *L);
int lua_GetShapesTextureRectangle(lua_State *L);
int lua_DrawPixel(lua_State *L);
int lua_DrawPixelV(lua_State *L);
int lua_DrawLineV(lua_State *L);
int lua_DrawCircleV(lua_State *L);
int lua_DrawCircleLines(lua_State *L);
int lua_DrawCircleLinesV(lua_State *L);
int lua_DrawEllipseLines(lua_State *L);
int lua_DrawRectangleV(lua_State *L);
int lua_DrawRectangleRec(lua_State *L);
int lua_DrawRectanglePro(lua_State *L);
int lua_DrawRectangleGradientH(lua_State *L);
int lua_DrawRectangleLinesEx(lua_State *L);
int lua_DrawSplineLinear(lua_State *L);
int lua_DrawSplineBasis(lua_State *L);
int lua_DrawSplineCatmullRom(lua_State *L);
int lua_DrawSplineBezierQuadratic(lua_State *L);
int lua_DrawSplineBezierCubic(lua_State *L);
int lua_DrawSplineSegmentLinear(lua_State *L);
int lua_DrawSplineSegmentBasis(lua_State *L);
int lua_DrawSplineSegmentCatmullRom(lua_State *L);
int lua_DrawSplineSegmentBezierQuadratic(lua_State *L);
int lua_DrawSplineSegmentBezierCubic(lua_State *L);
int lua_GetSplinePointLinear(lua_State *L);
int lua_GetSplinePointBasis(lua_State *L);
int lua_GetSplinePointCatmullRom(lua_State *L);
int lua_GetSplinePointBezierQuad(lua_State *L);
int lua_GetSplinePointBezierCubic(lua_State *L);
int lua_CheckCollisionRecs(lua_State *L);
int lua_CheckCollisionCircles(lua_State *L);
int lua_CheckCollisionCircleRec(lua_State *L);
int lua_CheckCollisionCircleLine(lua_State *L);
int lua_CheckCollisionPointRec(lua_State *L);
int lua_CheckCollisionPointCircle(lua_State *L);
int lua_CheckCollisionPointTriangle(lua_State *L);
int lua_CheckCollisionPointLine(lua_State *L);
int lua_CheckCollisionPointPoly(lua_State *L);
int lua_CheckCollisionLines(lua_State *L);
int lua_GetCollisionRec(lua_State *L);


#endif 