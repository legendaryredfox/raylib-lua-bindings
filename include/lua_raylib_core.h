#ifndef RAYLIB_LUA_CORE_H
#define RAYLIB_LUA_CORE_H

#include "lua_raylib.h"

/**
 * @brief Initializes a window with specified width, height, and title.
 * 
 * This function creates a window for rendering. It sets the dimensions and the window title. 
 * Once this function is called, the window will remain open until `lua_CloseWindow` is called 
 * or `lua_WindowShouldClose` returns true.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `width` (int) - The width of the window in pixels.
 *       - `height` (int) - The height of the window in pixels.
 *       - `title` (string) - The title displayed in the window's title bar.
 * 
 * @usage
 * ```lua
 * raylib.InitWindow(800, 600, "My Awesome Game")
 * print("Window initialized with size 800x600 and title 'My Awesome Game'.")
 * ```
 * 
 * @warning This function must be called before any rendering can be done. If a window is already open, calling this function again has no effect.
 */
int lua_InitWindow(lua_State *L);

/**
 * @brief Closes the current window and releases all associated resources.
 * 
 * This function closes the rendering window and deinitializes resources that were initialized 
 * with `lua_InitWindow`. It should be called at the end of the program or when the user intends 
 * to exit the game/application.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @usage
 * ```lua
 * raylib.InitWindow(800, 600, "My Game")
 * -- Game loop here
 * raylib.CloseWindow()
 * print("Window closed.")
 * ```
 * 
 * @note If no window is open, calling this function has no effect.
 * 
 * @warning Ensure that all game resources (textures, sounds, etc.) are unloaded before calling this function to prevent memory leaks.
 */
int lua_CloseWindow(lua_State *L);

/**
 * @brief Checks if the window should close.
 * 
 * This function checks if the user has requested to close the window, 
 * typically by clicking the close button or pressing a system-defined key (like Alt+F4 or Command+W).
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1 (boolean result), which is true if the window should close, false otherwise.
 * 
 * @usage
 * ```lua
 * while not raylib.WindowShouldClose() do
 *     -- Game loop logic
 * end
 * raylib.CloseWindow()
 * print("Window closed due to user request.")
 * ```
 * 
 * @note This function is typically used as the main loop condition for games or applications.
 * 
 * @warning If this function is not checked regularly in the main game loop, 
 * the user may be unable to close the window gracefully.
 */
int lua_WindowShouldClose(lua_State *L);

/**
 * @brief Retrieves an image from the system clipboard.
 * 
 * This function gets an image that was copied to the system clipboard. If an image exists 
 * in the clipboard, it will be returned as an `Image` structure that can be used within the 
 * application.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1 (Image result), pushing the image to the Lua stack.
 * 
 * @usage
 * ```lua
 * local image = raylib.GetClipboardImage()
 * if image then
 *     print("Image successfully retrieved from clipboard.")
 * else
 *     print("No image found in the clipboard.")
 * end
 * ```
 * 
 * @note If no image is present in the clipboard, this function returns `nil`.
 * 
 * @warning The returned image must be properly unloaded using `raylib.UnloadImage(image)` to prevent memory leaks.
 */
int lua_GetClipboardImage(lua_State *L);

/**
 * @brief Sets the window icon using an image.
 * 
 * This function sets the icon of the current window to the specified image. The image 
 * must be a valid `Image` structure loaded or created before calling this function.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @usage
 * ```lua
 * local icon = raylib.LoadImage("icon.png")
 * raylib.SetWindowIcon(icon)
 * print("Window icon set successfully.")
 * ```
 * 
 * @note The image used for the window icon should be small (like 32x32 or 64x64) for best results. 
 * If no window is currently open, this function has no effect.
 * 
 * @warning This function does not automatically unload the image used as the icon. 
 * Be sure to call `raylib.UnloadImage(icon)` when the image is no longer needed.
 */
int lua_SetWindowIcon(lua_State *L);

/**
 * @brief Captures a screenshot of the current window.
 * 
 * This function takes a screenshot of the current window and saves it to an image file 
 * in the working directory. The filename is automatically generated based on the 
 * current date and time.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @usage
 * ```lua
 * raylib.TakeScreenshot()
 * print("Screenshot captured successfully.")
 * ```
 * 
 * @note The screenshot is saved in the current working directory as `screenshotYYYYMMDD_HHMMSS.png`, 
 * where `YYYYMMDD_HHMMSS` represents the date and time of the capture.
 * 
 * @warning If the application does not have write permissions to the current directory, 
 * the screenshot may fail to be saved.
 */
int lua_TakeScreenshot(lua_State *L);

/**
 * @brief Retrieves the current frames per second (FPS) of the application.
 * 
 * This function returns the number of frames per second currently being rendered. 
 * The FPS value is updated each frame and can be used for debugging, performance analysis, 
 * or for displaying the FPS counter in your application.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1 (integer result), pushing the FPS value to the Lua stack.
 * 
 * @usage
 * ```lua
 * local fps = raylib.GetFPS()
 * print("Current FPS:", fps)
 * ```
 * 
 * @note This function is useful for tracking performance and rendering statistics.
 */
int lua_GetFPS(lua_State *L);

/**
 * @brief Checks if the current window is minimized.
 * 
 * This function returns `true` if the application window is currently minimized. 
 * It can be used to pause animations, gameplay, or other logic when the user minimizes the window.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1 (boolean result), pushing `true` if the window is minimized, otherwise `false`.
 * 
 * @usage
 * ```lua
 * if raylib.IsWindowMinimized() then
 *     print("Window is minimized.")
 * end
 * ```
 * 
 * @note This function is useful for pausing updates when the window is minimized to avoid unnecessary processing.
 */
