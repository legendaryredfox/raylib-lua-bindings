#ifndef LUA_RAYLIB_MODELS_H
#define LUA_RAYLIB_MODELS_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "raylib.h"

int lua_LoadModel(lua_State *L);
int lua_DrawModel(lua_State *L);
int lua_DrawModelEx(lua_State *L);
int lua_UnloadModel(lua_State *L);
int lua_UpdateModelAnimation(lua_State *L);
int lua_DrawMesh(lua_State *L);
int lua_UnloadMesh(lua_State *L);
int lua_GenMeshCube(lua_State *L);
int lua_GenMeshSphere(lua_State *L);
int lua_GenMeshPlane(lua_State *L);
int lua_DrawLine3D(lua_State *L);
int lua_DrawPoint3D(lua_State *L);
int lua_DrawCircle3D(lua_State *L);
int lua_DrawTriangle3D(lua_State *L);
int lua_DrawTriangleStrip3D(lua_State *L);
int lua_DrawCube(lua_State *L);
int lua_DrawCubeV(lua_State *L);
int lua_DrawCubeWires(lua_State *L);
int lua_DrawCubeWiresV(lua_State *L);
int lua_DrawSphereWires(lua_State *L);
int lua_DrawCylinder(lua_State *L);
int lua_DrawCylinderEx(lua_State *L);
int lua_DrawCylinderWires(lua_State *L);
int lua_DrawCylinderWiresEx(lua_State *L);
int lua_DrawCapsule(lua_State *L);
int lua_DrawCapsuleWires(lua_State *L);
int lua_DrawPlane(lua_State *L);
int lua_DrawRay(lua_State *L);
int lua_DrawGrid(lua_State *L);
int lua_LoadModelFromMesh(lua_State *L);
int lua_IsModelValid(lua_State *L);
int lua_GetModelBoundingBox(lua_State *L);
int lua_DrawBoundingBox(lua_State *L);
int lua_DrawBillboard(lua_State *L);
int lua_DrawBillboardRec(lua_State *L);
int lua_DrawBillboardPro(lua_State *L);
int lua_UploadMesh(lua_State *L);
int lua_UpdateMeshBuffer(lua_State *L);
int lua_GetMeshBoundingBox(lua_State *L);
int lua_GenMeshTangents(lua_State *L);
int lua_ExportMesh(lua_State *L);
int lua_ExportMeshAsCode(lua_State *L);
int lua_GenMeshPoly(lua_State *L);
int lua_GenMeshHemiSphere(lua_State *L);
int lua_GenMeshCylinder(lua_State *L);
int lua_GenMeshCone(lua_State *L);
int lua_GenMeshTorus(lua_State *L);
int lua_GenMeshKnot(lua_State *L);
int lua_GenMeshHeightmap(lua_State *L);
int lua_GenMeshCubicmap(lua_State *L);
int lua_LoadMaterials(lua_State *L);
int lua_LoadMaterialDefault(lua_State *L);
int lua_IsMaterialValid(lua_State *L);
int lua_UnloadMaterial(lua_State *L);
int lua_SetMaterialTexture(lua_State *L);
int lua_SetModelMeshMaterial(lua_State *L);
int lua_LoadModelAnimations(lua_State *L);
int lua_UnloadModelAnimation(lua_State *L);
int lua_UnloadModelAnimations(lua_State *L);
int lua_IsModelAnimationValid(lua_State *L);
int lua_CheckCollisionSpheres(lua_State *L);
int lua_CheckCollisionBoxes(lua_State *L);
int lua_CheckCollisionBoxSphere(lua_State *L);
int lua_GetRayCollisionSphere(lua_State *L);
int lua_GetRayCollisionBox(lua_State *L);
int lua_GetRayCollisionMesh(lua_State *L);
int lua_GetRayCollisionTriangle(lua_State *L);
int lua_GetRayCollisionQuad(lua_State *L);

#endif