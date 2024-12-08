#ifndef LUA_RAYLIB_SHAPES_H
#define LUA_RAYLIB_SHAPES_H

#include "lua.h"
#include "lauxlib.h"
#include "raylib.h"

/**
 * @brief Sets the texture to be used for shapes.
 * 
 * This function sets the texture and source rectangle to be used for drawing shapes like rectangles, circles, and other primitives.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Texture2D texture`: The texture to be used for shapes.
 *  - `Rectangle source`: The source rectangle from the texture to be used for shapes.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local texture = raylib.LoadTexture("path/to/texture.png")
 * local source = { x = 0, y = 0, width = 64, height = 64 }
 * raylib.SetShapesTexture(texture, source)
 * ```
 * 
 * @note This function allows for textured shapes instead of solid colors. The source rectangle determines which part of the texture to use.
 */
int lua_SetShapesTexture(lua_State *L);

/**
 * @brief Gets the current texture used for shapes.
 * 
 * This function retrieves the texture currently set for shapes drawing.
 * 
 * @param L A pointer to the current Lua state. No arguments are required.
 * 
 * @return int Always returns 1 (Texture2D result).
 * 
 * @usage
 * ```lua
 * local texture = raylib.GetShapesTexture()
 * print("Current shapes texture:", texture)
 * ```
 * 
 * @note This function is useful for querying the current shape texture to restore it later.
 */
int lua_GetShapesTexture(lua_State *L);

/**
 * @brief Gets the source rectangle of the current shapes texture.
 * 
 * This function retrieves the source rectangle used for the current texture in shapes drawing.
 * 
 * @param L A pointer to the current Lua state. No arguments are required.
 * 
 * @return int Always returns 1 (Rectangle result).
 * 
 * @usage
 * ```lua
 * local rect = raylib.GetShapesTextureRectangle()
 * print("Source rectangle:", rect.x, rect.y, rect.width, rect.height)
 * ```
 * 
 * @note This function allows you to know which part of the texture is being used for shapes, useful when handling multiple texture regions.
 */
int lua_GetShapesTextureRectangle(lua_State *L);

/**
 * @brief Draws a pixel at the specified position with the specified color.
 * 
 * This function draws an individual pixel on the screen at the given coordinates with the specified color.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `int posX`: The X position where the pixel will be drawn.
 *  - `int posY`: The Y position where the pixel will be drawn.
 *  - `Color color`: The color of the pixel to be drawn.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawPixel(100, 150, { r = 255, g = 0, b = 0, a = 255 }) -- Draw a red pixel at (100, 150)
 * ```
 * 
 * @note This function is slow for large-scale pixel drawing, so it's recommended to use image manipulation for efficiency.
 */
int lua_DrawPixel(lua_State *L);

/**
 * @brief Draws a pixel at the specified position (Vector2) with the specified color.
 * 
 * This function draws a pixel on the screen at the given position using a `Vector2` to specify the position.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Vector2 position`: The position where the pixel will be drawn.
 *  - `Color color`: The color of the pixel to be drawn.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawPixelV({ x = 100, y = 150 }, { r = 255, g = 0, b = 0, a = 255 }) -- Draw a red pixel at (100, 150)
 * ```
 * 
 * @note This function is a more flexible version of `DrawPixel` since it accepts a `Vector2` instead of two separate coordinates.
 */
int lua_DrawPixelV(lua_State *L);

/**
 * @brief Draws a line between two points (Vector2).
 * 
 * This function draws a line between two points using `Vector2` for start and end positions.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Vector2 startPos`: The starting position of the line.
 *  - `Vector2 endPos`: The ending position of the line.
 *  - `Color color`: The color of the line.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawLineV({ x = 50, y = 50 }, { x = 200, y = 200 }, { r = 0, g = 255, b = 0, a = 255 }) -- Draw a green line from (50, 50) to (200, 200)
 * ```
 * 
 * @note This function is useful for drawing diagonal or custom-angle lines on the screen.
 */
int lua_DrawLineV(lua_State *L);

