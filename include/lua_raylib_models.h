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
 * This function creates a 3D model from a mesh. The resulting model can be used in rendering.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Mesh mesh`: The mesh to load as a model.
 * 
 * @return int Always returns 1 (Model result).
 * 
 * @usage
 * ```lua
 * local model = raylib.LoadModelFromMesh(mesh)
 * print("Model loaded from mesh successfully")
 * ```
 * 
 * @note This function allows you to convert a mesh to a model that can be rendered with materials.
 */
int lua_LoadModelFromMesh(lua_State *L);

/**
 * @brief Checks if a model is valid.
 * 
 * This function checks if a model is valid and usable.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Model model`: The model to check for validity.
 * 
 * @return int Always returns 1 (boolean result).
 * 
 * @usage
 * ```lua
 * local isValid = raylib.IsModelValid(model)
 * print("Is model valid?", isValid)
 * ```
 * 
 * @note This function returns `true` if the model is valid and `false` otherwise.
 */
int lua_IsModelValid(lua_State *L);

/**
 * @brief Gets the bounding box of a model.
 * 
 * This function calculates and returns the bounding box of a 3D model.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Model model`: The model to get the bounding box for.
 * 
 * @return int Always returns 1 (BoundingBox result).
 * 
 * @usage
 * ```lua
 * local boundingBox = raylib.GetModelBoundingBox(model)
 * print("Bounding box min:", boundingBox.min, "max:", boundingBox.max)
 * ```
 * 
 * @note The bounding box is a rectangular box that encloses the entire 3D model.
 */
int lua_GetModelBoundingBox(lua_State *L);

/**
 * @brief Draws a bounding box with specified parameters.
 * 
 * This function draws a bounding box with a given color.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `BoundingBox bbox`: The bounding box to draw.
 *  - `Color color`: The color of the bounding box.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawBoundingBox(boundingBox, {r=255, g=0, b=0, a=255})
 * print("Bounding box drawn successfully")
 * ```
 * 
 * @note This function draws the edges (wireframe) of the bounding box using the current active shader.
 */
int lua_DrawBoundingBox(lua_State *L);

/**
 * @brief Draws a billboard with specified parameters.
 * 
 * This function draws a 2D image (billboard) that always faces the camera, commonly used to display 2D objects in 3D space.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `Camera camera`: The camera to orient the billboard towards.
 *  - `Texture2D texture`: The texture to use for the billboard.
 *  - `Vector3 position`: The position in 3D space where the billboard is drawn.
 *  - `float size`: The size of the billboard.
 *  - `Color tint`: The color tint to apply to the billboard.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawBillboard(camera, texture, {x=0, y=1, z=0}, 2.0, {r=255, g=255, b=255, a=255})
 * print("Billboard drawn successfully")
 * ```
 * 
 * @note The billboard will always face the camera, making it useful for sprites or icons in 3D worlds.
 */
int lua_DrawBillboard(lua_State *L);

/**
 * @brief Draws a billboard with a specified rectangle.
 * 
 * This function draws a billboard using a specific region (rectangle) from a texture.
 * 
 * @param L A pointer to the current Lua state. Expects 6 arguments:
 *  - `Camera camera`: The camera to orient the billboard towards.
 *  - `Texture2D texture`: The texture to use for the billboard.
 *  - `Rectangle sourceRect`: The source rectangle of the texture to draw.
 *  - `Vector3 position`: The position in 3D space where the billboard is drawn.
 *  - `Vector2 size`: The size of the billboard.
 *  - `Color tint`: The color tint to apply to the billboard.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawBillboardRec(camera, texture, {x=0, y=0, width=64, height=64}, {x=0, y=1, z=0}, {x=2, y=2}, {r=255, g=255, b=255, a=255})
 * print("Billboard with rectangle drawn successfully")
 * ```
 * 
 * @note This function allows you to draw a specific portion of the texture as a billboard.
 */
int lua_DrawBillboardRec(lua_State *L);

