
#include <raylib.h>
#include "lua_raylib_models.h"
#include "raylib_wrappers.h"

int lua_LoadModel(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    Model model = LoadModel(fileName);
    Model *pModel = lua_newuserdata(L, sizeof(Model));
    *pModel = model;
    luaL_setmetatable(L, "Model");
    return 1;
}

int lua_DrawModel(lua_State *L) {
    Model *model = luaL_checkudata(L, 1, "Model");
    Vector3 position = get_vector3_from_table(L, 2);
    float scale = luaL_checknumber(L, 3);
    Color color = get_color_from_table(L, 4);
    DrawModel(*model, position, scale, color);
    return 0;
}

int lua_DrawModelEx(lua_State *L) {
    Model *model = luaL_checkudata(L, 1, "Model");
    Vector3 position = get_vector3_from_table(L, 2);
    Vector3 rotationAxis = get_vector3_from_table(L, 3);
    float rotationAngle = luaL_checknumber(L, 4);
    Vector3 scale = get_vector3_from_table(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawModelEx(*model, position, rotationAxis, rotationAngle, scale, color);
    return 0;
}

int lua_UnloadModel(lua_State *L) {
    Model *model = luaL_checkudata(L, 1, "Model");
    UnloadModel(*model);
    return 0;
}

int lua_UpdateModelAnimation(lua_State *L) {
    Model *model = luaL_checkudata(L, 1, "Model");
    ModelAnimation *animation = luaL_checkudata(L, 2, "ModelAnimation");
    int frame = luaL_checkinteger(L, 3);
    UpdateModelAnimation(*model, *animation, frame);
    return 0;
}

int lua_DrawMesh(lua_State *L) {
    Mesh *mesh = luaL_checkudata(L, 1, "Mesh");
    Material *material = luaL_checkudata(L, 2, "Material");
    Matrix transform = get_matrix_from_table(L, 3);
    DrawMesh(*mesh, *material, transform);
    return 0;
}

int lua_UnloadMesh(lua_State *L) {
    Mesh *mesh = luaL_checkudata(L, 1, "Mesh");
    UnloadMesh(*mesh);
    return 0;
}

int lua_GenMeshCube(lua_State *L) {
    float width = luaL_checknumber(L, 1);
    float height = luaL_checknumber(L, 2);
    float length = luaL_checknumber(L, 3);
    Mesh cube = GenMeshCube(width, height, length);
    Mesh *pCube = lua_newuserdata(L, sizeof(Mesh));
    *pCube = cube;
    luaL_setmetatable(L, "Mesh");
    return 1;
}

int lua_GenMeshSphere(lua_State *L) {
    float radius = luaL_checknumber(L, 1);
    int rings = luaL_checkinteger(L, 2);
    int slices = luaL_checkinteger(L, 3);
    Mesh sphere = GenMeshSphere(radius, rings, slices);
    Mesh *pSphere = lua_newuserdata(L, sizeof(Mesh));
    *pSphere = sphere;
    luaL_setmetatable(L, "Mesh");
    return 1;
}

int lua_GenMeshPlane(lua_State *L) {
    float width = luaL_checknumber(L, 1);
    float length = luaL_checknumber(L, 2);
    int resX = luaL_checkinteger(L, 3);
    int resZ = luaL_checkinteger(L, 4);
    Mesh plane = GenMeshPlane(width, length, resX, resZ);
    Mesh *pPlane = lua_newuserdata(L, sizeof(Mesh));
    *pPlane = plane;
    luaL_setmetatable(L, "Mesh");
    return 1;
}

