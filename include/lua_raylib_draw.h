#ifndef RAYLIB_LUA_DRAW_H
#define RAYLIB_LUA_DRAW_H

#include "lua_raylib.h"

/**
 * @brief Begins drawing on the screen.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_BeginDrawing(lua_State *L);

/**
 * @brief Ends drawing on the screen.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_EndDrawing(lua_State *L);

/**
 * @brief Clears the background with a specified color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_ClearBackground(lua_State *L);

/**
 * @brief Draws a rectangle with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawRectangle(lua_State *L);

/**
 * @brief Draws a circle with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCircle(lua_State *L);

/**
 * @brief Draws a line with extended parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawLineEx(lua_State *L);

/**
 * @brief Draws an ellipse with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawEllipse(lua_State *L);

/**
 * @brief Draws the outline of a rectangle with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawRectangleLines(lua_State *L);

/**
 * @brief Draws a rectangle with a gradient fill.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawRectangleGradient(lua_State *L);

/**
 * @brief Draws a rounded rectangle with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawRectangleRounded(lua_State *L);

/**
 * @brief Draws a line strip with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawLineStrip(lua_State *L);

/**
 * @brief Draws a polygon with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawPoly(lua_State *L);

/**
 * @brief Draws the outline of a polygon with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawPolyLines(lua_State *L);

/**
 * @brief Draws the outline of a polygon with extended parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawPolyLinesEx(lua_State *L);

/**
 * @brief Draws a grid with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawGrid(lua_State *L);

/**
 * @brief Draws a sector of a circle with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCircleSector(lua_State *L);

/**
 * @brief Draws the outline of a sector of a circle with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCircleSectorLines(lua_State *L);

/**
 * @brief Draws a rectangle with a vertical gradient fill.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawRectangleGradientV(lua_State *L);

/**
 * @brief Draws a rectangle with an extended gradient fill.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawRectangleGradientEx(lua_State *L);

/**
 * @brief Draws a circle with a gradient fill.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawCircleGradient(lua_State *L);

/**
 * @brief Draws a line between two points.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawLine(lua_State *L);

/**
 * @brief Draws a Bezier line with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawLineBezier(lua_State *L);

/**
 * @brief Draws a triangle with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawTriangle(lua_State *L);

/**
 * @brief Draws the outline of a triangle with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawTriangleLines(lua_State *L);

/**
 * @brief Draws a triangle strip with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawTriangleStrip(lua_State *L);

/**
 * @brief Draws a ring with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawRing(lua_State *L);

/**
 * @brief Draws the outline of a ring with specified parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawRingLines(lua_State *L);

#endif