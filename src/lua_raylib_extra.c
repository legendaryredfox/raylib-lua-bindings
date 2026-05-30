// lua_raylib_extra.c
//
// Additional raylib bindings filling the coverage gap documented in IMPLEMENT.md:
// render-state mode pairs, 3D/2D camera + coordinate transforms, shaders, audio
// playback control, 3D/2D draw extras, gamepad/gesture/touch input, filesystem,
// data (de)compression / base64, random sequences and a couple of text helpers.
//
// Everything here is registered onto the module table by register_extra(), which
// is called from luaopen_raylib after luaL_newlib(). All wrapper functions are
// static; only register_extra() is exported.

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "raylib.h"
#include <lua.h>
#include <lauxlib.h>
#include "raylib_wrappers.h"

// ---------------------------------------------------------------------------
// Local helpers
// ---------------------------------------------------------------------------

// Camera2D is passed from Lua as a plain table {offset, target, rotation, zoom}.
static Camera2D get_camera2d(lua_State *L, int idx) {
    luaL_checktype(L, idx, LUA_TTABLE);
    Camera2D c;
    lua_getfield(L, idx, "offset");   c.offset   = get_vector2_from_table(L, -1); lua_pop(L, 1);
    lua_getfield(L, idx, "target");   c.target   = get_vector2_from_table(L, -1); lua_pop(L, 1);
    lua_getfield(L, idx, "rotation"); c.rotation = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    lua_getfield(L, idx, "zoom");     c.zoom     = (float)luaL_checknumber(L, -1); lua_pop(L, 1);
    return c;
}

static void push_ray_to_table(lua_State *L, Ray ray) {
    lua_createtable(L, 0, 2);
    push_vector3_to_table(L, ray.position);  lua_setfield(L, -2, "position");
    push_vector3_to_table(L, ray.direction); lua_setfield(L, -2, "direction");
}

// Number of components for a shader uniform type.
static int shader_elem_count(int type) {
    switch (type) {
        case SHADER_UNIFORM_VEC2: case SHADER_UNIFORM_IVEC2: return 2;
        case SHADER_UNIFORM_VEC3: case SHADER_UNIFORM_IVEC3: return 3;
        case SHADER_UNIFORM_VEC4: case SHADER_UNIFORM_IVEC4: return 4;
        default: return 1; // FLOAT, INT, SAMPLER2D
    }
}

static int shader_is_int(int type) {
    return (type == SHADER_UNIFORM_INT  || type == SHADER_UNIFORM_IVEC2 ||
            type == SHADER_UNIFORM_IVEC3 || type == SHADER_UNIFORM_IVEC4 ||
            type == SHADER_UNIFORM_SAMPLER2D);
}

// ---------------------------------------------------------------------------
// Render-state mode pairs
// ---------------------------------------------------------------------------

static int lua_BeginMode2D(lua_State *L) { BeginMode2D(get_camera2d(L, 1)); return 0; }
static int lua_EndMode2D(lua_State *L)   { (void)L; EndMode2D(); return 0; }

static int lua_BeginMode3D(lua_State *L) {
    Camera *camera = luaL_checkudata(L, 1, "Camera");
    BeginMode3D(*camera);
    return 0;
}
static int lua_EndMode3D(lua_State *L) { (void)L; EndMode3D(); return 0; }

static int lua_BeginTextureMode(lua_State *L) {
    RenderTexture2D *target = luaL_checkudata(L, 1, "RenderTexture2D");
    BeginTextureMode(*target);
    return 0;
}
static int lua_EndTextureMode(lua_State *L) { (void)L; EndTextureMode(); return 0; }

static int lua_BeginShaderMode(lua_State *L) {
    Shader *shader = luaL_checkudata(L, 1, "Shader");
    BeginShaderMode(*shader);
    return 0;
}
static int lua_EndShaderMode(lua_State *L) { (void)L; EndShaderMode(); return 0; }

static int lua_BeginBlendMode(lua_State *L) {
    BeginBlendMode((int)luaL_checkinteger(L, 1));
    return 0;
}
static int lua_EndBlendMode(lua_State *L) { (void)L; EndBlendMode(); return 0; }

static int lua_BeginScissorMode(lua_State *L) {
    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    int w = (int)luaL_checkinteger(L, 3);
    int h = (int)luaL_checkinteger(L, 4);
    BeginScissorMode(x, y, w, h);
    return 0;
}
static int lua_EndScissorMode(lua_State *L) { (void)L; EndScissorMode(); return 0; }

// ---------------------------------------------------------------------------
// Camera (3D userdata "Camera") + coordinate transforms
// ---------------------------------------------------------------------------

// Constructor: builds a "Camera" userdata. Not a raylib function, but required
// so Lua can create a camera to pass to BeginMode3D / UpdateCamera / DrawBillboard.
static int lua_CreateCamera3D(lua_State *L) {
    Camera cam;
    cam.position   = get_vector3_from_table(L, 1);
    cam.target     = get_vector3_from_table(L, 2);
    cam.up         = get_vector3_from_table(L, 3);
    cam.fovy       = (float)luaL_checknumber(L, 4);
    cam.projection = (int)luaL_checkinteger(L, 5);
    Camera *p = (Camera *)lua_newuserdata(L, sizeof(Camera));
    *p = cam;
    luaL_setmetatable(L, "Camera");
    return 1;
}

static int lua_UpdateCamera(lua_State *L) {
    Camera *camera = luaL_checkudata(L, 1, "Camera");
    int mode = (int)luaL_checkinteger(L, 2);
    UpdateCamera(camera, mode);
    return 0;
}

static int lua_UpdateCameraPro(lua_State *L) {
    Camera *camera = luaL_checkudata(L, 1, "Camera");
    Vector3 movement = get_vector3_from_table(L, 2);
    Vector3 rotation = get_vector3_from_table(L, 3);
    float zoom = (float)luaL_checknumber(L, 4);
    UpdateCameraPro(camera, movement, rotation, zoom);
    return 0;
}

static int lua_GetCameraMatrix(lua_State *L) {
    Camera *camera = luaL_checkudata(L, 1, "Camera");
    push_matrix_to_table(L, GetCameraMatrix(*camera));
    return 1;
}

static int lua_GetCameraMatrix2D(lua_State *L) {
    push_matrix_to_table(L, GetCameraMatrix2D(get_camera2d(L, 1)));
    return 1;
}

static int lua_GetWorldToScreen(lua_State *L) {
    Vector3 position = get_vector3_from_table(L, 1);
    Camera *camera = luaL_checkudata(L, 2, "Camera");
    push_vector2_to_table(L, GetWorldToScreen(position, *camera));
    return 1;
}

static int lua_GetWorldToScreenEx(lua_State *L) {
    Vector3 position = get_vector3_from_table(L, 1);
    Camera *camera = luaL_checkudata(L, 2, "Camera");
    int width  = (int)luaL_checkinteger(L, 3);
    int height = (int)luaL_checkinteger(L, 4);
    push_vector2_to_table(L, GetWorldToScreenEx(position, *camera, width, height));
    return 1;
}

static int lua_GetWorldToScreen2D(lua_State *L) {
    Vector2 position = get_vector2_from_table(L, 1);
    Camera2D camera = get_camera2d(L, 2);
    push_vector2_to_table(L, GetWorldToScreen2D(position, camera));
    return 1;
}

static int lua_GetScreenToWorld2D(lua_State *L) {
    Vector2 position = get_vector2_from_table(L, 1);
    Camera2D camera = get_camera2d(L, 2);
    push_vector2_to_table(L, GetScreenToWorld2D(position, camera));
    return 1;
}

