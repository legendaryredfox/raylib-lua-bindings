#include "lua_raylib_core.h"
#include "raylib_wrappers.h"

int lua_InitWindow(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    const char *title = luaL_checkstring(L, 3);
    InitWindow(width, height, title);
    return 0;
}

int lua_CloseWindow(lua_State *L) {
    CloseWindow();
    return 0;
}

int lua_WindowShouldClose(lua_State *L) {
    lua_pushboolean(L, WindowShouldClose());
    return 1;
}

int lua_GetClipboardImage(lua_State *L) {
    Image image = GetClipboardImage();
    Image *userdata = (Image *)lua_newuserdata(L, sizeof(Image));
    *userdata = image;
    luaL_setmetatable(L, "Image");
    return 1;
}


int lua_SetWindowIcon(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    SetWindowIcon(*image);
    return 0;
}

int lua_TakeScreenshot(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    TakeScreenshot(fileName);
    return 0;
}

int lua_GetFPS(lua_State *L) {
    lua_pushinteger(L, GetFPS());
    return 1;
}

int lua_IsWindowMinimized(lua_State *L) {
    lua_pushboolean(L, IsWindowMinimized());
    return 1;
}

int lua_IsWindowMaximized(lua_State *L) {
    lua_pushboolean(L, IsWindowMaximized());
    return 1;
}

int lua_RestoreWindow(lua_State *L) {
    RestoreWindow();
    return 0;
}

int lua_ToggleFullscreen(lua_State *L) {
    ToggleFullscreen();
    return 0;
}

int lua_SetClipboardText(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    SetClipboardText(text);
    return 0;
}

int lua_GetClipboardText(lua_State *L) {
    const char *text = GetClipboardText();
    lua_pushstring(L, text);
    return 1;
}

int lua_GetMouseX(lua_State *L) {
    lua_pushinteger(L, GetMouseX());
    return 1;
}

int lua_GetMouseY(lua_State *L) {
    lua_pushinteger(L, GetMouseY());
    return 1;
}

int lua_GetMousePosition(lua_State *L) {
    push_vector2_to_table(L, GetMousePosition());
    return 1;
}

int lua_GetMouseWheelMove(lua_State *L) {
    lua_pushnumber(L, GetMouseWheelMove());
    return 1;
}

int lua_GetFrameTime(lua_State *L) {
    lua_pushnumber(L, GetFrameTime());
    return 1;
}

int lua_IsKeyReleased(lua_State *L) {
    int key = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsKeyReleased(key));
    return 1;
}

int lua_GetMonitorWidth(lua_State *L) {
    int monitor = luaL_checkinteger(L, 1);
    lua_pushinteger(L, GetMonitorWidth(monitor));
    return 1;
}

int lua_GetMonitorHeight(lua_State *L) {
    int monitor = luaL_checkinteger(L, 1);
    lua_pushinteger(L, GetMonitorHeight(monitor));
    return 1;
}

int lua_MaximizeWindow(lua_State *L) {
    MaximizeWindow();
    return 0;
}

int lua_MinimizeWindow(lua_State *L) {
    MinimizeWindow();
    return 0;
}

int lua_SetWindowTitle(lua_State *L) {
    const char *title = luaL_checkstring(L, 1);
    SetWindowTitle(title);
    return 0;
}

int lua_SetWindowPosition(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    SetWindowPosition(x, y);
    return 0;
}

int lua_SetWindowMonitor(lua_State *L) {
    int monitor = luaL_checkinteger(L, 1);
    SetWindowMonitor(monitor);
    return 0;
}

int lua_SetWindowSize(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    SetWindowSize(width, height);
    return 0;
}

int lua_SetConfigFlags(lua_State *L) {
    unsigned int flags = luaL_checkinteger(L, 1);
    SetConfigFlags(flags);
    return 0;
}

int lua_GetScreenWidth(lua_State *L) {
    lua_pushinteger(L, GetScreenWidth());
    return 1;
}

int lua_GetScreenHeight(lua_State *L) {
    lua_pushinteger(L, GetScreenHeight());
    return 1;
}

int lua_GetMonitorCount(lua_State *L) {
    lua_pushinteger(L, GetMonitorCount());
    return 1;
}

int lua_GetMonitorName(lua_State *L) {
    int monitor = luaL_checkinteger(L, 1);
    const char *name = GetMonitorName(monitor);
    lua_pushstring(L, name);
    return 1;
}

int lua_GetMonitorPhysicalWidth(lua_State *L) {
    int monitor = luaL_checkinteger(L, 1);
    lua_pushinteger(L, GetMonitorPhysicalWidth(monitor));
    return 1;
}

int lua_GetMonitorPhysicalHeight(lua_State *L) {
    int monitor = luaL_checkinteger(L, 1);
    lua_pushinteger(L, GetMonitorPhysicalHeight(monitor));
    return 1;
}

int lua_GetMonitorRefreshRate(lua_State *L) {
    int monitor = luaL_checkinteger(L, 1);
    lua_pushinteger(L, GetMonitorRefreshRate(monitor));
    return 1;
}

