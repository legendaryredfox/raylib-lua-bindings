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


Vector3 get_vector3_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    Vector3 vec;
    lua_getfield(L, index, "x");
    vec.x = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "y");
    vec.y = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "z");
    vec.z = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    return vec;
}

Matrix get_matrix_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    Matrix mat;

    lua_getfield(L, index, "m0");
    mat.m0 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m1");
    mat.m1 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m2");
    mat.m2 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m3");
    mat.m3 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m4");
    mat.m4 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m5");
    mat.m5 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m6");
    mat.m6 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m7");
    mat.m7 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m8");
    mat.m8 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m9");
    mat.m9 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m10");
    mat.m10 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m11");
    mat.m11 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m12");
    mat.m12 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m13");
    mat.m13 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m14");
    mat.m14 = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, index, "m15");
    mat.m15 = luaL_checknumber(L, -1);
    lua_pop(L, 1);

    return mat;
}

Ray get_ray_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    Ray ray;


    lua_getfield(L, index, "position");
    ray.position = get_vector3_from_table(L, -1);
    lua_pop(L, 1);


    lua_getfield(L, index, "direction");
    ray.direction = get_vector3_from_table(L, -1);
    lua_pop(L, 1);

    return ray;
}

BoundingBox get_bounding_box_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    BoundingBox bbox;

    lua_getfield(L, index, "min");
    bbox.min = get_vector3_from_table(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, index, "max");
    bbox.max = get_vector3_from_table(L, -1);
    lua_pop(L, 1);

    return bbox;
}

Rectangle get_rectangle_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    Rectangle rect;

    lua_getfield(L, index, "x");
    rect.x = luaL_checknumber(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, index, "y");
    rect.y = luaL_checknumber(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, index, "width");
    rect.width = luaL_checknumber(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, index, "height");
    rect.height = luaL_checknumber(L, -1);
    lua_pop(L, 1);

    return rect;
}