static int lua_GetScreenToWorldRay(lua_State *L) {
    Vector2 position = get_vector2_from_table(L, 1);
    Camera *camera = luaL_checkudata(L, 2, "Camera");
    push_ray_to_table(L, GetScreenToWorldRay(position, *camera));
    return 1;
}

static int lua_GetScreenToWorldRayEx(lua_State *L) {
    Vector2 position = get_vector2_from_table(L, 1);
    Camera *camera = luaL_checkudata(L, 2, "Camera");
    int width  = (int)luaL_checkinteger(L, 3);
    int height = (int)luaL_checkinteger(L, 4);
    push_ray_to_table(L, GetScreenToWorldRayEx(position, *camera, width, height));
    return 1;
}

// ---------------------------------------------------------------------------
// Shaders ("Shader" userdata)
// ---------------------------------------------------------------------------

static int lua_LoadShader(lua_State *L) {
    const char *vs = luaL_optstring(L, 1, NULL);
    const char *fs = luaL_optstring(L, 2, NULL);
    Shader shader = LoadShader(vs, fs);
    Shader *p = (Shader *)lua_newuserdata(L, sizeof(Shader));
    *p = shader;
    luaL_setmetatable(L, "Shader");
    return 1;
}

static int lua_LoadShaderFromMemory(lua_State *L) {
    const char *vs = luaL_optstring(L, 1, NULL);
    const char *fs = luaL_optstring(L, 2, NULL);
    Shader shader = LoadShaderFromMemory(vs, fs);
    Shader *p = (Shader *)lua_newuserdata(L, sizeof(Shader));
    *p = shader;
    luaL_setmetatable(L, "Shader");
    return 1;
}

static int lua_IsShaderValid(lua_State *L) {
    Shader *shader = luaL_checkudata(L, 1, "Shader");
    lua_pushboolean(L, IsShaderValid(*shader));
    return 1;
}

static int lua_GetShaderLocation(lua_State *L) {
    Shader *shader = luaL_checkudata(L, 1, "Shader");
    const char *name = luaL_checkstring(L, 2);
    lua_pushinteger(L, GetShaderLocation(*shader, name));
    return 1;
}

static int lua_GetShaderLocationAttrib(lua_State *L) {
    Shader *shader = luaL_checkudata(L, 1, "Shader");
    const char *name = luaL_checkstring(L, 2);
    lua_pushinteger(L, GetShaderLocationAttrib(*shader, name));
    return 1;
}

static int lua_SetShaderValue(lua_State *L) {
    Shader *shader = luaL_checkudata(L, 1, "Shader");
    int loc  = (int)luaL_checkinteger(L, 2);
    int type = (int)luaL_checkinteger(L, 4);
    int n = shader_elem_count(type);
    if (n > 4) n = 4;
    if (shader_is_int(type)) {
        int buf[4] = {0, 0, 0, 0};
        if (lua_istable(L, 3)) {
            for (int i = 0; i < n; i++) { lua_rawgeti(L, 3, i + 1); buf[i] = (int)luaL_checkinteger(L, -1); lua_pop(L, 1); }
        } else { buf[0] = (int)luaL_checkinteger(L, 3); }
        SetShaderValue(*shader, loc, buf, type);
    } else {
        float buf[4] = {0, 0, 0, 0};
        if (lua_istable(L, 3)) {
            for (int i = 0; i < n; i++) { lua_rawgeti(L, 3, i + 1); buf[i] = (float)luaL_checknumber(L, -1); lua_pop(L, 1); }
        } else { buf[0] = (float)luaL_checknumber(L, 3); }
        SetShaderValue(*shader, loc, buf, type);
    }
    return 0;
}