/**
 * @brief Draws a billboard with extended parameters.
 * 
 * This function draws a billboard with options for scaling, rotation, and other extended parameters.
 * 
 * @param L A pointer to the current Lua state. Expects 9 arguments:
 *  - `Camera camera`: The camera to orient the billboard towards.
 *  - `Texture2D texture`: The texture to use for the billboard.
 *  - `Rectangle sourceRect`: The source rectangle of the texture to draw.
 *  - `Vector3 position`: The position in 3D space where the billboard is drawn.
 *  - `Vector2 size`: The size of the billboard.
 *  - `Vector2 origin`: The origin point of the billboard.
 *  - `float rotation`: The rotation of the billboard in degrees.
 *  - `Color tint`: The color tint to apply to the billboard.
 *  - `bool drawCenter`: If `true`, the billboard is drawn centered on the position.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawBillboardPro(camera, texture, {x=0, y=0, width=64, height=64}, {x=0, y=1, z=0}, {x=2, y=2}, {x=1, y=1}, 45.0, {r=255, g=255, b=255, a=255}, true)
 * print("Pro billboard drawn successfully")
 * ```
 * 
 * @note This function gives you full control over the size, rotation, origin, and source rectangle of the billboard.
 */
int lua_DrawBillboardPro(lua_State *L);

/**
 * @brief Uploads a mesh to the GPU.
 * 
 * This function uploads mesh data to the GPU, enabling faster rendering.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Mesh mesh`: The mesh to upload to the GPU.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.UploadMesh(mesh)
 * print("Mesh uploaded to GPU successfully")
 * ```
 * 
 * @note Once uploaded, the mesh resides in GPU memory, which improves rendering speed.
 */
int lua_UploadMesh(lua_State *L);

/**
 * @brief Updates a mesh buffer with new data.
 * 
 * This function updates a specific buffer of the mesh with new data.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `Mesh mesh`: The mesh to update.
 *  - `int bufferIndex`: The index of the buffer to update.
 *  - `void *data`: The pointer to the data to update the buffer with.
 *  - `int dataSize`: The size of the data in bytes.
 *  - `int offset`: The offset within the buffer to start updating from.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.UpdateMeshBuffer(mesh, 0, data, #data, 0)
 * print("Mesh buffer updated successfully")
 * ```
 * 
 * @note This function can be used to partially update vertex data, normals, or indices of the mesh.
 */
int lua_UpdateMeshBuffer(lua_State *L);

/**
 * @brief Gets the bounding box of a mesh.
 * 
 * This function returns the minimum and maximum 3D coordinates of the mesh as a BoundingBox.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Mesh mesh`: The mesh to compute the bounding box for.
 * 
 * @return int Always returns 1 (BoundingBox result).
 * 
 * @usage
 * ```lua
 * local boundingBox = raylib.GetMeshBoundingBox(mesh)
 * print("Bounding box:", boundingBox.min, boundingBox.max)
 * ```
 * 
 * @note This function computes the bounding box of the mesh in world space, useful for collision detection or visibility checks.
 */
int lua_GetMeshBoundingBox(lua_State *L);

/**
 * @brief Generates tangents for a mesh.
 * 
 * This function generates tangents for a mesh, which are necessary for normal mapping.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Mesh mesh`: The mesh to generate tangents for.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.GenMeshTangents(mesh)
 * print("Tangents generated for the mesh")
 * ```
 * 
 * @note Tangents are vectors perpendicular to the normals, and they are required for proper lighting with normal maps.
 */
int lua_GenMeshTangents(lua_State *L);

/**
 * @brief Exports a mesh to a file.
 * 
 * This function saves the mesh to a file in a specific format (e.g., OBJ or GLTF).
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Mesh mesh`: The mesh to export.
 *  - `string filename`: The path where the mesh will be saved.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.ExportMesh(mesh, "output.obj")
 * print("Mesh exported to 'output.obj' successfully")
 * ```
 * 
 * @note The export format is determined by the file extension (e.g., `.obj`, `.gltf`).
 */
int lua_ExportMesh(lua_State *L);

