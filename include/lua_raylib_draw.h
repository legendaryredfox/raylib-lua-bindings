#ifndef RAYLIB_LUA_DRAW_H
#define RAYLIB_LUA_DRAW_H

#include "lua_raylib.h"

/**
 * @brief Starts a new frame for drawing on the screen.
 * 
 * This function must be called before any drawing functions to initialize the drawing process. 
 * It sets up the frame buffer and prepares the screen for rendering.
 * 
 * @param L A pointer to the current Lua state. This is a standard parameter in Lua C API functions 
 *          and allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note This function should be paired with `lua_EndDrawing` to complete the frame rendering process.
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * -- Drawing calls here
 * raylib.EndDrawing()
 * ```
 */
int lua_BeginDrawing(lua_State *L);

/**
 * @brief Ends the current frame and presents the drawn content to the screen.
 * 
 * This function finalizes the drawing process by submitting the current frame to the screen.
 * It must be called after `lua_BeginDrawing` to ensure proper rendering.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note This function should be called after all drawing calls have been made, following a call to `lua_BeginDrawing`.
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * -- Drawing calls here
 * raylib.EndDrawing()
 * ```
 */
int lua_EndDrawing(lua_State *L);

/**
 * @brief Clears the entire screen with the specified color.
 * 
 * This function fills the screen with a solid color, effectively erasing any previously drawn content.
 * It is typically called at the beginning of a frame to create a blank canvas for new drawing operations.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The color should be provided as a Lua table or as a predefined constant (e.g., `raylib.RAYWHITE`). 
 *       The color table must have fields for `r`, `g`, `b`, and optionally `a` (alpha), all in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE) -- Clear the screen with white color
 * raylib.EndDrawing()
 * ```
 */
int lua_ClearBackground(lua_State *L);

