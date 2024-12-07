#ifndef LUA_RAYLIB_SHAPES_H
#define LUA_RAYLIB_SHAPES_H

#include "lua.h"
#include "lauxlib.h"
#include "raylib.h"

/**
 * @brief Sets the texture to be used for shapes.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetShapesTexture(lua_State *L);

/**
 * @brief Gets the current texture used for shapes.
 * 
 * @param L Lua state
 * @return int Always returns 1
 */
int lua_GetShapesTexture(lua_State *L);

/**
 * @brief Gets the source rectangle of the current shapes texture.
 * 
 * @param L Lua state
 * @return int Always returns 1
 */
int lua_GetShapesTextureRectangle(lua_State *L);

/**
 * @brief Draws a pixel at the specified position with the specified color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawPixel(lua_State *L);

/**
 * @brief Draws a pixel at the specified position (Vector2) with the specified color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawPixelV(lua_State *L);

/**
 * @brief Draws a line between two points (Vector2).
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawLineV(lua_State *L);

/**
 * @brief Draws a circle at the specified position (Vector2) with the specified radius and color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCircleV(lua_State *L);

/**
 * @brief Draws the outline of a circle at the specified position with the specified radius and color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCircleLines(lua_State *L);

/**
 * @brief Draws the outline of a circle at the specified position (Vector2) with the specified radius and color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCircleLinesV(lua_State *L);

/**
 * @brief Draws the outline of an ellipse at the specified position with the specified radii and color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawEllipseLines(lua_State *L);

/**
 * @brief Draws a rectangle at the specified position (Vector2) with the specified width, height, and color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawRectangleV(lua_State *L);

/**
 * @brief Draws a rectangle using a Rectangle struct.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawRectangleRec(lua_State *L);

/**
 * @brief Draws a rectangle with the specified position, size, and rotation.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawRectanglePro(lua_State *L);

/**
 * @brief Draws a rectangle with a horizontal gradient.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawRectangleGradientH(lua_State *L);

/**
 * @brief Draws the outline of a rectangle with extended parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawRectangleLinesEx(lua_State *L);

/**
 * @brief Draws a linear spline.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawSplineLinear(lua_State *L);

/**
 * @brief Draws a basis spline.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawSplineBasis(lua_State *L);

/**
 * @brief Draws a Catmull-Rom spline.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawSplineCatmullRom(lua_State *L);

/**
 * @brief Draws a quadratic Bezier spline.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawSplineBezierQuadratic(lua_State *L);

/**
 * @brief Draws a cubic Bezier spline.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawSplineBezierCubic(lua_State *L);

/**
 * @brief Draws a segment of a linear spline.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawSplineSegmentLinear(lua_State *L);

/**
 * @brief Draws a segment of a basis spline.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawSplineSegmentBasis(lua_State *L);

/**
 * @brief Draws a segment of a Catmull-Rom spline.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawSplineSegmentCatmullRom(lua_State *L);

/**
 * @brief Draws a segment of a quadratic Bezier spline.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawSplineSegmentBezierQuadratic(lua_State *L);

/**
 * @brief Draws a segment of a cubic Bezier spline.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawSplineSegmentBezierCubic(lua_State *L);

/**
 * @brief Gets a point on a linear spline.
 * 
 * @param L Lua state
 * @return int Always returns 1
 */
int lua_GetSplinePointLinear(lua_State *L);

/**
 * @brief Gets a point on a basis spline.
 * 
 * @param L Lua state
 * @return int Always returns 1
 */
int lua_GetSplinePointBasis(lua_State *L);

/**
 * @brief Gets a point on a Catmull-Rom spline.
 * 
 * @param L Lua state
 * @return int Always returns 1
 */
int lua_GetSplinePointCatmullRom(lua_State *L);

/**
 * @brief Gets a point on a quadratic Bezier spline.
 * 
 * @param L Lua state
 * @return int Always returns 1
 */
int lua_GetSplinePointBezierQuad(lua_State *L);

/**
 * @brief Gets a point on a cubic Bezier spline.
 * 
 * @param L Lua state
 * @return int Always returns 1
 */
int lua_GetSplinePointBezierCubic(lua_State *L);

/**
 * @brief Checks collision between two rectangles.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_CheckCollisionRecs(lua_State *L);

/**
 * @brief Checks collision between two circles.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_CheckCollisionCircles(lua_State *L);

/**
 * @brief Checks collision between a circle and a rectangle.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_CheckCollisionCircleRec(lua_State *L);

/**
 * @brief Checks collision between a circle and a line.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_CheckCollisionCircleLine(lua_State *L);

/**
 * @brief Checks collision between a point and a rectangle.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_CheckCollisionPointRec(lua_State *L);

/**
 * @brief Checks collision between a point and a circle.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_CheckCollisionPointCircle(lua_State *L);

/**
 * @brief Checks collision between a point and a triangle.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_CheckCollisionPointTriangle(lua_State *L);

/**
 * @brief Checks collision between a point and a line.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_CheckCollisionPointLine(lua_State *L);

/**
 * @brief Checks collision between a point and a polygon.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_CheckCollisionPointPoly(lua_State *L);

/**
 * @brief Checks collision between two lines.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_CheckCollisionLines(lua_State *L);

/**
 * @brief Gets the collision rectangle between two rectangles.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Rectangle result)
 */
int lua_GetCollisionRec(lua_State *L);

#endif