/**
 * @brief Draws a circle at the specified position (Vector2) with the specified radius and color.
 * 
 * This function draws a filled circle on the screen using `Vector2` to specify its center position.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Vector2 center`: The center position of the circle.
 *  - `float radius`: The radius of the circle.
 *  - `Color color`: The color of the circle.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawCircleV({ x = 100, y = 100 }, 50, { r = 0, g = 0, b = 255, a = 255 }) -- Draw a blue circle at (100, 100) with a radius of 50
 * ```
 * 
 * @note This function is useful for drawing centered circles, and the `Vector2` allows for more flexible control of the position.
 */
int lua_DrawCircleV(lua_State *L);

/**
 * @brief Draws the outline of a circle at the specified position with the specified radius and color.
 * 
 * This function draws an outline of a circle at the specified position with a given radius and color.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `int centerX`: The X coordinate of the circle's center.
 *  - `int centerY`: The Y coordinate of the circle's center.
 *  - `float radius`: The radius of the circle.
 *  - `Color color`: The color of the circle outline.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawCircleLines(150, 150, 75, { r = 255, g = 0, b = 0, a = 255 }) -- Draw a red circle outline at (150, 150) with a radius of 75
 * ```
 * 
 * @note Unlike `DrawCircle`, this function only draws the outline of the circle instead of filling it.
 */
int lua_DrawCircleLines(lua_State *L);

/**
 * @brief Draws the outline of a circle at the specified position (Vector2) with the specified radius and color.
 * 
 * This function draws the outline of a circle at a given position using a `Vector2` for the center position.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Vector2 center`: The center position of the circle.
 *  - `float radius`: The radius of the circle.
 *  - `Color color`: The color of the circle outline.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawCircleLinesV({ x = 100, y = 100 }, 50, { r = 255, g = 255, b = 0, a = 255 }) -- Draw a yellow circle outline at (100, 100) with a radius of 50
 * ```
 * 
 * @note This function is similar to `DrawCircleLines`, but it allows for the position to be specified using a `Vector2`.
 */
int lua_DrawCircleLinesV(lua_State *L);

/**
 * @brief Draws the outline of an ellipse at the specified position with the specified radii and color.
 * 
 * This function draws the outline of an ellipse centered at a given position with the specified horizontal and vertical radii.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `int centerX`: The X coordinate of the ellipse center.
 *  - `int centerY`: The Y coordinate of the ellipse center.
 *  - `float radiusH`: The horizontal radius of the ellipse.
 *  - `float radiusV`: The vertical radius of the ellipse.
 *  - `Color color`: The color of the ellipse outline.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawEllipseLines(200, 150, 80, 50, { r = 0, g = 255, b = 255, a = 255 }) -- Draw a cyan ellipse outline centered at (200, 150) with horizontal radius 80 and vertical radius 50
 * ```
 * 
 * @note This function is useful for drawing ellipses with different horizontal and vertical radii, unlike `DrawCircleLines`, which uses a single radius.
 */
int lua_DrawEllipseLines(lua_State *L);

/**
 * @brief Draws a rectangle at the specified position (Vector2) with the specified width, height, and color.
 * 
 * This function draws a rectangle at a specified position using a `Vector2` to define the position.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Vector2 position`: The position where the top-left corner of the rectangle will be drawn.
 *  - `Vector2 size`: The size of the rectangle (width and height) represented as a `Vector2`.
 *  - `Color color`: The color of the rectangle.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawRectangleV({ x = 50, y = 50 }, { x = 200, y = 100 }, { r = 0, g = 0, b = 255, a = 255 }) -- Draw a blue rectangle at (50, 50) with width 200 and height 100
 * ```
 * 
 * @note This function is similar to `DrawRectangle`, but it allows for the position and size to be specified using `Vector2` values.
 */
int lua_DrawRectangleV(lua_State *L);

/**
 * @brief Draws a rectangle using a Rectangle struct.
 * 
 * This function draws a rectangle at the specified position, width, and height using a `Rectangle` struct.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Rectangle rec`: The rectangle to be drawn, with properties `x`, `y`, `width`, and `height`.
 *  - `Color color`: The color of the rectangle.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawRectangleRec({ x = 50, y = 50, width = 200, height = 100 }, { r = 255, g = 0, b = 0, a = 255 }) -- Draw a red rectangle at (50, 50) with width 200 and height 100
 * ```
 * 
 * @note This function is similar to `DrawRectangle`, but it uses a `Rectangle` struct to specify the rectangle's position, width, and height.
 */
