
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

int lua_DrawLine3D(lua_State *L) {
    Vector3 startPos = get_vector3_from_table(L, 1);
    Vector3 endPos = get_vector3_from_table(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawLine3D(startPos, endPos, color);
    return 0;
}

int lua_DrawPoint3D(lua_State *L) {
    Vector3 position = get_vector3_from_table(L, 1);
    Color color = get_color_from_table(L, 2);
    DrawPoint3D(position, color);
    return 0;
}

int lua_DrawCircle3D(lua_State *L) {
    Vector3 center = get_vector3_from_table(L, 1);
    float radius = luaL_checknumber(L, 2);
    Vector3 rotationAxis = get_vector3_from_table(L, 3);
    float rotationAngle = luaL_checknumber(L, 4);
    Color color = get_color_from_table(L, 5);
    DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);
    return 0;
}

int lua_DrawTriangle3D(lua_State *L) {
    Vector3 v1 = get_vector3_from_table(L, 1);
    Vector3 v2 = get_vector3_from_table(L, 2);
    Vector3 v3 = get_vector3_from_table(L, 3);
    Color color = get_color_from_table(L, 4);
    DrawTriangle3D(v1, v2, v3, color);
    return 0;
}

int lua_DrawTriangleStrip3D(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int pointCount = lua_rawlen(L, 1);
    Vector3 *points = malloc(sizeof(Vector3) * pointCount);

    for (int i = 0; i < pointCount; i++) {
        lua_rawgeti(L, 1, i + 1);
        points[i] = get_vector3_from_table(L, -1);
        lua_pop(L, 1);
    }

    Color color = get_color_from_table(L, 2);
    DrawTriangleStrip3D(points, pointCount, color);

    free(points);
    return 0;
}

int lua_DrawCube(lua_State *L) {
    Vector3 position = get_vector3_from_table(L, 1);
    float width = luaL_checknumber(L, 2);
    float height = luaL_checknumber(L, 3);
    float length = luaL_checknumber(L, 4);
    Color color = get_color_from_table(L, 5);
    DrawCube(position, width, height, length, color);
    return 0;
}