/**
 * @brief Exports a mesh as C code.
 * 
 * This function exports the mesh as C code, which can be included in a C/C++ project as a static resource.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Mesh mesh`: The mesh to export.
 *  - `string filename`: The path where the C code will be saved.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.ExportMeshAsCode(mesh, "mesh_code.c")
 * print("Mesh exported as C code to 'mesh_code.c'")
 * ```
 * 
 * @note The exported C code contains the vertex data, normals, and indices as C arrays.
 */
int lua_ExportMeshAsCode(lua_State *L);

/**
 * @brief Generates a polygon mesh.
 * 
 * This function generates a mesh representing a polygon with a specified number of sides.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `int sides`: The number of sides of the polygon.
 *  - `float radius`: The radius of the polygon.
 * 
 * @return int Always returns 1 (Mesh result).
 * 
 * @usage
 * ```lua
 * local polygonMesh = raylib.GenMeshPoly(6, 2.0)
 * print("Generated hexagon mesh")
 * ```
 * 
 * @note This function is useful for creating shapes like triangles, pentagons, hexagons, etc.
 */
int lua_GenMeshPoly(lua_State *L);

/**
 * @brief Generates a hemisphere mesh.
 * 
 * This function generates a mesh representing a hemisphere.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `float radius`: The radius of the hemisphere.
 *  - `int rings`: The number of horizontal slices in the hemisphere.
 * 
 * @return int Always returns 1 (Mesh result).
 * 
 * @usage
 * ```lua
 * local hemisphereMesh = raylib.GenMeshHemiSphere(2.0, 16)
 * print("Generated hemisphere mesh")
 * ```
 * 
 * @note The hemisphere is a half-sphere, often used for skyboxes or ground objects.
 */
int lua_GenMeshHemiSphere(lua_State *L);

/**
 * @brief Generates a cylinder mesh.
 * 
 * This function generates a mesh representing a cylinder.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `float radius`: The radius of the base of the cylinder.
 *  - `float height`: The height of the cylinder.
 *  - `int slices`: The number of vertical divisions of the cylinder.
 *  - `int stacks`: The number of horizontal layers of the cylinder.
 * 
 * @return int Always returns 1 (Mesh result).
 * 
 * @usage
 * ```lua
 * local cylinderMesh = raylib.GenMeshCylinder(1.0, 3.0, 16, 4)
 * print("Generated cylinder mesh")
 * ```
 * 
 * @note This function generates a 3D mesh for cylindrical shapes. The slices determine the radial division, while stacks determine the vertical division.
 */
int lua_GenMeshCylinder(lua_State *L);

/**
 * @brief Generates a cone mesh.
 * 
 * This function generates a mesh representing a 3D cone shape.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `float radius`: The radius of the base of the cone.
 *  - `float height`: The height of the cone.
 *  - `int slices`: The number of vertical divisions of the cone.
 *  - `int stacks`: The number of horizontal layers of the cone.
 * 
 * @return int Always returns 1 (Mesh result).
 * 
 * @usage
 * ```lua
 * local coneMesh = raylib.GenMeshCone(1.0, 3.0, 16, 4)
 * print("Generated cone mesh")
 * ```
 * 
 * @note This function generates a 3D mesh for conical shapes. The slices determine the radial division, while stacks determine the vertical division.
 */
int lua_GenMeshCone(lua_State *L);

/**
 * @brief Generates a torus mesh.
 * 
 * This function generates a mesh representing a 3D torus (donut) shape.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `float radius`: The radius of the torus.
 *  - `float size`: The thickness of the torus.
 *  - `int radialSegments`: The number of radial segments.
 *  - `int sideSegments`: The number of sides for each segment.
 * 
 * @return int Always returns 1 (Mesh result).
 * 
 * @usage
 * ```lua
 * local torusMesh = raylib.GenMeshTorus(1.0, 0.5, 16, 16)
 * print("Generated torus mesh")
 * ```
 * 
 * @note The torus is a circular ring or donut-like shape. This function allows for control of radial and side segmentation.
 */