int lua_DrawRectangleRec(lua_State *L);

/**
 * @brief Draws a rectangle with the specified position, size, and rotation.
 * 
 * This function draws a rectangle with a given position, size, origin, and rotation.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Rectangle rec`: The rectangle to be drawn, with properties `x`, `y`, `width`, and `height`.
 *  - `Vector2 origin`: The point of origin used to rotate the rectangle.
 *  - `float rotation`: The angle of rotation (in degrees) for the rectangle.
 *  - `Color color`: The color of the rectangle.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawRectanglePro({ x = 100, y = 100, width = 150, height = 50 }, { x = 75, y = 25 }, 45, { r = 255, g = 255, b = 0, a = 255 }) -- Draw a yellow rotated rectangle
 * ```
 * 
 * @note This function allows for rotation of the rectangle around a specified origin point, unlike `DrawRectangle`.
 */
int lua_DrawRectanglePro(lua_State *L);

/**
 * @brief Draws a rectangle with a horizontal gradient.
 * 
 * This function draws a rectangle with a horizontal gradient that transitions from one color to another.
 * 
 * @param L A pointer to the current Lua state. Expects 6 arguments:
 *  - `int posX`: The X position of the top-left corner of the rectangle.
 *  - `int posY`: The Y position of the top-left corner of the rectangle.
 *  - `int width`: The width of the rectangle.
 *  - `int height`: The height of the rectangle.
 *  - `Color left`: The color on the left side of the gradient.
 *  - `Color right`: The color on the right side of the gradient.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawRectangleGradientH(50, 50, 200, 100, { r = 255, g = 0, b = 0, a = 255 }, { r = 0, g = 0, b = 255, a = 255 }) -- Draw a gradient from red to blue
 * ```
 * 
 * @note The gradient transition occurs horizontally from left to right.
 */
int lua_DrawRectangleGradientH(lua_State *L);

/**
 * @brief Draws the outline of a rectangle with extended parameters.
 * 
 * This function draws the outline of a rectangle with an adjustable line thickness.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Rectangle rec`: The rectangle to be outlined, with properties `x`, `y`, `width`, and `height`.
 *  - `float lineThick`: The thickness of the rectangle outline.
 *  - `Color color`: The color of the outline.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawRectangleLinesEx({ x = 100, y = 100, width = 150, height = 50 }, 5, { r = 0, g = 255, b = 0, a = 255 }) -- Draw a green rectangle outline with 5px thickness
 * ```
 * 
 * @note This function allows for control of the outline thickness, unlike `DrawRectangleLines`, which uses a default thickness.
 */
int lua_DrawRectangleLinesEx(lua_State *L);

/**
 * @brief Draws a linear spline.
 * 
 * This function draws a linear spline connecting multiple points.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector2[] points`: An array of points representing the spline path.
 *  - `int pointCount`: The number of points in the array.
 *  - `float thick`: The thickness of the spline line.
 *  - `Color color`: The color of the spline line.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawSplineLinear({ { x = 50, y = 50 }, { x = 100, y = 100 }, { x = 150, y = 50 } }, 3, 2, { r = 255, g = 0, b = 0, a = 255 }) -- Draw a red linear spline through 3 points
 * ```
 * 
 * @note A linear spline is a simple path made by connecting points with straight line segments.
 */
int lua_DrawSplineLinear(lua_State *L);

/**
 * @brief Draws a basis spline.
 * 
 * This function draws a smooth spline that passes near the given points, but not necessarily through them, using a B-Spline algorithm.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector2[] points`: An array of points representing the spline path.
 *  - `int pointCount`: The number of points in the array.
 *  - `float thick`: The thickness of the spline line.
 *  - `Color color`: The color of the spline line.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawSplineBasis({ { x = 50, y = 50 }, { x = 100, y = 100 }, { x = 150, y = 50 }, { x = 200, y = 100 } }, 4, 2, { r = 0, g = 255, b = 0, a = 255 }) -- Draw a green basis spline
 * ```
 * 
 * @note A basis spline is a smooth curve that does not necessarily pass through the control points.
 */
int lua_DrawSplineBasis(lua_State *L);

