#include "lua_raylib_audio.h"

int lua_LoadSound(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    Sound sound = LoadSound(fileName);
    Sound *pSound = lua_newuserdata(L, sizeof(Sound));
    *pSound = sound;
    luaL_setmetatable(L, "Sound");
    return 1;
}

int lua_PlaySound(lua_State *L) {
    Sound *sound = luaL_checkudata(L, 1, "Sound");
    PlaySound(*sound);
    return 0;
}

int lua_StopSound(lua_State *L) {
    Sound *sound = luaL_checkudata(L, 1, "Sound");
    StopSound(*sound);
    return 0;
}

int lua_UnloadSound(lua_State *L) {
    Sound *sound = luaL_checkudata(L, 1, "Sound");
    UnloadSound(*sound);
    return 0;
}

int lua_SetSoundVolume(lua_State *L) {
    Sound *sound = luaL_checkudata(L, 1, "Sound");
    float volume = luaL_checknumber(L, 2);
    SetSoundVolume(*sound, volume);
    return 0;
}

int lua_LoadMusicStream(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    Music music = LoadMusicStream(fileName);
    Music *pMusic = lua_newuserdata(L, sizeof(Music));
    *pMusic = music;
    luaL_setmetatable(L, "Music");
    return 1;
}

int lua_PlayMusicStream(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    PlayMusicStream(*music);
    return 0;
}

int lua_StopMusicStream(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    StopMusicStream(*music);
    return 0;
}

int lua_UpdateMusicStream(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    UpdateMusicStream(*music);
    return 0;
}

int lua_SetMusicVolume(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    float volume = luaL_checknumber(L, 2);
    SetMusicVolume(*music, volume);
    return 0;
}

int lua_IsSoundPlaying(lua_State *L) {
    Sound *sound = luaL_checkudata(L, 1, "Sound");
    lua_pushboolean(L, IsSoundPlaying(*sound));
    return 1;
}