static int lua_SetShaderValueV(lua_State *L) {
    Shader *shader = luaL_checkudata(L, 1, "Shader");
    int loc   = (int)luaL_checkinteger(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    int type  = (int)luaL_checkinteger(L, 4);
    int count = (int)luaL_checkinteger(L, 5);
    int total = shader_elem_count(type) * count;
    if (total <= 0) return 0;
    if (shader_is_int(type)) {
        int *buf = (int *)malloc(sizeof(int) * total);
        for (int i = 0; i < total; i++) { lua_rawgeti(L, 3, i + 1); buf[i] = (int)luaL_checkinteger(L, -1); lua_pop(L, 1); }
        SetShaderValueV(*shader, loc, buf, type, count);
        free(buf);
    } else {
        float *buf = (float *)malloc(sizeof(float) * total);
        for (int i = 0; i < total; i++) { lua_rawgeti(L, 3, i + 1); buf[i] = (float)luaL_checknumber(L, -1); lua_pop(L, 1); }
        SetShaderValueV(*shader, loc, buf, type, count);
        free(buf);
    }
    return 0;
}

static int lua_SetShaderValueMatrix(lua_State *L) {
    Shader *shader = luaL_checkudata(L, 1, "Shader");
    int loc = (int)luaL_checkinteger(L, 2);
    Matrix mat = get_matrix_from_table(L, 3);
    SetShaderValueMatrix(*shader, loc, mat);
    return 0;
}

static int lua_SetShaderValueTexture(lua_State *L) {
    Shader *shader = luaL_checkudata(L, 1, "Shader");
    int loc = (int)luaL_checkinteger(L, 2);
    Texture2D *texture = luaL_checkudata(L, 3, "Texture2D");
    SetShaderValueTexture(*shader, loc, *texture);
    return 0;
}

static int lua_UnloadShader(lua_State *L) {
    Shader *shader = luaL_checkudata(L, 1, "Shader");
    UnloadShader(*shader);
    return 0;
}

// ---------------------------------------------------------------------------
// Audio playback control ("Sound" userdata)
// ---------------------------------------------------------------------------

static int lua_PauseSound(lua_State *L)  { Sound *s = luaL_checkudata(L, 1, "Sound"); PauseSound(*s);  return 0; }
static int lua_ResumeSound(lua_State *L) { Sound *s = luaL_checkudata(L, 1, "Sound"); ResumeSound(*s); return 0; }

static int lua_SetSoundVolume(lua_State *L) {
    Sound *s = luaL_checkudata(L, 1, "Sound");
    SetSoundVolume(*s, (float)luaL_checknumber(L, 2));
    return 0;
}
static int lua_SetSoundPitch(lua_State *L) {
    Sound *s = luaL_checkudata(L, 1, "Sound");
    SetSoundPitch(*s, (float)luaL_checknumber(L, 2));
    return 0;
}
static int lua_SetSoundPan(lua_State *L) {
    Sound *s = luaL_checkudata(L, 1, "Sound");
    SetSoundPan(*s, (float)luaL_checknumber(L, 2));
    return 0;
}

// ---------------------------------------------------------------------------
// 3D drawing extras
// ---------------------------------------------------------------------------

static int lua_DrawSphere(lua_State *L) {
    Vector3 center = get_vector3_from_table(L, 1);
    float radius = (float)luaL_checknumber(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawSphere(center, radius, color);
    return 0;
}

static int lua_DrawSphereEx(lua_State *L) {
    Vector3 center = get_vector3_from_table(L, 1);
    float radius = (float)luaL_checknumber(L, 2);
    int rings  = (int)luaL_checkinteger(L, 3);
    int slices = (int)luaL_checkinteger(L, 4);
    Color color = get_color_from_table(L, 5);
    DrawSphereEx(center, radius, rings, slices, color);
    return 0;
}

static int lua_DrawModelWires(lua_State *L) {
    Model *model = luaL_checkudata(L, 1, "Model");
    Vector3 position = get_vector3_from_table(L, 2);
    float scale = (float)luaL_checknumber(L, 3);
    Color tint = get_color_from_table(L, 4);
    DrawModelWires(*model, position, scale, tint);
    return 0;
}

static int lua_DrawModelWiresEx(lua_State *L) {
    Model *model = luaL_checkudata(L, 1, "Model");
    Vector3 position = get_vector3_from_table(L, 2);
    Vector3 rotationAxis = get_vector3_from_table(L, 3);
    float rotationAngle = (float)luaL_checknumber(L, 4);
    Vector3 scale = get_vector3_from_table(L, 5);
    Color tint = get_color_from_table(L, 6);
    DrawModelWiresEx(*model, position, rotationAxis, rotationAngle, scale, tint);
    return 0;
}

static int lua_DrawMeshInstanced(lua_State *L) {
    Mesh *mesh = luaL_checkudata(L, 1, "Mesh");
    Material *material = luaL_checkudata(L, 2, "Material");
    luaL_checktype(L, 3, LUA_TTABLE);
    int instances = (int)luaL_len(L, 3);
    if (instances <= 0) return 0;
    Matrix *transforms = (Matrix *)malloc(sizeof(Matrix) * instances);
    for (int i = 0; i < instances; i++) {
        lua_rawgeti(L, 3, i + 1);
        transforms[i] = get_matrix_from_table(L, -1);
        lua_pop(L, 1);
    }
    DrawMeshInstanced(*mesh, *material, transforms, instances);
    free(transforms);
    return 0;
}

// ---------------------------------------------------------------------------
// 2D drawing extras
// ---------------------------------------------------------------------------

static int lua_DrawTriangleFan(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int pointCount = (int)luaL_len(L, 1);
    Vector2 *points = get_vector2_array_from_table(L, 1);
    Color color = get_color_from_table(L, 2);
    DrawTriangleFan(points, pointCount, color);
    free(points);
    return 0;
}

static int lua_DrawRectangleRoundedLines(lua_State *L) {
    Rectangle rec = get_rectangle_from_table(L, 1);
    float roundness = (float)luaL_checknumber(L, 2);
    int segments = (int)luaL_checkinteger(L, 3);
    Color color = get_color_from_table(L, 4);
    DrawRectangleRoundedLines(rec, roundness, segments, color);
    return 0;
}

static int lua_DrawRectangleRoundedLinesEx(lua_State *L) {
    Rectangle rec = get_rectangle_from_table(L, 1);
    float roundness = (float)luaL_checknumber(L, 2);
    int segments = (int)luaL_checkinteger(L, 3);
    float lineThick = (float)luaL_checknumber(L, 4);
    Color color = get_color_from_table(L, 5);
    DrawRectangleRoundedLinesEx(rec, roundness, segments, lineThick, color);
    return 0;
}

// ---------------------------------------------------------------------------
// Window / system
// ---------------------------------------------------------------------------

static int lua_GetRenderWidth(lua_State *L)  { lua_pushinteger(L, GetRenderWidth());  return 1; }
static int lua_GetRenderHeight(lua_State *L) { lua_pushinteger(L, GetRenderHeight()); return 1; }
static int lua_GetWindowPosition(lua_State *L) { push_vector2_to_table(L, GetWindowPosition()); return 1; }
static int lua_WaitTime(lua_State *L)  { WaitTime((double)luaL_checknumber(L, 1)); return 0; }
static int lua_OpenURL(lua_State *L)   { OpenURL(luaL_checkstring(L, 1)); return 0; }
static int lua_SetExitKey(lua_State *L){ SetExitKey((int)luaL_checkinteger(L, 1)); return 0; }
static int lua_SwapScreenBuffer(lua_State *L) { (void)L; SwapScreenBuffer(); return 0; }
static int lua_PollInputEvents(lua_State *L)  { (void)L; PollInputEvents(); return 0; }

// ---------------------------------------------------------------------------
// Input: mouse extras, gamepad, gestures, touch
// ---------------------------------------------------------------------------

static int lua_GetMouseDelta(lua_State *L)      { push_vector2_to_table(L, GetMouseDelta());      return 1; }
static int lua_GetMouseWheelMoveV(lua_State *L) { push_vector2_to_table(L, GetMouseWheelMoveV()); return 1; }
static int lua_SetMouseCursor(lua_State *L)     { SetMouseCursor((int)luaL_checkinteger(L, 1));   return 0; }

static int lua_IsGamepadAvailable(lua_State *L) {
    lua_pushboolean(L, IsGamepadAvailable((int)luaL_checkinteger(L, 1)));
    return 1;
}
static int lua_GetGamepadName(lua_State *L) {
    lua_pushstring(L, GetGamepadName((int)luaL_checkinteger(L, 1)));
    return 1;
}
static int lua_IsGamepadButtonPressed(lua_State *L) {
    lua_pushboolean(L, IsGamepadButtonPressed((int)luaL_checkinteger(L, 1), (int)luaL_checkinteger(L, 2)));
    return 1;
}
static int lua_IsGamepadButtonDown(lua_State *L) {
    lua_pushboolean(L, IsGamepadButtonDown((int)luaL_checkinteger(L, 1), (int)luaL_checkinteger(L, 2)));
    return 1;
}
static int lua_IsGamepadButtonReleased(lua_State *L) {
    lua_pushboolean(L, IsGamepadButtonReleased((int)luaL_checkinteger(L, 1), (int)luaL_checkinteger(L, 2)));
    return 1;
}
static int lua_IsGamepadButtonUp(lua_State *L) {
    lua_pushboolean(L, IsGamepadButtonUp((int)luaL_checkinteger(L, 1), (int)luaL_checkinteger(L, 2)));
    return 1;
}
static int lua_GetGamepadButtonPressed(lua_State *L) {
    lua_pushinteger(L, GetGamepadButtonPressed());
    return 1;
}
static int lua_GetGamepadAxisCount(lua_State *L) {
    lua_pushinteger(L, GetGamepadAxisCount((int)luaL_checkinteger(L, 1)));
    return 1;
}
static int lua_GetGamepadAxisMovement(lua_State *L) {
    lua_pushnumber(L, GetGamepadAxisMovement((int)luaL_checkinteger(L, 1), (int)luaL_checkinteger(L, 2)));
    return 1;
}
static int lua_SetGamepadMappings(lua_State *L) {
    lua_pushinteger(L, SetGamepadMappings(luaL_checkstring(L, 1)));
    return 1;
}
static int lua_SetGamepadVibration(lua_State *L) {
    int gamepad = (int)luaL_checkinteger(L, 1);
    float left  = (float)luaL_checknumber(L, 2);
    float right = (float)luaL_checknumber(L, 3);
    float duration = (float)luaL_optnumber(L, 4, 0.0);
    SetGamepadVibration(gamepad, left, right, duration);
    return 0;
}

static int lua_SetGesturesEnabled(lua_State *L) {
    SetGesturesEnabled((unsigned int)luaL_checkinteger(L, 1));
    return 0;
}
static int lua_IsGestureDetected(lua_State *L) {
    lua_pushboolean(L, IsGestureDetected((unsigned int)luaL_checkinteger(L, 1)));
    return 1;
}
static int lua_GetGestureDetected(lua_State *L)     { lua_pushinteger(L, GetGestureDetected());     return 1; }
static int lua_GetGestureHoldDuration(lua_State *L) { lua_pushnumber(L, GetGestureHoldDuration());   return 1; }
static int lua_GetGestureDragVector(lua_State *L)   { push_vector2_to_table(L, GetGestureDragVector());  return 1; }
static int lua_GetGestureDragAngle(lua_State *L)    { lua_pushnumber(L, GetGestureDragAngle());      return 1; }
static int lua_GetGesturePinchVector(lua_State *L)  { push_vector2_to_table(L, GetGesturePinchVector()); return 1; }
static int lua_GetGesturePinchAngle(lua_State *L)   { lua_pushnumber(L, GetGesturePinchAngle());     return 1; }

static int lua_GetTouchX(lua_State *L)          { lua_pushinteger(L, GetTouchX());          return 1; }
static int lua_GetTouchY(lua_State *L)          { lua_pushinteger(L, GetTouchY());          return 1; }
static int lua_GetTouchPointCount(lua_State *L) { lua_pushinteger(L, GetTouchPointCount()); return 1; }
static int lua_GetTouchPointId(lua_State *L) {
    lua_pushinteger(L, GetTouchPointId((int)luaL_checkinteger(L, 1)));
    return 1;
}

// ---------------------------------------------------------------------------
// Filesystem & path utilities (window-free)
// ---------------------------------------------------------------------------

static int lua_FileExists(lua_State *L)      { lua_pushboolean(L, FileExists(luaL_checkstring(L, 1)));      return 1; }
static int lua_DirectoryExists(lua_State *L) { lua_pushboolean(L, DirectoryExists(luaL_checkstring(L, 1))); return 1; }
static int lua_IsPathFile(lua_State *L)      { lua_pushboolean(L, IsPathFile(luaL_checkstring(L, 1)));      return 1; }
static int lua_IsFileExtension(lua_State *L) {
    lua_pushboolean(L, IsFileExtension(luaL_checkstring(L, 1), luaL_checkstring(L, 2)));
    return 1;
}
static int lua_GetFileExtension(lua_State *L)      { lua_pushstring(L, GetFileExtension(luaL_checkstring(L, 1)));      return 1; }
static int lua_GetFileName(lua_State *L)           { lua_pushstring(L, GetFileName(luaL_checkstring(L, 1)));           return 1; }
static int lua_GetFileNameWithoutExt(lua_State *L) { lua_pushstring(L, GetFileNameWithoutExt(luaL_checkstring(L, 1))); return 1; }
static int lua_GetDirectoryPath(lua_State *L)      { lua_pushstring(L, GetDirectoryPath(luaL_checkstring(L, 1)));      return 1; }
static int lua_GetPrevDirectoryPath(lua_State *L)  { lua_pushstring(L, GetPrevDirectoryPath(luaL_checkstring(L, 1)));  return 1; }
static int lua_GetWorkingDirectory(lua_State *L)   { (void)L; lua_pushstring(L, GetWorkingDirectory());     return 1; }
static int lua_GetApplicationDirectory(lua_State *L){ (void)L; lua_pushstring(L, GetApplicationDirectory()); return 1; }
static int lua_ChangeDirectory(lua_State *L)       { lua_pushboolean(L, ChangeDirectory(luaL_checkstring(L, 1)));      return 1; }
static int lua_GetFileLength(lua_State *L)         { lua_pushinteger(L, GetFileLength(luaL_checkstring(L, 1)));        return 1; }
static int lua_GetFileModTime(lua_State *L)        { lua_pushinteger(L, (lua_Integer)GetFileModTime(luaL_checkstring(L, 1))); return 1; }

static int lua_LoadFileData(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    int dataSize = 0;
    unsigned char *data = LoadFileData(fileName, &dataSize);
    if (data == NULL) { lua_pushnil(L); return 1; }
    lua_pushlstring(L, (const char *)data, (size_t)dataSize);
    UnloadFileData(data);
    return 1;
}
// Data is returned to Lua as a string (owned by Lua); the raylib buffer is freed
// in LoadFileData already, so this is a safe no-op kept for API symmetry.
static int lua_UnloadFileData(lua_State *L) { (void)L; return 0; }

static int lua_SaveFileData(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    size_t dataSize;
    const char *data = luaL_checklstring(L, 2, &dataSize);
    lua_pushboolean(L, SaveFileData(fileName, (void *)data, (int)dataSize));
    return 1;
}

static int lua_LoadFileText(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    char *text = LoadFileText(fileName);
    if (text == NULL) { lua_pushnil(L); return 1; }
    lua_pushstring(L, text);
    UnloadFileText(text);
    return 1;
}
static int lua_UnloadFileText(lua_State *L) { (void)L; return 0; }

static int lua_SaveFileText(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    const char *text = luaL_checkstring(L, 2);
    lua_pushboolean(L, SaveFileText(fileName, (char *)text));
    return 1;
}

// ---------------------------------------------------------------------------
// Data compression / encoding (window-free)
// ---------------------------------------------------------------------------

static int lua_CompressData(lua_State *L) {
    size_t dataSize;
    const char *data = luaL_checklstring(L, 1, &dataSize);
    int compSize = 0;
    unsigned char *comp = CompressData((const unsigned char *)data, (int)dataSize, &compSize);
    if (comp == NULL) { lua_pushnil(L); return 1; }
    lua_pushlstring(L, (const char *)comp, (size_t)compSize);
    MemFree(comp);
    return 1;
}

static int lua_DecompressData(lua_State *L) {
    size_t compSize;
    const char *comp = luaL_checklstring(L, 1, &compSize);
    int dataSize = 0;
    unsigned char *data = DecompressData((const unsigned char *)comp, (int)compSize, &dataSize);
    if (data == NULL) { lua_pushnil(L); return 1; }
    lua_pushlstring(L, (const char *)data, (size_t)dataSize);
    MemFree(data);
    return 1;
}

static int lua_EncodeDataBase64(lua_State *L) {
    size_t dataSize;
    const char *data = luaL_checklstring(L, 1, &dataSize);
    int outputSize = 0;
    char *encoded = EncodeDataBase64((const unsigned char *)data, (int)dataSize, &outputSize);
    if (encoded == NULL) { lua_pushnil(L); return 1; }
    // raylib 6.0 includes the NUL terminator in outputSize; trim it so the Lua
    // string is exactly the base64 text (base64 has no embedded NUL bytes).
    size_t len = (size_t)outputSize;
    while (len > 0 && encoded[len - 1] == '\0') len--;
    lua_pushlstring(L, encoded, len);
    MemFree(encoded);
    return 1;
}

static int lua_DecodeDataBase64(lua_State *L) {
    const char *data = luaL_checkstring(L, 1);
    int outputSize = 0;
    unsigned char *decoded = DecodeDataBase64((const unsigned char *)data, &outputSize);
    if (decoded == NULL) { lua_pushnil(L); return 1; }
    lua_pushlstring(L, (const char *)decoded, (size_t)outputSize);
    MemFree(decoded);
    return 1;
}

// ---------------------------------------------------------------------------
// Random
// ---------------------------------------------------------------------------

static int lua_SetRandomSeed(lua_State *L) {
    SetRandomSeed((unsigned int)luaL_checkinteger(L, 1));
    return 0;
}

static int lua_LoadRandomSequence(lua_State *L) {
    unsigned int count = (unsigned int)luaL_checkinteger(L, 1);
    int min = (int)luaL_checkinteger(L, 2);
    int max = (int)luaL_checkinteger(L, 3);
    int *seq = LoadRandomSequence(count, min, max);
    lua_createtable(L, (int)count, 0);
    if (seq != NULL) {
        for (unsigned int i = 0; i < count; i++) {
            lua_pushinteger(L, seq[i]);
            lua_rawseti(L, -2, (lua_Integer)i + 1);
        }
        UnloadRandomSequence(seq);
    }
    return 1;
}
static int lua_UnloadRandomSequence(lua_State *L) { (void)L; return 0; }

// ---------------------------------------------------------------------------
// Text helpers (window-free)
// ---------------------------------------------------------------------------

static int lua_TextToInteger(lua_State *L) {
    lua_pushinteger(L, TextToInteger(luaL_checkstring(L, 1)));
    return 1;
}
static int lua_TextToFloat(lua_State *L) {
    lua_pushnumber(L, TextToFloat(luaL_checkstring(L, 1)));
    return 1;
}

// ---------------------------------------------------------------------------
// Logging
// ---------------------------------------------------------------------------

static int lua_TraceLog(lua_State *L) {
    int logLevel = (int)luaL_checkinteger(L, 1);
    const char *text = luaL_checkstring(L, 2);
    TraceLog(logLevel, "%s", text);   // pass through %s to avoid format-string injection
    return 0;
}
static int lua_SetTraceLogLevel(lua_State *L) {
    SetTraceLogLevel((int)luaL_checkinteger(L, 1));
    return 0;
}

// ---------------------------------------------------------------------------
// Directory listing (returns a Lua array of path strings; window-free)
// ---------------------------------------------------------------------------

static int lua_LoadDirectoryFiles(lua_State *L) {
    const char *dirPath = luaL_checkstring(L, 1);
    FilePathList list = LoadDirectoryFiles(dirPath);
    lua_createtable(L, (int)list.count, 0);
    for (unsigned int i = 0; i < list.count; i++) {
        lua_pushstring(L, list.paths[i]);
        lua_rawseti(L, -2, (lua_Integer)i + 1);
    }
    UnloadDirectoryFiles(list);
    return 1;
}

static int lua_LoadDirectoryFilesEx(lua_State *L) {
    const char *basePath = luaL_checkstring(L, 1);
    const char *filter = luaL_optstring(L, 2, NULL);
    bool scanSubdirs = lua_toboolean(L, 3);
    FilePathList list = LoadDirectoryFilesEx(basePath, filter, scanSubdirs);
    lua_createtable(L, (int)list.count, 0);
    for (unsigned int i = 0; i < list.count; i++) {
        lua_pushstring(L, list.paths[i]);
        lua_rawseti(L, -2, (lua_Integer)i + 1);
    }
    UnloadDirectoryFiles(list);
    return 1;
}
// Paths are returned as a Lua array (the FilePathList is freed immediately), so
// this is a safe no-op kept for API symmetry.
static int lua_UnloadDirectoryFiles(lua_State *L) { (void)L; return 0; }

// ---------------------------------------------------------------------------
// Export data as C array source code
// ---------------------------------------------------------------------------

static int lua_ExportDataAsCode(lua_State *L) {
    size_t dataSize;
    const char *data = luaL_checklstring(L, 1, &dataSize);
    const char *fileName = luaL_checkstring(L, 2);
    lua_pushboolean(L, ExportDataAsCode((const unsigned char *)data, (int)dataSize, fileName));
    return 1;
}

// ---------------------------------------------------------------------------
// Window icons (array of "Image" userdata)
// ---------------------------------------------------------------------------

static int lua_SetWindowIcons(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int count = (int)luaL_len(L, 1);
    if (count <= 0) { SetWindowIcons(NULL, 0); return 0; }
    Image *images = (Image *)malloc(sizeof(Image) * count);
    for (int i = 0; i < count; i++) {
        lua_rawgeti(L, 1, i + 1);
        Image *img = luaL_checkudata(L, -1, "Image");
        images[i] = *img;
        lua_pop(L, 1);
    }
    SetWindowIcons(images, count);   // raylib copies the pixel data internally
    free(images);
    return 0;
}

// ---------------------------------------------------------------------------
// Music stream from an in-memory buffer ("Music" userdata)
// ---------------------------------------------------------------------------

static int lua_LoadMusicStreamFromMemory(lua_State *L) {
    const char *fileType = luaL_checkstring(L, 1);
    size_t dataSize;
    const char *data = luaL_checklstring(L, 2, &dataSize);
    Music music = LoadMusicStreamFromMemory(fileType, (const unsigned char *)data, (int)dataSize);
    Music *p = (Music *)lua_newuserdata(L, sizeof(Music));
    *p = music;
    luaL_setmetatable(L, "Music");
    return 1;
}

// ---------------------------------------------------------------------------
// VR stereo ("VrStereoConfig" userdata; VrDeviceInfo passed as a table)
// ---------------------------------------------------------------------------

static VrDeviceInfo get_vrdeviceinfo(lua_State *L, int idx) {
    luaL_checktype(L, idx, LUA_TTABLE);
    VrDeviceInfo d = {0};
    lua_getfield(L, idx, "hResolution");            d.hResolution            = (int)luaL_optinteger(L, -1, 0); lua_pop(L, 1);
    lua_getfield(L, idx, "vResolution");            d.vResolution            = (int)luaL_optinteger(L, -1, 0); lua_pop(L, 1);
    lua_getfield(L, idx, "hScreenSize");            d.hScreenSize            = (float)luaL_optnumber(L, -1, 0.0); lua_pop(L, 1);
    lua_getfield(L, idx, "vScreenSize");            d.vScreenSize            = (float)luaL_optnumber(L, -1, 0.0); lua_pop(L, 1);
    lua_getfield(L, idx, "eyeToScreenDistance");    d.eyeToScreenDistance    = (float)luaL_optnumber(L, -1, 0.0); lua_pop(L, 1);
    lua_getfield(L, idx, "lensSeparationDistance"); d.lensSeparationDistance = (float)luaL_optnumber(L, -1, 0.0); lua_pop(L, 1);
    lua_getfield(L, idx, "interpupillaryDistance"); d.interpupillaryDistance = (float)luaL_optnumber(L, -1, 0.0); lua_pop(L, 1);
    lua_getfield(L, idx, "lensDistortionValues");
    if (lua_istable(L, -1)) for (int i = 0; i < 4; i++) { lua_rawgeti(L, -1, i + 1); d.lensDistortionValues[i] = (float)luaL_optnumber(L, -1, 0.0); lua_pop(L, 1); }
    lua_pop(L, 1);
    lua_getfield(L, idx, "chromaAbCorrection");
    if (lua_istable(L, -1)) for (int i = 0; i < 4; i++) { lua_rawgeti(L, -1, i + 1); d.chromaAbCorrection[i] = (float)luaL_optnumber(L, -1, 0.0); lua_pop(L, 1); }
    lua_pop(L, 1);
    return d;
}

static int lua_LoadVrStereoConfig(lua_State *L) {
    VrDeviceInfo device = get_vrdeviceinfo(L, 1);
    VrStereoConfig config = LoadVrStereoConfig(device);
    VrStereoConfig *p = (VrStereoConfig *)lua_newuserdata(L, sizeof(VrStereoConfig));
    *p = config;
    luaL_setmetatable(L, "VrStereoConfig");
    return 1;
}

static int lua_UnloadVrStereoConfig(lua_State *L) {
    VrStereoConfig *config = luaL_checkudata(L, 1, "VrStereoConfig");
    UnloadVrStereoConfig(*config);
    return 0;
}

static int lua_BeginVrStereoMode(lua_State *L) {
    VrStereoConfig *config = luaL_checkudata(L, 1, "VrStereoConfig");
    BeginVrStereoMode(*config);
    return 0;
}
static int lua_EndVrStereoMode(lua_State *L) { (void)L; EndVrStereoMode(); return 0; }

// ---------------------------------------------------------------------------
// Automation events ("AutomationEventList" userdata)
// ---------------------------------------------------------------------------

static int lua_LoadAutomationEventList(lua_State *L) {
    const char *fileName = luaL_optstring(L, 1, NULL);   // NULL → empty list for recording
    AutomationEventList list = LoadAutomationEventList(fileName);
    AutomationEventList *p = (AutomationEventList *)lua_newuserdata(L, sizeof(AutomationEventList));
    *p = list;
    luaL_setmetatable(L, "AutomationEventList");
    return 1;
}

static int lua_UnloadAutomationEventList(lua_State *L) {
    AutomationEventList *list = luaL_checkudata(L, 1, "AutomationEventList");
    UnloadAutomationEventList(*list);
    return 0;
}

static int lua_ExportAutomationEventList(lua_State *L) {
    AutomationEventList *list = luaL_checkudata(L, 1, "AutomationEventList");
    const char *fileName = luaL_checkstring(L, 2);
    lua_pushboolean(L, ExportAutomationEventList(*list, fileName));
    return 1;
}

static int lua_SetAutomationEventList(lua_State *L) {
    AutomationEventList *list = luaL_checkudata(L, 1, "AutomationEventList");
    SetAutomationEventList(list);   // raylib keeps this pointer; keep the userdata alive in Lua
    return 0;
}

static int lua_SetAutomationEventBaseFrame(lua_State *L) {
    SetAutomationEventBaseFrame((int)luaL_checkinteger(L, 1));
    return 0;
}

static int lua_StartAutomationEventRecording(lua_State *L) { (void)L; StartAutomationEventRecording(); return 0; }
static int lua_StopAutomationEventRecording(lua_State *L)  { (void)L; StopAutomationEventRecording();  return 0; }

// Accessor (not a raylib function): number of recorded events in a list.
static int lua_GetAutomationEventCount(lua_State *L) {
    AutomationEventList *list = luaL_checkudata(L, 1, "AutomationEventList");
    lua_pushinteger(L, (lua_Integer)list->count);
    return 1;
}

// raylib's PlayAutomationEvent takes a single AutomationEvent; from Lua we
// address it by (list, index) since events live inside the list userdata.
static int lua_PlayAutomationEvent(lua_State *L) {
    AutomationEventList *list = luaL_checkudata(L, 1, "AutomationEventList");
    lua_Integer index = luaL_checkinteger(L, 2);
    if (index < 0 || (unsigned int)index >= list->count)
        return luaL_error(L, "PlayAutomationEvent: index %d out of range [0,%d)", (int)index, (int)list->count);
    PlayAutomationEvent(list->events[index]);
    return 0;
}

// ---------------------------------------------------------------------------
// Text lines: LoadTextLines (bound elsewhere) returns a Lua table, so the
// matching unload has nothing raw to free — safe no-op for API symmetry.
// ---------------------------------------------------------------------------
static int lua_UnloadTextLines(lua_State *L) { (void)L; return 0; }

// ===========================================================================
// File I/O & trace-log callbacks
//
// Each Set*Callback stores the Lua function in the registry and installs a C
// trampoline that forwards to it through the shared globalLuaState. Passing nil
// clears the callback and restores raylib's default behavior.
// ===========================================================================

extern lua_State *globalLuaState;   // set in luaopen_raylib (src/lua_raylib.c)

static int traceLogRef     = LUA_NOREF;
static int loadFileDataRef = LUA_NOREF;
static int saveFileDataRef = LUA_NOREF;
static int loadFileTextRef = LUA_NOREF;
static int saveFileTextRef = LUA_NOREF;

static void trace_log_trampoline(int logLevel, const char *text, va_list args) {
    lua_State *L = globalLuaState;
    if (L == NULL || traceLogRef == LUA_NOREF) return;
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), text, args);
    lua_rawgeti(L, LUA_REGISTRYINDEX, traceLogRef);
    lua_pushinteger(L, logLevel);
    lua_pushstring(L, buffer);
    if (lua_pcall(L, 2, 0, 0) != LUA_OK) lua_pop(L, 1);   // swallow errors; never break logging
}