int lua_IsWindowMinimized(lua_State *L);

/**
 * @brief Checks if the current window is maximized.
 * 
 * This function returns `true` if the application window is currently maximized. 
 * It can be used to trigger specific UI changes or layout adjustments for maximized mode.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1 (boolean result), pushing `true` if the window is maximized, otherwise `false`.
 * 
 * @usage
 * ```lua
 * if raylib.IsWindowMaximized() then
 *     print("Window is maximized.")
 * end
 * ```
 * 
 * @note This function is useful for managing layout changes or fullscreen mode toggles.
 */
int lua_IsWindowMaximized(lua_State *L);

/**
 * @brief Restores the window if it is minimized or maximized.
 * 
 * This function restores the application window to its normal state if it is currently minimized or maximized. 
 * It is useful for ensuring that the window is in a predictable state for subsequent operations.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0. No value is pushed onto the Lua stack.
 * 
 * @usage
 * ```lua
 * raylib.RestoreWindow()
 * print("Window restored.")
 * ```
 * 
 * @note This function is useful for situations where you need to guarantee that the window is neither minimized nor maximized.
 */
int lua_RestoreWindow(lua_State *L);

/**
 * @brief Toggles fullscreen mode for the window.
 * 
 * This function switches the application window between fullscreen and windowed mode. 
 * It can be useful for providing users with a fullscreen experience or allowing them to return to windowed mode.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0. No value is pushed onto the Lua stack.
 * 
 * @usage
 * ```lua
 * raylib.ToggleFullscreen()
 * print("Fullscreen mode toggled.")
 * ```
 * 
 * @note This function can be used to implement a fullscreen toggle shortcut (like F11) in your application.
 * @warning Switching to fullscreen may change the window resolution and aspect ratio.
 */
int lua_ToggleFullscreen(lua_State *L);

/**
 * @brief Sets the clipboard text to the specified value.
 * 
 * This function copies the specified text to the system clipboard. The copied text can be pasted into 
 * other applications or used later within the same application.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0. No value is pushed onto the Lua stack.
 * 
 * @usage
 * ```lua
 * raylib.SetClipboardText("Hello, world!")
 * print("Text copied to clipboard.")
 * ```
 * 
 * @note This function is useful for copying text from the application to be used elsewhere.
 * @warning The clipboard text may be overwritten if another application sets it after this call.
 */
int lua_SetClipboardText(lua_State *L);

/**
 * @brief Gets the text currently stored in the system clipboard.
 * 
 * This function retrieves the text currently stored in the system clipboard. 
 * It allows you to access text that has been copied from other applications 
 * or set using `lua_SetClipboardText`.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1. The retrieved clipboard text is pushed onto the Lua stack as a string.
 * 
 * @usage
 * ```lua
 * local clipboardText = raylib.GetClipboardText()
 * print("Clipboard contains: " .. clipboardText)
 * ```
 * 
 * @note If the clipboard is empty or contains non-text data, the function may return an empty string.
 * @warning The returned string may be affected by encoding issues if special characters are present.
 */
int lua_GetClipboardText(lua_State *L);

/**
 * @brief Gets the X coordinate of the current mouse position.
 * 
 * This function retrieves the X coordinate of the mouse position relative to the 
 * top-left corner of the application window. The X coordinate increases as the mouse 
 * moves to the right.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1. The X coordinate is pushed onto the Lua stack as an integer.
 * 
 * @usage
 * ```lua
 * local mouseX = raylib.GetMouseX()
 * print("Mouse X position: " .. mouseX)
 * ```
 * 
 * @note This function is useful for implementing custom mouse interaction logic in your application.
 * @warning The X coordinate is relative to the window, not the entire screen.
 */
int lua_GetMouseX(lua_State *L);

/**
 * @brief Gets the Y coordinate of the current mouse position.
 * 
 * This function retrieves the Y coordinate of the mouse position relative to the 
 * top-left corner of the application window. The Y coordinate increases as the mouse 
 * moves downward.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1. The Y coordinate is pushed onto the Lua stack as an integer.
 * 
 * @usage
 * ```lua
 * local mouseY = raylib.GetMouseY()
 * print("Mouse Y position: " .. mouseY)
 * ```
 * 
 * @note This function is useful for implementing custom mouse interaction logic in your application.
 * @warning The Y coordinate is relative to the window, not the entire screen.
 */
int lua_GetMouseY(lua_State *L);

/**
 * @brief Gets the current position of the mouse as a Vector2.
 * 
 * This function retrieves the current position of the mouse pointer relative to 
 * the top-left corner of the application window. The position is returned as a 
 * Vector2 table with `x` and `y` components.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1. The mouse position is pushed onto the Lua stack as a Vector2 table `{x, y}`.
 * 
 * @usage
 * ```lua
 * local mousePos = raylib.GetMousePosition()
 * print("Mouse position: X=" .. mousePos.x .. ", Y=" .. mousePos.y)
 * ```
 * 
 * @note This function is useful for creating interactive elements that track the mouse position.
 * @warning The position is relative to the window, not the entire screen.
 */
int lua_GetMousePosition(lua_State *L);

