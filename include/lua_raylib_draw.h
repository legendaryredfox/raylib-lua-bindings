#ifndef RAYLIB_LUA_DRAW_H
#define RAYLIB_LUA_DRAW_H

#include "lua_raylib.h"

int lua_BeginDrawing(lua_State *L) ;
int lua_EndDrawing(lua_State *L) ;
int lua_ClearBackground(lua_State *L);
int lua_DrawRectangle(lua_State *L);

int lua_DrawRectangle(lua_State *L);
int lua_DrawCircle(lua_State *L);
int lua_DrawLineEx(lua_State *L);
int lua_DrawEllipse(lua_State *L);
int lua_DrawRectangleLines(lua_State *L);
int lua_DrawRectangleGradient(lua_State *L);
int lua_DrawRectangleRounded(lua_State *L);
int lua_DrawLineStrip(lua_State *L);
int lua_DrawPoly(lua_State *L);
int lua_DrawPolyLines(lua_State *L);
int lua_DrawPolyLinesEx(lua_State *L);
int lua_DrawGrid(lua_State *L);
int lua_DrawText(lua_State *L);
int lua_DrawCircleSector(lua_State *L);
int lua_DrawCircleSectorLines(lua_State *L);
int lua_DrawRectangleGradientV(lua_State *L);
int lua_DrawRectangleGradientEx(lua_State *L);
int lua_DrawCircleGradient(lua_State *L);
int lua_DrawLine(lua_State *L);
int lua_DrawLineBezier(lua_State *L);
int lua_DrawTriangle(lua_State *L);
int lua_DrawTriangleLines(lua_State *L);
int lua_DrawTriangleStrip(lua_State *L);
int lua_DrawRing(lua_State *L);
int lua_DrawRingLines(lua_State *L);

#endif