/**
 * @brief Draws a Catmull-Rom spline.
 * 
 * This function draws a smooth curve that passes through each of the control points using the Catmull-Rom algorithm.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector2[] points`: An array of points representing the spline path.
 *  - `int pointCount`: The number of points in the array.
 *  - `float thick`: The thickness of the spline line.
 *  - `Color color`: The color of the spline line.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawSplineCatmullRom({ { x = 50, y = 50 }, { x = 100, y = 100 }, { x = 150, y = 50 }, { x = 200, y = 100 } }, 4, 2, { r = 0, g = 0, b = 255, a = 255 }) -- Draw a blue Catmull-Rom spline
 * ```
 * 
 * @note A Catmull-Rom spline is a type of interpolating spline, meaning it passes through the control points.
 */
int lua_DrawSplineCatmullRom(lua_State *L);

/**
 * @brief Draws a quadratic Bezier spline.
 * 
 * This function draws a smooth curve that passes through the first and last points, while the second point acts as a control point that defines the curve's shape.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector2[] points`: An array of points representing the control points.
 *  - `int pointCount`: The number of points in the array (must be 3 for quadratic Bezier).
 *  - `float thick`: The thickness of the spline line.
 *  - `Color color`: The color of the spline line.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawSplineBezierQuadratic({ { x = 50, y = 50 }, { x = 125, y = 200 }, { x = 200, y = 50 } }, 3, 2, { r = 255, g = 0, b = 255, a = 255 }) -- Draw a purple quadratic Bezier spline
 * ```
 * 
 * @note A quadratic Bezier spline requires exactly 3 control points: a start point, a control point, and an end point.
 */
int lua_DrawSplineBezierQuadratic(lua_State *L);

/**
 * @brief Draws a cubic Bezier spline.
 * 
 * This function draws a smooth curve that passes through the first and last points, while the second and third points act as control points that define the curve's shape.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector2[] points`: An array of points representing the control points.
 *  - `int pointCount`: The number of points in the array (must be 4 for cubic Bezier).
 *  - `float thick`: The thickness of the spline line.
 *  - `Color color`: The color of the spline line.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawSplineBezierCubic({ { x = 50, y = 50 }, { x = 100, y = 200 }, { x = 150, y = 0 }, { x = 200, y = 50 } }, 4, 2, { r = 255, g = 165, b = 0, a = 255 }) -- Draw an orange cubic Bezier spline
 * ```
 * 
 * @note A cubic Bezier spline requires exactly 4 control points: a start point, two control points, and an end point.
 */
int lua_DrawSplineBezierCubic(lua_State *L);

/**
 * @brief Draws a segment of a linear spline between two points.
 * 
 * This function draws a straight line between two points, forming a segment of a linear spline.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector2 p1`: The starting point of the line segment.
 *  - `Vector2 p2`: The ending point of the line segment.
 *  - `float thick`: The thickness of the line.
 *  - `Color color`: The color of the line.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawSplineSegmentLinear({ x = 50, y = 50 }, { x = 200, y = 100 }, 2, { r = 0, g = 255, b = 0, a = 255 }) -- Draw a green line segment
 * ```
 */
int lua_DrawSplineSegmentLinear(lua_State *L);

/**
 * @brief Draws a segment of a basis spline.
 * 
 * This function draws a smooth curve between four control points using a B-Spline algorithm.
 * 
 * @param L A pointer to the current Lua state. Expects 6 arguments:
 *  - `Vector2 p1`: The first control point.
 *  - `Vector2 p2`: The second control point.
 *  - `Vector2 p3`: The third control point.
 *  - `Vector2 p4`: The fourth control point.
 *  - `float thick`: The thickness of the line.
 *  - `Color color`: The color of the line.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawSplineSegmentBasis({ x = 50, y = 50 }, { x = 100, y = 150 }, { x = 150, y = 50 }, { x = 200, y = 100 }, 2, { r = 0, g = 0, b = 255, a = 255 }) -- Draw a blue basis spline segment
 * ```
 */
int lua_DrawSplineSegmentBasis(lua_State *L);

