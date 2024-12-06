#ifndef RAYLIB_LUA_CORE_H
#define RAYLIB_LUA_CORE_H

#include "lua_raylib.h"

int lua_InitWindow(lua_State *L);
int lua_CloseWindow(lua_State *L);
int lua_WindowShouldClose(lua_State *L);
int lua_GetClipboardImage(lua_State *L);

#endif