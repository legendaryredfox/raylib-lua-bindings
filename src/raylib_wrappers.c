#include "raylib_wrappers.h"

Color convert_color(int color) {
    return (Color){
        (unsigned char)((color >> 24) & 0xFF),
        (unsigned char)((color >> 16) & 0xFF),
        (unsigned char)((color >> 8) & 0xFF),
        (unsigned char)(color & 0xFF)
    };
}

void push_image_to_lua(lua_State *L, Image image) {
    lua_newtable(L);

    lua_pushstring(L, "data");
    lua_pushlightuserdata(L, image.data);
    lua_settable(L, -3);

    lua_pushstring(L, "width");
    lua_pushinteger(L, image.width);
    lua_settable(L, -3);

    lua_pushstring(L, "height");
    lua_pushinteger(L, image.height);
    lua_settable(L, -3);

    lua_pushstring(L, "mipmaps");
    lua_pushinteger(L, image.mipmaps);
    lua_settable(L, -3);

    lua_pushstring(L, "format");
    lua_pushinteger(L, image.format);
    lua_settable(L, -3);
}