/**
 * @brief Draws a segment of a Catmull-Rom spline.
 * 
 * This function draws a smooth curve between four control points using a Catmull-Rom interpolation.
 * 
 * @param L A pointer to the current Lua state. Expects 6 arguments:
 *  - `Vector2 p1`: The first control point.
 *  - `Vector2 p2`: The second control point.
 *  - `Vector2 p3`: The third control point.
 *  - `Vector2 p4`: The fourth control point.
 *  - `float thick`: The thickness of the line.
 *  - `Color color`: The color of the line.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawSplineSegmentCatmullRom({ x = 50, y = 50 }, { x = 100, y = 150 }, { x = 150, y = 50 }, { x = 200, y = 100 }, 2, { r = 255, g = 0, b = 0, a = 255 }) -- Draw a red Catmull-Rom spline segment
 * ```
 */
int lua_DrawSplineSegmentCatmullRom(lua_State *L);

/**
 * @brief Draws a segment of a quadratic Bezier spline.
 * 
 * This function draws a smooth curve between two points using a quadratic Bezier interpolation. The control point defines the curve's shape.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `Vector2 p1`: The starting point of the curve.
 *  - `Vector2 c2`: The control point that determines the curve's shape.
 *  - `Vector2 p3`: The ending point of the curve.
 *  - `float thick`: The thickness of the line.
 *  - `Color color`: The color of the line.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawSplineSegmentBezierQuadratic({ x = 50, y = 50 }, { x = 125, y = 200 }, { x = 200, y = 50 }, 2, { r = 255, g = 0, b = 255, a = 255 }) -- Draw a purple quadratic Bezier spline segment
 * ```
 * 
 * @note A quadratic Bezier spline segment requires exactly 3 points: a start point, a control point, and an end point.
 */
int lua_DrawSplineSegmentBezierQuadratic(lua_State *L);

/**
 * @brief Draws a segment of a cubic Bezier spline.
 * 
 * This function draws a smooth curve between two points using a cubic Bezier interpolation. 
 * The curve is controlled by two control points that shape the curve's trajectory.
 * 
 * @param L A pointer to the current Lua state. Expects 6 arguments:
 *  - `Vector2 p1`: The starting point of the curve.
 *  - `Vector2 c2`: The first control point that determines the curve's shape.
 *  - `Vector2 c3`: The second control point that determines the curve's shape.
 *  - `Vector2 p4`: The ending point of the curve.
 *  - `float thick`: The thickness of the line.
 *  - `Color color`: The color of the line.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.DrawSplineSegmentBezierCubic({ x = 50, y = 50 }, { x = 80, y = 200 }, { x = 150, y = 200 }, { x = 200, y = 50 }, 2, { r = 255, g = 165, b = 0, a = 255 }) -- Draw an orange cubic Bezier spline segment
 * ```
 * 
 * @note A cubic Bezier spline segment requires exactly 4 points: a start point, two control points, and an end point.
 */
int lua_DrawSplineSegmentBezierCubic(lua_State *L);

/**
 * @brief Gets a point on a linear spline.
 * 
 * This function calculates a position on a linear spline at a specific time `t` 
 * using linear interpolation between two points.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Vector2 startPos`: The starting point of the line.
 *  - `Vector2 endPos`: The ending point of the line.
 *  - `float t`: The interpolation factor, where 0.0 is at `startPos` and 1.0 is at `endPos`.
 * 
 * @return int Always returns 1 (Vector2 result) representing the interpolated point.
 * 
 * @usage
 * ```lua
 * local point = raylib.GetSplinePointLinear({ x = 50, y = 50 }, { x = 200, y = 100 }, 0.5)
 * print(point.x, point.y) -- Prints the interpolated position
 * ```
 * 
 * @note The value of `t` should be between 0.0 and 1.0.
 */
int lua_GetSplinePointLinear(lua_State *L);

/**
 * @brief Gets a point on a basis spline.
 * 
 * This function calculates a position on a basis spline using four control points 
 * at a specific time `t`.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `Vector2 p1`: The first control point.
 *  - `Vector2 p2`: The second control point.
 *  - `Vector2 p3`: The third control point.
 *  - `Vector2 p4`: The fourth control point.
 *  - `float t`: The interpolation factor, where 0.0 is at `p2` and 1.0 is at `p3`.
 * 
 * @return int Always returns 1 (Vector2 result) representing the interpolated point.
 * 
 * @usage
 * ```lua
 * local point = raylib.GetSplinePointBasis({ x = 50, y = 50 }, { x = 100, y = 150 }, { x = 150, y = 50 }, { x = 200, y = 100 }, 0.75)
 * print(point.x, point.y) -- Prints the interpolated position
 * ```
 * 
 * @note The value of `t` should be between 0.0 and 1.0.
 */
