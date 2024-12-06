#ifndef RAYLIB_WRAPPERS_H
#define RAYLIB_WRAPPERS_H

#include "raylib.h"
#include <lua.h>

Color convert_color(int color);
Color get_color_from_table(lua_State *L, int index);
Vector2 get_vector2_from_table(lua_State *L, int index);
Vector3 get_vector3_from_table(lua_State *L, int index);
Matrix get_matrix_from_table(lua_State *L, int index);
Ray get_ray_from_table(lua_State *L, int index);
BoundingBox get_bounding_box_from_table(lua_State *L, int index);
Rectangle get_rectangle_from_table(lua_State *L, int index);
void push_image_to_lua(lua_State *L, Image image);
void push_vector3_to_table(lua_State *L, Vector3 vector);
void UnloadMaterials(Material *materials, int count);

#endif
