#ifndef LUA_RAYLIB_MODELS_H
#define LUA_RAYLIB_MODELS_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "raylib.h"

/**
 * @brief Loads a model from a file.
 * 
 * This function loads a 3D model from a file and returns it as a `Model` object.
 * Supported file formats include `.obj`, `.gltf`, `.glb`, and `.iqm`.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `string fileName`: The path to the model file to be loaded.
 * 
 * @return int Always returns 1, pushing the loaded Model to the Lua stack.
 * 
 * @usage
 * ```lua
 * local model = raylib.LoadModel("resources/model.obj")
 * print("Model loaded successfully")
 * ```
 * 
 * @note The loaded model must be unloaded using `raylib.UnloadModel()` to avoid memory leaks.
 */
int lua_LoadModel(lua_State *L);

/**
 * @brief Draws a model with default parameters.
 * 
 * This function draws a 3D model using its default position, scale, and rotation.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Model model`: The model to be drawn.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawModel(model)
 * print("Model drawn successfully")
 * ```
 * 
 * @note This function uses the default shader and standard draw parameters.
 */
int lua_DrawModel(lua_State *L);

/**
 * @brief Draws a model with extended parameters.
 * 
 * This function draws a 3D model with extended options for position, rotation, and scaling.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Model model`: The model to be drawn.
 *  - `Vector3 position`: The position to draw the model.
 *  - `Vector3 rotationAxis`: The axis to rotate the model around.
 *  - `float rotationAngle`: The angle to rotate the model in degrees.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local position = { x = 0, y = 0, z = 0 }
 * local axis = { x = 0, y = 1, z = 0 }
 * raylib.DrawModelEx(model, position, axis, 45)
 * print("Model drawn with extended parameters")
 * ```
 * 
 * @note This function allows you to customize the draw position, rotation, and orientation of the model.
 */
int lua_DrawModelEx(lua_State *L);

/**
 * @brief Unloads a model from memory.
 * 
 * This function unloads a previously loaded 3D model from memory, freeing up resources.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Model model`: The model to be unloaded.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.UnloadModel(model)
 * print("Model unloaded successfully")
 * ```
 * 
 * @note After calling this function, the model can no longer be used unless it is reloaded.
 */
int lua_UnloadModel(lua_State *L);

/**
 * @brief Updates a model animation.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UpdateModelAnimation(lua_State *L);

/**
 * @brief Draws a mesh with default parameters.
 * 
 * This function draws a 3D mesh using its default position, scale, and rotation.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Mesh mesh`: The mesh to be drawn.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawMesh(mesh)
 * print("Mesh drawn successfully")
 * ```
 * 
 * @note This function uses the default shader and standard draw parameters.
 */
int lua_DrawMesh(lua_State *L);

/**
 * @brief Unloads a mesh from memory.
 * 
 * This function unloads a previously generated or loaded mesh from memory, freeing up resources.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Mesh mesh`: The mesh to be unloaded.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.UnloadMesh(mesh)
 * print("Mesh unloaded successfully")
 * ```
 * 
 * @note After calling this function, the mesh can no longer be used unless it is reloaded or regenerated.
 */
int lua_UnloadMesh(lua_State *L);

/**
 * @brief Generates a cube mesh.
 * 
 * This function generates a 3D cube mesh with the given dimensions.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `float width`: The width of the cube.
 *  - `float height`: The height of the cube.
 *  - `float length`: The length of the cube.
 * 
 * @return int Always returns 1, pushing the generated Mesh to the Lua stack.
 * 
 * @usage
 * ```lua
 * local cube = raylib.GenMeshCube(2.0, 2.0, 2.0)
 * print("Cube mesh generated successfully")
 * ```
 * 
 * @note The generated mesh must be unloaded using `raylib.UnloadMesh()` to avoid memory leaks.
 */
int lua_GenMeshCube(lua_State *L);