int lua_GetSplinePointBasis(lua_State *L);

/**
 * @brief Gets a point on a Catmull-Rom spline.
 * 
 * This function calculates a position on a Catmull-Rom spline using four control points 
 * at a specific time `t`.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `Vector2 p1`: The first control point.
 *  - `Vector2 p2`: The second control point.
 *  - `Vector2 p3`: The third control point.
 *  - `Vector2 p4`: The fourth control point.
 *  - `float t`: The interpolation factor, where 0.0 is at `p2` and 1.0 is at `p3`.
 * 
 * @return int Always returns 1 (Vector2 result) representing the interpolated point.
 * 
 * @usage
 * ```lua
 * local point = raylib.GetSplinePointCatmullRom({ x = 50, y = 50 }, { x = 100, y = 150 }, { x = 150, y = 50 }, { x = 200, y = 100 }, 0.25)
 * print(point.x, point.y) -- Prints the interpolated position
 * ```
 * 
 * @note The value of `t` should be between 0.0 and 1.0.
 */
int lua_GetSplinePointCatmullRom(lua_State *L);

/**
 * @brief Gets a point on a quadratic Bezier spline.
 * 
 * This function calculates a point on a quadratic Bezier spline using two endpoints 
 * and one control point at a specific time `t`.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector2 p1`: The starting point of the curve.
 *  - `Vector2 c2`: The control point that determines the curve's shape.
 *  - `Vector2 p3`: The ending point of the curve.
 *  - `float t`: The interpolation factor, where 0.0 is at `p1` and 1.0 is at `p3`.
 * 
 * @return int Always returns 1 (Vector2 result) representing the interpolated point.
 * 
 * @usage
 * ```lua
 * local point = raylib.GetSplinePointBezierQuad({ x = 50, y = 50 }, { x = 100, y = 150 }, { x = 150, y = 50 }, 0.5)
 * print(point.x, point.y) -- Prints the interpolated position
 * ```
 * 
 * @note The value of `t` should be between 0.0 and 1.0.
 */
int lua_GetSplinePointBezierQuad(lua_State *L);

/**
 * @brief Gets a point on a cubic Bezier spline.
 * 
 * This function calculates a point on a cubic Bezier spline using two endpoints 
 * and two control points at a specific time `t`.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `Vector2 p1`: The starting point of the curve.
 *  - `Vector2 c2`: The first control point that determines the curve's shape.
 *  - `Vector2 c3`: The second control point that determines the curve's shape.
 *  - `Vector2 p4`: The ending point of the curve.
 *  - `float t`: The interpolation factor, where 0.0 is at `p1` and 1.0 is at `p4`.
 * 
 * @return int Always returns 1 (Vector2 result) representing the interpolated point.
 * 
 * @usage
 * ```lua
 * local point = raylib.GetSplinePointBezierCubic({ x = 50, y = 50 }, { x = 80, y = 200 }, { x = 150, y = 200 }, { x = 200, y = 50 }, 0.75)
 * print(point.x, point.y) -- Prints the interpolated position
 * ```
 * 
 * @note The value of `t` should be between 0.0 and 1.0.
 */
int lua_GetSplinePointBezierCubic(lua_State *L);

/**
 * @brief Checks collision between two rectangles.
 * 
 * This function checks if two rectangles are overlapping or intersecting.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Rectangle rec1`: The first rectangle.
 *  - `Rectangle rec2`: The second rectangle.
 * 
 * @return int Always returns 1 (boolean result), `true` if the rectangles collide, `false` otherwise.
 * 
 * @usage
 * ```lua
 * local result = raylib.CheckCollisionRecs({ x = 10, y = 10, width = 50, height = 50 }, { x = 30, y = 30, width = 50, height = 50 })
 * print(result) -- Prints true if the rectangles collide, false otherwise
 * ```
 * 
 * @note The rectangles are defined using their top-left position, width, and height.
 */
int lua_CheckCollisionRecs(lua_State *L);