int lua_GetMonitorPosition(lua_State *L) {
    int monitor = luaL_checkinteger(L, 1);
    push_vector2_to_table(L, GetMonitorPosition(monitor));
    return 1;
}

int lua_GetTime(lua_State *L) {
    lua_pushnumber(L, GetTime());
    return 1;
}

int lua_GetRandomValue(lua_State *L) {
    int min = luaL_checkinteger(L, 1);
    int max = luaL_checkinteger(L, 2);
    lua_pushinteger(L, GetRandomValue(min, max));
    return 1;
}

int lua_SetTargetFPS(lua_State *L) {
    int fps = luaL_checkinteger(L, 1);
    SetTargetFPS(fps);
    return 0;
}

int lua_GetTargetFPS(lua_State *L) {
    lua_pushinteger(L, GetFPS());
    return 1;
}

int lua_IsKeyDown(lua_State *L) {
    int key = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsKeyDown(key));
    return 1;
}

int lua_IsKeyUp(lua_State *L) {
    int key = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsKeyUp(key));
    return 1;
}

int lua_IsMouseButtonDown(lua_State *L) {
    int button = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsMouseButtonDown(button));
    return 1;
}

int lua_IsMouseButtonUp(lua_State *L) {
    int button = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsMouseButtonUp(button));
    return 1;
}

int lua_SetMousePosition(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    SetMousePosition(x, y);
    return 0;
}

int lua_SetMouseOffset(lua_State *L) {
    int offsetX = luaL_checkinteger(L, 1);
    int offsetY = luaL_checkinteger(L, 2);
    SetMouseOffset(offsetX, offsetY);
    return 0;
}

int lua_SetMouseScale(lua_State *L) {
    float scaleX = luaL_checknumber(L, 1);
    float scaleY = luaL_checknumber(L, 2);
    SetMouseScale(scaleX, scaleY);
    return 0;
}

int lua_GetTouchPosition(lua_State *L) {
    int index = luaL_checkinteger(L, 1);
    push_vector2_to_table(L, GetTouchPosition(index));
    return 1;
}

int lua_ShowCursor(lua_State *L) {
    ShowCursor();
    return 0;
}

int lua_HideCursor(lua_State *L) {
    HideCursor();
    return 0;
}

int lua_IsCursorHidden(lua_State *L) {
    lua_pushboolean(L, IsCursorHidden());
    return 1;
}

int lua_EnableCursor(lua_State *L) {
    EnableCursor();
    return 0;
}

int lua_DisableCursor(lua_State *L) {
    DisableCursor();
    return 0;
}

int lua_GetClipboardTextLength(lua_State *L) {
    const char *text = GetClipboardText();
    if (text != NULL) {
        lua_pushinteger(L, strlen(text));
    } else {
        lua_pushinteger(L, 0);
    }
    return 1;
}

int lua_IsWindowReady(lua_State *L) {
    lua_pushboolean(L, IsWindowReady());
    return 1;
}

int lua_IsWindowFocused(lua_State *L) {
    lua_pushboolean(L, IsWindowFocused());
    return 1;
}

int lua_IsWindowFullscreen(lua_State *L) {
    lua_pushboolean(L, IsWindowFullscreen());
    return 1;
}

int lua_IsWindowHidden(lua_State *L) {
    lua_pushboolean(L, IsWindowHidden());
    return 1;
}

int lua_IsWindowResized(lua_State *L) {
    lua_pushboolean(L, IsWindowResized());
    return 1;
}

int lua_IsWindowState(lua_State *L) {
    unsigned int flag = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsWindowState(flag));
    return 1;
}

int lua_SetWindowState(lua_State *L) {
    unsigned int flags = luaL_checkinteger(L, 1);
    SetWindowState(flags);
    return 0;
}

int lua_ClearWindowState(lua_State *L) {
    unsigned int flags = luaL_checkinteger(L, 1);
    ClearWindowState(flags);
    return 0;
}

int lua_ToggleBorderlessWindowed(lua_State *L) {
    ToggleBorderlessWindowed();
    return 0;
}

int lua_SetWindowMinSize(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    SetWindowMinSize(width, height);
    return 0;
}

int lua_SetWindowMaxSize(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    SetWindowMaxSize(width, height);
    return 0;
}

int lua_SetWindowOpacity(lua_State *L) {
    float opacity = luaL_checknumber(L, 1);
    SetWindowOpacity(opacity);
    return 0;
}

int lua_SetWindowFocused(lua_State *L) {
    SetWindowFocused();
    return 0;
}

int lua_GetWindowHandle(lua_State *L) {
    void *handle = GetWindowHandle();
    lua_pushlightuserdata(L, handle);
    return 1;
}

int lua_GetCurrentMonitor(lua_State *L) {
    lua_pushinteger(L, GetCurrentMonitor());
    return 1;
}

int lua_GetWindowScaleDPI(lua_State *L) {
    Vector2 scale = GetWindowScaleDPI();
    lua_newtable(L);
    lua_pushnumber(L, scale.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, scale.y);
    lua_setfield(L, -2, "y");
    return 1;
}

int lua_EnableEventWaiting(lua_State *L) {
    EnableEventWaiting();
    return 0;
}

