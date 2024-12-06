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
