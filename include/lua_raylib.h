#ifndef LUA_RAYLIB_H
#define LUA_RAYLIB_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>
#include <stdlib.h>
#include "raylib.h"

void push_color(lua_State *L, Color color);
void register_raylib_colors(lua_State *L);

#endif