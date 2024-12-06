#ifndef RAYLIB_LUA_DRAW_H
#define RAYLIB_LUA_DRAW_H

#include "lua_raylib.h"

int lua_BeginDrawing(lua_State *L) ;
int lua_EndDrawing(lua_State *L) ;
int lua_ClearBackground(lua_State *L);
int lua_DrawRectangle(lua_State *L) ;

#endif