/**
 * @brief Gets the movement of the mouse wheel.
 * 
 * This function retrieves the amount of movement of the mouse wheel since the last frame. 
 * Positive values indicate upward movement, while negative values indicate downward movement.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1. The mouse wheel movement is pushed onto the Lua stack as a float.
 * 
 * @usage
 * ```lua
 * local wheelMove = raylib.GetMouseWheelMove()
 * if wheelMove > 0 then
 *     print("Mouse wheel moved up")
 * elseif wheelMove < 0 then
 *     print("Mouse wheel moved down")
 * end
 * ```
 * 
 * @note This function is useful for zooming or scrolling functionality in applications.
 * @warning The movement is relative to the last frame, so it resets each frame.
 */
int lua_GetMouseWheelMove(lua_State *L);

/**
 * @brief Gets the frame time (time to process one frame) in seconds.
 * 
 * This function retrieves the time taken to render the last frame in seconds. 
 * It can be used to implement frame-rate-independent logic in your game or application.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1. The frame time is pushed onto the Lua stack as a float.
 * 
 * @usage
 * ```lua
 * local frameTime = raylib.GetFrameTime()
 * print("Time for last frame: " .. frameTime .. " seconds")
 * ```
 * 
 * @note Use frame time to normalize animations and movement across different frame rates.
 * @warning If the frame rate is capped, frame time may not reflect the actual frame time.
 */
int lua_GetFrameTime(lua_State *L);

/**
 * @brief Checks if a specific key was released during the current frame.
 * 
 * This function checks if a given key was released during the current frame. 
 * It only returns `true` on the frame that the key is released.
 * 
 * @param L A pointer to the current Lua state. The first argument on the stack is the key to check.
 * 
 * @return int Always returns 1. A boolean value is pushed onto the Lua stack (`true` if the key was released, `false` otherwise).
 * 
 * @usage
 * ```lua
 * if raylib.IsKeyReleased(raylib.KEY_SPACE) then
 *     print("Space key released!")
 * end
 * ```
 * 
 * @note This function is useful for triggering events that should only happen once when a key is released.
 * @warning Key codes are defined in the Raylib library (e.g., `raylib.KEY_SPACE`, `raylib.KEY_ENTER`, etc.).
 */
int lua_IsKeyReleased(lua_State *L);

/**
 * @brief Gets the width of the specified monitor.
 * 
 * This function retrieves the width (in pixels) of the specified monitor. 
 * The monitor is identified by its index, starting from 0.
 * 
 * @param L A pointer to the current Lua state. The first argument on the stack is the monitor index (integer).
 * 
 * @return int Always returns 1. The monitor width is pushed onto the Lua stack as an integer.
 * 
 * @usage
 * ```lua
 * local monitorWidth = raylib.GetMonitorWidth(0)
 * print("Monitor width: " .. monitorWidth)
 * ```
 * 
 * @note If the index is out of range, the width of the first monitor (index 0) is returned.
 * @warning Monitor indices start from 0. Use `raylib.GetMonitorCount()` to get the total number of monitors.
 */
int lua_GetMonitorWidth(lua_State *L);

/**
 * @brief Gets the height of the specified monitor.
 * 
 * This function retrieves the height (in pixels) of the specified monitor. 
 * The monitor is identified by its index, starting from 0.
 * 
 * @param L A pointer to the current Lua state. The first argument on the stack is the monitor index (integer).
 * 
 * @return int Always returns 1. The monitor height is pushed onto the Lua stack as an integer.
 * 
 * @usage
 * ```lua
 * local monitorHeight = raylib.GetMonitorHeight(0)
 * print("Monitor height: " .. monitorHeight)
 * ```
 * 
 * @note If the index is out of range, the height of the first monitor (index 0) is returned.
 * @warning Monitor indices start from 0. Use `raylib.GetMonitorCount()` to get the total number of monitors.
 */
int lua_GetMonitorHeight(lua_State *L);

/**
 * @brief Maximizes the application window.
 * 
 * This function maximizes the application window to occupy the full screen space, 
 * except for system taskbars or UI elements. 
 * 
 * @param L A pointer to the current Lua state. No arguments are required.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.MaximizeWindow()
 * ```
 * 
 * @note This function is useful for applications that need to provide a maximized windowed experience.
 * @warning This function has no effect if the window is already maximized.
 */
int lua_MaximizeWindow(lua_State *L);

/**
 * @brief Minimizes the application window.
 * 
 * This function minimizes the window to the system taskbar, making it inactive 
 * and hidden from the user's view.
 * 
 * @param L A pointer to the current Lua state. No arguments are required.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.MinimizeWindow()
 * ```
 * 
 * @note This function is useful for applications that need to programmatically minimize the window.
 * @warning This function has no effect if the window is already minimized.
 */
int lua_MinimizeWindow(lua_State *L);

/**
 * @brief Sets the title of the application window.
 * 
 * This function changes the title of the window to the specified text.
 * 
 * @param L A pointer to the current Lua state. The first argument on the stack is the new window title (string).
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetWindowTitle("My Custom Game Title")
 * ```
 * 
 * @note The window title is displayed in the title bar of the window, 
 * and it may also be used by the operating system in taskbars or window switchers.
 * @warning The title must be a valid UTF-8 encoded string.
 */
int lua_SetWindowTitle(lua_State *L);

/**
 * @brief Sets the position of the application window.
 * 
 * This function moves the window to the specified screen coordinates (x, y).
 * 
 * @param L A pointer to the current Lua state. The first two arguments on the stack are the x and y position (integers).
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetWindowPosition(100, 200)
 * ```
 * 
 * @note The window position is relative to the top-left corner of the primary monitor.
 * @warning If the window is in fullscreen mode, this function has no effect.
 */
int lua_SetWindowPosition(lua_State *L);

