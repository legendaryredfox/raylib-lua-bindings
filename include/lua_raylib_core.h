#ifndef RAYLIB_LUA_CORE_H
#define RAYLIB_LUA_CORE_H

#include "lua_raylib.h"

/**
 * @brief Initializes a window.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_InitWindow(lua_State *L);

/**
 * @brief Closes the window.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_CloseWindow(lua_State *L);

/**
 * @brief Checks if the window should close.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_WindowShouldClose(lua_State *L);

/**
 * @brief Gets the image from the clipboard.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 */
int lua_GetClipboardImage(lua_State *L);

/**
 * @brief Sets the window icon.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetWindowIcon(lua_State *L);

/**
 * @brief Takes a screenshot of the current window.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_TakeScreenshot(lua_State *L);

/**
 * @brief Gets the current frames per second (FPS).
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetFPS(lua_State *L);

int lua_IsWindowMinimized(lua_State *L);
int lua_IsWindowMaximized(lua_State *L);
int lua_RestoreWindow(lua_State *L);
int lua_ToggleFullscreen(lua_State *L);
int lua_SetClipboardText(lua_State *L);
int lua_GetClipboardText(lua_State *L);
int lua_GetMouseX(lua_State *L);
int lua_GetMouseY(lua_State *L);
int lua_GetMousePosition(lua_State *L);
int lua_GetMouseWheelMove(lua_State *L);
int lua_GetFrameTime(lua_State *L);
int lua_IsKeyReleased(lua_State *L);
int lua_GetMonitorWidth(lua_State *L);
int lua_GetMonitorHeight(lua_State *L);
int lua_MaximizeWindow(lua_State *L);
int lua_MinimizeWindow(lua_State *L);
int lua_SetWindowTitle(lua_State *L);
int lua_SetWindowPosition(lua_State *L);
int lua_SetWindowMonitor(lua_State *L);
int lua_SetWindowSize(lua_State *L);
int lua_SetConfigFlags(lua_State *L);
int lua_GetScreenWidth(lua_State *L);
int lua_GetScreenHeight(lua_State *L);
int lua_GetMonitorCount(lua_State *L);
int lua_GetMonitorName(lua_State *L);
int lua_GetMonitorPhysicalWidth(lua_State *L);
int lua_GetMonitorPhysicalHeight(lua_State *L);
int lua_GetMonitorRefreshRate(lua_State *L);
int lua_GetMonitorPosition(lua_State *L);
int lua_GetTime(lua_State *L);
int lua_GetRandomValue(lua_State *L);
int lua_SetTargetFPS(lua_State *L);
int lua_GetTargetFPS(lua_State *L);
int lua_IsKeyDown(lua_State *L);
int lua_IsKeyUp(lua_State *L);
int lua_IsMouseButtonDown(lua_State *L);
int lua_IsMouseButtonUp(lua_State *L);
int lua_SetMousePosition(lua_State *L);
int lua_SetMouseOffset(lua_State *L);
int lua_SetMouseScale(lua_State *L);
int lua_GetTouchPosition(lua_State *L);
int lua_ShowCursor(lua_State *L);
int lua_HideCursor(lua_State *L);
int lua_IsCursorHidden(lua_State *L);
int lua_EnableCursor(lua_State *L);
int lua_DisableCursor(lua_State *L);
int lua_GetClipboardTextLength(lua_State *L);
int lua_IsWindowReady(lua_State *L);
int lua_IsWindowFocused(lua_State *L);
int lua_IsWindowFullscreen(lua_State *L);
int lua_IsWindowHidden(lua_State *L);
int lua_IsWindowResized(lua_State *L);
int lua_IsWindowState(lua_State *L);
int lua_SetWindowState(lua_State *L);
int lua_ClearWindowState(lua_State *L);
int lua_ToggleBorderlessWindowed(lua_State *L);
int lua_SetWindowMinSize(lua_State *L);
int lua_SetWindowMaxSize(lua_State *L);
int lua_SetWindowOpacity(lua_State *L);
int lua_SetWindowFocused(lua_State *L);
int lua_GetWindowHandle(lua_State *L);
int lua_GetCurrentMonitor(lua_State *L);
int lua_GetWindowScaleDPI(lua_State *L);
int lua_GetClipboardImage(lua_State *L);
int lua_EnableEventWaiting(lua_State *L);
int lua_DisableEventWaiting(lua_State *L);
int lua_IsCursorOnScreen(lua_State *L);

#endif