static unsigned char *load_file_data_trampoline(const char *fileName, int *dataSize) {
    lua_State *L = globalLuaState;
    if (dataSize) *dataSize = 0;
    if (L == NULL || loadFileDataRef == LUA_NOREF) return NULL;
    lua_rawgeti(L, LUA_REGISTRYINDEX, loadFileDataRef);
    lua_pushstring(L, fileName);
    if (lua_pcall(L, 1, 1, 0) != LUA_OK) { lua_pop(L, 1); return NULL; }
    if (lua_type(L, -1) != LUA_TSTRING) { lua_pop(L, 1); return NULL; }
    size_t len; const char *s = lua_tolstring(L, -1, &len);
    unsigned char *buf = (unsigned char *)MemAlloc((unsigned int)len);   // raylib frees this with MemFree
    if (buf != NULL) { memcpy(buf, s, len); if (dataSize) *dataSize = (int)len; }
    lua_pop(L, 1);
    return buf;
}

static char *load_file_text_trampoline(const char *fileName) {
    lua_State *L = globalLuaState;
    if (L == NULL || loadFileTextRef == LUA_NOREF) return NULL;
    lua_rawgeti(L, LUA_REGISTRYINDEX, loadFileTextRef);
    lua_pushstring(L, fileName);
    if (lua_pcall(L, 1, 1, 0) != LUA_OK) { lua_pop(L, 1); return NULL; }
    if (lua_type(L, -1) != LUA_TSTRING) { lua_pop(L, 1); return NULL; }
    size_t len; const char *s = lua_tolstring(L, -1, &len);
    char *buf = (char *)MemAlloc((unsigned int)len + 1);
    if (buf != NULL) { memcpy(buf, s, len); buf[len] = '\0'; }
    lua_pop(L, 1);
    return buf;
}

