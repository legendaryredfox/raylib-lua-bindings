#include "lua_raylib_core.h"

int lua_InitWindow(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    const char *title = luaL_checkstring(L, 3);
    InitWindow(width, height, title);
    return 0;
}

int lua_CloseWindow(lua_State *L) {
    CloseWindow();
    return 0;
}

int lua_WindowShouldClose(lua_State *L) {
    lua_pushboolean(L, WindowShouldClose());
    return 1;
}

int lua_GetClipboardImage(lua_State *L) {
    Image image = GetClipboardImage(); 
    push_image_to_lua(L, image);        
    return 1;                          
}
