#ifndef LUA_RAYLIB_AUDIO_H
#define LUA_RAYLIB_AUDIO_H

#include "lua_raylib.h"

int lua_LoadSound(lua_State *L);
int lua_PlaySound(lua_State *L);
int lua_StopSound(lua_State *L);
int lua_UnloadSound(lua_State *L);

int lua_LoadMusicStream(lua_State *L);
int lua_PlayMusicStream(lua_State *L);
int lua_StopMusicStream(lua_State *L);
int lua_UpdateMusicStream(lua_State *L);
int lua_SetMusicVolume(lua_State *L);
int lua_SetSoundVolume(lua_State *L);
int lua_IsSoundPlaying(lua_State *L);

#endif