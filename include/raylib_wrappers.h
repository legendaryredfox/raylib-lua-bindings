#ifndef RAYLIB_WRAPPERS_H
#define RAYLIB_WRAPPERS_H

#include "raylib.h"
#include <lua.h>

// Convert a 32-bit integer color to a Raylib Color struct
Color convert_color(int color);
void push_image_to_lua(lua_State *L, Image image);

#endif // RAYLIB_WRAPPERS_H
