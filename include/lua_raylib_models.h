#ifndef LUA_RAYLIB_MODELS_H
#define LUA_RAYLIB_MODELS_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "raylib.h"

int lua_LoadModel(lua_State *L);
int lua_DrawModel(lua_State *L);
int lua_DrawModelEx(lua_State *L);
int lua_UnloadModel(lua_State *L);
int lua_UpdateModelAnimation(lua_State *L);
int lua_DrawMesh(lua_State *L);
int lua_UnloadMesh(lua_State *L);
int lua_GenMeshCube(lua_State *L);
int lua_GenMeshSphere(lua_State *L);
int lua_GenMeshPlane(lua_State *L);

#endif