/**
 * @brief Sets the monitor on which the window is displayed.
 * 
 * This function moves the window to the specified monitor, identified by its index.
 * 
 * @param L A pointer to the current Lua state. The first argument on the stack is the monitor index (integer).
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetWindowMonitor(1) -- Moves the window to the second monitor
 * ```
 * 
 * @note Monitor indices start from 0. 
 * @warning If the index is out of range, the window may not move, 
 * and the behavior depends on the operating system's handling of out-of-bounds indices.
 */
int lua_SetWindowMonitor(lua_State *L);

/**
 * @brief Sets the size of the application window.
 * 
 * This function resizes the window to the specified width and height.
 * 
 * @param L A pointer to the current Lua state. The first two arguments on the stack are the width and height (integers).
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetWindowSize(800, 600)
 * ```
 * 
 * @note The minimum and maximum size of the window can be controlled with `SetWindowMinSize` and `SetWindowMaxSize`.
 * @warning If the specified width or height is less than the minimum allowed size, 
 * the window size may be clamped by the system.
 */
int lua_SetWindowSize(lua_State *L);

/**
 * @brief Sets configuration flags for the application window.
 * 
 * This function sets internal flags that change the behavior or properties of the window. 
 * These flags must be set before `InitWindow()` is called.
 * 
 * @param L A pointer to the current Lua state. The first argument on the stack is a set of configuration flags (integer bitmask).
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI)
 * ```
 * 
 * @note Flags must be combined using bitwise OR (|) to enable multiple features.
 * Available flags include:
 * - `FLAG_WINDOW_RESIZABLE`: Makes the window resizable.
 * - `FLAG_WINDOW_UNDECORATED`: Removes window title bar and border.
 * - `FLAG_WINDOW_TRANSPARENT`: Makes the window background transparent.
 * 
 * @warning This function must be called before `raylib.InitWindow()`. 
 * Calling it after the window is initialized has no effect.
 */
int lua_SetConfigFlags(lua_State *L);

/**
 * @brief Gets the width of the screen.
 * 
 * This function returns the width of the application window, which may be affected 
 * by DPI scaling or fullscreen mode.
 * 
 * @param L A pointer to the current Lua state. No arguments are required.
 * 
 * @return int Always returns 1 (integer result) representing the screen width in pixels.
 * 
 * @usage
 * ```lua
 * local width = raylib.GetScreenWidth()
 * print("Screen width:", width)
 * ```
 * 
 * @note The screen width may differ from the window width in cases where the application 
 * runs on a high-DPI display or when the window is in fullscreen mode.
 */
int lua_GetScreenWidth(lua_State *L);

/**
 * @brief Gets the height of the screen.
 * 
 * This function returns the height of the application window, which may be affected 
 * by DPI scaling or fullscreen mode.
 * 
 * @param L A pointer to the current Lua state. No arguments are required.
 * 
 * @return int Always returns 1 (integer result) representing the screen height in pixels.
 * 
 * @usage
 * ```lua
 * local height = raylib.GetScreenHeight()
 * print("Screen height:", height)
 * ```
 * 
 * @note The screen height may differ from the window height in cases where the application 
 * runs on a high-DPI display or when the window is in fullscreen mode.
 */
int lua_GetScreenHeight(lua_State *L);

/**
 * @brief Gets the number of connected monitors.
 * 
 * This function returns the total number of monitors connected to the system.
 * 
 * @param L A pointer to the current Lua state. No arguments are required.
 * 
 * @return int Always returns 1 (integer result) representing the number of monitors.
 * 
 * @usage
 * ```lua
 * local monitorCount = raylib.GetMonitorCount()
 * print("Number of connected monitors:", monitorCount)
 * ```
 * 
 * @note The primary monitor is typically indexed as monitor 0.
 */
int lua_GetMonitorCount(lua_State *L);

/**
 * @brief Gets the name of a specific monitor.
 * 
 * This function returns the name or description of the specified monitor.
 * 
 * @param L A pointer to the current Lua state. The first argument is the monitor index (integer), starting from 0.
 * 
 * @return int Always returns 1 (string result) containing the name of the monitor.
 * 
 * @usage
 * ```lua
 * local monitorName = raylib.GetMonitorName(0)
 * print("Primary monitor name:", monitorName)
 * ```
 * 
 * @note Monitor indices start from 0 for the primary monitor.
 * @warning If the monitor index is out of range, the behavior is undefined.
 */
int lua_GetMonitorName(lua_State *L);

/**
 * @brief Gets the physical width of a specific monitor in millimeters.
 * 
 * This function returns the physical width of the monitor, which may be useful for 
 * calculating DPI (dots per inch) or PPI (pixels per inch).
 * 
 * @param L A pointer to the current Lua state. The first argument is the monitor index (integer), starting from 0.
 * 
 * @return int Always returns 1 (integer result) representing the physical width of the monitor in millimeters.
 * 
 * @usage
 * ```lua
 * local widthMM = raylib.GetMonitorPhysicalWidth(0)
 * print("Monitor 0 physical width in mm:", widthMM)
 * ```
 * 
 * @note Monitor indices start from 0 for the primary monitor.
 * @warning If the monitor index is out of range, the behavior is undefined.
 */
int lua_GetMonitorPhysicalWidth(lua_State *L);