int lua_DrawCubeV(lua_State *L) {
    Vector3 position = get_vector3_from_table(L, 1);
    Vector3 size = get_vector3_from_table(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawCubeV(position, size, color);
    return 0;
}

int lua_DrawCubeWires(lua_State *L) {
    Vector3 position = get_vector3_from_table(L, 1);
    float width = luaL_checknumber(L, 2);
    float height = luaL_checknumber(L, 3);
    float length = luaL_checknumber(L, 4);
    Color color = get_color_from_table(L, 5);
    DrawCubeWires(position, width, height, length, color);
    return 0;
}

int lua_DrawCubeWiresV(lua_State *L) {
    Vector3 position = get_vector3_from_table(L, 1);
    Vector3 size = get_vector3_from_table(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawCubeWiresV(position, size, color);
    return 0;
}

int lua_DrawSphereWires(lua_State *L) {
    Vector3 centerPos = get_vector3_from_table(L, 1);
    float radius = luaL_checknumber(L, 2);
    int rings = luaL_checkinteger(L, 3);
    int slices = luaL_checkinteger(L, 4);
    Color color = get_color_from_table(L, 5);
    DrawSphereWires(centerPos, radius, rings, slices, color);
    return 0;
}

int lua_DrawCylinder(lua_State *L) {
    Vector3 position = get_vector3_from_table(L, 1);
    float radiusTop = luaL_checknumber(L, 2);
    float radiusBottom = luaL_checknumber(L, 3);
    float height = luaL_checknumber(L, 4);
    int slices = luaL_checkinteger(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
    return 0;
}

int lua_DrawCylinderEx(lua_State *L) {
    Vector3 startPos = get_vector3_from_table(L, 1);
    Vector3 endPos = get_vector3_from_table(L, 2);
    float startRadius = luaL_checknumber(L, 3);
    float endRadius = luaL_checknumber(L, 4);
    int sides = luaL_checkinteger(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawCylinderEx(startPos, endPos, startRadius, endRadius, sides, color);
    return 0;
}

int lua_DrawCylinderWires(lua_State *L) {
    Vector3 position = get_vector3_from_table(L, 1);
    float radiusTop = luaL_checknumber(L, 2);
    float radiusBottom = luaL_checknumber(L, 3);
    float height = luaL_checknumber(L, 4);
    int slices = luaL_checkinteger(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
    return 0;
}

int lua_DrawCylinderWiresEx(lua_State *L) {
    Vector3 startPos = get_vector3_from_table(L, 1);
    Vector3 endPos = get_vector3_from_table(L, 2);
    float startRadius = luaL_checknumber(L, 3);
    float endRadius = luaL_checknumber(L, 4);
    int sides = luaL_checkinteger(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawCylinderWiresEx(startPos, endPos, startRadius, endRadius, sides, color);
    return 0;
}

int lua_DrawCapsule(lua_State *L) {
    Vector3 startPos = get_vector3_from_table(L, 1);
    Vector3 endPos = get_vector3_from_table(L, 2);
    float radius = luaL_checknumber(L, 3);
    int slices = luaL_checkinteger(L, 4);
    int rings = luaL_checkinteger(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawCapsule(startPos, endPos, radius, slices, rings, color);
    return 0;
}

int lua_DrawCapsuleWires(lua_State *L) {
    Vector3 startPos = get_vector3_from_table(L, 1);
    Vector3 endPos = get_vector3_from_table(L, 2);
    float radius = luaL_checknumber(L, 3);
    int slices = luaL_checkinteger(L, 4);
    int rings = luaL_checkinteger(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawCapsuleWires(startPos, endPos, radius, slices, rings, color);
    return 0;
}

int lua_DrawPlane(lua_State *L) {
    Vector3 centerPos = get_vector3_from_table(L, 1);
    Vector2 size = get_vector2_from_table(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawPlane(centerPos, size, color);
    return 0;
}

int lua_DrawRay(lua_State *L) {
    Ray ray = get_ray_from_table(L, 1);
    Color color = get_color_from_table(L, 2);
    DrawRay(ray, color);
    return 0;
}

int lua_DrawGrid(lua_State *L) {
    int slices = luaL_checkinteger(L, 1);
    float spacing = luaL_checknumber(L, 2);
    DrawGrid(slices, spacing);
    return 0;
}

int lua_LoadModelFromMesh(lua_State *L) {
    Mesh *mesh = luaL_checkudata(L, 1, "Mesh");
    Model model = LoadModelFromMesh(*mesh);
    Model *pModel = lua_newuserdata(L, sizeof(Model));
    *pModel = model;
    luaL_setmetatable(L, "Model");
    return 1;
}

int lua_IsModelValid(lua_State *L) {
    Model *model = luaL_checkudata(L, 1, "Model");
    lua_pushboolean(L, IsModelValid(*model));
    return 1;
}

int lua_GetModelBoundingBox(lua_State *L) {
    Model *model = luaL_checkudata(L, 1, "Model");
    BoundingBox bbox = GetModelBoundingBox(*model);

    lua_newtable(L);
    lua_pushstring(L, "min");
    push_vector3_to_table(L, bbox.min);
    lua_settable(L, -3);

    lua_pushstring(L, "max");
    push_vector3_to_table(L, bbox.max);
    lua_settable(L, -3);

    return 1;
}

int lua_DrawBoundingBox(lua_State *L) {
    BoundingBox bbox = get_bounding_box_from_table(L, 1);
    Color color = get_color_from_table(L, 2);
    DrawBoundingBox(bbox, color);
    return 0;
}

int lua_DrawBillboard(lua_State *L) {
    Camera *camera = luaL_checkudata(L, 1, "Camera");
    Texture2D *texture = luaL_checkudata(L, 2, "Texture2D");
    Vector3 position = get_vector3_from_table(L, 3);
    float scale = luaL_checknumber(L, 4);
    Color tint = get_color_from_table(L, 5);
    DrawBillboard(*camera, *texture, position, scale, tint);
    return 0;
}

int lua_DrawBillboardRec(lua_State *L) {
    Camera *camera = luaL_checkudata(L, 1, "Camera");
    Texture2D *texture = luaL_checkudata(L, 2, "Texture2D");
    Rectangle source = get_rectangle_from_table(L, 3);
    Vector3 position = get_vector3_from_table(L, 4);
    Vector2 size = get_vector2_from_table(L, 5);
    Color tint = get_color_from_table(L, 6);
    DrawBillboardRec(*camera, *texture, source, position, size, tint);
    return 0;
}

int lua_DrawBillboardPro(lua_State *L) {
    Camera *camera = luaL_checkudata(L, 1, "Camera");
    Texture2D *texture = luaL_checkudata(L, 2, "Texture2D");
    Rectangle source = get_rectangle_from_table(L, 3);
    Vector3 position = get_vector3_from_table(L, 4);
    Vector3 up = get_vector3_from_table(L, 5);
    Vector2 size = get_vector2_from_table(L, 6);
    Vector2 origin = get_vector2_from_table(L, 7);
    float rotation = luaL_checknumber(L, 8);
    Color tint = get_color_from_table(L, 9);
    DrawBillboardPro(*camera, *texture, source, position, up, size, origin, rotation, tint);
    return 0;
}

int lua_UploadMesh(lua_State *L) {
    Mesh *mesh = luaL_checkudata(L, 1, "Mesh");
    bool dynamic = lua_toboolean(L, 2);
    UploadMesh(mesh, dynamic);
    return 0;
}

int lua_UpdateMeshBuffer(lua_State *L) {
    Mesh *mesh = luaL_checkudata(L, 1, "Mesh");
    int index = luaL_checkinteger(L, 2);
    const void *data = lua_touserdata(L, 3);
    int dataSize = luaL_checkinteger(L, 4);
    int offset = luaL_checkinteger(L, 5);
    UpdateMeshBuffer(*mesh, index, data, dataSize, offset);
    return 0;
}

int lua_GetMeshBoundingBox(lua_State *L) {
    Mesh *mesh = luaL_checkudata(L, 1, "Mesh");
    BoundingBox bbox = GetMeshBoundingBox(*mesh);

    lua_newtable(L);
    lua_pushstring(L, "min");
    push_vector3_to_table(L, bbox.min);
    lua_settable(L, -3);

    lua_pushstring(L, "max");
    push_vector3_to_table(L, bbox.max);
    lua_settable(L, -3);

    return 1;
}

int lua_GenMeshTangents(lua_State *L) {
    Mesh *mesh = luaL_checkudata(L, 1, "Mesh");
    GenMeshTangents(mesh);
    return 0;
}

int lua_ExportMesh(lua_State *L) {
    Mesh *mesh = luaL_checkudata(L, 1, "Mesh");
    const char *fileName = luaL_checkstring(L, 2);
    bool success = ExportMesh(*mesh, fileName);
    lua_pushboolean(L, success);
    return 1;
}

int lua_ExportMeshAsCode(lua_State *L) {
    Mesh *mesh = luaL_checkudata(L, 1, "Mesh");
    const char *fileName = luaL_checkstring(L, 2);
    bool success = ExportMeshAsCode(*mesh, fileName);
    lua_pushboolean(L, success);
    return 1;
}

int lua_GenMeshPoly(lua_State *L) {
    int sides = luaL_checkinteger(L, 1);
    float radius = luaL_checknumber(L, 2);
    Mesh mesh = GenMeshPoly(sides, radius);
    Mesh *pMesh = lua_newuserdata(L, sizeof(Mesh));
    *pMesh = mesh;
    luaL_setmetatable(L, "Mesh");
    return 1;
}

int lua_GenMeshHemiSphere(lua_State *L) {
    float radius = luaL_checknumber(L, 1);
    int rings = luaL_checkinteger(L, 2);
    int slices = luaL_checkinteger(L, 3);
    Mesh mesh = GenMeshHemiSphere(radius, rings, slices);
    Mesh *pMesh = lua_newuserdata(L, sizeof(Mesh));
    *pMesh = mesh;
    luaL_setmetatable(L, "Mesh");
    return 1;
}

int lua_GenMeshCylinder(lua_State *L) {
    float radius = luaL_checknumber(L, 1);
    float height = luaL_checknumber(L, 2);
    int slices = luaL_checkinteger(L, 3);
    Mesh mesh = GenMeshCylinder(radius, height, slices);
    Mesh *pMesh = lua_newuserdata(L, sizeof(Mesh));
    *pMesh = mesh;
    luaL_setmetatable(L, "Mesh");
    return 1;
}

int lua_GenMeshCone(lua_State *L) {
    float radius = luaL_checknumber(L, 1);
    float height = luaL_checknumber(L, 2);
    int slices = luaL_checkinteger(L, 3);
    Mesh mesh = GenMeshCone(radius, height, slices);
    Mesh *pMesh = lua_newuserdata(L, sizeof(Mesh));
    *pMesh = mesh;
    luaL_setmetatable(L, "Mesh");
    return 1;
}

int lua_GenMeshTorus(lua_State *L) {
    float radius = luaL_checknumber(L, 1);
    float size = luaL_checknumber(L, 2);
    int radSeg = luaL_checkinteger(L, 3);
    int sides = luaL_checkinteger(L, 4);
    Mesh mesh = GenMeshTorus(radius, size, radSeg, sides);
    Mesh *pMesh = lua_newuserdata(L, sizeof(Mesh));
    *pMesh = mesh;
    luaL_setmetatable(L, "Mesh");
    return 1;
}

int lua_GenMeshKnot(lua_State *L) {
    float radius = luaL_checknumber(L, 1);
    float size = luaL_checknumber(L, 2);
    int radSeg = luaL_checkinteger(L, 3);
    int sides = luaL_checkinteger(L, 4);
    Mesh mesh = GenMeshKnot(radius, size, radSeg, sides);
    Mesh *pMesh = lua_newuserdata(L, sizeof(Mesh));
    *pMesh = mesh;
    luaL_setmetatable(L, "Mesh");
    return 1;
}

int lua_GenMeshHeightmap(lua_State *L) {
    Image *heightmap = luaL_checkudata(L, 1, "Image");
    Vector3 size = get_vector3_from_table(L, 2);
    Mesh mesh = GenMeshHeightmap(*heightmap, size);
    Mesh *pMesh = lua_newuserdata(L, sizeof(Mesh));
    *pMesh = mesh;
    luaL_setmetatable(L, "Mesh");
    return 1;
}

int lua_GenMeshCubicmap(lua_State *L) {
    Image *cubicmap = luaL_checkudata(L, 1, "Image");
    Vector3 cubeSize = get_vector3_from_table(L, 2);
    Mesh mesh = GenMeshCubicmap(*cubicmap, cubeSize);
    Mesh *pMesh = lua_newuserdata(L, sizeof(Mesh));
    *pMesh = mesh;
    luaL_setmetatable(L, "Mesh");
    return 1;
}

int lua_LoadMaterials(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    int materialCount;
    Material *materials = LoadMaterials(fileName, &materialCount);

    lua_newtable(L);
    for (int i = 0; i < materialCount; i++) {
        Material *pMaterial = lua_newuserdata(L, sizeof(Material));
        *pMaterial = materials[i];
        luaL_setmetatable(L, "Material");
        lua_rawseti(L, -2, i + 1);
    }
    UnloadMaterials(materials, materialCount);
    return 1;
}

int lua_LoadMaterialDefault(lua_State *L) {
    Material material = LoadMaterialDefault();
    Material *pMaterial = lua_newuserdata(L, sizeof(Material));
    *pMaterial = material;
    luaL_setmetatable(L, "Material");
    return 1;
}

int lua_IsMaterialValid(lua_State *L) {
    Material *material = luaL_checkudata(L, 1, "Material");
    lua_pushboolean(L, IsMaterialValid(*material));
    return 1;
}

int lua_UnloadMaterial(lua_State *L) {
    Material *material = luaL_checkudata(L, 1, "Material");
    UnloadMaterial(*material);
    return 0;
}

int lua_SetMaterialTexture(lua_State *L) {
    Material *material = luaL_checkudata(L, 1, "Material");
    int mapType = luaL_checkinteger(L, 2);
    Texture2D *texture = luaL_checkudata(L, 3, "Texture2D");
    SetMaterialTexture(material, mapType, *texture);
    return 0;
}

int lua_SetModelMeshMaterial(lua_State *L) {
    Model *model = luaL_checkudata(L, 1, "Model");
    int meshId = luaL_checkinteger(L, 2);
    int materialId = luaL_checkinteger(L, 3);
    SetModelMeshMaterial(model, meshId, materialId);
    return 0;
}

int lua_LoadModelAnimations(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    int animCount;
    ModelAnimation *animations = LoadModelAnimations(fileName, &animCount);

    lua_newtable(L);
    for (int i = 0; i < animCount; i++) {
        ModelAnimation *pAnim = lua_newuserdata(L, sizeof(ModelAnimation));
        *pAnim = animations[i];
        luaL_setmetatable(L, "ModelAnimation");
        lua_rawseti(L, -2, i + 1);
    }
    UnloadModelAnimations(animations, animCount);
    return 1;
}

int lua_UnloadModelAnimation(lua_State *L) {
    ModelAnimation *animation = luaL_checkudata(L, 1, "ModelAnimation");
    UnloadModelAnimation(*animation);
    return 0;
}

int lua_UnloadModelAnimations(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int animCount = lua_rawlen(L, 1);

    for (int i = 1; i <= animCount; i++) {
        lua_rawgeti(L, 1, i);
        ModelAnimation *animation = luaL_checkudata(L, -1, "ModelAnimation");
        UnloadModelAnimation(*animation);
        lua_pop(L, 1);
    }
    return 0;
}

int lua_IsModelAnimationValid(lua_State *L) {
    Model *model = luaL_checkudata(L, 1, "Model");
    ModelAnimation *animation = luaL_checkudata(L, 2, "ModelAnimation");
    lua_pushboolean(L, IsModelAnimationValid(*model, *animation));
    return 1;
}

int lua_CheckCollisionSpheres(lua_State *L) {
    Vector3 center1 = get_vector3_from_table(L, 1);
    float radius1 = luaL_checknumber(L, 2);
    Vector3 center2 = get_vector3_from_table(L, 3);
    float radius2 = luaL_checknumber(L, 4);
    lua_pushboolean(L, CheckCollisionSpheres(center1, radius1, center2, radius2));
    return 1;
}

int lua_CheckCollisionBoxes(lua_State *L) {
    BoundingBox box1 = get_bounding_box_from_table(L, 1);
    BoundingBox box2 = get_bounding_box_from_table(L, 2);
    lua_pushboolean(L, CheckCollisionBoxes(box1, box2));
    return 1;
}

int lua_CheckCollisionBoxSphere(lua_State *L) {
    BoundingBox box = get_bounding_box_from_table(L, 1);
    Vector3 center = get_vector3_from_table(L, 2);
    float radius = luaL_checknumber(L, 3);
    lua_pushboolean(L, CheckCollisionBoxSphere(box, center, radius));
    return 1;
}

int lua_GetRayCollisionSphere(lua_State *L) {
    Ray ray = get_ray_from_table(L, 1);
    Vector3 center = get_vector3_from_table(L, 2);
    float radius = luaL_checknumber(L, 3);
    RayCollision collision = GetRayCollisionSphere(ray, center, radius);

    lua_newtable(L);
    lua_pushstring(L, "hit");
    lua_pushboolean(L, collision.hit);
    lua_settable(L, -3);

    lua_pushstring(L, "distance");
    lua_pushnumber(L, collision.distance);
    lua_settable(L, -3);

    lua_pushstring(L, "point");
    push_vector3_to_table(L, collision.point);
    lua_settable(L, -3);

    lua_pushstring(L, "normal");
    push_vector3_to_table(L, collision.normal);
    lua_settable(L, -3);

    return 1;
}

int lua_GetRayCollisionBox(lua_State *L) {
    Ray ray = get_ray_from_table(L, 1);
    BoundingBox box = get_bounding_box_from_table(L, 2);
    RayCollision collision = GetRayCollisionBox(ray, box);

    lua_newtable(L);
    lua_pushstring(L, "hit");
    lua_pushboolean(L, collision.hit);
    lua_settable(L, -3);

    lua_pushstring(L, "distance");
    lua_pushnumber(L, collision.distance);
    lua_settable(L, -3);

    lua_pushstring(L, "point");
    push_vector3_to_table(L, collision.point);
    lua_settable(L, -3);

    lua_pushstring(L, "normal");
    push_vector3_to_table(L, collision.normal);
    lua_settable(L, -3);

    return 1;
}

int lua_GetRayCollisionMesh(lua_State *L) {
    Ray ray = get_ray_from_table(L, 1);
    Mesh *mesh = luaL_checkudata(L, 2, "Mesh");
    Matrix transform = get_matrix_from_table(L, 3);
    RayCollision collision = GetRayCollisionMesh(ray, *mesh, transform);

    lua_newtable(L);
    lua_pushstring(L, "hit");
    lua_pushboolean(L, collision.hit);
    lua_settable(L, -3);

    lua_pushstring(L, "distance");
    lua_pushnumber(L, collision.distance);
    lua_settable(L, -3);

    lua_pushstring(L, "point");
    push_vector3_to_table(L, collision.point);
    lua_settable(L, -3);

    lua_pushstring(L, "normal");
    push_vector3_to_table(L, collision.normal);
    lua_settable(L, -3);

    return 1;
}

int lua_GetRayCollisionTriangle(lua_State *L) {
    Ray ray = get_ray_from_table(L, 1);
    Vector3 p1 = get_vector3_from_table(L, 2);
    Vector3 p2 = get_vector3_from_table(L, 3);
    Vector3 p3 = get_vector3_from_table(L, 4);
    RayCollision collision = GetRayCollisionTriangle(ray, p1, p2, p3);

    lua_newtable(L);
    lua_pushstring(L, "hit");
    lua_pushboolean(L, collision.hit);
    lua_settable(L, -3);

    lua_pushstring(L, "distance");
    lua_pushnumber(L, collision.distance);
    lua_settable(L, -3);

    lua_pushstring(L, "point");
    push_vector3_to_table(L, collision.point);
    lua_settable(L, -3);

    lua_pushstring(L, "normal");
    push_vector3_to_table(L, collision.normal);
    lua_settable(L, -3);

    return 1;
}

int lua_GetRayCollisionQuad(lua_State *L) {
    Ray ray = get_ray_from_table(L, 1);
    Vector3 p1 = get_vector3_from_table(L, 2);
    Vector3 p2 = get_vector3_from_table(L, 3);
    Vector3 p3 = get_vector3_from_table(L, 4);
    Vector3 p4 = get_vector3_from_table(L, 5);
    RayCollision collision = GetRayCollisionQuad(ray, p1, p2, p3, p4);

    lua_newtable(L);
    lua_pushstring(L, "hit");
    lua_pushboolean(L, collision.hit);
    lua_settable(L, -3);

    lua_pushstring(L, "distance");
    lua_pushnumber(L, collision.distance);
    lua_settable(L, -3);

    lua_pushstring(L, "point");
    push_vector3_to_table(L, collision.point);
    lua_settable(L, -3);

    lua_pushstring(L, "normal");
    push_vector3_to_table(L, collision.normal);
    lua_settable(L, -3);

    return 1;
}