static bool save_file_data_trampoline(const char *fileName, void *data, int dataSize) {
    lua_State *L = globalLuaState;
    if (L == NULL || saveFileDataRef == LUA_NOREF) return false;
    lua_rawgeti(L, LUA_REGISTRYINDEX, saveFileDataRef);
    lua_pushstring(L, fileName);
    lua_pushlstring(L, (const char *)data, (size_t)dataSize);
    if (lua_pcall(L, 2, 1, 0) != LUA_OK) { lua_pop(L, 1); return false; }
    bool ok = lua_toboolean(L, -1);
    lua_pop(L, 1);
    return ok;
}

static bool save_file_text_trampoline(const char *fileName, const char *text) {
    lua_State *L = globalLuaState;
    if (L == NULL || saveFileTextRef == LUA_NOREF) return false;
    lua_rawgeti(L, LUA_REGISTRYINDEX, saveFileTextRef);
    lua_pushstring(L, fileName);
    lua_pushstring(L, text);
    if (lua_pcall(L, 2, 1, 0) != LUA_OK) { lua_pop(L, 1); return false; }
    bool ok = lua_toboolean(L, -1);
    lua_pop(L, 1);
    return ok;
}

// Rebind one callback slot from Lua stack position 1. Returns 1 if the caller
// should install a NULL (cleared) callback, 0 if it should install the trampoline.
static int set_callback_slot(lua_State *L, int *ref) {
    if (*ref != LUA_NOREF) { luaL_unref(L, LUA_REGISTRYINDEX, *ref); *ref = LUA_NOREF; }
    if (lua_isnoneornil(L, 1)) return 1;
    luaL_checktype(L, 1, LUA_TFUNCTION);
    lua_pushvalue(L, 1);
    *ref = luaL_ref(L, LUA_REGISTRYINDEX);
    return 0;
}