/**
 * @brief Generates a sphere mesh.
 * 
 * This function generates a 3D sphere mesh with the given radius and number of rings and slices.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `float radius`: The radius of the sphere.
 *  - `int rings`: The number of horizontal rings in the sphere.
 *  - `int slices`: The number of vertical slices in the sphere.
 * 
 * @return int Always returns 1, pushing the generated Mesh to the Lua stack.
 * 
 * @usage
 * ```lua
 * local sphere = raylib.GenMeshSphere(1.0, 16, 16)
 * print("Sphere mesh generated successfully")
 * ```
 * 
 * @note The generated mesh must be unloaded using `raylib.UnloadMesh()` to avoid memory leaks.
 */
int lua_GenMeshSphere(lua_State *L);

/**
 * @brief Generates a plane mesh.
 * 
 * This function generates a 3D plane mesh with the given width, length, and subdivisions.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `float width`: The width of the plane.
 *  - `float length`: The length of the plane.
 *  - `int resX`: The number of subdivisions on the X-axis.
 *  - `int resZ`: The number of subdivisions on the Z-axis.
 * 
 * @return int Always returns 1, pushing the generated Mesh to the Lua stack.
 * 
 * @usage
 * ```lua
 * local plane = raylib.GenMeshPlane(5.0, 5.0, 4, 4)
 * print("Plane mesh generated successfully")
 * ```
 * 
 * @note The generated mesh must be unloaded using `raylib.UnloadMesh()` to avoid memory leaks.
 */
int lua_GenMeshPlane(lua_State *L);

/**
 * @brief Draws a 3D line with specified parameters.
 * 
 * This function draws a 3D line between two points with a specific color.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Vector3 startPos`: The starting position of the line.
 *  - `Vector3 endPos`: The ending position of the line.
 *  - `Color color`: The color of the line.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawLine3D({x=0, y=0, z=0}, {x=1, y=1, z=1}, {r=255, g=0, b=0, a=255})
 * print("3D line drawn successfully")
 * ```
 * 
 * @note This function uses the default shader and standard draw parameters.
 */
int lua_DrawLine3D(lua_State *L);

/**
 * @brief Draws a 3D point with specified parameters.
 * 
 * This function draws a 3D point at the given position with the specified color.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Vector3 position`: The position of the point.
 *  - `Color color`: The color of the point.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawPoint3D({x=2, y=2, z=2}, {r=0, g=255, b=0, a=255})
 * print("3D point drawn successfully")
 * ```
 * 
 * @note This function uses the default shader and standard draw parameters.
 */
int lua_DrawPoint3D(lua_State *L);

/**
 * @brief Draws a 3D circle with specified parameters.
 * 
 * This function draws a 3D circle with a given center position, radius, rotation axis, and rotation angle.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `Vector3 center`: The center position of the circle.
 *  - `float radius`: The radius of the circle.
 *  - `Vector3 rotationAxis`: The axis around which the circle is rotated.
 *  - `float rotationAngle`: The angle of rotation in degrees.
 *  - `Color color`: The color of the circle.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawCircle3D({x=0, y=0, z=0}, 3.0, {x=0, y=1, z=0}, 45.0, {r=0, g=0, b=255, a=255})
 * print("3D circle drawn successfully")
 * ```
 * 
 * @note This function draws a circle using the current active shader.
 */
int lua_DrawCircle3D(lua_State *L);

/**
 * @brief Draws a 3D triangle with specified parameters.
 * 
 * This function draws a 3D triangle defined by three vertices and a specific color.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector3 v1`: The first vertex of the triangle.
 *  - `Vector3 v2`: The second vertex of the triangle.
 *  - `Vector3 v3`: The third vertex of the triangle.
 *  - `Color color`: The color of the triangle.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawTriangle3D({x=0, y=1, z=0}, {x=1, y=0, z=0}, {x=-1, y=0, z=0}, {r=255, g=255, b=0, a=255})
 * print("3D triangle drawn successfully")
 * ```
 * 
 * @note This function draws a filled 3D triangle using the current active shader.
 */
int lua_DrawTriangle3D(lua_State *L);

/**
 * @brief Draws a 3D triangle strip with specified parameters.
 * 
 * This function draws a 3D triangle strip using an array of vertices and a specific color.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Vector3[] points`: An array of points defining the triangle strip.
 *  - `int pointCount`: The number of points in the array.
 *  - `Color color`: The color of the triangle strip.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local points = {{x=0, y=1, z=0}, {x=1, y=0, z=0}, {x=2, y=1, z=0}, {x=3, y=0, z=0}}
 * raylib.DrawTriangleStrip3D(points, 4, {r=0, g=255, b=255, a=255})
 * print("3D triangle strip drawn successfully")
 * ```
 * 
 * @note The `points` parameter is an array of Vector3 points. The triangle strip must have at least 3 points.
 */