/**
 * @brief Gets the physical height of a specific monitor in millimeters.
 * 
 * This function returns the physical height of the monitor, which may be useful for 
 * calculating DPI (dots per inch) or PPI (pixels per inch).
 * 
 * @param L A pointer to the current Lua state. The first argument is the monitor index (integer), starting from 0.
 * 
 * @return int Always returns 1 (integer result) representing the physical height of the monitor in millimeters.
 * 
 * @usage
 * ```lua
 * local heightMM = raylib.GetMonitorPhysicalHeight(0)
 * print("Monitor 0 physical height in mm:", heightMM)
 * ```
 * 
 * @note Monitor indices start from 0 for the primary monitor.
 * @warning If the monitor index is out of range, the behavior is undefined.
 */
int lua_GetMonitorPhysicalHeight(lua_State *L);

/**
 * @brief Gets the refresh rate of a specific monitor.
 * 
 * This function returns the refresh rate (in Hz) of the specified monitor.
 * 
 * @param L A pointer to the current Lua state. The first argument is the monitor index (integer), starting from 0.
 * 
 * @return int Always returns 1 (integer result) representing the refresh rate of the monitor in Hertz (Hz).
 * 
 * @usage
 * ```lua
 * local refreshRate = raylib.GetMonitorRefreshRate(0)
 * print("Monitor 0 refresh rate:", refreshRate, "Hz")
 * ```
 * 
 * @note Monitor indices start from 0 for the primary monitor.
 * @warning If the monitor index is out of range, the behavior is undefined.
 */
int lua_GetMonitorRefreshRate(lua_State *L);

/**
 * @brief Gets the position of a specific monitor on the screen.
 * 
 * This function returns the position of the top-left corner of the specified monitor in screen coordinates.
 * 
 * @param L A pointer to the current Lua state. The first argument is the monitor index (integer), starting from 0.
 * 
 * @return int Always returns 1 (Vector2 result) representing the position of the monitor as a Vector2 {x, y}.
 * 
 * @usage
 * ```lua
 * local position = raylib.GetMonitorPosition(0)
 * print("Monitor 0 position: X =", position.x, ", Y =", position.y)
 * ```
 * 
 * @note Monitor indices start from 0 for the primary monitor.
 * @warning If the monitor index is out of range, the behavior is undefined.
 */
int lua_GetMonitorPosition(lua_State *L);

/**
 * @brief Gets the current time since the application started.
 * 
 * This function returns the current time (in seconds) as a high-precision double value.
 * 
 * @param L A pointer to the current Lua state. No arguments are required.
 * 
 * @return int Always returns 1 (double result) representing the elapsed time in seconds since the application started.
 * 
 * @usage
 * ```lua
 * local currentTime = raylib.GetTime()
 * print("Time since start:", currentTime, "seconds")
 * ```
 * 
 * @note This function provides a high-precision time value, which can be useful for animations or frame-time calculations.
 */
int lua_GetTime(lua_State *L);

/**
 * @brief Gets a random integer value between min and max (inclusive).
 * 
 * This function returns a random integer value within the specified range, inclusive of both min and max.
 * 
 * @param L A pointer to the current Lua state. The first argument is the minimum value (integer), and the second argument is the maximum value (integer).
 * 
 * @return int Always returns 1 (integer result) representing the random value between min and max.
 * 
 * @usage
 * ```lua
 * local randomValue = raylib.GetRandomValue(1, 100)
 * print("Random value between 1 and 100:", randomValue)
 * ```
 * 
 * @note The range [min, max] is inclusive, meaning both min and max can be returned as possible values.
 * @warning If min is greater than max, the behavior is undefined.
 */
int lua_GetRandomValue(lua_State *L);

/**
 * @brief Sets the target frames per second (FPS) for the application.
 * 
 * This function limits the application's frame rate to the specified FPS.
 * 
 * @param L A pointer to the current Lua state. The first argument is the target FPS (integer).
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetTargetFPS(60) -- Set the target FPS to 60
 * ```
 * 
 * @note Setting a lower FPS may help reduce CPU/GPU usage, while higher FPS can provide smoother animations.
 * @warning If an FPS of 0 or a negative value is specified, the behavior is undefined.
 */
int lua_SetTargetFPS(lua_State *L);

/**
 * @brief Gets the currently set target frames per second (FPS).
 * 
 * This function returns the target FPS previously set with `SetTargetFPS`.
 * 
 * @param L A pointer to the current Lua state. No arguments are required.
 * 
 * @return int Always returns 1 (integer result) representing the target FPS.
 * 
 * @usage
 * ```lua
 * local targetFPS = raylib.GetTargetFPS()
 * print("Current target FPS:", targetFPS)
 * ```
 * 
 * @note If no FPS has been explicitly set, this function may return the default FPS.
 */
int lua_GetTargetFPS(lua_State *L);

/**
 * @brief Checks if a specific key is currently being held down.
 * 
 * This function returns `true` if the specified key is being held down.
 * 
 * @param L A pointer to the current Lua state. The first argument is the key code (integer) corresponding to the key being checked.
 * 
 * @return int Always returns 1 (boolean result) where `true` means the key is being held down.
 * 
 * @usage
 * ```lua
 * local isSpaceDown = raylib.IsKeyDown(raylib.KEY_SPACE)
 * if isSpaceDown then
 *     print("Spacebar is being held down!")
 * end
 * ```
 * 
 * @note Key codes can be found in the raylib key constants (e.g., `raylib.KEY_A`, `raylib.KEY_SPACE`, etc.).
 */
int lua_IsKeyDown(lua_State *L);