/**
 * @brief Checks collision between two circles.
 * 
 * This function checks if two circles are overlapping or intersecting.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector2 center1`: The position of the first circle's center.
 *  - `float radius1`: The radius of the first circle.
 *  - `Vector2 center2`: The position of the second circle's center.
 *  - `float radius2`: The radius of the second circle.
 * 
 * @return int Always returns 1 (boolean result), `true` if the circles collide, `false` otherwise.
 * 
 * @usage
 * ```lua
 * local result = raylib.CheckCollisionCircles({ x = 50, y = 50 }, 30, { x = 80, y = 80 }, 40)
 * print(result) -- Prints true if the circles collide, false otherwise
 * ```
 * 
 * @note The position of the circles is based on their center coordinates.
 */
int lua_CheckCollisionCircles(lua_State *L);

/**
 * @brief Checks collision between a circle and a rectangle.
 * 
 * This function checks if a circle overlaps or intersects with a rectangle.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Vector2 center`: The position of the circle's center.
 *  - `float radius`: The radius of the circle.
 *  - `Rectangle rec`: The rectangle to check against.
 * 
 * @return int Always returns 1 (boolean result), `true` if the circle and rectangle collide, `false` otherwise.
 * 
 * @usage
 * ```lua
 * local result = raylib.CheckCollisionCircleRec({ x = 50, y = 50 }, 30, { x = 20, y = 20, width = 100, height = 100 })
 * print(result) -- Prints true if the circle and rectangle collide, false otherwise
 * ```
 * 
 * @note The rectangle is defined using its top-left position, width, and height.
 */
int lua_CheckCollisionCircleRec(lua_State *L);

/**
 * @brief Checks collision between a circle and a line.
 * 
 * This function checks if a circle overlaps or intersects with a line segment.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector2 center`: The position of the circle's center.
 *  - `float radius`: The radius of the circle.
 *  - `Vector2 p1`: The starting point of the line.
 *  - `Vector2 p2`: The ending point of the line.
 * 
 * @return int Always returns 1 (boolean result), `true` if the circle and line collide, `false` otherwise.
 * 
 * @usage
 * ```lua
 * local result = raylib.CheckCollisionCircleLine({ x = 50, y = 50 }, 30, { x = 20, y = 20 }, { x = 100, y = 100 })
 * print(result) -- Prints true if the circle and line collide, false otherwise
 * ```
 * 
 * @note The line is defined using two points (start and end).
 */
int lua_CheckCollisionCircleLine(lua_State *L);

/**
 * @brief Checks collision between a point and a rectangle.
 * 
 * This function checks if a point is inside a given rectangle.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Vector2 point`: The point to check.
 *  - `Rectangle rec`: The rectangle to check against.
 * 
 * @return int Always returns 1 (boolean result), `true` if the point is inside the rectangle, `false` otherwise.
 * 
 * @usage
 * ```lua
 * local result = raylib.CheckCollisionPointRec({ x = 50, y = 50 }, { x = 20, y = 20, width = 100, height = 100 })
 * print(result) -- Prints true if the point is inside the rectangle, false otherwise
 * ```
 * 
 * @note The rectangle is defined using its top-left position, width, and height.
 */
int lua_CheckCollisionPointRec(lua_State *L);

/**
 * @brief Checks collision between a point and a circle.
 * 
 * This function checks if a point is inside a given circle.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Vector2 point`: The point to check.
 *  - `Vector2 center`: The position of the circle's center.
 *  - `float radius`: The radius of the circle.
 * 
 * @return int Always returns 1 (boolean result), `true` if the point is inside the circle, `false` otherwise.
 * 
 * @usage
 * ```lua
 * local result = raylib.CheckCollisionPointCircle({ x = 50, y = 50 }, { x = 80, y = 80 }, 30)
 * print(result) -- Prints true if the point is inside the circle, false otherwise
 * ```
 * 
 * @note The position of the circle is its center coordinate.
 */
int lua_CheckCollisionPointCircle(lua_State *L);