int lua_DrawTriangleStrip3D(lua_State *L);

/**
 * @brief Draws a 3D cube with specified parameters.
 * 
 * This function draws a 3D cube at a given position, with a specific width, height, depth, and color.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `float posX`: The X position of the cube.
 *  - `float posY`: The Y position of the cube.
 *  - `float posZ`: The Z position of the cube.
 *  - `float width`: The width of the cube.
 *  - `float height`: The height of the cube.
 *  - `float depth`: The depth of the cube.
 *  - `Color color`: The color of the cube.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawCube(0, 0, 0, 2, 2, 2, {r=255, g=0, b=0, a=255})
 * print("3D cube drawn successfully")
 * ```
 * 
 * @note This function draws a cube at the given position using the current active shader.
 */
int lua_DrawCube(lua_State *L);

/**
 * @brief Draws a 3D cube with specified parameters using a Vector3.
 * 
 * This function draws a 3D cube at a given position using a Vector3 for position, and another Vector3 for size.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Vector3 position`: The position of the cube (X, Y, Z).
 *  - `Vector3 size`: The size of the cube (width, height, depth).
 *  - `Color color`: The color of the cube.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawCubeV({x=0, y=0, z=0}, {x=2, y=2, z=2}, {r=0, g=0, b=255, a=255})
 * print("3D cube (vector version) drawn successfully")
 * ```
 * 
 * @note This function uses Vector3 parameters for position and size, allowing for more flexible 3D drawing.
 */
int lua_DrawCubeV(lua_State *L);

/**
 * @brief Draws the wireframe of a cube with specified parameters.
 * 
 * This function draws the wireframe of a 3D cube at a given position, with a specific width, height, depth, and color.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `float posX`: The X position of the cube.
 *  - `float posY`: The Y position of the cube.
 *  - `float posZ`: The Z position of the cube.
 *  - `float width`: The width of the cube.
 *  - `float height`: The height of the cube.
 *  - `float depth`: The depth of the cube.
 *  - `Color color`: The color of the wireframe.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawCubeWires(0, 0, 0, 2, 2, 2, {r=255, g=255, b=0, a=255})
 * print("3D cube wireframe drawn successfully")
 * ```
 * 
 * @note This function draws only the edges (wireframe) of the cube using the current active shader.
 */
int lua_DrawCubeWires(lua_State *L);

/**
 * @brief Draws the wireframe of a cube with specified parameters using a Vector3.
 * 
 * This function draws the wireframe of a 3D cube at a given position using a Vector3 for position, and another Vector3 for size.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Vector3 position`: The position of the cube (X, Y, Z).
 *  - `Vector3 size`: The size of the cube (width, height, depth).
 *  - `Color color`: The color of the wireframe.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawCubeWiresV({x=0, y=0, z=0}, {x=2, y=2, z=2}, {r=0, g=255, b=0, a=255})
 * print("3D cube wireframe (vector version) drawn successfully")
 * ```
 * 
 * @note This function draws only the edges (wireframe) of the cube using the current active shader.
 */
int lua_DrawCubeWiresV(lua_State *L);

/**
 * @brief Draws the wireframe of a sphere with specified parameters.
 * 
 * This function draws the wireframe of a 3D sphere at a given position, with a specific radius, number of rings, slices, and color.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `float centerX`: The X position of the sphere's center.
 *  - `float centerY`: The Y position of the sphere's center.
 *  - `float centerZ`: The Z position of the sphere's center.
 *  - `float radius`: The radius of the sphere.
 *  - `int rings`: The number of rings in the sphere.
 *  - `int slices`: The number of slices in the sphere.
 *  - `Color color`: The color of the wireframe.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawSphereWires(0, 0, 0, 2, 16, 16, {r=0, g=0, b=255, a=255})
 * print("3D sphere wireframe drawn successfully")
 * ```
 * 
 * @note This function draws only the edges (wireframe) of the sphere using the current active shader.
 */
