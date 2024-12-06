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

Color get_color_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    Color color;
    lua_getfield(L, index, "r");
    color.r = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "g");
    color.g = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "b");
    color.b = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "a");
    color.a = luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    return color;
}

Vector2 get_vector2_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    Vector2 vec;
    lua_getfield(L, index, "x");
    vec.x = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "y");
    vec.y = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    return vec;
}
