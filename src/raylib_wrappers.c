#include "raylib_wrappers.h"
#include "lauxlib.h"

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

void push_vector3_to_table(lua_State *L, Vector3 vector) {
    lua_newtable(L);
    lua_pushstring(L, "x");
    lua_pushnumber(L, vector.x);
    lua_settable(L, -3);

    lua_pushstring(L, "y");
    lua_pushnumber(L, vector.y);
    lua_settable(L, -3);

    lua_pushstring(L, "z");
    lua_pushnumber(L, vector.z);
    lua_settable(L, -3);
}

void UnloadMaterials(Material *materials, int count) {
    for (int i = 0; i < count; i++) {
        UnloadMaterial(materials[i]);
    }
}

void push_vector2_to_table(lua_State *L, Vector2 vec) {
    lua_newtable(L);
    lua_pushstring(L, "x");
    lua_pushnumber(L, vec.x);
    lua_settable(L, -3);

    lua_pushstring(L, "y");
    lua_pushnumber(L, vec.y);
    lua_settable(L, -3);
}

void push_rectangle_to_table(lua_State *L, Rectangle rect) {
    lua_newtable(L);
    lua_pushstring(L, "x");
    lua_pushnumber(L, rect.x);
    lua_settable(L, -3);

    lua_pushstring(L, "y");
    lua_pushnumber(L, rect.y);
    lua_settable(L, -3);

    lua_pushstring(L, "width");
    lua_pushnumber(L, rect.width);
    lua_settable(L, -3);

    lua_pushstring(L, "height");
    lua_pushnumber(L, rect.height);
    lua_settable(L, -3);
}

void push_image_to_table(lua_State *L, Image image) {
    lua_newtable(L);

    lua_pushinteger(L, image.width);
    lua_setfield(L, -2, "width");

    lua_pushinteger(L, image.height);
    lua_setfield(L, -2, "height");

    lua_pushinteger(L, image.mipmaps);
    lua_setfield(L, -2, "mipmaps");

    lua_pushinteger(L, image.format);
    lua_setfield(L, -2, "format");
}

void push_color_to_table(lua_State *L, Color color) {
    lua_newtable(L);
    lua_pushinteger(L, color.r);
    lua_setfield(L, -2, "r");
    lua_pushinteger(L, color.g);
    lua_setfield(L, -2, "g");
    lua_pushinteger(L, color.b);
    lua_setfield(L, -2, "b");
    lua_pushinteger(L, color.a);
    lua_setfield(L, -2, "a");
}

NPatchInfo get_npatchinfo_from_table(lua_State *L, int index) {
    NPatchInfo nPatchInfo;

    luaL_checktype(L, index, LUA_TTABLE);

    lua_getfield(L, index, "sourceRec");
    if (lua_istable(L, -1)) {
        nPatchInfo.source = get_rectangle_from_table(L, lua_gettop(L));
    } else {
        luaL_error(L, "'sourceRec' field must be a table");
    }
    lua_pop(L, 1);

    lua_getfield(L, index, "layout");
    if (lua_isinteger(L, -1)) {
        nPatchInfo.layout = lua_tointeger(L, -1);
    } else {
        luaL_error(L, "'layout' field must be an integer");
    }
    lua_pop(L, 1);

    lua_getfield(L, index, "left");
    if (lua_isinteger(L, -1)) {
        nPatchInfo.left = lua_tointeger(L, -1);
    } else {
        luaL_error(L, "'left' field must be an integer");
    }
    lua_pop(L, 1);

    lua_getfield(L, index, "top");
    if (lua_isinteger(L, -1)) {
        nPatchInfo.top = lua_tointeger(L, -1);
    } else {
        luaL_error(L, "'top' field must be an integer");
    }
    lua_pop(L, 1);

    lua_getfield(L, index, "right");
    if (lua_isinteger(L, -1)) {
        nPatchInfo.right = lua_tointeger(L, -1);
    } else {
        luaL_error(L, "'right' field must be an integer");
    }
    lua_pop(L, 1);

    lua_getfield(L, index, "bottom");
    if (lua_isinteger(L, -1)) {
        nPatchInfo.bottom = lua_tointeger(L, -1);
    } else {
        luaL_error(L, "'bottom' field must be an integer");
    }
    lua_pop(L, 1);

    return nPatchInfo;
}

Vector4 get_vector4_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);

    Vector4 vec;

    lua_pushstring(L, "x");
    lua_gettable(L, index);
    vec.x = luaL_checknumber(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "y");
    lua_gettable(L, index);
    vec.y = luaL_checknumber(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "z");
    lua_gettable(L, index);
    vec.z = luaL_checknumber(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "w");
    lua_gettable(L, index);
    vec.w = luaL_checknumber(L, -1);
    lua_pop(L, 1);

    return vec;
}

#include "raylib.h"
#include "lua.h"
#include "lauxlib.h"

void push_vector4_to_table(lua_State *L, Vector4 vec) {
    lua_newtable(L);

    lua_pushstring(L, "x");
    lua_pushnumber(L, vec.x);
    lua_settable(L, -3);

    lua_pushstring(L, "y");
    lua_pushnumber(L, vec.y);
    lua_settable(L, -3);

    lua_pushstring(L, "z");
    lua_pushnumber(L, vec.z);
    lua_settable(L, -3);

    lua_pushstring(L, "w");
    lua_pushnumber(L, vec.w);
    lua_settable(L, -3);
}