int lua_DrawSphereWires(lua_State *L);

/**
 * @brief Draws a cylinder with specified parameters.
 * 
 * This function draws a 3D cylinder at a given position, with a specific radius, height, and color.
 * 
 * @param L A pointer to the current Lua state. Expects 6 arguments:
 *  - `float positionX`: The X position of the cylinder's base.
 *  - `float positionY`: The Y position of the cylinder's base.
 *  - `float positionZ`: The Z position of the cylinder's base.
 *  - `float radiusTop`: The radius of the top of the cylinder.
 *  - `float radiusBottom`: The radius of the bottom of the cylinder.
 *  - `float height`: The height of the cylinder.
 *  - `int slices`: The number of slices in the cylinder.
 *  - `Color color`: The color of the cylinder.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawCylinder(0, 0, 0, 1, 1, 3, 16, {r=255, g=0, b=255, a=255})
 * print("3D cylinder drawn successfully")
 * ```
 * 
 * @note This function draws a 3D cylinder using the current active shader.
 */
int lua_DrawCylinder(lua_State *L);

/**
 * @brief Draws a cylinder with extended parameters.
 * 
 * This function draws a 3D cylinder with specified positions, radii, height, slices, and color.
 * 
 * @param L A pointer to the current Lua state. Expects 7 arguments:
 *  - `Vector3 startPos`: The position of the bottom base of the cylinder (X, Y, Z).
 *  - `Vector3 endPos`: The position of the top base of the cylinder (X, Y, Z).
 *  - `float startRadius`: The radius of the bottom base.
 *  - `float endRadius`: The radius of the top base.
 *  - `int sides`: The number of sides (slices) of the cylinder.
 *  - `Color color`: The color of the cylinder.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawCylinderEx({x=0, y=0, z=0}, {x=0, y=5, z=0}, 1.0, 0.5, 16, {r=255, g=128, b=0, a=255})
 * print("3D extended cylinder drawn successfully")
 * ```
 * 
 * @note This function draws a 3D cylinder using the current active shader. The bottom and top bases can have different radii.
 */
int lua_DrawCylinderEx(lua_State *L);

/**
 * @brief Draws the wireframe of a cylinder with specified parameters.
 * 
 * This function draws the wireframe of a 3D cylinder with specified position, radius, height, and color.
 * 
 * @param L A pointer to the current Lua state. Expects 6 arguments:
 *  - `float positionX`: The X position of the cylinder's base.
 *  - `float positionY`: The Y position of the cylinder's base.
 *  - `float positionZ`: The Z position of the cylinder's base.
 *  - `float radius`: The radius of the cylinder.
 *  - `float height`: The height of the cylinder.
 *  - `int slices`: The number of slices in the cylinder.
 *  - `Color color`: The color of the wireframe.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawCylinderWires(0, 0, 0, 1, 3, 16, {r=255, g=0, b=0, a=255})
 * print("3D cylinder wireframe drawn successfully")
 * ```
 * 
 * @note This function draws only the edges (wireframe) of the cylinder using the current active shader.
 */
int lua_DrawCylinderWires(lua_State *L);

/**
 * @brief Draws the wireframe of a cylinder with extended parameters.
 * 
 * This function draws the wireframe of a 3D cylinder with specified positions, radii, height, slices, and color.
 * 
 * @param L A pointer to the current Lua state. Expects 7 arguments:
 *  - `Vector3 startPos`: The position of the bottom base of the cylinder (X, Y, Z).
 *  - `Vector3 endPos`: The position of the top base of the cylinder (X, Y, Z).
 *  - `float startRadius`: The radius of the bottom base.
 *  - `float endRadius`: The radius of the top base.
 *  - `int sides`: The number of sides (slices) of the cylinder.
 *  - `Color color`: The color of the wireframe.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawCylinderWiresEx({x=0, y=0, z=0}, {x=0, y=5, z=0}, 1.0, 0.5, 16, {r=0, g=0, b=255, a=255})
 * print("3D extended cylinder wireframe drawn successfully")
 * ```
 * 
 * @note This function draws only the edges (wireframe) of the cylinder using the current active shader.
 */
int lua_DrawCylinderWiresEx(lua_State *L);