/**
 * @brief Checks collision between a point and a triangle.
 * 
 * This function checks if a point lies inside a given triangle.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector2 point`: The point to check.
 *  - `Vector2 p1`: The first vertex of the triangle.
 *  - `Vector2 p2`: The second vertex of the triangle.
 *  - `Vector2 p3`: The third vertex of the triangle.
 * 
 * @return int Always returns 1 (boolean result), `true` if the point is inside the triangle, `false` otherwise.
 * 
 * @usage
 * ```lua
 * local result = raylib.CheckCollisionPointTriangle({ x = 50, y = 50 }, { x = 20, y = 20 }, { x = 100, y = 20 }, { x = 50, y = 100 })
 * print(result) -- Prints true if the point is inside the triangle, false otherwise
 * ```
 * 
 * @note The vertices of the triangle are defined as three 2D points.
 */
int lua_CheckCollisionPointTriangle(lua_State *L);

/**
 * @brief Checks collision between a point and a line.
 * 
 * This function checks if a point lies on a given line within a specified threshold.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector2 point`: The point to check.
 *  - `Vector2 p1`: The starting point of the line.
 *  - `Vector2 p2`: The ending point of the line.
 *  - `int threshold`: The threshold distance from the line for the point to be considered on the line.
 * 
 * @return int Always returns 1 (boolean result), `true` if the point is within the threshold distance of the line, `false` otherwise.
 * 
 * @usage
 * ```lua
 * local result = raylib.CheckCollisionPointLine({ x = 50, y = 50 }, { x = 20, y = 20 }, { x = 100, y = 100 }, 5)
 * print(result) -- Prints true if the point is within 5 units of the line, false otherwise
 * ```
 * 
 * @note The line is defined as two 2D points, and the threshold is an integer representing distance in pixels.
 */
int lua_CheckCollisionPointLine(lua_State *L);

/**
 * @brief Checks collision between a point and a polygon.
 * 
 * This function checks if a point is inside a given polygon defined by an array of points.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Vector2 point`: The point to check.
 *  - `Vector2[] points`: An array of vertices that define the polygon.
 * 
 * @return int Always returns 1 (boolean result), `true` if the point is inside the polygon, `false` otherwise.
 * 
 * @usage
 * ```lua
 * local polygon = { { x = 20, y = 20 }, { x = 100, y = 20 }, { x = 80, y = 80 }, { x = 50, y = 100 } }
 * local result = raylib.CheckCollisionPointPoly({ x = 50, y = 50 }, polygon)
 * print(result) -- Prints true if the point is inside the polygon, false otherwise
 * ```
 * 
 * @note The polygon is defined as an array of 2D points, and it should be a closed shape.
 */
int lua_CheckCollisionPointPoly(lua_State *L);

/**
 * @brief Checks collision between two lines.
 * 
 * This function checks if two line segments intersect and provides the collision point.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Vector2 startPos1`: The starting point of the first line.
 *  - `Vector2 endPos1`: The ending point of the first line.
 *  - `Vector2 startPos2`: The starting point of the second line.
 *  - `Vector2 endPos2`: The ending point of the second line.
 * 
 * @return int Always returns 2:
 *  - `boolean`: `true` if the lines collide, `false` otherwise.
 *  - `Vector2 collisionPoint`: The collision point of the two lines.
 * 
 * @usage
 * ```lua
 * local result, collisionPoint = raylib.CheckCollisionLines({ x = 0, y = 0 }, { x = 100, y = 100 }, { x = 0, y = 100 }, { x = 100, y = 0 })
 * print(result) -- Prints true if the two lines collide, false otherwise
 * if result then
 *     print("Collision Point:", collisionPoint.x, collisionPoint.y)
 * end
 * ```
 * 
 * @note The collision point is only valid if the function returns `true`.
 */
int lua_CheckCollisionLines(lua_State *L);

/**
 * @brief Gets the collision rectangle between two rectangles.
 * 
 * This function calculates the intersection area of two rectangles.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Rectangle rec1`: The first rectangle.
 *  - `Rectangle rec2`: The second rectangle.
 * 
 * @return int Always returns 1 (Rectangle result), which represents the overlapping region between the two rectangles.
 * 
 * @usage
 * ```lua
 * local collisionRec = raylib.GetCollisionRec({ x = 20, y = 20, width = 50, height = 50 }, { x = 30, y = 30, width = 60, height = 60 })
 * print("Collision Rectangle:", collisionRec.x, collisionRec.y, collisionRec.width, collisionRec.height)
 * ```
 * 
 * @note If the rectangles do not intersect, the returned rectangle will have width and height of zero.
 */
int lua_GetCollisionRec(lua_State *L);

#endif