int lua_GenMeshTorus(lua_State *L);

/**
 * @brief Generates a knot mesh.
 * 
 * This function generates a mesh representing a 3D knot shape.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `float radius`: The radius of the knot.
 *  - `float size`: The thickness of the knot.
 *  - `int radialSegments`: The number of radial segments.
 *  - `int sideSegments`: The number of sides for each segment.
 * 
 * @return int Always returns 1 (Mesh result).
 * 
 * @usage
 * ```lua
 * local knotMesh = raylib.GenMeshKnot(1.0, 0.3, 16, 8)
 * print("Generated knot mesh")
 * ```
 * 
 * @note The knot is a 3D representation of a mathematical knot. This function allows control of the radius, size, and segmentation of the knot.
 */
int lua_GenMeshKnot(lua_State *L);

/**
 * @brief Generates a heightmap mesh.
 * 
 * This function generates a mesh from a heightmap image, where the brightness of the image's pixels determines the height of the vertices.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Image heightmap`: The heightmap image used to generate the mesh.
 *  - `Vector3 size`: The size of the generated mesh.
 * 
 * @return int Always returns 1 (Mesh result).
 * 
 * @usage
 * ```lua
 * local heightmapImage = raylib.LoadImage("heightmap.png")
 * local size = { x = 10.0, y = 2.0, z = 10.0 }
 * local heightmapMesh = raylib.GenMeshHeightmap(heightmapImage, size)
 * print("Generated heightmap mesh")
 * ```
 * 
 * @note This function is useful for generating terrain from grayscale images. Higher brightness values in the image produce higher vertices on the mesh.
 */
int lua_GenMeshHeightmap(lua_State *L);

/**
 * @brief Generates a cubicmap mesh.
 * 
 * This function generates a 3D mesh from a cubic map image where pixel colors represent the presence or absence of cubes.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Image cubicmap`: The image used to generate the cubic map. White pixels are converted to cubes, and black pixels are left as empty space.
 *  - `Vector3 cubeSize`: The size of the cubes in the generated map.
 * 
 * @return int Always returns 1 (Mesh result).
 * 
 * @usage
 * ```lua
 * local cubicmapImage = raylib.LoadImage("cubicmap.png")
 * local cubeSize = { x = 1.0, y = 1.0, z = 1.0 }
 * local cubicmapMesh = raylib.GenMeshCubicmap(cubicmapImage, cubeSize)
 * print("Generated cubicmap mesh")
 * ```
 * 
 * @note This function is useful for creating voxel-style worlds where each pixel in the image represents the presence of a cube in 3D space.
 */
int lua_GenMeshCubicmap(lua_State *L);

/**
 * @brief Loads materials from a file.
 * 
 * This function loads materials from an external file (e.g., an MTL file) and returns them as an array of materials.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `string fileName`: The path to the file containing the material definitions.
 * 
 * @return int Always returns 1 (Materials result).
 * 
 * @usage
 * ```lua
 * local materials = raylib.LoadMaterials("materials.mtl")
 * print("Loaded materials from file")
 * ```
 * 
 * @note The materials are used to apply textures, shaders, and other properties to 3D objects. They are commonly used with 3D models.
 */
int lua_LoadMaterials(lua_State *L);

/**
 * @brief Loads the default material.
 * 
 * This function returns a default material that can be used for basic 3D rendering.
 * 
 * @param L A pointer to the current Lua state. No arguments are required.
 * 
 * @return int Always returns 1 (Material result).
 * 
 * @usage
 * ```lua
 * local defaultMaterial = raylib.LoadMaterialDefault()
 * print("Loaded default material")
 * ```
 * 
 * @note This is useful when you need a simple material to apply to meshes without loading custom textures or shaders.
 */
int lua_LoadMaterialDefault(lua_State *L);