static int lua_SetTraceLogCallback(lua_State *L) {
    if (set_callback_slot(L, &traceLogRef)) SetTraceLogCallback(NULL);
    else SetTraceLogCallback(trace_log_trampoline);
    return 0;
}
static int lua_SetLoadFileDataCallback(lua_State *L) {
    if (set_callback_slot(L, &loadFileDataRef)) SetLoadFileDataCallback(NULL);
    else SetLoadFileDataCallback(load_file_data_trampoline);
    return 0;
}
static int lua_SetSaveFileDataCallback(lua_State *L) {
    if (set_callback_slot(L, &saveFileDataRef)) SetSaveFileDataCallback(NULL);
    else SetSaveFileDataCallback(save_file_data_trampoline);
    return 0;
}
static int lua_SetLoadFileTextCallback(lua_State *L) {
    if (set_callback_slot(L, &loadFileTextRef)) SetLoadFileTextCallback(NULL);
    else SetLoadFileTextCallback(load_file_text_trampoline);
    return 0;
}
static int lua_SetSaveFileTextCallback(lua_State *L) {
    if (set_callback_slot(L, &saveFileTextRef)) SetSaveFileTextCallback(NULL);
    else SetSaveFileTextCallback(save_file_text_trampoline);
    return 0;
}

// ===========================================================================
// Raw memory — operates on raylib-owned buffers as light userdata pointers.
// Advanced/interop use only; ordinary Lua code never needs these.
// ===========================================================================