/**
 * @brief Checks if a specific key is currently not being held down.
 * 
 * This function returns `true` if the specified key is not being held down.
 * 
 * @param L A pointer to the current Lua state. The first argument is the key code (integer) corresponding to the key being checked.
 * 
 * @return int Always returns 1 (boolean result) where `true` means the key is not being held down.
 * 
 * @usage
 * ```lua
 * local isEscapeUp = raylib.IsKeyUp(raylib.KEY_ESCAPE)
 * if isEscapeUp then
 *     print("Escape key is not being held down.")
 * end
 * ```
 * 
 * @note Key codes can be found in the raylib key constants (e.g., `raylib.KEY_A`, `raylib.KEY_SPACE`, etc.).
 */
int lua_IsKeyUp(lua_State *L);

/**
 * @brief Checks if a specific mouse button is currently being held down.
 * 
 * This function returns `true` if the specified mouse button is being pressed down.
 * 
 * @param L A pointer to the current Lua state. The first argument is the mouse button (integer) corresponding to the button being checked (e.g., `MOUSE_LEFT_BUTTON`, `MOUSE_RIGHT_BUTTON`, etc.).
 * 
 * @return int Always returns 1 (boolean result) where `true` means the button is being held down.
 * 
 * @usage
 * ```lua
 * local isLeftButtonDown = raylib.IsMouseButtonDown(raylib.MOUSE_LEFT_BUTTON)
 * if isLeftButtonDown then
 *     print("Left mouse button is being held down!")
 * end
 * ```
 * 
 * @note Mouse button constants can be found in raylib's mouse button definitions (e.g., `raylib.MOUSE_LEFT_BUTTON`, `raylib.MOUSE_RIGHT_BUTTON`, etc.).
 */
int lua_IsMouseButtonDown(lua_State *L);

/**
 * @brief Checks if a specific mouse button is currently up (not pressed).
 * 
 * This function returns `true` if the specified mouse button is not being pressed.
 * 
 * @param L A pointer to the current Lua state. The first argument is the mouse button (integer) corresponding to the button being checked (e.g., `MOUSE_LEFT_BUTTON`, `MOUSE_RIGHT_BUTTON`, etc.).
 * 
 * @return int Always returns 1 (boolean result) where `true` means the button is not being pressed.
 * 
 * @usage
 * ```lua
 * local isRightButtonUp = raylib.IsMouseButtonUp(raylib.MOUSE_RIGHT_BUTTON)
 * if isRightButtonUp then
 *     print("Right mouse button is not being held down.")
 * end
 * ```
 * 
 * @note Mouse button constants can be found in raylib's mouse button definitions (e.g., `raylib.MOUSE_LEFT_BUTTON`, `raylib.MOUSE_RIGHT_BUTTON`, etc.).
 */
int lua_IsMouseButtonUp(lua_State *L);

/**
 * @brief Sets the mouse position on the screen.
 * 
 * This function moves the mouse cursor to the specified position on the screen.
 * 
 * @param L A pointer to the current Lua state. The first argument is the X-coordinate (integer) and the second argument is the Y-coordinate (integer) for the new position.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetMousePosition(100, 150) -- Move the mouse cursor to position (100, 150)
 * ```
 * 
 * @note This function does not simulate a "mouse event" but simply moves the cursor to a new position.
 */
int lua_SetMousePosition(lua_State *L);

/**
 * @brief Sets the mouse offset relative to the window.
 * 
 * This function shifts the mouse's position by the specified offset values.
 * 
 * @param L A pointer to the current Lua state. The first argument is the X offset (integer) and the second argument is the Y offset (integer).
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetMouseOffset(10, -10) -- Shift the mouse cursor 10 pixels to the right and 10 pixels up
 * ```
 * 
 * @note This offset is relative to the window's current position.
 */
int lua_SetMouseOffset(lua_State *L);

/**
 * @brief Sets the scale for mouse input.
 * 
 * This function scales the mouse's movement and position relative to the screen. 
 * Useful for high-DPI displays or non-standard window sizes.
 * 
 * @param L A pointer to the current Lua state. The first argument is the X-axis scale (float) and the second argument is the Y-axis scale (float).
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetMouseScale(1.5, 1.5) -- Scale the mouse input by 1.5x in both X and Y directions
 * ```
 * 
 * @note The default scale is 1.0 for both axes.
 */
int lua_SetMouseScale(lua_State *L);

/**
 * @brief Gets the position of a touch input.
 * 
 * This function retrieves the position of a touch on the screen, useful for multi-touch devices.
 * 
 * @param L A pointer to the current Lua state. The first argument is the touch index (integer), starting from 0.
 * 
 * @return int Always returns 1 (Vector2 result) representing the X and Y position of the touch.
 * 
 * @usage
 * ```lua
 * local touchPos = raylib.GetTouchPosition(0) -- Get the position of the first touch
 * print("Touch position:", touchPos.x, touchPos.y)
 * ```
 * 
 * @note If no touch is detected, the function returns a zero Vector2.
 */
int lua_GetTouchPosition(lua_State *L);

/**
 * @brief Shows the mouse cursor on the screen.
 * 
 * Makes the mouse cursor visible if it is currently hidden.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.ShowCursor() -- Make the mouse cursor visible
 * ```
 * 
 * @note This function only affects the visibility of the cursor, not its functionality.
 */
int lua_ShowCursor(lua_State *L);

/**
 * @brief Hides the mouse cursor on the screen.
 * 
 * Makes the mouse cursor invisible while maintaining its functionality.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.HideCursor() -- Make the mouse cursor invisible
 * ```
 * 
 * @note The mouse can still interact with the screen, but it will not be visible.
 */
int lua_HideCursor(lua_State *L);