/**
 * @brief Checks if a material is valid.
 * 
 * This function checks if a given material is valid.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Material material`: The material to check for validity.
 * 
 * @return int Always returns 1 (boolean result).
 * 
 * @usage
 * ```lua
 * local material = raylib.LoadMaterialDefault()
 * local isValid = raylib.IsMaterialValid(material)
 * print("Is the material valid?", isValid)
 * ```
 * 
 * @note This function verifies if the provided material has been loaded correctly and is safe to use for rendering.
 */
int lua_IsMaterialValid(lua_State *L);

/**
 * @brief Unloads a material from memory.
 * 
 * This function releases the resources used by a material, including its textures and shaders.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Material material`: The material to unload from memory.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local material = raylib.LoadMaterialDefault()
 * raylib.UnloadMaterial(material)
 * print("Material unloaded")
 * ```
 * 
 * @note After unloading a material, it is no longer valid for use in rendering. Ensure that no meshes are referencing it.
 */
int lua_UnloadMaterial(lua_State *L);

/**
 * @brief Sets a texture for a material.
 * 
 * This function sets a texture for a material at the specified map index.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Material material`: The material to modify.
 *  - `int mapType`: The map type (e.g., diffuse, normal, specular) from `MaterialMapIndex`.
 *  - `Texture2D texture`: The texture to apply to the material.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local material = raylib.LoadMaterialDefault()
 * local texture = raylib.LoadTexture("diffuse.png")
 * raylib.SetMaterialTexture(material, raylib.MATERIAL_MAP_DIFFUSE, texture)
 * print("Texture set for material")
 * ```
 * 
 * @note This function allows you to change the appearance of a material by associating it with new textures.
 */
int lua_SetMaterialTexture(lua_State *L);

/**
 * @brief Sets the material for a model mesh.
 * 
 * This function sets the material for a specific mesh within a model.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Model model`: The model whose mesh material will be set.
 *  - `int meshIndex`: The index of the mesh within the model.
 *  - `int materialIndex`: The index of the material to use.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local model = raylib.LoadModel("model.obj")
 * local material = raylib.LoadMaterialDefault()
 * raylib.SetModelMeshMaterial(model, 0, 0)
 * print("Material set for model mesh")
 * ```
 * 
 * @note This function allows you to specify which material is used for individual meshes within a model.
 */
int lua_SetModelMeshMaterial(lua_State *L);

/**
 * @brief Loads model animations from a file.
 * 
 * This function loads all animations for a model from a specified file.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `string fileName`: The path to the file containing the model animations.
 * 
 * @return int Always returns 1 (ModelAnimations result).
 * 
 * @usage
 * ```lua
 * local animations = raylib.LoadModelAnimations("animations.iqm")
 * print("Loaded animations from file")
 * ```
 * 
 * @note This function is used to load animations for 3D models. The animations can be played or applied to the model at runtime.
 */
int lua_LoadModelAnimations(lua_State *L);

/**
 * @brief Unloads a model animation from memory.
 * 
 * This function releases the resources used by a single model animation.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `ModelAnimation animation`: The model animation to unload.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local animations = raylib.LoadModelAnimations("animations.iqm")
 * raylib.UnloadModelAnimation(animations[1])
 * print("Model animation unloaded")
 * ```
 * 
 * @note After unloading an animation, it is no longer valid for use. 
 */
int lua_UnloadModelAnimation(lua_State *L);

/**
 * @brief Unloads model animations from memory.
 * 
 * This function releases the resources used by all loaded model animations.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `ModelAnimation[] animations`: The array of model animations to unload.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local animations = raylib.LoadModelAnimations("animations.iqm")
 * raylib.UnloadModelAnimations(animations)
 * print("All model animations unloaded")
 * ```
 * 
 * @note This function is useful when you have loaded multiple animations and want to release all of them at once.
 */
int lua_UnloadModelAnimations(lua_State *L);

/**
 * @brief Checks if a model animation is valid.
 * 
 * This function verifies if the given model animation is valid.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `ModelAnimation animation`: The model animation to validate.
 * 
 * @return int Always returns 1 (boolean result).
 * 
 * @usage
 * ```lua
 * local animations = raylib.LoadModelAnimations("animations.iqm")
 * local isValid = raylib.IsModelAnimationValid(animations[1])
 * print("Is animation valid?", isValid)
 * ```
 * 
 * @note This function helps to ensure that a model animation is valid before attempting to use it.
 */
