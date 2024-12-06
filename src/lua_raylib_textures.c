#include "lua_raylib_textures.h"
#include "raylib_wrappers.h"

int lua_LoadImage(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    Image image = LoadImage(fileName);
    Image *pImage = lua_newuserdata(L, sizeof(Image));
    *pImage = image;
    luaL_setmetatable(L, "Image");
    return 1;
}

int lua_UnloadImage(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    UnloadImage(*image);
    return 0;
}

int lua_LoadTexture(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    Texture2D texture = LoadTexture(fileName);
    Texture2D *pTexture = lua_newuserdata(L, sizeof(Texture2D));
    *pTexture = texture;
    luaL_setmetatable(L, "Texture");
    return 1;
}

int lua_LoadTextureFromImage(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Texture2D texture = LoadTextureFromImage(*image);
    Texture2D *pTexture = lua_newuserdata(L, sizeof(Texture2D));
    *pTexture = texture;
    luaL_setmetatable(L, "Texture");
    return 1;
}

int lua_UnloadTexture(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture");
    UnloadTexture(*texture);
    return 0;
}

int lua_UpdateTexture(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture");
    const void *pixels = lua_touserdata(L, 2);
    UpdateTexture(*texture, pixels);
    return 0;
}

int lua_GenTextureMipmaps(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture");
    GenTextureMipmaps(texture);
    return 0;
}

int lua_ImageResize(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    int width = luaL_checkinteger(L, 2);
    int height = luaL_checkinteger(L, 3);
    ImageResize(image, width, height);
    return 0;
}

int lua_ImageFlipHorizontal(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    ImageFlipHorizontal(image);
    return 0;
}

int lua_ImageFlipVertical(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    ImageFlipVertical(image);
    return 0;
}

int lua_ImageCopy(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Image copiedImage = ImageCopy(*image);
    Image *pCopiedImage = lua_newuserdata(L, sizeof(Image));
    *pCopiedImage = copiedImage;
    luaL_setmetatable(L, "Image");
    return 1;
}

int lua_ImageCrop(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Rectangle cropRect = {
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3),
        luaL_checknumber(L, 4),
        luaL_checknumber(L, 5)
    };
    ImageCrop(image, cropRect);
    return 0;
}

int lua_ImageColorTint(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Color tint = get_color_from_table(L, 2);
    ImageColorTint(image, tint);
    return 0;
}

int lua_ImageColorInvert(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    ImageColorInvert(image);
    return 0;
}

int lua_ImageColorGrayscale(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    ImageColorGrayscale(image);
    return 0;
}

int lua_ImageColorBrightness(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    int brightness = luaL_checkinteger(L, 2);
    ImageColorBrightness(image, brightness);
    return 0;
}

int lua_ImageColorContrast(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    float contrast = luaL_checknumber(L, 2);
    ImageColorContrast(image, contrast);
    return 0;
}

int lua_ImageColorReplace(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Color color = get_color_from_table(L, 2);
    Color replace = get_color_from_table(L, 3);
    ImageColorReplace(image, color, replace);
    return 0;
}

int lua_LoadTextureCubemap(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    int layout = luaL_checkinteger(L, 2);
    TextureCubemap cubemap = LoadTextureCubemap(*image, layout);
    TextureCubemap *pCubemap = lua_newuserdata(L, sizeof(TextureCubemap));
    *pCubemap = cubemap;
    luaL_setmetatable(L, "TextureCubemap");
    return 1;
}

int lua_UpdateTextureRec(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture");
    Rectangle rec = {
        luaL_checknumber(L, 2),
        luaL_checknumber(L, 3),
        luaL_checknumber(L, 4),
        luaL_checknumber(L, 5)
    };
    const void *pixels = lua_touserdata(L, 6);
    UpdateTextureRec(*texture, rec, pixels);
    return 0;
}