/**
 * @brief Draws a capsule with specified parameters.
 * 
 * This function draws a 3D capsule between two points with a specified radius and color.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector3 startPos`: The position of one end of the capsule (X, Y, Z).
 *  - `Vector3 endPos`: The position of the other end of the capsule (X, Y, Z).
 *  - `float radius`: The radius of the capsule.
 *  - `int slices`: The number of sides (slices) of the capsule.
 *  - `Color color`: The color of the capsule.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawCapsule({x=0, y=0, z=0}, {x=0, y=5, z=0}, 1.0, 16, {r=255, g=0, b=255, a=255})
 * print("3D capsule drawn successfully")
 * ```
 * 
 * @note This function draws a 3D capsule using the current active shader. The capsule is essentially a cylinder with hemispherical ends.
 */
int lua_DrawCapsule(lua_State *L);

/**
 * @brief Draws the wireframe of a capsule with specified parameters.
 * 
 * This function draws the wireframe of a 3D capsule between two points with a specified radius, slices, and color.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `Vector3 startPos`: The position of one end of the capsule (X, Y, Z).
 *  - `Vector3 endPos`: The position of the other end of the capsule (X, Y, Z).
 *  - `float radius`: The radius of the capsule.
 *  - `int slices`: The number of sides (slices) of the capsule.
 *  - `Color color`: The color of the wireframe.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawCapsuleWires({x=0, y=0, z=0}, {x=0, y=5, z=0}, 1.0, 16, {r=0, g=255, b=255, a=255})
 * print("3D capsule wireframe drawn successfully")
 * ```
 * 
 * @note This function draws only the edges (wireframe) of the capsule using the current active shader.
 */
int lua_DrawCapsuleWires(lua_State *L);

/**
 * @brief Draws a plane with specified parameters.
 * 
 * This function draws a 3D plane at a specified position with a given size and color.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Vector3 centerPos`: The center position of the plane (X, Y, Z).
 *  - `Vector2 size`: The size of the plane (width, height).
 *  - `Color color`: The color of the plane.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawPlane({x=0, y=0, z=0}, {x=10, y=10}, {r=128, g=128, b=255, a=255})
 * print("3D plane drawn successfully")
 * ```
 * 
 * @note This function draws a 3D plane using the current active shader.
 */
int lua_DrawPlane(lua_State *L);

/**
 * @brief Draws a ray with specified parameters.
 * 
 * This function draws a 3D ray with a starting position, direction, and color.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Ray ray`: The ray to draw (position and direction).
 *  - `Color color`: The color of the ray.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawRay({position={x=0, y=0, z=0}, direction={x=1, y=0, z=0}}, {r=255, g=255, b=0, a=255})
 * print("3D ray drawn successfully")
 * ```
 * 
 * @note This function draws a 3D ray using the current active shader.
 */
int lua_DrawRay(lua_State *L);

/**
 * @brief Draws a grid with specified parameters.
 * 
 * This function draws a 3D grid centered at the origin with a specified number of slices and spacing.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `int slices`: The number of grid slices.
 *  - `float spacing`: The space between each grid line.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawGrid(10, 1.0)
 * print("3D grid drawn successfully")
 * ```
 * 
 * @note This function draws a 3D grid at the origin using the current active shader.
 */
int lua_DrawGrid(lua_State *L);

/**
 * @brief Loads a model from a mesh.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Model result)
 */
int lua_LoadModelFromMesh(lua_State *L);

/**
 * @brief Checks if a model is valid.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsModelValid(lua_State *L);

/**
 * @brief Gets the bounding box of a model.
 * 
 * @param L Lua state
 * @return int Always returns 1 (BoundingBox result)
 */
int lua_GetModelBoundingBox(lua_State *L);

/**
 * @brief Draws a bounding box with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawBoundingBox(lua_State *L);

/**
 * @brief Draws a billboard with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawBillboard(lua_State *L);

/**
 * @brief Draws a billboard with a specified rectangle.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawBillboardRec(lua_State *L);

/**
 * @brief Draws a billboard with extended parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawBillboardPro(lua_State *L);

/**
 * @brief Uploads a mesh to the GPU.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UploadMesh(lua_State *L);

/**
 * @brief Updates a mesh buffer with new data.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UpdateMeshBuffer(lua_State *L);

/**
 * @brief Gets the bounding box of a mesh.
 * 
 * @param L Lua state
 * @return int Always returns 1 (BoundingBox result)
 */
