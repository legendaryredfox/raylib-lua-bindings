#ifndef RAYLIB_WRAPPERS_H
#define RAYLIB_WRAPPERS_H

#include "raylib.h"
#include <lua.h>

// Convert a 32-bit integer color to a Raylib Color struct
Color convert_color(int color);
Color get_color_from_table(lua_State *L, int index);
Vector2 get_vector2_from_table(lua_State *L, int index);
void push_image_to_lua(lua_State *L, Image image);

#endif // RAYLIB_WRAPPERS_H