static int lua_MemAlloc(lua_State *L) {
    void *p = MemAlloc((unsigned int)luaL_checkinteger(L, 1));
    if (p) lua_pushlightuserdata(L, p); else lua_pushnil(L);
    return 1;
}
static int lua_MemRealloc(lua_State *L) {
    void *p = MemRealloc(lua_touserdata(L, 1), (unsigned int)luaL_checkinteger(L, 2));
    if (p) lua_pushlightuserdata(L, p); else lua_pushnil(L);
    return 1;
}
static int lua_MemFree(lua_State *L) {
    MemFree(lua_touserdata(L, 1));
    return 0;
}

// ===========================================================================
// Drag-and-drop files (needs a window; returns a Lua array of dropped paths)
// ===========================================================================

static int lua_IsFileDropped(lua_State *L) {
    lua_pushboolean(L, IsFileDropped());
    return 1;
}
static int lua_LoadDroppedFiles(lua_State *L) {
    FilePathList list = LoadDroppedFiles();
    lua_createtable(L, (int)list.count, 0);
    for (unsigned int i = 0; i < list.count; i++) {
        lua_pushstring(L, list.paths[i]);
        lua_rawseti(L, -2, (lua_Integer)i + 1);
    }
    UnloadDroppedFiles(list);
    return 1;
}
static int lua_UnloadDroppedFiles(lua_State *L) { (void)L; return 0; }   // paths returned as a Lua table

// ===========================================================================
// Font atlas internals — "GlyphInfoArray" userdata holds the raw glyph array
// produced by LoadFontData and consumed by GenImageFontAtlas / UnloadFontData.
// ===========================================================================

typedef struct { GlyphInfo *glyphs; int count; } GlyphInfoArray;

static int lua_LoadFontData(lua_State *L) {
    size_t dataSize;
    const char *fileData = luaL_checklstring(L, 1, &dataSize);
    int fontSize = (int)luaL_checkinteger(L, 2);
    int type = (int)luaL_optinteger(L, 4, 0);     // arg 3 = optional codepoints array
    int *codepoints = NULL; int codepointCount = 0;
    if (lua_istable(L, 3)) {
        codepointCount = (int)luaL_len(L, 3);
        if (codepointCount > 0) {
            codepoints = (int *)malloc(sizeof(int) * codepointCount);
            for (int i = 0; i < codepointCount; i++) { lua_rawgeti(L, 3, i + 1); codepoints[i] = (int)luaL_checkinteger(L, -1); lua_pop(L, 1); }
        }
    }
    int glyphCount = 0;
    GlyphInfo *glyphs = LoadFontData((const unsigned char *)fileData, (int)dataSize, fontSize, codepoints, codepointCount, type, &glyphCount);
    free(codepoints);
    GlyphInfoArray *arr = (GlyphInfoArray *)lua_newuserdata(L, sizeof(GlyphInfoArray));
    arr->glyphs = glyphs;
    arr->count = glyphCount;   // raylib reports the actual glyph count
    luaL_setmetatable(L, "GlyphInfoArray");
    return 1;
}

static int lua_GenImageFontAtlas(lua_State *L) {
    GlyphInfoArray *arr = luaL_checkudata(L, 1, "GlyphInfoArray");
    int fontSize   = (int)luaL_checkinteger(L, 2);
    int padding    = (int)luaL_checkinteger(L, 3);
    int packMethod = (int)luaL_checkinteger(L, 4);
    Rectangle *recs = NULL;
    Image image = GenImageFontAtlas(arr->glyphs, &recs, arr->count, fontSize, padding, packMethod);
    push_image_to_userdata(L, image);
    lua_createtable(L, arr->count, 0);
    if (recs != NULL) {
        for (int i = 0; i < arr->count; i++) { push_rectangle_to_table(L, recs[i]); lua_rawseti(L, -2, i + 1); }
        MemFree(recs);
    }
    return 2;   // image, recsTable
}

static int lua_UnloadFontData(lua_State *L) {
    GlyphInfoArray *arr = luaL_checkudata(L, 1, "GlyphInfoArray");
    if (arr->glyphs != NULL) { UnloadFontData(arr->glyphs, arr->count); arr->glyphs = NULL; arr->count = 0; }
    return 0;
}

// ---------------------------------------------------------------------------
// Registration
// ---------------------------------------------------------------------------