int lua_IsModelAnimationValid(lua_State *L);

/**
 * @brief Checks collision between two spheres.
 * 
 * This function checks if two spheres collide.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector3 center1`: The center position of the first sphere.
 *  - `float radius1`: The radius of the first sphere.
 *  - `Vector3 center2`: The center position of the second sphere.
 *  - `float radius2`: The radius of the second sphere.
 * 
 * @return int Always returns 1 (boolean result).
 * 
 * @usage
 * ```lua
 * local center1 = { x = 0, y = 0, z = 0 }
 * local center2 = { x = 1, y = 1, z = 1 }
 * local result = raylib.CheckCollisionSpheres(center1, 1.0, center2, 1.0)
 * print("Do spheres collide?", result)
 * ```
 * 
 * @note This function is useful for physics simulations and collision detection in 3D environments.
 */
int lua_CheckCollisionSpheres(lua_State *L);

/**
 * @brief Checks collision between two boxes.
 * 
 * This function checks if two 3D bounding boxes collide.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `BoundingBox box1`: The first bounding box.
 *  - `BoundingBox box2`: The second bounding box.
 * 
 * @return int Always returns 1 (boolean result).
 * 
 * @usage
 * ```lua
 * local box1 = { min = {x = 0, y = 0, z = 0}, max = {x = 2, y = 2, z = 2} }
 * local box2 = { min = {x = 1, y = 1, z = 1}, max = {x = 3, y = 3, z = 3} }
 * local result = raylib.CheckCollisionBoxes(box1, box2)
 * print("Do boxes collide?", result)
 * ```
 * 
 * @note Useful for 3D collision detection in physics simulations.
 */
int lua_CheckCollisionBoxes(lua_State *L);

/**
 * @brief Checks collision between a box and a sphere.
 * 
 * This function checks if a 3D bounding box and a sphere collide.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `BoundingBox box`: The bounding box.
 *  - `Vector3 center`: The center of the sphere.
 *  - `float radius`: The radius of the sphere.
 * 
 * @return int Always returns 1 (boolean result).
 * 
 * @usage
 * ```lua
 * local box = { min = {x = 0, y = 0, z = 0}, max = {x = 2, y = 2, z = 2} }
 * local center = { x = 1, y = 1, z = 1 }
 * local radius = 1.5
 * local result = raylib.CheckCollisionBoxSphere(box, center, radius)
 * print("Do box and sphere collide?", result)
 * ```
 * 
 * @note This function is useful for collision detection in 3D environments.
 */
int lua_CheckCollisionBoxSphere(lua_State *L);

/**
 * @brief Gets the collision information between a ray and a sphere.
 * 
 * This function checks if a ray intersects with a sphere and provides detailed collision information.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Ray ray`: The ray to check for collision.
 *  - `Vector3 center`: The center of the sphere.
 *  - `float radius`: The radius of the sphere.
 * 
 * @return int Always returns 1 (RayCollision result).
 * 
 * @usage
 * ```lua
 * local ray = { position = {x = 0, y = 0, z = 0}, direction = {x = 1, y = 1, z = 1} }
 * local center = { x = 3, y = 3, z = 3 }
 * local radius = 1.0
 * local collision = raylib.GetRayCollisionSphere(ray, center, radius)
 * print("Ray collision point:", collision.point)
 * print("Did ray hit sphere?", collision.hit)
 * ```
 * 
 * @note This function provides collision point, distance, and whether the collision occurred.
 */
int lua_GetRayCollisionSphere(lua_State *L);

