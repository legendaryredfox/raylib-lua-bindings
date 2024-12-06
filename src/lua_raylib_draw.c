#include "lua_raylib_draw.h"
#include "raylib_wrappers.h"

int lua_BeginDrawing(lua_State *L) {
    BeginDrawing();
    return 0;
}

int lua_EndDrawing(lua_State *L) {
    EndDrawing();
    return 0;
}

int lua_ClearBackground(lua_State *L) {
    int color = luaL_checkinteger(L, 1);
    Color bgColor = convert_color(color);
    ClearBackground(bgColor);
    return 0;
}

int lua_DrawRectangle(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    int color = luaL_checkinteger(L, 5);
    Color rectColor = convert_color(color);
    DrawRectangle(x, y, width, height, rectColor);
    return 0;
}

// Binding for DrawRectangle
int lua_DrawRectangle(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    Color color = get_color_from_table(L, 5);
    DrawRectangle(x, y, width, height, color);
    return 0;
}

// Binding for DrawCircle
int lua_DrawCircle(lua_State *L) {
    int centerX = luaL_checkinteger(L, 1);
    int centerY = luaL_checkinteger(L, 2);
    int radius = luaL_checkinteger(L, 3);
    Color color = get_color_from_table(L, 4);
    DrawCircle(centerX, centerY, radius, color);
    return 0;
}

// Binding for DrawLineEx
int lua_DrawLineEx(lua_State *L) {
    Vector2 startPos = get_vector2_from_table(L, 1);
    Vector2 endPos = get_vector2_from_table(L, 2);
    float thick = luaL_checknumber(L, 3);
    Color color = get_color_from_table(L, 4);
    DrawLineEx(startPos, endPos, thick, color);
    return 0;
}

// Binding for DrawEllipse
int lua_DrawEllipse(lua_State *L) {
    int centerX = luaL_checkinteger(L, 1);
    int centerY = luaL_checkinteger(L, 2);
    int radiusH = luaL_checkinteger(L, 3);
    int radiusV = luaL_checkinteger(L, 4);
    Color color = get_color_from_table(L, 5);
    DrawEllipse(centerX, centerY, radiusH, radiusV, color);
    return 0;
}

// Binding for DrawRectangleLines
int lua_DrawRectangleLines(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    int lineThick = luaL_checkinteger(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawRectangleLinesEx((Rectangle){x, y, width, height}, lineThick, color);
    return 0;
}

// Binding for DrawRectangleGradient
int lua_DrawRectangleGradient(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    Color color1 = get_color_from_table(L, 5);
    Color color2 = get_color_from_table(L, 6);
    DrawRectangleGradientH(x, y, width, height, color1, color2);
    return 0;
}

// Binding for DrawRectangleRounded
int lua_DrawRectangleRounded(lua_State *L) {
    Rectangle rect = {
        luaL_checknumber(L, 1),
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3),
        luaL_checknumber(L, 4),
    };
    float roundness = luaL_checknumber(L, 5);
    int segments = luaL_checkinteger(L, 6);
    Color color = get_color_from_table(L, 7);
    DrawRectangleRounded(rect, roundness, segments, color);
    return 0;
}

// Binding for DrawLineStrip
int lua_DrawLineStrip(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int pointsCount = lua_rawlen(L, 1);
    Vector2 *points = malloc(pointsCount * sizeof(Vector2));
    if (!points) {
        return luaL_error(L, "Memory allocation failed for points array");
    }

    for (int i = 0; i < pointsCount; i++) {
        lua_rawgeti(L, 1, i + 1);
        points[i] = get_vector2_from_table(L, -1);
        lua_pop(L, 1);
    }

    Color color = get_color_from_table(L, 2);
    DrawLineStrip(points, pointsCount, color);
    free(points);
    return 0;
}

// Binding for DrawPoly
int lua_DrawPoly(lua_State *L) {
    Vector2 center = get_vector2_from_table(L, 1);
    int sides = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);
    float rotation = luaL_checknumber(L, 4);
    Color color = get_color_from_table(L, 5);
    DrawPoly(center, sides, radius, rotation, color);
    return 0;
}

// Binding for DrawPolyLines
int lua_DrawPolyLines(lua_State *L) {
    Vector2 center = get_vector2_from_table(L, 1);
    int sides = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);
    float rotation = luaL_checknumber(L, 4);
    Color color = get_color_from_table(L, 5);
    DrawPolyLines(center, sides, radius, rotation, color);
    return 0;
}

// Binding for DrawPolyLinesEx
int lua_DrawPolyLinesEx(lua_State *L) {
    Vector2 center = get_vector2_from_table(L, 1);
    int sides = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);
    float rotation = luaL_checknumber(L, 4);
    float lineThick = luaL_checknumber(L, 5);
    Color color = get_color_from_table(L, 6); 

    DrawPolyLinesEx(center, sides, radius, rotation, lineThick, color);
    return 0;
}

int lua_DrawGrid(lua_State *L) {
    int slices = luaL_checkinteger(L, 1);
    float spacing = luaL_checknumber(L, 2);
    DrawGrid(slices, spacing);
    return 0;
}

int lua_DrawText(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    int posX = luaL_checkinteger(L, 2);      
    int posY = luaL_checkinteger(L, 3);      
    int fontSize = luaL_checkinteger(L, 4);  
    Color color = get_color_from_table(L, 5);
    DrawText(text, posX, posY, fontSize, color);
    return 0;
}

