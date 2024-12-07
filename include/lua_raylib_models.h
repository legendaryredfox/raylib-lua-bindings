#ifndef LUA_RAYLIB_MODELS_H
#define LUA_RAYLIB_MODELS_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "raylib.h"

/**
 * @brief Loads a model from a file.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Model result)
 */
int lua_LoadModel(lua_State *L);

/**
 * @brief Draws a model with default parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawModel(lua_State *L);

/**
 * @brief Draws a model with extended parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawModelEx(lua_State *L);

/**
 * @brief Unloads a model from memory.
 * 
 * @param L Lua state
 * @return int Always returns 0
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
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawMesh(lua_State *L);

/**
 * @brief Unloads a mesh from memory.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UnloadMesh(lua_State *L);

/**
 * @brief Generates a cube mesh.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Mesh result)
 */
int lua_GenMeshCube(lua_State *L);

/**
 * @brief Generates a sphere mesh.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Mesh result)
 */
int lua_GenMeshSphere(lua_State *L);

/**
 * @brief Generates a plane mesh.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Mesh result)
 */
int lua_GenMeshPlane(lua_State *L);

/**
 * @brief Draws a 3D line with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawLine3D(lua_State *L);

/**
 * @brief Draws a 3D point with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawPoint3D(lua_State *L);

/**
 * @brief Draws a 3D circle with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCircle3D(lua_State *L);

/**
 * @brief Draws a 3D triangle with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawTriangle3D(lua_State *L);

/**
 * @brief Draws a 3D triangle strip with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawTriangleStrip3D(lua_State *L);

/**
 * @brief Draws a cube with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCube(lua_State *L);

/**
 * @brief Draws a cube with specified parameters using a Vector3.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCubeV(lua_State *L);

/**
 * @brief Draws the wireframe of a cube with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCubeWires(lua_State *L);

/**
 * @brief Draws the wireframe of a cube with specified parameters using a Vector3.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCubeWiresV(lua_State *L);

/**
 * @brief Draws the wireframe of a sphere with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawSphereWires(lua_State *L);

/**
 * @brief Draws a cylinder with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCylinder(lua_State *L);

/**
 * @brief Draws a cylinder with extended parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCylinderEx(lua_State *L);

/**
 * @brief Draws the wireframe of a cylinder with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCylinderWires(lua_State *L);

/**
 * @brief Draws the wireframe of a cylinder with extended parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCylinderWiresEx(lua_State *L);

/**
 * @brief Draws a capsule with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCapsule(lua_State *L);

/**
 * @brief Draws the wireframe of a capsule with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCapsuleWires(lua_State *L);

/**
 * @brief Draws a plane with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawPlane(lua_State *L);

/**
 * @brief Draws a ray with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawRay(lua_State *L);

/**
 * @brief Draws a grid with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
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