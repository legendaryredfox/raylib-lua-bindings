#include <lua.h>
#include <lauxlib.h>
#include "raylib_wrappers.h"
#include "lua_raylib_core.h"
#include "lua_raylib_draw.h"

// Register bindings
static const luaL_Reg raylib_functions[] = {

    // Core
    {"InitWindow", lua_InitWindow},
    {"CloseWindow", lua_CloseWindow},
    {"WindowShouldClose", lua_WindowShouldClose},
    {"GetClipboardImage", lua_GetClipboardImage},

    {"SetWindowIcon", lua_SetWindowIcon},
    {"TakeScreenshot", lua_TakeScreenshot},
    {"GetFPS", lua_GetFPS},
    {"IsWindowMinimized", lua_IsWindowMinimized},
    {"IsWindowMaximized", lua_IsWindowMaximized},
    {"RestoreWindow", lua_RestoreWindow},
    {"ToggleFullscreen", lua_ToggleFullscreen},
    {"SetClipboardText", lua_SetClipboardText},
    {"GetClipboardText", lua_GetClipboardText},
    {"GetMouseX", lua_GetMouseX},
    {"GetMouseY", lua_GetMouseY},
    {"GetMousePosition", lua_GetMousePosition},
    {"GetMouseWheelMove", lua_GetMouseWheelMove},
    {"GetFrameTime", lua_GetFrameTime},
    {"IsKeyReleased", lua_IsKeyReleased},
    {"GetMonitorWidth", lua_GetMonitorWidth},
    {"GetMonitorHeight", lua_GetMonitorHeight},
    {"MaximizeWindow", lua_MaximizeWindow},
    {"MinimizeWindow", lua_MinimizeWindow},
    {"SetWindowTitle", lua_SetWindowTitle},
    {"SetWindowPosition", lua_SetWindowPosition},
    {"SetWindowMonitor", lua_SetWindowMonitor},
    {"SetWindowSize", lua_SetWindowSize},
    {"SetConfigFlags", lua_SetConfigFlags},
    {"GetScreenWidth", lua_GetScreenWidth},
    {"GetScreenHeight", lua_GetScreenHeight},
    {"GetMonitorCount", lua_GetMonitorCount},
    {"GetMonitorName", lua_GetMonitorName},
    {"GetMonitorPhysicalWidth", lua_GetMonitorPhysicalWidth},
    {"GetMonitorPhysicalHeight", lua_GetMonitorPhysicalHeight},
    {"GetMonitorRefreshRate", lua_GetMonitorRefreshRate},
    {"GetMonitorPosition", lua_GetMonitorPosition},
    {"GetTime", lua_GetTime},
    {"GetRandomValue", lua_GetRandomValue},
    {"SetTargetFPS", lua_SetTargetFPS},
    {"GetTargetFPS", lua_GetTargetFPS},
    {"IsKeyDown", lua_IsKeyDown},
    {"IsKeyUp", lua_IsKeyUp},
    {"IsMouseButtonDown", lua_IsMouseButtonDown},
    {"IsMouseButtonUp", lua_IsMouseButtonUp},
    {"SetMousePosition", lua_SetMousePosition},
    {"SetMouseOffset", lua_SetMouseOffset},
    {"SetMouseScale", lua_SetMouseScale},
    {"GetTouchPosition", lua_GetTouchPosition},
    {"ShowCursor", lua_ShowCursor},
    {"HideCursor", lua_HideCursor},
    {"IsCursorHidden", lua_IsCursorHidden},
    {"EnableCursor", lua_EnableCursor},
    {"DisableCursor", lua_DisableCursor},
    {"GetClipboardTextLength", lua_GetClipboardTextLength},
    {"IsWindowReady", lua_IsWindowReady},
    {"IsWindowFocused", lua_IsWindowFocused},
    {"IsWindowFullscreen", lua_IsWindowFullscreen},
    {"IsWindowHidden", lua_IsWindowHidden},
    {"IsWindowResized", lua_IsWindowResized},
    {"SetWindowState", lua_SetWindowState},
    {"ClearWindowState", lua_ClearWindowState},
    {"ToggleBorderlessWindowed", lua_ToggleBorderlessWindowed},
    {"SetWindowMinSize", lua_SetWindowMinSize},
    {"SetWindowMaxSize", lua_SetWindowMaxSize},
    {"SetWindowOpacity", lua_SetWindowOpacity},
    {"SetWindowFocused", lua_SetWindowFocused},
    {"GetWindowHandle", lua_GetWindowHandle},
    {"GetCurrentMonitor", lua_GetCurrentMonitor},
    {"GetWindowScaleDPI", lua_GetWindowScaleDPI},
    {"GetClipboardImage", lua_GetClipboardImage},
    {"EnableEventWaiting", lua_EnableEventWaiting},
    {"DisableEventWaiting", lua_DisableEventWaiting},
    {"IsCursorOnScreen", lua_IsCursorOnScreen},

    //Draw
    {"BeginDrawing", lua_BeginDrawing},
    {"EndDrawing", lua_EndDrawing},
    {"ClearBackground", lua_ClearBackground},
    {"DrawRectangle", lua_DrawRectangle},
    
    {NULL, NULL} // Sentinel
};

int luaopen_raylib(lua_State *L) {
    luaL_newlib(L, raylib_functions);
    return 1;
}