// Binding for DrawCircleSector
int lua_DrawCircleSector(lua_State *L) {
    Vector2 center = get_vector2_from_table(L, 1);
    float radius = luaL_checknumber(L, 2);
    float startAngle = luaL_checknumber(L, 3);
    float endAngle = luaL_checknumber(L, 4);
    int segments = luaL_checkinteger(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
    return 0;
}

// Binding for DrawCircleSectorLines
int lua_DrawCircleSectorLines(lua_State *L) {
    Vector2 center = get_vector2_from_table(L, 1);
    float radius = luaL_checknumber(L, 2);
    float startAngle = luaL_checknumber(L, 3);
    float endAngle = luaL_checknumber(L, 4);
    int segments = luaL_checkinteger(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
    return 0;
}

// Binding for DrawRectangleGradientV
int lua_DrawRectangleGradientV(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    Color color1 = get_color_from_table(L, 5);
    Color color2 = get_color_from_table(L, 6);
    DrawRectangleGradientV(x, y, width, height, color1, color2);
    return 0;
}

// Binding for DrawRectangleGradientEx
int lua_DrawRectangleGradientEx(lua_State *L) {
    Rectangle rect = {
        luaL_checknumber(L, 1),
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3),
        luaL_checknumber(L, 4)
    };
    Color color1 = get_color_from_table(L, 5);
    Color color2 = get_color_from_table(L, 6);
    Color color3 = get_color_from_table(L, 7);
    Color color4 = get_color_from_table(L, 8);
    DrawRectangleGradientEx(rect, color1, color2, color3, color4);
    return 0;
}

// Binding for DrawCircleGradient
int lua_DrawCircleGradient(lua_State *L) {
    int centerX = luaL_checkinteger(L, 1);
    int centerY = luaL_checkinteger(L, 2);
    float radius = luaL_checknumber(L, 3);
    Color color1 = get_color_from_table(L, 4);
    Color color2 = get_color_from_table(L, 5);
    DrawCircleGradient(centerX, centerY, radius, color1, color2);
    return 0;
}

// Binding for DrawLine
int lua_DrawLine(lua_State *L) {
    int startX = luaL_checkinteger(L, 1);
    int startY = luaL_checkinteger(L, 2);
    int endX = luaL_checkinteger(L, 3);
    int endY = luaL_checkinteger(L, 4);
    Color color = get_color_from_table(L, 5);
    DrawLine(startX, startY, endX, endY, color);
    return 0;
}

// Binding for DrawLineBezier
int lua_DrawLineBezier(lua_State *L) {
    Vector2 startPos = get_vector2_from_table(L, 1);
    Vector2 endPos = get_vector2_from_table(L, 2);
    float thick = luaL_checknumber(L, 3);
    Color color = get_color_from_table(L, 4);
    DrawLineBezier(startPos, endPos, thick, color);
    return 0;
}

// Binding for DrawTriangle
int lua_DrawTriangle(lua_State *L) {
    Vector2 v1 = get_vector2_from_table(L, 1);
    Vector2 v2 = get_vector2_from_table(L, 2);
    Vector2 v3 = get_vector2_from_table(L, 3);
    Color color = get_color_from_table(L, 4);
    DrawTriangle(v1, v2, v3, color);
    return 0;
}

// Binding for DrawTriangleLines
int lua_DrawTriangleLines(lua_State *L) {
    Vector2 v1 = get_vector2_from_table(L, 1);
    Vector2 v2 = get_vector2_from_table(L, 2);
    Vector2 v3 = get_vector2_from_table(L, 3);
    Color color = get_color_from_table(L, 4);
    DrawTriangleLines(v1, v2, v3, color);
    return 0;
}

// Binding for DrawTriangleStrip
int lua_DrawTriangleStrip(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE); // Array of Vector2
    int pointsCount = lua_rawlen(L, 1);
    Vector2 *points = malloc(pointsCount * sizeof(Vector2));
    if (!points) {
        return luaL_error(L, "Memory allocation failed for points array");
    }

    for (int i = 0; i < pointsCount; i++) {
        lua_rawgeti(L, 1, i + 1);
        points[i] = get_vector2_from_table(L, -1);
        lua_pop(L, 1);
    }

    Color color = get_color_from_table(L, 2);
    DrawTriangleStrip(points, pointsCount, color);
    free(points);
    return 0;
}

// Binding for DrawRing
int lua_DrawRing(lua_State *L) {
    Vector2 center = get_vector2_from_table(L, 1);
    float innerRadius = luaL_checknumber(L, 2);
    float outerRadius = luaL_checknumber(L, 3);
    float startAngle = luaL_checknumber(L, 4);
    float endAngle = luaL_checknumber(L, 5);
    int segments = luaL_checkinteger(L, 6);
    Color color = get_color_from_table(L, 7);
    DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
    return 0;
}

// Binding for DrawRingLines
int lua_DrawRingLines(lua_State *L) {
    Vector2 center = get_vector2_from_table(L, 1);
    float innerRadius = luaL_checknumber(L, 2);
    float outerRadius = luaL_checknumber(L, 3);
    float startAngle = luaL_checknumber(L, 4);
    float endAngle = luaL_checknumber(L, 5);
    int segments = luaL_checkinteger(L, 6);
    Color color = get_color_from_table(L, 7);
    DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
    return 0;
}