int lua_DisableEventWaiting(lua_State *L) {
    DisableEventWaiting();
    return 0;
}

int lua_IsCursorOnScreen(lua_State *L) {
    lua_pushboolean(L, IsCursorOnScreen());
    return 1;
}

int lua_IsKeyPressed(lua_State *L) {
    int key = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsKeyPressed(key));
    return 1;
}

int lua_IsKeyPressedRepeat(lua_State *L) {
    int key = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsKeyPressedRepeat(key));
    return 1;
}

int lua_GetKeyPressed(lua_State *L) {
    lua_pushinteger(L, GetKeyPressed());
    return 1;
}

int lua_GetCharPressed(lua_State *L) {
    lua_pushinteger(L, GetCharPressed());
    return 1;
}

int lua_GetKeyName(lua_State *L) {
    int key = luaL_checkinteger(L, 1);
    lua_pushstring(L, GetKeyName(key));
    return 1;
}

int lua_IsMouseButtonPressed(lua_State *L) {
    int button = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsMouseButtonPressed(button));
    return 1;
}

int lua_IsMouseButtonReleased(lua_State *L) {
    int button = luaL_checkinteger(L, 1);
    lua_pushboolean(L, IsMouseButtonReleased(button));
    return 1;
}

int lua_MakeDirectory(lua_State *L) {
    const char *dirPath = luaL_checkstring(L, 1);
    lua_pushinteger(L, MakeDirectory(dirPath));
    return 1;
}

int lua_IsFileNameValid(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    lua_pushboolean(L, IsFileNameValid(fileName));
    return 1;
}

int lua_ComputeCRC32(lua_State *L) {
    size_t dataSize;
    const char *data = luaL_checklstring(L, 1, &dataSize);
    unsigned int crc = ComputeCRC32((unsigned char *)data, (int)dataSize);
    lua_pushinteger(L, (lua_Integer)crc);
    return 1;
}

int lua_ComputeMD5(lua_State *L) {
    size_t dataSize;
    const char *data = luaL_checklstring(L, 1, &dataSize);
    unsigned int *hash = ComputeMD5((unsigned char *)data, (int)dataSize);
    lua_createtable(L, 4, 0);
    for (int i = 0; i < 4; i++) {
        lua_pushinteger(L, (lua_Integer)hash[i]);
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

int lua_ComputeSHA1(lua_State *L) {
    size_t dataSize;
    const char *data = luaL_checklstring(L, 1, &dataSize);
    unsigned int *hash = ComputeSHA1((unsigned char *)data, (int)dataSize);
    lua_createtable(L, 5, 0);
    for (int i = 0; i < 5; i++) {
        lua_pushinteger(L, (lua_Integer)hash[i]);
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

int lua_ComputeSHA256(lua_State *L) {
    size_t dataSize;
    const char *data = luaL_checklstring(L, 1, &dataSize);
    unsigned int *hash = ComputeSHA256((unsigned char *)data, (int)dataSize);
    lua_createtable(L, 8, 0);
    for (int i = 0; i < 8; i++) {
        lua_pushinteger(L, (lua_Integer)hash[i]);
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

int lua_FileCopy(lua_State *L) {
    const char *srcPath = luaL_checkstring(L, 1);
    const char *dstPath = luaL_checkstring(L, 2);
    lua_pushinteger(L, FileCopy(srcPath, dstPath));
    return 1;
}

int lua_FileMove(lua_State *L) {
    const char *srcPath = luaL_checkstring(L, 1);
    const char *dstPath = luaL_checkstring(L, 2);
    lua_pushinteger(L, FileMove(srcPath, dstPath));
    return 1;
}

int lua_FileRemove(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    lua_pushinteger(L, FileRemove(fileName));
    return 1;
}

int lua_FileRename(lua_State *L) {
    const char *fileName   = luaL_checkstring(L, 1);
    const char *fileRename = luaL_checkstring(L, 2);
    lua_pushinteger(L, FileRename(fileName, fileRename));
    return 1;
}

int lua_FileTextFindIndex(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    const char *search   = luaL_checkstring(L, 2);
    lua_pushinteger(L, FileTextFindIndex(fileName, search));
    return 1;
}

int lua_FileTextReplace(lua_State *L) {
    const char *fileName    = luaL_checkstring(L, 1);
    const char *search      = luaL_checkstring(L, 2);
    const char *replacement = luaL_checkstring(L, 3);
    lua_pushinteger(L, FileTextReplace(fileName, search, replacement));
    return 1;
}

int lua_GetDirectoryFileCount(lua_State *L) {
    const char *dirPath = luaL_checkstring(L, 1);
    lua_pushinteger(L, (lua_Integer)GetDirectoryFileCount(dirPath));
    return 1;
}

int lua_GetDirectoryFileCountEx(lua_State *L) {
    const char *basePath      = luaL_checkstring(L, 1);
    const char *filter        = luaL_checkstring(L, 2);
    bool scanSubdirs          = lua_toboolean(L, 3);
    lua_pushinteger(L, (lua_Integer)GetDirectoryFileCountEx(basePath, filter, scanSubdirs));
    return 1;
}