/**
 * @brief Checks if the cursor is currently hidden.
 * 
 * This function returns `true` if the cursor is hidden, otherwise `false`.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 1 (boolean result) indicating whether the cursor is hidden.
 * 
 * @usage
 * ```lua
 * local isHidden = raylib.IsCursorHidden()
 * print("Is the cursor hidden?", isHidden)
 * ```
 * 
 * @note The cursor can be hidden using `raylib.HideCursor()` or other methods.
 */
int lua_IsCursorHidden(lua_State *L);

/**
 * @brief Enables the mouse cursor.
 * 
 * Makes the mouse cursor visible and functional on the screen.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.EnableCursor() -- Enable the mouse cursor if it was disabled
 * ```
 * 
 * @note This function restores the default behavior of the cursor.
 */
int lua_EnableCursor(lua_State *L);

/**
 * @brief Disables the mouse cursor.
 * 
 * Makes the mouse cursor invisible and disables its interaction with the screen.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DisableCursor() -- Disable the mouse cursor interaction
 * ```
 * 
 * @note This function hides and deactivates the cursor. Use `raylib.EnableCursor()` to restore its functionality.
 */
int lua_DisableCursor(lua_State *L);

/**
 * @brief Gets the length of the clipboard text.
 * 
 * This function returns the number of characters in the clipboard text.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 1 (integer result) representing the length of the clipboard text.
 * 
 * @usage
 * ```lua
 * local textLength = raylib.GetClipboardTextLength()
 * print("Clipboard text length:", textLength)
 * ```
 * 
 * @note If the clipboard is empty or contains no text, this function returns 0.
 */
int lua_GetClipboardTextLength(lua_State *L);

/**
 * @brief Checks if the window is ready.
 * 
 * This function returns `true` if the window has been successfully initialized and is ready for use.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 1 (boolean result) indicating whether the window is ready.
 * 
 * @usage
 * ```lua
 * local isReady = raylib.IsWindowReady()
 * print("Is the window ready?", isReady)
 * ```
 * 
 * @note This function is useful for ensuring that rendering can begin without errors.
 */
int lua_IsWindowReady(lua_State *L);

/**
 * @brief Checks if the window is currently focused.
 * 
 * This function returns `true` if the window is the currently active and focused window.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 1 (boolean result) indicating whether the window is focused.
 * 
 * @usage
 * ```lua
 * local isFocused = raylib.IsWindowFocused()
 * print("Is the window focused?", isFocused)
 * ```
 * 
 * @note Useful for pausing gameplay or animations when the window loses focus.
 */
int lua_IsWindowFocused(lua_State *L);

/**
 * @brief Checks if the window is in fullscreen mode.
 * 
 * This function returns `true` if the window is currently in fullscreen mode.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 1 (boolean result) indicating whether the window is in fullscreen mode.
 * 
 * @usage
 * ```lua
 * local isFullscreen = raylib.IsWindowFullscreen()
 * print("Is the window in fullscreen mode?", isFullscreen)
 * ```
 * 
 * @note Fullscreen mode can be toggled using `raylib.ToggleFullscreen()`.
 */
int lua_IsWindowFullscreen(lua_State *L);

/**
 * @brief Checks if the window is currently hidden.
 * 
 * This function returns `true` if the window is currently hidden.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 1 (boolean result) indicating whether the window is hidden.
 * 
 * @usage
 * ```lua
 * local isHidden = raylib.IsWindowHidden()
 * print("Is the window hidden?", isHidden)
 * ```
 * 
 * @note Windows can be hidden using window flags or specific functions, and this function checks their visibility.
 */
int lua_IsWindowHidden(lua_State *L);

/**
 * @brief Checks if the window has been resized.
 * 
 * This function returns `true` if the window has been resized during the current frame.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 1 (boolean result) indicating whether the window has been resized.
 * 
 * @usage
 * ```lua
 * local isResized = raylib.IsWindowResized()
 * print("Was the window resized?", isResized)
 * ```
 * 
 * @note Useful for adjusting UI elements or other game elements that depend on window size.
 */
int lua_IsWindowResized(lua_State *L);

/**
 * @brief Checks if the window has a specific state.
 * 
 * This function returns `true` if the window has the specified state flag.
 * 
 * @param L A pointer to the current Lua state.
 * @param flag An integer representing the state flag to check.
 * 
 * @return int Always returns 1 (boolean result) indicating whether the window has the specified state.
 * 
 * @usage
 * ```lua
 * local hasState = raylib.IsWindowState(raylib.FLAG_WINDOW_RESIZABLE)
 * print("Is the window resizable?", hasState)
 * ```
 * 
 * @note Common state flags include `FLAG_FULLSCREEN_MODE`, `FLAG_WINDOW_RESIZABLE`, etc.
 */
int lua_IsWindowState(lua_State *L);

/**
 * @brief Sets a specific state for the window.
 * 
 * This function sets a state flag for the window, modifying its behavior.
 * 
 * @param L A pointer to the current Lua state.
 * @param flag An integer representing the state flag to set.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetWindowState(raylib.FLAG_FULLSCREEN_MODE)
 * print("The window is now in fullscreen mode")
 * ```
 * 
 * @note Use this function to change the window's behavior, such as enabling fullscreen or borderless windowed mode.
 */
int lua_SetWindowState(lua_State *L);

/**
 * @brief Clears a specific state for the window.
 * 
 * This function clears a previously set state flag for the window, reverting its behavior.
 * 
 * @param L A pointer to the current Lua state.
 * @param flag An integer representing the state flag to clear.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.ClearWindowState(raylib.FLAG_FULLSCREEN_MODE)
 * print("The window is no longer in fullscreen mode")
 * ```
 * 
 * @note Use this function to revert changes made with `raylib.SetWindowState()`.
 */
