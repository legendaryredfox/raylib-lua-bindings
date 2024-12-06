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