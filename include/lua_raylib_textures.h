#ifndef LUA_RAYLIB_TEXTURES_H
#define LUA_RAYLIB_TEXTURES_H

#include "lua_raylib.h"

int lua_LoadImage(lua_State *L);
int lua_UnloadImage(lua_State *L);
int lua_LoadTexture(lua_State *L);
int lua_LoadTextureFromImage(lua_State *L);
int lua_UnloadTexture(lua_State *L);
int lua_UpdateTexture(lua_State *L);
int lua_GenTextureMipmaps(lua_State *L);
int lua_ImageResize(lua_State *L);
int lua_ImageFlipHorizontal(lua_State *L);
int lua_ImageFlipVertical(lua_State *L);
int lua_ImageCopy(lua_State *L);
int lua_ImageCrop(lua_State *L);
int lua_ImageColorTint(lua_State *L);
int lua_ImageColorInvert(lua_State *L);
int lua_ImageColorGrayscale(lua_State *L);
int lua_ImageColorBrightness(lua_State *L);
int lua_ImageColorContrast(lua_State *L);
int lua_ImageColorReplace(lua_State *L);
int lua_LoadTextureCubemap(lua_State *L);
int lua_UpdateTextureRec(lua_State *L);

#endif