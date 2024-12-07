#ifndef RAYLIB_WRAPPERS_H
#define RAYLIB_WRAPPERS_H

#include "raylib.h"
#include <lua.h>

/**
 * @brief Converts an integer to a Color struct.
 * 
 * @param color Integer representing the color
 * @return Color The converted Color struct
 */
Color convert_color(int color);

/**
 * @brief Retrieves a Color struct from a Lua table.
 * 
 * @param L Lua state
 * @param index Index of the table on the Lua stack
 * @return Color The retrieved Color struct
 */
Color get_color_from_table(lua_State *L, int index);

/**
 * @brief Retrieves a Vector2 struct from a Lua table.
 * 
 * @param L Lua state
 * @param index Index of the table on the Lua stack
 * @return Vector2 The retrieved Vector2 struct
 */
Vector2 get_vector2_from_table(lua_State *L, int index);

/**
 * @brief Retrieves an array of Vector2 structs from a Lua table.
 * 
 * @param L Lua state
 * @param index Index of the table on the Lua stack
 * @return Vector2* Pointer to the array of Vector2 structs
 */
Vector2 *get_vector2_array_from_table(lua_State *L, int index);

/**
 * @brief Retrieves a Vector3 struct from a Lua table.
 * 
 * @param L Lua state
 * @param index Index of the table on the Lua stack
 * @return Vector3 The retrieved Vector3 struct
 */
Vector3 get_vector3_from_table(lua_State *L, int index);

/**
 * @brief Retrieves a Vector4 struct from a Lua table.
 * 
 * @param L Lua state
 * @param index Index of the table on the Lua stack
 * @return Vector4 The retrieved Vector4 struct
 */
Vector4 get_vector4_from_table(lua_State *L, int index);

/**
 * @brief Retrieves a Matrix struct from a Lua table.
 * 
 * @param L Lua state
 * @param index Index of the table on the Lua stack
 * @return Matrix The retrieved Matrix struct
 */
Matrix get_matrix_from_table(lua_State *L, int index);

/**
 * @brief Retrieves a Ray struct from a Lua table.
 * 
 * @param L Lua state
 * @param index Index of the table on the Lua stack
 * @return Ray The retrieved Ray struct
 */
Ray get_ray_from_table(lua_State *L, int index);

/**
 * @brief Retrieves a BoundingBox struct from a Lua table.
 * 
 * @param L Lua state
 * @param index Index of the table on the Lua stack
 * @return BoundingBox The retrieved BoundingBox struct
 */
BoundingBox get_bounding_box_from_table(lua_State *L, int index);

/**
 * @brief Retrieves a Rectangle struct from a Lua table.
 * 
 * @param L Lua state
 * @param index Index of the table on the Lua stack
 * @return Rectangle The retrieved Rectangle struct
 */
Rectangle get_rectangle_from_table(lua_State *L, int index);

/**
 * @brief Retrieves an NPatchInfo struct from a Lua table.
 * 
 * @param L Lua state
 * @param index Index of the table on the Lua stack
 * @return NPatchInfo The retrieved NPatchInfo struct
 */
NPatchInfo get_npatchinfo_from_table(lua_State *L, int index);

/**
 * @brief Pushes an Image struct onto the Lua stack.
 * 
 * @param L Lua state
 * @param image The Image struct to push
 */
void push_image_to_lua(lua_State *L, Image image);

/**
 * @brief Pushes a Vector3 struct to a Lua table.
 * 
 * @param L Lua state
 * @param vector The Vector3 struct to push
 */
void push_vector3_to_table(lua_State *L, Vector3 vector);

/**
 * @brief Unloads an array of Material structs.
 * 
 * @param materials Pointer to the array of Material structs
 * @param count Number of Material structs in the array
 */
void UnloadMaterials(Material *materials, int count);

/**
 * @brief Pushes a Vector2 struct to a Lua table.
 * 
 * @param L Lua state
 * @param vec The Vector2 struct to push
 */
void push_vector2_to_table(lua_State *L, Vector2 vec);

/**
 * @brief Pushes a Vector4 struct to a Lua table.
 * 
 * @param L Lua state
 * @param vec The Vector4 struct to push
 */
void push_vector4_to_table(lua_State *L, Vector4 vec);

/**
 * @brief Pushes a Rectangle struct to a Lua table.
 * 
 * @param L Lua state
 * @param rect The Rectangle struct to push
 */
void push_rectangle_to_table(lua_State *L, Rectangle rect);

/**
 * @brief Pushes an Image struct to a Lua table.
 * 
 * @param L Lua state
 * @param image The Image struct to push
 */
void push_image_to_table(lua_State *L, Image image);

/**
 * @brief Pushes a Color struct to a Lua table.
 * 
 * @param L Lua state
 * @param color The Color struct to push
 */
void push_color_to_table(lua_State *L, Color color);

#endif
