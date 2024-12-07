#ifndef LUA_RAYLIB_SHAPES_H
#define LUA_RAYLIB_SHAPES_H

#include "lua.h"
#include "lauxlib.h"
#include "raylib.h"

int lua_SetShapesTexture(lua_State *L);
int lua_GetShapesTexture(lua_State *L);
int lua_GetShapesTextureRectangle(lua_State *L);

#endif 