int lua_ClearWindowState(lua_State *L);

/**
 * @brief Toggles borderless windowed mode.
 * 
 * This function switches the window between regular windowed mode and borderless windowed mode.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.ToggleBorderlessWindowed()
 * print("The window is now in borderless windowed mode")
 * ```
 * 
 * @note Useful for switching between windowed and borderless modes during runtime.
 */
int lua_ToggleBorderlessWindowed(lua_State *L);

/**
 * @brief Sets the minimum size of the window.
 * 
 * This function defines the minimum width and height that the window can be resized to.
 * 
 * @param L A pointer to the current Lua state.
 * @param width An integer specifying the minimum width of the window.
 * @param height An integer specifying the minimum height of the window.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetWindowMinSize(800, 600)
 * print("The minimum window size is now 800x600")
 * ```
 * 
 * @note If the current window size is smaller than this, the window will automatically resize.
 */
int lua_SetWindowMinSize(lua_State *L);

/**
 * @brief Sets the maximum size of the window.
 * 
 * This function defines the maximum width and height that the window can be resized to.
 * 
 * @param L A pointer to the current Lua state.
 * @param width An integer specifying the maximum width of the window.
 * @param height An integer specifying the maximum height of the window.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetWindowMaxSize(1920, 1080)
 * print("The maximum window size is now 1920x1080")
 * ```
 * 
 * @note This function is useful to restrict how large a resizable window can get.
 */
int lua_SetWindowMaxSize(lua_State *L);

/**
 * @brief Sets the opacity of the window.
 * 
 * This function defines the opacity of the window, allowing you to make it more or less transparent.
 * 
 * @param L A pointer to the current Lua state.
 * @param opacity A float value between 0.0 (completely transparent) and 1.0 (fully opaque).
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetWindowOpacity(0.5)
 * print("The window is now 50% transparent")
 * ```
 * 
 * @note This function allows for visual effects, like dimming the window or making it semi-transparent.
 */
int lua_SetWindowOpacity(lua_State *L);

/**
 * @brief Sets the window as focused.
 * 
 * This function forces the window to be the active, focused window on the user's screen.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetWindowFocused()
 * print("The window is now focused")
 * ```
 * 
 * @note This can be useful for ensuring the window has input focus after a state change.
 */
int lua_SetWindowFocused(lua_State *L);

/**
 * @brief Gets the window handle.
 * 
 * This function returns a handle to the system window, which can be used for integration with other system-level APIs.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 1, pushing the window handle to the Lua stack.
 * 
 * @usage
 * ```lua
 * local handle = raylib.GetWindowHandle()
 * print("Window handle:", handle)
 * ```
 * 
 * @note The return value is platform-specific. It may be useful for advanced integrations.
 */
int lua_GetWindowHandle(lua_State *L);

/**
 * @brief Gets the current monitor.
 * 
 * This function returns the index of the monitor where the window is currently displayed.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 1, pushing the monitor index to the Lua stack.
 * 
 * @usage
 * ```lua
 * local monitorIndex = raylib.GetCurrentMonitor()
 * print("The window is currently on monitor:", monitorIndex)
 * ```
 * 
 * @note This can be useful for applications running on multi-monitor setups.
 */
int lua_GetCurrentMonitor(lua_State *L);

/**
 * @brief Gets the window's DPI scale.
 * 
 * This function returns the DPI (dots per inch) scaling factor for the window as a Vector2.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 1, pushing the DPI scale (Vector2) to the Lua stack.
 * 
 * @usage
 * ```lua
 * local scale = raylib.GetWindowScaleDPI()
 * print("DPI Scale X:", scale.x, "DPI Scale Y:", scale.y)
 * ```
 * 
 * @note This is useful for scaling UI elements to match high-DPI displays.
 */
int lua_GetWindowScaleDPI(lua_State *L);

/**
 * @brief Enables event waiting.
 * 
 * This function enables event waiting mode, which causes the program to wait for input events 
 * (like mouse or keyboard actions) before continuing. This can reduce CPU usage.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.EnableEventWaiting()
 * print("Event waiting mode enabled")
 * ```
 * 
 * @note This is useful for reducing CPU usage during periods of low activity.
 */
int lua_EnableEventWaiting(lua_State *L);

/**
 * @brief Disables event waiting.
 * 
 * This function disables event waiting mode, causing the program to continuously check for input events 
 * rather than waiting for them. This may increase CPU usage.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DisableEventWaiting()
 * print("Event waiting mode disabled")
 * ```
 * 
 * @note This is useful when you want to ensure smooth animations or handle input without delay.
 */
int lua_DisableEventWaiting(lua_State *L);

/**
 * @brief Checks if the cursor is on the screen.
 * 
 * This function checks if the cursor is currently within the boundaries of the screen.
 * 
 * @param L A pointer to the current Lua state. This function takes no arguments.
 * 
 * @return int Always returns 1, pushing a boolean value (true if cursor is on screen, false otherwise) to the Lua stack.
 * 
 * @usage
 * ```lua
 * local isCursorOnScreen = raylib.IsCursorOnScreen()
 * if isCursorOnScreen then
 *     print("Cursor is on the screen")
 * else
 *     print("Cursor is not on the screen")
 * end
 * ```
 * 
 * @note This can be useful for detecting when the user moves the cursor outside the window.
 */
int lua_IsCursorOnScreen(lua_State *L);

#endif