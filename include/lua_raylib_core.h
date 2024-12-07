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

/**
 * @brief Checks if the window is minimized.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsWindowMinimized(lua_State *L);

/**
 * @brief Checks if the window is maximized.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsWindowMaximized(lua_State *L);

/**
 * @brief Restores the window if it is minimized or maximized.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_RestoreWindow(lua_State *L);

/**
 * @brief Toggles fullscreen mode for the window.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_ToggleFullscreen(lua_State *L);

/**
 * @brief Sets the clipboard text.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetClipboardText(lua_State *L);

/**
 * @brief Gets the clipboard text.
 * 
 * @param L Lua state
 * @return int Always returns 1 (string result)
 */
int lua_GetClipboardText(lua_State *L);

/**
 * @brief Gets the X coordinate of the mouse position.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetMouseX(lua_State *L);

/**
 * @brief Gets the Y coordinate of the mouse position.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetMouseY(lua_State *L);

/**
 * @brief Gets the mouse position as a Vector2.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Vector2 result)
 */
int lua_GetMousePosition(lua_State *L);

/**
 * @brief Gets the mouse wheel movement.
 * 
 * @param L Lua state
 * @return int Always returns 1 (float result)
 */
int lua_GetMouseWheelMove(lua_State *L);

/**
 * @brief Gets the frame time (time for one frame).
 * 
 * @param L Lua state
 * @return int Always returns 1 (float result)
 */
int lua_GetFrameTime(lua_State *L);

/**
 * @brief Checks if a key was released.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsKeyReleased(lua_State *L);

/**
 * @brief Gets the width of the monitor.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetMonitorWidth(lua_State *L);

/**
 * @brief Gets the height of the monitor.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetMonitorHeight(lua_State *L);

/**
 * @brief Maximizes the window.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_MaximizeWindow(lua_State *L);

/**
 * @brief Minimizes the window.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_MinimizeWindow(lua_State *L);

/**
 * @brief Sets the window title.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetWindowTitle(lua_State *L);

/**
 * @brief Sets the window position.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetWindowPosition(lua_State *L);

/**
 * @brief Sets the window monitor.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetWindowMonitor(lua_State *L);

/**
 * @brief Sets the window size.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetWindowSize(lua_State *L);

/**
 * @brief Sets the configuration flags for the window.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetConfigFlags(lua_State *L);

/**
 * @brief Gets the screen width.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetScreenWidth(lua_State *L);

/**
 * @brief Gets the screen height.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetScreenHeight(lua_State *L);

/**
 * @brief Gets the number of monitors.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetMonitorCount(lua_State *L);

/**
 * @brief Gets the name of the monitor.
 * 
 * @param L Lua state
 * @return int Always returns 1 (string result)
 */
int lua_GetMonitorName(lua_State *L);

/**
 * @brief Gets the physical width of the monitor.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetMonitorPhysicalWidth(lua_State *L);

/**
 * @brief Gets the physical height of the monitor.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetMonitorPhysicalHeight(lua_State *L);

/**
 * @brief Gets the refresh rate of the monitor.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetMonitorRefreshRate(lua_State *L);

/**
 * @brief Gets the position of the monitor.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Vector2 result)
 */
int lua_GetMonitorPosition(lua_State *L);

/**
 * @brief Gets the current time.
 * 
 * @param L Lua state
 * @return int Always returns 1 (double result)
 */
int lua_GetTime(lua_State *L);

/**
 * @brief Gets a random value between min and max.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetRandomValue(lua_State *L);

/**
 * @brief Sets the target frames per second (FPS).
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetTargetFPS(lua_State *L);

/**
 * @brief Gets the target frames per second (FPS).
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetTargetFPS(lua_State *L);

/**
 * @brief Checks if a key is currently down.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsKeyDown(lua_State *L);

/**
 * @brief Checks if a key is currently up.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsKeyUp(lua_State *L);

/**
 * @brief Checks if a mouse button is currently down.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsMouseButtonDown(lua_State *L);

/**
 * @brief Checks if a mouse button is currently up.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsMouseButtonUp(lua_State *L);

/**
 * @brief Sets the mouse position.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetMousePosition(lua_State *L);

/**
 * @brief Sets the mouse offset.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetMouseOffset(lua_State *L);

/**
 * @brief Sets the mouse scale.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetMouseScale(lua_State *L);

/**
 * @brief Gets the touch position.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Vector2 result)
 */
int lua_GetTouchPosition(lua_State *L);

/**
 * @brief Shows the cursor.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_ShowCursor(lua_State *L);

/**
 * @brief Hides the cursor.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_HideCursor(lua_State *L);

/**
 * @brief Checks if the cursor is hidden.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsCursorHidden(lua_State *L);

/**
 * @brief Enables the cursor.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_EnableCursor(lua_State *L);

/**
 * @brief Disables the cursor.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DisableCursor(lua_State *L);

/**
 * @brief Gets the length of the clipboard text.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetClipboardTextLength(lua_State *L);

/**
 * @brief Checks if the window is ready.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsWindowReady(lua_State *L);

/**
 * @brief Checks if the window is focused.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsWindowFocused(lua_State *L);

/**
 * @brief Checks if the window is in fullscreen mode.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsWindowFullscreen(lua_State *L);

/**
 * @brief Checks if the window is hidden.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsWindowHidden(lua_State *L);

/**
 * @brief Checks if the window is resized.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsWindowResized(lua_State *L);

/**
 * @brief Checks if the window has a specific state.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsWindowState(lua_State *L);

/**
 * @brief Sets a specific state for the window.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetWindowState(lua_State *L);

/**
 * @brief Clears a specific state for the window.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_ClearWindowState(lua_State *L);

/**
 * @brief Toggles borderless windowed mode.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_ToggleBorderlessWindowed(lua_State *L);

/**
 * @brief Sets the minimum size of the window.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetWindowMinSize(lua_State *L);

/**
 * @brief Sets the maximum size of the window.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetWindowMaxSize(lua_State *L);

/**
 * @brief Sets the opacity of the window.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetWindowOpacity(lua_State *L);

/**
 * @brief Sets the window as focused.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetWindowFocused(lua_State *L);

/**
 * @brief Gets the window handle.
 * 
 * @param L Lua state
 * @return int Always returns 1 (handle result)
 */
int lua_GetWindowHandle(lua_State *L);

/**
 * @brief Gets the current monitor.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetCurrentMonitor(lua_State *L);

/**
 * @brief Gets the window scale DPI.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Vector2 result)
 */
int lua_GetWindowScaleDPI(lua_State *L);

/**
 * @brief Enables event waiting.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_EnableEventWaiting(lua_State *L);

/**
 * @brief Disables event waiting.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DisableEventWaiting(lua_State *L);

/**
 * @brief Checks if the cursor is on the screen.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsCursorOnScreen(lua_State *L);

#endif