/**
 * @brief Gets the collision information between a ray and a box.
 * 
 * This function checks if a ray intersects with a 3D bounding box and provides detailed collision information.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Ray ray`: The ray to check for collision.
 *  - `BoundingBox box`: The 3D bounding box to check for collision.
 * 
 * @return int Always returns 1 (RayCollision result).
 * 
 * @usage
 * ```lua
 * local ray = { position = {x = 0, y = 0, z = 0}, direction = {x = 1, y = 1, z = 1} }
 * local box = { min = {x = 2, y = 2, z = 2}, max = {x = 4, y = 4, z = 4} }
 * local collision = raylib.GetRayCollisionBox(ray, box)
 * print("Ray collision point:", collision.point)
 * print("Did ray hit box?", collision.hit)
 * ```
 * 
 * @note This function is useful for raycasting in 3D environments.
 */
int lua_GetRayCollisionBox(lua_State *L);

/**
 * @brief Gets the collision information between a ray and a mesh.
 * 
 * This function checks if a ray intersects with a mesh and provides detailed collision information.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Ray ray`: The ray to check for collision.
 *  - `Mesh mesh`: The mesh to check for collision.
 * 
 * @return int Always returns 1 (RayCollision result).
 * 
 * @usage
 * ```lua
 * local ray = { position = {x = 0, y = 0, z = 0}, direction = {x = 1, y = 1, z = 1} }
 * local mesh = raylib.LoadMesh("path/to/mesh.obj")
 * local collision = raylib.GetRayCollisionMesh(ray, mesh)
 * print("Ray collision point:", collision.point)
 * print("Did ray hit mesh?", collision.hit)
 * ```
 * 
 * @note This function provides collision point, distance, and hit status. It's useful for raycasting against 3D meshes.
 */
int lua_GetRayCollisionMesh(lua_State *L);

/**
 * @brief Gets the collision information between a ray and a triangle.
 * 
 * This function checks if a ray intersects with a triangle and provides detailed collision information.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Ray ray`: The ray to check for collision.
 *  - `Vector3 p1`: The first vertex of the triangle.
 *  - `Vector3 p2`: The second vertex of the triangle.
 *  - `Vector3 p3`: The third vertex of the triangle.
 * 
 * @return int Always returns 1 (RayCollision result).
 * 
 * @usage
 * ```lua
 * local ray = { position = {x = 0, y = 0, z = 0}, direction = {x = 1, y = 1, z = 1} }
 * local p1 = { x = 0, y = 0, z = 0 }
 * local p2 = { x = 1, y = 0, z = 0 }
 * local p3 = { x = 0, y = 1, z = 0 }
 * local collision = raylib.GetRayCollisionTriangle(ray, p1, p2, p3)
 * print("Ray collision point:", collision.point)
 * print("Did ray hit triangle?", collision.hit)
 * ```
 * 
 * @note This function is useful for precise collision checks with individual triangles in a mesh.
 */
int lua_GetRayCollisionTriangle(lua_State *L);

/**
 * @brief Gets the collision information between a ray and a quad.
 * 
 * This function checks if a ray intersects with a quad (a four-sided polygon) and provides detailed collision information.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `Ray ray`: The ray to check for collision.
 *  - `Vector3 p1`: The first vertex of the quad.
 *  - `Vector3 p2`: The second vertex of the quad.
 *  - `Vector3 p3`: The third vertex of the quad.
 *  - `Vector3 p4`: The fourth vertex of the quad.
 * 
 * @return int Always returns 1 (RayCollision result).
 * 
 * @usage
 * ```lua
 * local ray = { position = {x = 0, y = 0, z = 0}, direction = {x = 1, y = 1, z = 1} }
 * local p1 = { x = 0, y = 0, z = 0 }
 * local p2 = { x = 1, y = 0, z = 0 }
 * local p3 = { x = 1, y = 1, z = 0 }
 * local p4 = { x = 0, y = 1, z = 0 }
 * local collision = raylib.GetRayCollisionQuad(ray, p1, p2, p3, p4)
 * print("Ray collision point:", collision.point)
 * print("Did ray hit quad?", collision.hit)
 * ```
 * 
 * @note This function allows for collision detection against quads, useful for custom polygonal shapes.
 */
int lua_GetRayCollisionQuad(lua_State *L);

#endif