static const luaL_Reg extra_functions[] = {
    // Mode pairs
    {"BeginMode2D", lua_BeginMode2D}, {"EndMode2D", lua_EndMode2D},
    {"BeginMode3D", lua_BeginMode3D}, {"EndMode3D", lua_EndMode3D},
    {"BeginTextureMode", lua_BeginTextureMode}, {"EndTextureMode", lua_EndTextureMode},
    {"BeginShaderMode", lua_BeginShaderMode}, {"EndShaderMode", lua_EndShaderMode},
    {"BeginBlendMode", lua_BeginBlendMode}, {"EndBlendMode", lua_EndBlendMode},
    {"BeginScissorMode", lua_BeginScissorMode}, {"EndScissorMode", lua_EndScissorMode},
    // Camera + transforms
    {"CreateCamera3D", lua_CreateCamera3D},
    {"UpdateCamera", lua_UpdateCamera}, {"UpdateCameraPro", lua_UpdateCameraPro},
    {"GetCameraMatrix", lua_GetCameraMatrix}, {"GetCameraMatrix2D", lua_GetCameraMatrix2D},
    {"GetWorldToScreen", lua_GetWorldToScreen}, {"GetWorldToScreenEx", lua_GetWorldToScreenEx},
    {"GetWorldToScreen2D", lua_GetWorldToScreen2D}, {"GetScreenToWorld2D", lua_GetScreenToWorld2D},
    {"GetScreenToWorldRay", lua_GetScreenToWorldRay}, {"GetScreenToWorldRayEx", lua_GetScreenToWorldRayEx},
    // Shaders
    {"LoadShader", lua_LoadShader}, {"LoadShaderFromMemory", lua_LoadShaderFromMemory},
    {"IsShaderValid", lua_IsShaderValid}, {"UnloadShader", lua_UnloadShader},
    {"GetShaderLocation", lua_GetShaderLocation}, {"GetShaderLocationAttrib", lua_GetShaderLocationAttrib},
    {"SetShaderValue", lua_SetShaderValue}, {"SetShaderValueV", lua_SetShaderValueV},
    {"SetShaderValueMatrix", lua_SetShaderValueMatrix}, {"SetShaderValueTexture", lua_SetShaderValueTexture},
    // Audio control
    {"PauseSound", lua_PauseSound}, {"ResumeSound", lua_ResumeSound},
    {"SetSoundVolume", lua_SetSoundVolume}, {"SetSoundPitch", lua_SetSoundPitch}, {"SetSoundPan", lua_SetSoundPan},
    // 3D draw
    {"DrawSphere", lua_DrawSphere}, {"DrawSphereEx", lua_DrawSphereEx},
    {"DrawModelWires", lua_DrawModelWires}, {"DrawModelWiresEx", lua_DrawModelWiresEx},
    {"DrawMeshInstanced", lua_DrawMeshInstanced},
    // 2D draw
    {"DrawTriangleFan", lua_DrawTriangleFan},
    {"DrawRectangleRoundedLines", lua_DrawRectangleRoundedLines},
    {"DrawRectangleRoundedLinesEx", lua_DrawRectangleRoundedLinesEx},
    // Window / system
    {"GetRenderWidth", lua_GetRenderWidth}, {"GetRenderHeight", lua_GetRenderHeight},
    {"GetWindowPosition", lua_GetWindowPosition}, {"WaitTime", lua_WaitTime},
    {"OpenURL", lua_OpenURL}, {"SetExitKey", lua_SetExitKey},
    {"SwapScreenBuffer", lua_SwapScreenBuffer}, {"PollInputEvents", lua_PollInputEvents},
    // Input
    {"GetMouseDelta", lua_GetMouseDelta}, {"GetMouseWheelMoveV", lua_GetMouseWheelMoveV},
    {"SetMouseCursor", lua_SetMouseCursor},
    {"IsGamepadAvailable", lua_IsGamepadAvailable}, {"GetGamepadName", lua_GetGamepadName},
    {"IsGamepadButtonPressed", lua_IsGamepadButtonPressed}, {"IsGamepadButtonDown", lua_IsGamepadButtonDown},
    {"IsGamepadButtonReleased", lua_IsGamepadButtonReleased}, {"IsGamepadButtonUp", lua_IsGamepadButtonUp},
    {"GetGamepadButtonPressed", lua_GetGamepadButtonPressed}, {"GetGamepadAxisCount", lua_GetGamepadAxisCount},
    {"GetGamepadAxisMovement", lua_GetGamepadAxisMovement}, {"SetGamepadMappings", lua_SetGamepadMappings},
    {"SetGamepadVibration", lua_SetGamepadVibration},
    {"SetGesturesEnabled", lua_SetGesturesEnabled}, {"IsGestureDetected", lua_IsGestureDetected},
    {"GetGestureDetected", lua_GetGestureDetected}, {"GetGestureHoldDuration", lua_GetGestureHoldDuration},
    {"GetGestureDragVector", lua_GetGestureDragVector}, {"GetGestureDragAngle", lua_GetGestureDragAngle},
    {"GetGesturePinchVector", lua_GetGesturePinchVector}, {"GetGesturePinchAngle", lua_GetGesturePinchAngle},
    {"GetTouchX", lua_GetTouchX}, {"GetTouchY", lua_GetTouchY},
    {"GetTouchPointId", lua_GetTouchPointId}, {"GetTouchPointCount", lua_GetTouchPointCount},
    // Filesystem
    {"FileExists", lua_FileExists}, {"DirectoryExists", lua_DirectoryExists}, {"IsPathFile", lua_IsPathFile},
    {"IsFileExtension", lua_IsFileExtension}, {"GetFileExtension", lua_GetFileExtension},
    {"GetFileName", lua_GetFileName}, {"GetFileNameWithoutExt", lua_GetFileNameWithoutExt},
    {"GetDirectoryPath", lua_GetDirectoryPath}, {"GetPrevDirectoryPath", lua_GetPrevDirectoryPath},
    {"GetWorkingDirectory", lua_GetWorkingDirectory}, {"GetApplicationDirectory", lua_GetApplicationDirectory},
    {"ChangeDirectory", lua_ChangeDirectory}, {"GetFileLength", lua_GetFileLength},
    {"GetFileModTime", lua_GetFileModTime},
    {"LoadFileData", lua_LoadFileData}, {"UnloadFileData", lua_UnloadFileData},
    {"SaveFileData", lua_SaveFileData}, {"LoadFileText", lua_LoadFileText},
    {"UnloadFileText", lua_UnloadFileText}, {"SaveFileText", lua_SaveFileText},
    // Data utils
    {"CompressData", lua_CompressData}, {"DecompressData", lua_DecompressData},
    {"EncodeDataBase64", lua_EncodeDataBase64}, {"DecodeDataBase64", lua_DecodeDataBase64},
    // Random
    {"SetRandomSeed", lua_SetRandomSeed}, {"LoadRandomSequence", lua_LoadRandomSequence},
    {"UnloadRandomSequence", lua_UnloadRandomSequence},
    // Text
    {"TextToInteger", lua_TextToInteger}, {"TextToFloat", lua_TextToFloat},
    // Logging
    {"TraceLog", lua_TraceLog}, {"SetTraceLogLevel", lua_SetTraceLogLevel},
    // Directory listing
    {"LoadDirectoryFiles", lua_LoadDirectoryFiles}, {"LoadDirectoryFilesEx", lua_LoadDirectoryFilesEx},
    {"UnloadDirectoryFiles", lua_UnloadDirectoryFiles},
    // Export
    {"ExportDataAsCode", lua_ExportDataAsCode},
    // Window icons / music-from-memory
    {"SetWindowIcons", lua_SetWindowIcons},
    {"LoadMusicStreamFromMemory", lua_LoadMusicStreamFromMemory},
    // VR
    {"LoadVrStereoConfig", lua_LoadVrStereoConfig}, {"UnloadVrStereoConfig", lua_UnloadVrStereoConfig},
    {"BeginVrStereoMode", lua_BeginVrStereoMode}, {"EndVrStereoMode", lua_EndVrStereoMode},
    // Automation events
    {"LoadAutomationEventList", lua_LoadAutomationEventList}, {"UnloadAutomationEventList", lua_UnloadAutomationEventList},
    {"ExportAutomationEventList", lua_ExportAutomationEventList}, {"SetAutomationEventList", lua_SetAutomationEventList},
    {"SetAutomationEventBaseFrame", lua_SetAutomationEventBaseFrame},
    {"StartAutomationEventRecording", lua_StartAutomationEventRecording},
    {"StopAutomationEventRecording", lua_StopAutomationEventRecording},
    {"GetAutomationEventCount", lua_GetAutomationEventCount}, {"PlayAutomationEvent", lua_PlayAutomationEvent},
    // Text lines
    {"UnloadTextLines", lua_UnloadTextLines},
    // File I/O & trace-log callbacks
    {"SetTraceLogCallback", lua_SetTraceLogCallback},
    {"SetLoadFileDataCallback", lua_SetLoadFileDataCallback}, {"SetSaveFileDataCallback", lua_SetSaveFileDataCallback},
    {"SetLoadFileTextCallback", lua_SetLoadFileTextCallback}, {"SetSaveFileTextCallback", lua_SetSaveFileTextCallback},
    // Raw memory
    {"MemAlloc", lua_MemAlloc}, {"MemRealloc", lua_MemRealloc}, {"MemFree", lua_MemFree},
    // Font atlas internals
    {"LoadFontData", lua_LoadFontData}, {"GenImageFontAtlas", lua_GenImageFontAtlas}, {"UnloadFontData", lua_UnloadFontData},
    // Drag-and-drop
    {"IsFileDropped", lua_IsFileDropped}, {"LoadDroppedFiles", lua_LoadDroppedFiles}, {"UnloadDroppedFiles", lua_UnloadDroppedFiles},
    {NULL, NULL}
};

// Adds the extra bindings onto the module table currently on top of the stack
// (the table returned by luaL_newlib in luaopen_raylib).
void register_extra(lua_State *L) {
    luaL_setfuncs(L, extra_functions, 0);
}