/**
 * @brief Draws a color-filled rectangle on the screen.
 * 
 * This function draws a solid color rectangle at the specified position with the given width, height, and color. 
 * It is commonly used to render 2D user interfaces, shapes, and background elements.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `posX` (int) - X-coordinate of the top-left corner of the rectangle.
 *       - `posY` (int) - Y-coordinate of the top-left corner of the rectangle.
 *       - `width` (int) - Width of the rectangle.
 *       - `height` (int) - Height of the rectangle.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawRectangle(50, 50, 200, 100, {r=255, g=0, b=0, a=255}) -- Draws a red rectangle
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawRectangle(lua_State *L);

/**
 * @brief Draws a color-filled circle on the screen.
 * 
 * This function draws a solid circle with the given center position, radius, and color. 
 * It can be used to create simple 2D shapes, indicators, and visual elements in a game or user interface.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `centerX` (int) - X-coordinate of the center of the circle.
 *       - `centerY` (int) - Y-coordinate of the center of the circle.
 *       - `radius` (float) - Radius of the circle.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawCircle(150, 150, 50, {r=0, g=0, b=255, a=255}) -- Draws a blue circle at (150, 150) with radius 50
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawCircle(lua_State *L);

/**
 * @brief Draws a thick line with customizable start and end points.
 * 
 * This function draws a line between two points with a specific thickness and color. 
 * It is useful for drawing paths, outlines, and visual effects.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `startX` (float) - X-coordinate of the start position.
 *       - `startY` (float) - Y-coordinate of the start position.
 *       - `endX` (float) - X-coordinate of the end position.
 *       - `endY` (float) - Y-coordinate of the end position.
 *       - `thickness` (float) - Thickness of the line.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawLineEx({x=100, y=100}, {x=300, y=200}, 5, {r=0, g=255, b=0, a=255}) -- Draws a thick green line
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawLineEx(lua_State *L);

/**
 * @brief Draws a color-filled ellipse on the screen.
 * 
 * This function draws an ellipse with the given center position, horizontal and vertical radii, and color. 
 * It is useful for creating 2D shapes, UI components, and graphical decorations.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `centerX` (int) - X-coordinate of the center of the ellipse.
 *       - `centerY` (int) - Y-coordinate of the center of the ellipse.
 *       - `radiusH` (float) - Horizontal radius of the ellipse.
 *       - `radiusV` (float) - Vertical radius of the ellipse.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawEllipse(200, 150, 60, 40, {r=255, g=0, b=255, a=255}) -- Draws a pink ellipse
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawEllipse(lua_State *L);

/**
 * @brief Draws the outline of a rectangle with specified parameters.
 * 
 * This function draws the border or outline of a rectangle using the specified position, width, height, 
 * and color. It does not fill the rectangle, only its edges. It is useful for drawing highlighted 
 * areas, UI borders, and interactive elements.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `posX` (int) - X-coordinate of the top-left corner of the rectangle.
 *       - `posY` (int) - Y-coordinate of the top-left corner of the rectangle.
 *       - `width` (int) - Width of the rectangle.
 *       - `height` (int) - Height of the rectangle.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawRectangleLines(50, 50, 200, 100, {r=255, g=0, b=0, a=255}) -- Draws a red rectangle outline
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawRectangleLines(lua_State *L);

/**
 * @brief Draws a rectangle with a gradient fill.
 * 
 * This function draws a rectangle that is filled with a vertical or horizontal gradient between two colors. 
 * It allows for smooth transitions between colors, which can be useful for UI elements, background effects, and game visuals.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `posX` (int) - X-coordinate of the top-left corner of the rectangle.
 *       - `posY` (int) - Y-coordinate of the top-left corner of the rectangle.
 *       - `width` (int) - Width of the rectangle.
 *       - `height` (int) - Height of the rectangle.
 *       - `color1` (table) - First color in the gradient (top or left).
 *       - `color2` (table) - Second color in the gradient (bottom or right).
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawRectangleGradient(100, 100, 150, 75, {r=0, g=255, b=0, a=255}, {r=0, g=0, b=255, a=255}) -- Draws a green-to-blue gradient
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawRectangleGradient(lua_State *L);

/**
 * @brief Draws a rounded rectangle with specified parameters.
 * 
 * This function draws a rectangle with rounded corners. The size of the rounded corners is controlled 
 * by the `roundness` parameter. This is useful for creating smooth and visually appealing user interfaces.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `posX` (int) - X-coordinate of the top-left corner of the rectangle.
 *       - `posY` (int) - Y-coordinate of the top-left corner of the rectangle.
 *       - `width` (int) - Width of the rectangle.
 *       - `height` (int) - Height of the rectangle.
 *       - `roundness` (float) - Controls the roundness of the rectangle's corners (value between 0.0 and 1.0).
 *       - `segments` (int) - Number of segments used to draw the rounded corners.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawRectangleRounded(50, 50, 200, 100, 0.25, 10, {r=255, g=0, b=0, a=255}) -- Draws a red rounded rectangle
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawRectangleRounded(lua_State *L);

/**
 * @brief Draws a line strip with specified parameters.
 * 
 * This function draws a line strip, which is a series of connected line segments. The line connects 
 * multiple points sequentially, forming a continuous path. It is useful for drawing paths, custom outlines, 
 * or interactive graphical elements.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `points` (table) - An array of points (Vector2) representing the vertices of the line strip.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * local points = {
 *     {x=50, y=50}, 
 *     {x=100, y=100}, 
 *     {x=150, y=50}, 
 *     {x=200, y=100}
 * }
 * raylib.DrawLineStrip(points, {r=255, g=0, b=0, a=255}) -- Draws a red zig-zag line strip
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawLineStrip(lua_State *L);

/**
 * @brief Draws a polygon with specified parameters.
 * 
 * This function draws a filled polygon with the specified number of sides, position, radius, 
 * rotation, and color. It is useful for creating shapes such as hexagons, pentagons, or custom 
 * multi-sided polygons.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `center` (table) - The center position of the polygon as a Vector2 `{x, y}`.
 *       - `sides` (int) - The number of sides of the polygon (e.g., 3 for a triangle, 6 for a hexagon).
 *       - `radius` (float) - The radius of the polygon (distance from center to vertex).
 *       - `rotation` (float) - The rotation of the polygon in degrees.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawPoly({x=200, y=200}, 6, 50, 45, {r=0, g=0, b=255, a=255}) -- Draws a blue hexagon rotated 45 degrees
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawPoly(lua_State *L);

/**
 * @brief Draws the outline of a polygon with specified parameters.
 * 
 * This function draws the outline of a polygon without filling it. The polygon is drawn with the 
 * specified number of sides, position, radius, rotation, and color. It is useful for creating 
 * wireframe shapes, path outlines, and other UI elements.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `center` (table) - The center position of the polygon as a Vector2 `{x, y}`.
 *       - `sides` (int) - The number of sides of the polygon (e.g., 3 for a triangle, 6 for a hexagon).
 *       - `radius` (float) - The radius of the polygon (distance from center to vertex).
 *       - `rotation` (float) - The rotation of the polygon in degrees.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawPolyLines({x=200, y=200}, 5, 50, 0, {r=255, g=0, b=0, a=255}) -- Draws a red pentagon outline
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawPolyLines(lua_State *L);

/**
 * @brief Draws the outline of a polygon with extended parameters.
 * 
 * This function draws the outline of a polygon with the option to control the thickness of the lines. 
 * The polygon is drawn with the specified number of sides, position, radius, rotation, and color. 
 * It is useful for creating custom visual effects, thicker wireframes, or highlighted outlines.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `center` (table) - The center position of the polygon as a Vector2 `{x, y}`.
 *       - `sides` (int) - The number of sides of the polygon (e.g., 3 for a triangle, 6 for a hexagon).
 *       - `radius` (float) - The radius of the polygon (distance from center to vertex).
 *       - `rotation` (float) - The rotation of the polygon in degrees.
 *       - `thickness` (float) - The thickness of the outline in pixels.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawPolyLinesEx({x=300, y=300}, 8, 40, 30, 5, {r=0, g=255, b=0, a=255}) -- Draws a green octagon outline with 5px thick borders
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawPolyLinesEx(lua_State *L);

/**
 * @brief Draws a 3D grid with specified parameters.
 * 
 * This function draws a 3D grid of lines centered on the origin of the world space. It is useful 
 * for debugging, aligning objects, and providing a reference for world space positioning. The 
 * grid can be customized in terms of size, spacing, and line thickness.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `slices` (int) - The number of divisions for the grid (the total number of lines will be `slices * 2`).
 *       - `spacing` (float) - The space between each line in world units.
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawGrid(10, 1.0) -- Draws a 10x10 grid with 1.0 unit spacing
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawGrid(lua_State *L);

/**
 * @brief Draws a sector of a circle with specified parameters.
 * 
 * This function draws a portion of a circle, also known as a "sector" or "wedge". It is useful for 
 * creating pie charts, radial menus, and other similar visual effects. The sector is defined by 
 * its center, radius, start and end angles, and number of segments to smooth out the curve.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `center` (table) - The center position of the circle as a Vector2 `{x, y}`.
 *       - `radius` (float) - The radius of the sector.
 *       - `startAngle` (float) - The starting angle of the sector in degrees.
 *       - `endAngle` (float) - The ending angle of the sector in degrees.
 *       - `segments` (int) - The number of segments used to draw the curve (higher values produce smoother edges).
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawCircleSector({x=400, y=300}, 100, 0, 90, 32, {r=255, g=0, b=0, a=255}) -- Draws a red quarter-circle
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawCircleSector(lua_State *L);

/**
 * @brief Draws the outline of a sector of a circle with specified parameters.
 * 
 * This function draws the outline of a circular sector (like a "wedge" or "slice"). It is useful 
 * for highlighting specific sections of a pie chart, drawing gauge indicators, or creating visual 
 * emphasis on circular sections. The sector is defined by its center, radius, start and end angles, 
 * and the number of segments for smoothness.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `center` (table) - The center position of the circle as a Vector2 `{x, y}`.
 *       - `radius` (float) - The radius of the sector.
 *       - `startAngle` (float) - The starting angle of the sector in degrees.
 *       - `endAngle` (float) - The ending angle of the sector in degrees.
 *       - `segments` (int) - The number of segments used to draw the curve (higher values produce smoother edges).
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawCircleSectorLines({x=400, y=300}, 100, 0, 180, 32, {r=0, g=0, b=255, a=255}) -- Draws a blue semi-circle outline
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawCircleSectorLines(lua_State *L);

/**
 * @brief Draws a rectangle with a vertical gradient fill.
 * 
 * This function draws a rectangle with a vertical gradient, where the top of the rectangle 
 * is one color and the bottom is another. It is useful for background effects, gradient-based 
 * health bars, and more. The gradient is drawn from top to bottom.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `posX` (int) - The x-coordinate of the top-left corner of the rectangle.
 *       - `posY` (int) - The y-coordinate of the top-left corner of the rectangle.
 *       - `width` (int) - The width of the rectangle.
 *       - `height` (int) - The height of the rectangle.
 *       - `top` (table) - The color for the top of the rectangle, as a table with `r`, `g`, `b`, and optional `a` components.
 *       - `bottom` (table) - The color for the bottom of the rectangle, as a table with `r`, `g`, `b`, and optional `a` components.
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawRectangleGradientV(100, 100, 200, 200, {r=255, g=0, b=0, a=255}, {r=0, g=0, b=255, a=255}) -- Red to blue vertical gradient
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawRectangleGradientV(lua_State *L);

/**
 * @brief Draws a rectangle with an extended gradient fill.
 * 
 * This function draws a rectangle with a gradient that allows control over the colors of each 
 * vertex. The gradient is applied diagonally, and it supports different colors at each of the 
 * four corners (top-left, top-right, bottom-left, bottom-right). It is useful for more complex 
 * gradient effects, custom UIs, and artistic effects.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `rec` (table) - A table representing the rectangle as `{x, y, width, height}`.
 *       - `topLeft` (table) - The color of the top-left corner, as a table with `r`, `g`, `b`, and optional `a` components.
 *       - `topRight` (table) - The color of the top-right corner, as a table with `r`, `g`, `b`, and optional `a` components.
 *       - `bottomLeft` (table) - The color of the bottom-left corner, as a table with `r`, `g`, `b`, and optional `a` components.
 *       - `bottomRight` (table) - The color of the bottom-right corner, as a table with `r`, `g`, `b`, and optional `a` components.
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawRectangleGradientEx({x=100, y=100, width=200, height=200}, 
 *     {r=255, g=0, b=0, a=255}, -- Top-left red
 *     {r=0, g=255, b=0, a=255}, -- Top-right green
 *     {r=0, g=0, b=255, a=255}, -- Bottom-left blue
 *     {r=255, g=255, b=0, a=255} -- Bottom-right yellow
 * )
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawRectangleGradientEx(lua_State *L);

/**
 * @brief Draws a circle with a gradient fill.
 * 
 * This function draws a circle with a gradient fill, transitioning from an inner color 
 * to an outer color. It is useful for creating radial gradient effects, highlighting 
 * circular buttons, and enhancing visual aesthetics.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `centerX` (int) - The x-coordinate of the center of the circle.
 *       - `centerY` (int) - The y-coordinate of the center of the circle.
 *       - `radius` (float) - The radius of the circle.
 *       - `innerColor` (table) - The color at the center of the circle, as a table with `r`, `g`, `b`, and optional `a` components.
 *       - `outerColor` (table) - The color at the edge of the circle, as a table with `r`, `g`, `b`, and optional `a` components.
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawCircleGradient(400, 300, 100, {r=255, g=0, b=0, a=255}, {r=0, g=0, b=255, a=255}) -- Red to blue radial gradient
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawCircleGradient(lua_State *L);

/**
 * @brief Draws a line between two points.
 * 
 * This function draws a straight line between two points with a specified color. 
 * It is useful for creating visual guides, gridlines, and other simple line-based 
 * graphics. The line is drawn from the starting position to the ending position.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `startX` (int) - The x-coordinate of the start of the line.
 *       - `startY` (int) - The y-coordinate of the start of the line.
 *       - `endX` (int) - The x-coordinate of the end of the line.
 *       - `endY` (int) - The y-coordinate of the end of the line.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawLine(100, 100, 500, 300, {r=0, g=0, b=0, a=255}) -- Black line from (100,100) to (500,300)
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawLine(lua_State *L);

/**
 * @brief Draws a Bezier line with specified parameters.
 * 
 * This function draws a cubic Bezier curve between two points, using control points to 
 * define the curve's shape. Bezier curves are widely used in graphic design, 
 * animation, and UI/UX design for smooth transitions and animations.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `startPos` (table) - The start position of the line as a Vector2 `{x, y}`.
 *       - `endPos` (table) - The end position of the line as a Vector2 `{x, y}`.
 *       - `thick` (float) - The thickness of the Bezier curve line.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawLineBezier({x=100, y=100}, {x=400, y=400}, 5, {r=0, g=255, b=0, a=255}) -- Green Bezier curve
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawLineBezier(lua_State *L);

/**
 * @brief Draws a triangle with specified parameters.
 * 
 * This function draws a filled triangle using three vertices. It is useful for creating 
 * simple shapes, meshes, and geometric designs. The triangle is filled with a color 
 * specified in the arguments.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `v1` (table) - The first vertex of the triangle as a Vector2 `{x, y}`.
 *       - `v2` (table) - The second vertex of the triangle as a Vector2 `{x, y}`.
 *       - `v3` (table) - The third vertex of the triangle as a Vector2 `{x, y}`.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawTriangle({x=100, y=100}, {x=200, y=300}, {x=300, y=100}, {r=0, g=0, b=255, a=255}) -- Blue filled triangle
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawTriangle(lua_State *L);

/**
 * @brief Draws the outline of a triangle with specified parameters.
 * 
 * This function draws the outline of a triangle using three vertices. It is useful for 
 * creating wireframe graphics, debugging geometric shapes, and outlining designs.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `v1` (table) - The first vertex of the triangle as a Vector2 `{x, y}`.
 *       - `v2` (table) - The second vertex of the triangle as a Vector2 `{x, y}`.
 *       - `v3` (table) - The third vertex of the triangle as a Vector2 `{x, y}`.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawTriangleLines({x=100, y=100}, {x=200, y=300}, {x=300, y=100}, {r=255, g=0, b=0, a=255}) -- Red triangle outline
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawTriangleLines(lua_State *L);

/**
 * @brief Draws a strip of connected triangles using a list of vertices.
 * 
 * This function draws a series of connected triangles that share vertices. It is useful 
 * for constructing complex shapes, rendering mesh data, and creating simple terrain-like 
 * structures. Each set of three consecutive points defines a new triangle in the strip.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `points` (table) - An array of Vector2 points `{ {x, y}, {x, y}, ... }` that define the vertices of the triangle strip.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawTriangleStrip({{x=100, y=100}, {x=150, y=50}, {x=200, y=100}, {x=250, y=50}}, {r=0, g=255, b=0, a=255}) -- Green triangle strip
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawTriangleStrip(lua_State *L);

/**
 * @brief Draws a ring with specified parameters.
 * 
 * This function draws a filled ring (donut-like shape) defined by a center point, an inner 
 * radius, an outer radius, and angular segments. It is useful for creating circular UI 
 * elements, charts, and visual effects.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `center` (table) - The center position of the ring as a Vector2 `{x, y}`.
 *       - `innerRadius` (number) - The inner radius of the ring.
 *       - `outerRadius` (number) - The outer radius of the ring.
 *       - `startAngle` (number) - The starting angle of the ring sector (in degrees).
 *       - `endAngle` (number) - The ending angle of the ring sector (in degrees).
 *       - `segments` (number) - The number of segments to divide the ring into.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawRing({x=200, y=200}, 50, 100, 0, 270, 36, {r=255, g=0, b=0, a=255}) -- Red 3/4 ring
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawRing(lua_State *L);

/**
 * @brief Draws the outline of a ring with specified parameters.
 * 
 * This function draws the outline of a ring (donut-like shape) defined by a center point, 
 * an inner radius, an outer radius, and angular segments. It is useful for creating wireframe 
 * ring graphics, debugging UI elements, and outlining circular designs.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `center` (table) - The center position of the ring as a Vector2 `{x, y}`.
 *       - `innerRadius` (number) - The inner radius of the ring.
 *       - `outerRadius` (number) - The outer radius of the ring.
 *       - `startAngle` (number) - The starting angle of the ring sector (in degrees).
 *       - `endAngle` (number) - The ending angle of the ring sector (in degrees).
 *       - `segments` (number) - The number of segments to divide the ring into.
 *       - `color` (table) - Color table with `r`, `g`, `b`, and optional `a` components in the range [0, 255].
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawRingLines({x=200, y=200}, 50, 100, 0, 360, 36, {r=0, g=0, b=255, a=255}) -- Blue full ring outline
 * raylib.EndDrawing()
 * ```
 */
int lua_DrawRingLines(lua_State *L);

#endif