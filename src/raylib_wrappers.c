#include <stdlib.h>
#include "raylib_wrappers.h"
#include "lauxlib.h"

const void *get_data_buffer(lua_State *L, int index) {
    if (lua_type(L, index) == LUA_TSTRING)
        return lua_tostring(L, index);
    return lua_touserdata(L, index);
}

Color convert_color(int color) {
    return (Color){
        (unsigned char)((color >> 24) & 0xFF),
        (unsigned char)((color >> 16) & 0xFF),
        (unsigned char)((color >> 8)  & 0xFF),
        (unsigned char)( color        & 0xFF)
    };
}

Color get_color_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    Color color;
    lua_getfield(L, index, "r"); color.r = (unsigned char)luaL_checkinteger(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "g"); color.g = (unsigned char)luaL_checkinteger(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "b"); color.b = (unsigned char)luaL_checkinteger(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "a"); color.a = (unsigned char)luaL_checkinteger(L, -1); lua_pop(L, 1);
    return color;
}

Vector2 get_vector2_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    Vector2 vec;
    lua_getfield(L, index, "x"); vec.x = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "y"); vec.y = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    return vec;
}

Vector3 get_vector3_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    Vector3 vec;
    lua_getfield(L, index, "x"); vec.x = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "y"); vec.y = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "z"); vec.z = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    return vec;
}

Vector4 get_vector4_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    Vector4 vec;
    lua_getfield(L, index, "x"); vec.x = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "y"); vec.y = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "z"); vec.z = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "w"); vec.w = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    return vec;
}

Matrix get_matrix_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    Matrix mat;
    lua_getfield(L, index, "m0");  mat.m0  = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m1");  mat.m1  = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m2");  mat.m2  = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m3");  mat.m3  = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m4");  mat.m4  = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m5");  mat.m5  = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m6");  mat.m6  = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m7");  mat.m7  = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m8");  mat.m8  = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m9");  mat.m9  = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m10"); mat.m10 = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m11"); mat.m11 = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m12"); mat.m12 = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m13"); mat.m13 = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m14"); mat.m14 = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "m15"); mat.m15 = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    return mat;
}

Ray get_ray_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    Ray ray;
    lua_getfield(L, index, "position");  ray.position  = get_vector3_from_table(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "direction"); ray.direction = get_vector3_from_table(L, -1); lua_pop(L, 1);
    return ray;
}

BoundingBox get_bounding_box_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    BoundingBox bbox;
    lua_getfield(L, index, "min"); bbox.min = get_vector3_from_table(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "max"); bbox.max = get_vector3_from_table(L, -1); lua_pop(L, 1);
    return bbox;
}

Rectangle get_rectangle_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    Rectangle rect;
    lua_getfield(L, index, "x");      rect.x      = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "y");      rect.y      = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "width");  rect.width  = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "height"); rect.height = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    return rect;
}

NPatchInfo get_npatchinfo_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    NPatchInfo info;
    lua_getfield(L, index, "sourceRec");
    if (!lua_istable(L, -1)) luaL_error(L, "'sourceRec' field must be a table");
    info.source = get_rectangle_from_table(L, lua_gettop(L));
    lua_pop(L, 1);
    lua_getfield(L, index, "layout");
    if (!lua_isinteger(L, -1)) luaL_error(L, "'layout' field must be an integer");
    info.layout = (int)lua_tointeger(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "left");
    if (!lua_isinteger(L, -1)) luaL_error(L, "'left' field must be an integer");
    info.left = (int)lua_tointeger(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "top");
    if (!lua_isinteger(L, -1)) luaL_error(L, "'top' field must be an integer");
    info.top = (int)lua_tointeger(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "right");
    if (!lua_isinteger(L, -1)) luaL_error(L, "'right' field must be an integer");
    info.right = (int)lua_tointeger(L, -1); lua_pop(L, 1);
    lua_getfield(L, index, "bottom");
    if (!lua_isinteger(L, -1)) luaL_error(L, "'bottom' field must be an integer");
    info.bottom = (int)lua_tointeger(L, -1); lua_pop(L, 1);
    return info;
}

Vector2 *get_vector2_array_from_table(lua_State *L, int index) {
    luaL_checktype(L, index, LUA_TTABLE);
    int len = (int)luaL_len(L, index);
    Vector2 *points = (Vector2 *)malloc(len * sizeof(Vector2));
    for (int i = 0; i < len; i++) {
        lua_rawgeti(L, index, i + 1);
        points[i] = get_vector2_from_table(L, -1);
        lua_pop(L, 1);
    }
    return points;
}

void push_vector2_to_table(lua_State *L, Vector2 vec) {
    lua_createtable(L, 0, 2);
    lua_pushnumber(L, vec.x); lua_setfield(L, -2, "x");
    lua_pushnumber(L, vec.y); lua_setfield(L, -2, "y");
}

void push_vector3_to_table(lua_State *L, Vector3 vec) {
    lua_createtable(L, 0, 3);
    lua_pushnumber(L, vec.x); lua_setfield(L, -2, "x");
    lua_pushnumber(L, vec.y); lua_setfield(L, -2, "y");
    lua_pushnumber(L, vec.z); lua_setfield(L, -2, "z");
}

void push_vector4_to_table(lua_State *L, Vector4 vec) {
    lua_createtable(L, 0, 4);
    lua_pushnumber(L, vec.x); lua_setfield(L, -2, "x");
    lua_pushnumber(L, vec.y); lua_setfield(L, -2, "y");
    lua_pushnumber(L, vec.z); lua_setfield(L, -2, "z");
    lua_pushnumber(L, vec.w); lua_setfield(L, -2, "w");
}

void push_rectangle_to_table(lua_State *L, Rectangle rect) {
    lua_createtable(L, 0, 4);
    lua_pushnumber(L, rect.x);      lua_setfield(L, -2, "x");
    lua_pushnumber(L, rect.y);      lua_setfield(L, -2, "y");
    lua_pushnumber(L, rect.width);  lua_setfield(L, -2, "width");
    lua_pushnumber(L, rect.height); lua_setfield(L, -2, "height");
}

void push_color_to_table(lua_State *L, Color color) {
    lua_createtable(L, 0, 4);
    lua_pushinteger(L, color.r); lua_setfield(L, -2, "r");
    lua_pushinteger(L, color.g); lua_setfield(L, -2, "g");
    lua_pushinteger(L, color.b); lua_setfield(L, -2, "b");
    lua_pushinteger(L, color.a); lua_setfield(L, -2, "a");
}

void push_image_to_userdata(lua_State *L, Image image) {
    Image *pImage = (Image *)lua_newuserdata(L, sizeof(Image));
    *pImage = image;
    luaL_setmetatable(L, "Image");
}

void push_bounding_box_to_table(lua_State *L, BoundingBox bbox) {
    lua_createtable(L, 0, 2);
    push_vector3_to_table(L, bbox.min); lua_setfield(L, -2, "min");
    push_vector3_to_table(L, bbox.max); lua_setfield(L, -2, "max");
}

void push_ray_collision_to_table(lua_State *L, RayCollision col) {
    lua_createtable(L, 0, 4);
    lua_pushboolean(L, col.hit);         lua_setfield(L, -2, "hit");
    lua_pushnumber(L, col.distance);     lua_setfield(L, -2, "distance");
    push_vector3_to_table(L, col.point); lua_setfield(L, -2, "point");
    push_vector3_to_table(L, col.normal);lua_setfield(L, -2, "normal");
}

void UnloadMaterials(Material *materials, int count) {
    for (int i = 0; i < count; i++) UnloadMaterial(materials[i]);
}