int lua_GetMeshBoundingBox(lua_State *L);

/**
 * @brief Generates tangents for a mesh.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_GenMeshTangents(lua_State *L);

/**
 * @brief Exports a mesh to a file.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_ExportMesh(lua_State *L);

/**
 * @brief Exports a mesh as code.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_ExportMeshAsCode(lua_State *L);

/**
 * @brief Generates a polygon mesh.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Mesh result)
 */
int lua_GenMeshPoly(lua_State *L);

/**
 * @brief Generates a hemisphere mesh.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Mesh result)
 */
int lua_GenMeshHemiSphere(lua_State *L);

/**
 * @brief Generates a cylinder mesh.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Mesh result)
 */
int lua_GenMeshCylinder(lua_State *L);

/**
 * @brief Generates a cone mesh.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Mesh result)
 */
int lua_GenMeshCone(lua_State *L);

/**
 * @brief Generates a torus mesh.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Mesh result)
 */
int lua_GenMeshTorus(lua_State *L);

/**
 * @brief Generates a knot mesh.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Mesh result)
 */
int lua_GenMeshKnot(lua_State *L);

/**
 * @brief Generates a heightmap mesh.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Mesh result)
 */
int lua_GenMeshHeightmap(lua_State *L);

/**
 * @brief Generates a cubicmap mesh.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Mesh result)
 */
int lua_GenMeshCubicmap(lua_State *L);

/**
 * @brief Loads materials from a file.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Materials result)
 */
int lua_LoadMaterials(lua_State *L);

/**
 * @brief Loads the default material.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Material result)
 */
int lua_LoadMaterialDefault(lua_State *L);

/**
 * @brief Checks if a material is valid.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsMaterialValid(lua_State *L);

/**
 * @brief Unloads a material from memory.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UnloadMaterial(lua_State *L);

/**
 * @brief Sets a texture for a material.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetMaterialTexture(lua_State *L);

/**
 * @brief Sets the material for a model mesh.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetModelMeshMaterial(lua_State *L);

/**
 * @brief Loads model animations from a file.
 * 
 * @param L Lua state
 * @return int Always returns 1 (ModelAnimations result)
 */
int lua_LoadModelAnimations(lua_State *L);

/**
 * @brief Unloads a model animation from memory.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UnloadModelAnimation(lua_State *L);

/**
 * @brief Unloads model animations from memory.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UnloadModelAnimations(lua_State *L);

/**
 * @brief Checks if a model animation is valid.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsModelAnimationValid(lua_State *L);

/**
 * @brief Checks collision between two spheres.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_CheckCollisionSpheres(lua_State *L);

/**
 * @brief Checks collision between two boxes.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_CheckCollisionBoxes(lua_State *L);

/**
 * @brief Checks collision between a box and a sphere.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_CheckCollisionBoxSphere(lua_State *L);

/**
 * @brief Gets the collision information between a ray and a sphere.
 * 
 * @param L Lua state
 * @return int Always returns 1 (RayCollision result)
 */
int lua_GetRayCollisionSphere(lua_State *L);

/**
 * @brief Gets the collision information between a ray and a box.
 * 
 * @param L Lua state
 * @return int Always returns 1 (RayCollision result)
 */
int lua_GetRayCollisionBox(lua_State *L);

/**
 * @brief Gets the collision information between a ray and a mesh.
 * 
 * @param L Lua state
 * @return int Always returns 1 (RayCollision result)
 */
int lua_GetRayCollisionMesh(lua_State *L);

/**
 * @brief Gets the collision information between a ray and a triangle.
 * 
 * @param L Lua state
 * @return int Always returns 1 (RayCollision result)
 */
int lua_GetRayCollisionTriangle(lua_State *L);

/**
 * @brief Gets the collision information between a ray and a quad.
 * 
 * @param L Lua state
 * @return int Always returns 1 (RayCollision result)
 */
int lua_GetRayCollisionQuad(lua_State *L);

#endif