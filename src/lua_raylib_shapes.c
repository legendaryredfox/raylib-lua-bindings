#include "raylib_wrappers.h"
#include "lua_raylib_shapes.h"

int lua_SetShapesTexture(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture2D");
    Rectangle source = get_rectangle_from_table(L, 2);
    SetShapesTexture(*texture, source);
    return 0;
}

int lua_GetShapesTexture(lua_State *L) {
    Texture2D texture = GetShapesTexture();
    Texture2D *pTexture = lua_newuserdata(L, sizeof(Texture2D));
    *pTexture = texture;
    luaL_setmetatable(L, "Texture2D");
    return 1;
}

int lua_GetShapesTextureRectangle(lua_State *L) {
    Rectangle rect = GetShapesTextureRectangle();
    push_rectangle_to_table(L, rect);
    return 1;
}
