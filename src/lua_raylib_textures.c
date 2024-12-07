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

int lua_LoadImageRaw(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    int width = luaL_checkinteger(L, 2);
    int height = luaL_checkinteger(L, 3);
    int format = luaL_checkinteger(L, 4);
    int headerSize = luaL_checkinteger(L, 5);

    Image image = LoadImageRaw(fileName, width, height, format, headerSize);
    push_image_to_table(L, image);
    return 1;
}

int lua_LoadImageAnim(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    int frames;
    Image image = LoadImageAnim(fileName, &frames);

    lua_newtable(L);
    push_image_to_table(L, image);
    lua_pushinteger(L, frames);
    lua_setfield(L, -2, "frames");
    return 1;
}

int lua_LoadImageAnimFromMemory(lua_State *L) {
    const char *fileType = luaL_checkstring(L, 1);
    const unsigned char *fileData = (unsigned char *)luaL_checkstring(L, 2);
    int dataSize = luaL_checkinteger(L, 3);
    int frames;

    Image image = LoadImageAnimFromMemory(fileType, fileData, dataSize, &frames);

    lua_newtable(L);
    push_image_to_table(L, image);
    lua_pushinteger(L, frames);
    lua_setfield(L, -2, "frames");
    return 1;
}

int lua_LoadImageFromMemory(lua_State *L) {
    const char *fileType = luaL_checkstring(L, 1);
    const unsigned char *fileData = (unsigned char *)luaL_checkstring(L, 2);
    int dataSize = luaL_checkinteger(L, 3);

    Image image = LoadImageFromMemory(fileType, fileData, dataSize);
    push_image_to_table(L, image);
    return 1;
}

int lua_LoadImageFromTexture(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture2D");

    Image image = LoadImageFromTexture(*texture);
    push_image_to_table(L, image);
    return 1;
}

int lua_LoadImageFromScreen(lua_State *L) {
    Image image = LoadImageFromScreen();
    push_image_to_table(L, image);
    return 1;
}

int lua_IsImageValid(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    lua_pushboolean(L, IsImageValid(*image));
    return 1;
}

int lua_ExportImage(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    const char *fileName = luaL_checkstring(L, 2);

    bool result = ExportImage(*image, fileName);
    lua_pushboolean(L, result);
    return 1;
}

int lua_ExportImageToMemory(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    const char *fileType = luaL_checkstring(L, 2);
    int fileSize;

    unsigned char *fileData = ExportImageToMemory(*image, fileType, &fileSize);

    if (fileData) {
        lua_pushlstring(L, (const char *)fileData, fileSize);
        UnloadImageColors((Color *)fileData);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

int lua_ExportImageAsCode(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    const char *fileName = luaL_checkstring(L, 2);

    bool result = ExportImageAsCode(*image, fileName);
    lua_pushboolean(L, result);
    return 1;
}

int lua_GenImageColor(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    Color color = get_color_from_table(L, 3);
    Image image = GenImageColor(width, height, color);
    push_image_to_table(L, image);
    return 1;
}

int lua_GenImageGradientLinear(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    int direction = luaL_checkinteger(L, 3);
    Color start = get_color_from_table(L, 4);
    Color end = get_color_from_table(L, 5);
    Image image = GenImageGradientLinear(width, height, direction, start, end);
    push_image_to_table(L, image);
    return 1;
}

int lua_GenImageGradientRadial(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    float density = luaL_checknumber(L, 3);
    Color inner = get_color_from_table(L, 4);
    Color outer = get_color_from_table(L, 5);
    Image image = GenImageGradientRadial(width, height, density, inner, outer);
    push_image_to_table(L, image);
    return 1;
}

int lua_GenImageGradientSquare(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    float density = luaL_checknumber(L, 3);
    Color inner = get_color_from_table(L, 4);
    Color outer = get_color_from_table(L, 5);
    Image image = GenImageGradientSquare(width, height, density, inner, outer);
    push_image_to_table(L, image);
    return 1;
}

int lua_GenImageChecked(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    int checksX = luaL_checkinteger(L, 3);
    int checksY = luaL_checkinteger(L, 4);
    Color col1 = get_color_from_table(L, 5);
    Color col2 = get_color_from_table(L, 6);
    Image image = GenImageChecked(width, height, checksX, checksY, col1, col2);
    push_image_to_table(L, image);
    return 1;
}

int lua_GenImageWhiteNoise(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    float factor = luaL_checknumber(L, 3);
    Image image = GenImageWhiteNoise(width, height, factor);
    push_image_to_table(L, image);
    return 1;
}

int lua_GenImagePerlinNoise(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    int offsetX = luaL_checkinteger(L, 3);
    int offsetY = luaL_checkinteger(L, 4);
    float scale = luaL_checknumber(L, 5);
    Image image = GenImagePerlinNoise(width, height, offsetX, offsetY, scale);
    push_image_to_table(L, image);
    return 1;
}

int lua_GenImageCellular(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    int tileSize = luaL_checkinteger(L, 3);
    Image image = GenImageCellular(width, height, tileSize);
    push_image_to_table(L, image);
    return 1;
}

int lua_GenImageText(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    const char *text = luaL_checkstring(L, 3);
    Image image = GenImageText(width, height, text);
    push_image_to_table(L, image);
    return 1;
}

int lua_ImageFromImage(lua_State *L) {
    Image *src = luaL_checkudata(L, 1, "Image");
    Rectangle rect = get_rectangle_from_table(L, 2);
    Image image = ImageFromImage(*src, rect);
    push_image_to_table(L, image);
    return 1;
}

int lua_ImageFromChannel(lua_State *L) {
    Image *src = luaL_checkudata(L, 1, "Image");
    int channel = luaL_checkinteger(L, 2);
    Image image = ImageFromChannel(*src, channel);
    push_image_to_table(L, image);
    return 1;
}

int lua_ImageText(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    int fontSize = luaL_checkinteger(L, 2);
    Color color = get_color_from_table(L, 3);
    Image image = ImageText(text, fontSize, color);
    push_image_to_table(L, image);
    return 1;
}

int lua_ImageTextEx(lua_State *L) {
    Font *font = luaL_checkudata(L, 1, "Font");
    const char *text = luaL_checkstring(L, 2);
    float fontSize = luaL_checknumber(L, 3);
    float spacing = luaL_checknumber(L, 4);
    Color tint = get_color_from_table(L, 5);
    Image image = ImageTextEx(*font, text, fontSize, spacing, tint);
    push_image_to_table(L, image);
    return 1;
}

int lua_ImageFormat(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    int newFormat = luaL_checkinteger(L, 2);
    ImageFormat(image, newFormat);
    return 0;
}

int lua_ImageToPOT(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Color fill = get_color_from_table(L, 2);
    ImageToPOT(image, fill);
    return 0;
}

int lua_ImageAlphaCrop(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    float threshold = luaL_checknumber(L, 2);
    ImageAlphaCrop(image, threshold);
    return 0;
}

int lua_ImageAlphaClear(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Color color = get_color_from_table(L, 2);
    float threshold = luaL_checknumber(L, 3);
    ImageAlphaClear(image, color, threshold);
    return 0;
}

int lua_ImageAlphaMask(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Image *mask = luaL_checkudata(L, 2, "Image");
    ImageAlphaMask(image, *mask);
    return 0;
}

int lua_ImageAlphaPremultiply(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    ImageAlphaPremultiply(image);
    return 0;
}

int lua_ImageBlurGaussian(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    int blurSize = luaL_checkinteger(L, 2);
    ImageBlurGaussian(image, blurSize);
    return 0;
}

int lua_ImageKernelConvolution(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    luaL_checktype(L, 2, LUA_TTABLE);
    int kernelSize = luaL_len(L, 2);
    float *kernel = malloc(kernelSize * sizeof(float));
    for (int i = 0; i < kernelSize; i++) {
        lua_rawgeti(L, 2, i + 1);
        kernel[i] = luaL_checknumber(L, -1);
        lua_pop(L, 1);
    }
    ImageKernelConvolution(image, kernel, kernelSize);
    free(kernel);
    return 0;
}

int lua_ImageResizeNN(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    int newWidth = luaL_checkinteger(L, 2);
    int newHeight = luaL_checkinteger(L, 3);
    ImageResizeNN(image, newWidth, newHeight);
    return 0;
}

int lua_ImageResizeCanvas(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    int newWidth = luaL_checkinteger(L, 2);
    int newHeight = luaL_checkinteger(L, 3);
    int offsetX = luaL_checkinteger(L, 4);
    int offsetY = luaL_checkinteger(L, 5);
    Color fill = get_color_from_table(L, 6);
    ImageResizeCanvas(image, newWidth, newHeight, offsetX, offsetY, fill);
    return 0;
}

int lua_ImageMipmaps(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    ImageMipmaps(image);
    return 0;
}

int lua_ImageDither(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    int rBpp = luaL_checkinteger(L, 2);
    int gBpp = luaL_checkinteger(L, 3);
    int bBpp = luaL_checkinteger(L, 4);
    int aBpp = luaL_checkinteger(L, 5);
    ImageDither(image, rBpp, gBpp, bBpp, aBpp);
    return 0;
}

int lua_ImageRotate(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    int degrees = luaL_checkinteger(L, 2);
    ImageRotate(image, degrees);
    return 0;
}

int lua_ImageRotateCW(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    ImageRotateCW(image);
    return 0;
}

int lua_ImageRotateCCW(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    ImageRotateCCW(image);
    return 0;
}

int lua_LoadImageColors(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Color *colors = LoadImageColors(*image);
    lua_pushlightuserdata(L, colors);
    return 1;
}

int lua_LoadImagePalette(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    int maxPaletteSize = luaL_checkinteger(L, 2);
    int colorCount;
    Color *palette = LoadImagePalette(*image, maxPaletteSize, &colorCount);
    lua_pushlightuserdata(L, palette);
    lua_pushinteger(L, colorCount);
    return 2;
}

int lua_UnloadImageColors(lua_State *L) {
    Color *colors = lua_touserdata(L, 1);
    if (colors != NULL) {
        UnloadImageColors(colors);
    }
    return 0;
}

int lua_UnloadImagePalette(lua_State *L) {
    Color *palette = lua_touserdata(L, 1);
    if (palette != NULL) {
        UnloadImagePalette(palette);
    }
    return 0;
}

int lua_GetImageAlphaBorder(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    float threshold = luaL_checknumber(L, 2);
    Rectangle border = GetImageAlphaBorder(*image, threshold);
    push_rectangle_to_table(L, border);
    return 1;
}

int lua_GetImageColor(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);
    Color color = GetImageColor(*image, x, y);
    push_color_to_table(L, color);
    return 1;
}

int lua_ImageClearBackground(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Color color = get_color_from_table(L, 2);
    ImageClearBackground(image, color);
    return 0;
}

int lua_ImageDrawPixel(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    int posX = luaL_checkinteger(L, 2);
    int posY = luaL_checkinteger(L, 3);
    Color color = get_color_from_table(L, 4);
    ImageDrawPixel(image, posX, posY, color);
    return 0;
}

int lua_ImageDrawPixelV(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Vector2 position = get_vector2_from_table(L, 2);
    Color color = get_color_from_table(L, 3);
    ImageDrawPixelV(image, position, color);
    return 0;
}

int lua_ImageDrawLine(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    int startPosX = luaL_checkinteger(L, 2);
    int startPosY = luaL_checkinteger(L, 3);
    int endPosX = luaL_checkinteger(L, 4);
    int endPosY = luaL_checkinteger(L, 5);
    Color color = get_color_from_table(L, 6);
    ImageDrawLine(image, startPosX, startPosY, endPosX, endPosY, color);
    return 0;
}

int lua_ImageDrawLineV(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Vector2 start = get_vector2_from_table(L, 2);
    Vector2 end = get_vector2_from_table(L, 3);
    Color color = get_color_from_table(L, 4);
    ImageDrawLineV(image, start, end, color);
    return 0;
}

int lua_ImageDrawLineEx(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Vector2 start = get_vector2_from_table(L, 2);
    Vector2 end = get_vector2_from_table(L, 3);
    int thick = luaL_checkinteger(L, 4);
    Color color = get_color_from_table(L, 5);
    ImageDrawLineEx(image, start, end, thick, color);
    return 0;
}

int lua_ImageDrawCircle(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    int centerX = luaL_checkinteger(L, 2);
    int centerY = luaL_checkinteger(L, 3);
    int radius = luaL_checkinteger(L, 4);
    Color color = get_color_from_table(L, 5);
    ImageDrawCircle(image, centerX, centerY, radius, color);
    return 0;
}

int lua_ImageDrawCircleV(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Vector2 center = get_vector2_from_table(L, 2);
    int radius = luaL_checkinteger(L, 3);
    Color color = get_color_from_table(L, 4);
    ImageDrawCircleV(image, center, radius, color);
    return 0;
}

int lua_ImageDrawCircleLines(lua_State *L) {
    Image *dst = luaL_checkudata(L, 1, "Image");
    int centerX = luaL_checkinteger(L, 2);
    int centerY = luaL_checkinteger(L, 3);
    int radius = luaL_checkinteger(L, 4);
    Color color = get_color_from_table(L, 5);
    ImageDrawCircleLines(dst, centerX, centerY, radius, color);
    return 0;
}

int lua_ImageDrawCircleLinesV(lua_State *L) {
    Image *dst = luaL_checkudata(L, 1, "Image");
    Vector2 center = get_vector2_from_table(L, 2);
    int radius = luaL_checkinteger(L, 3);
    Color color = get_color_from_table(L, 4);
    ImageDrawCircleLinesV(dst, center, radius, color);
    return 0;
}

int lua_ImageDrawRectangle(lua_State *L) {
    Image *dst = luaL_checkudata(L, 1, "Image");
    int posX = luaL_checkinteger(L, 2);
    int posY = luaL_checkinteger(L, 3);
    int width = luaL_checkinteger(L, 4);
    int height = luaL_checkinteger(L, 5);
    Color color = get_color_from_table(L, 6);
    ImageDrawRectangle(dst, posX, posY, width, height, color);
    return 0;
}

int lua_ImageDrawRectangleV(lua_State *L) {
    Image *dst = luaL_checkudata(L, 1, "Image");
    Vector2 position = get_vector2_from_table(L, 2);
    Vector2 size = get_vector2_from_table(L, 3);
    Color color = get_color_from_table(L, 4);
    ImageDrawRectangleV(dst, position, size, color);
    return 0;
}

int lua_ImageDrawRectangleRec(lua_State *L) {
    Image *dst = luaL_checkudata(L, 1, "Image");
    Rectangle rec = get_rectangle_from_table(L, 2);
    Color color = get_color_from_table(L, 3);
    ImageDrawRectangleRec(dst, rec, color);
    return 0;
}

int lua_ImageDrawRectangleLines(lua_State *L) {
    Image *dst = luaL_checkudata(L, 1, "Image");
    Rectangle rec = get_rectangle_from_table(L, 2);
    int thick = luaL_checkinteger(L, 3);
    Color color = get_color_from_table(L, 4);
    ImageDrawRectangleLines(dst, rec, thick, color);
    return 0;
}

int lua_ImageDrawTriangle(lua_State *L) {
    Image *dst = luaL_checkudata(L, 1, "Image");
    Vector2 v1 = get_vector2_from_table(L, 2);
    Vector2 v2 = get_vector2_from_table(L, 3);
    Vector2 v3 = get_vector2_from_table(L, 4);
    Color color = get_color_from_table(L, 5);
    ImageDrawTriangle(dst, v1, v2, v3, color);
    return 0;
}

int lua_ImageDrawTriangleEx(lua_State *L) {
    Image *dst = luaL_checkudata(L, 1, "Image");
    Vector2 v1 = get_vector2_from_table(L, 2);
    Vector2 v2 = get_vector2_from_table(L, 3);
    Vector2 v3 = get_vector2_from_table(L, 4);
    Color c1 = get_color_from_table(L, 5);
    Color c2 = get_color_from_table(L, 6);
    Color c3 = get_color_from_table(L, 7);
    ImageDrawTriangleEx(dst, v1, v2, v3, c1, c2, c3);
    return 0;
}

int lua_ImageDrawTriangleLines(lua_State *L) {
    Image *dst = luaL_checkudata(L, 1, "Image");
    Vector2 v1 = get_vector2_from_table(L, 2);
    Vector2 v2 = get_vector2_from_table(L, 3);
    Vector2 v3 = get_vector2_from_table(L, 4);
    Color color = get_color_from_table(L, 5);
    ImageDrawTriangleLines(dst, v1, v2, v3, color);
    return 0;
}

int lua_ImageDrawTriangleFan(lua_State *L) {
    Image *dst = luaL_checkudata(L, 1, "Image");
    int count = luaL_len(L, 2);
    Vector2 *points = malloc(count * sizeof(Vector2));
    for (int i = 0; i < count; i++) {
        lua_rawgeti(L, 2, i + 1);
        points[i] = get_vector2_from_table(L, -1);
        lua_pop(L, 1);
    }
    Color color = get_color_from_table(L, 3);
    ImageDrawTriangleFan(dst, points, count, color);
    free(points);
    return 0;
}

int lua_ImageDrawTriangleStrip(lua_State *L) {
    Image *dst = luaL_checkudata(L, 1, "Image");
    int count = luaL_len(L, 2);
    Vector2 *points = malloc(count * sizeof(Vector2));
    for (int i = 0; i < count; i++) {
        lua_rawgeti(L, 2, i + 1);
        points[i] = get_vector2_from_table(L, -1);
        lua_pop(L, 1);
    }
    Color color = get_color_from_table(L, 3);
    ImageDrawTriangleStrip(dst, points, count, color);
    free(points);
    return 0;
}

int lua_ImageDraw(lua_State *L) {
    Image *dst = luaL_checkudata(L, 1, "Image");
    Image *src = luaL_checkudata(L, 2, "Image");
    Rectangle srcRec = get_rectangle_from_table(L, 3);
    Rectangle dstRec = get_rectangle_from_table(L, 4);
    Color tint = get_color_from_table(L, 5);
    ImageDraw(dst, *src, srcRec, dstRec, tint);
    return 0;
}

int lua_ImageDrawText(lua_State *L) {
    Image *dst = luaL_checkudata(L, 1, "Image");
    const char *text = luaL_checkstring(L, 2);
    int posX = luaL_checkinteger(L, 3);
    int posY = luaL_checkinteger(L, 4);
    int fontSize = luaL_checkinteger(L, 5);
    Color color = get_color_from_table(L, 6);
    ImageDrawText(dst, text, posX, posY, fontSize, color);
    return 0;
}

int lua_ImageDrawTextEx(lua_State *L) {
    Image *dst = luaL_checkudata(L, 1, "Image");
    Font *font = luaL_checkudata(L, 2, "Font");
    const char *text = luaL_checkstring(L, 3);
    Vector2 position = get_vector2_from_table(L, 4);
    float fontSize = luaL_checknumber(L, 5);
    float spacing = luaL_checknumber(L, 6);
    Color tint = get_color_from_table(L, 7);
    ImageDrawTextEx(dst, *font, text, position, fontSize, spacing, tint);
    return 0;
}

int lua_LoadRenderTexture(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    RenderTexture2D renderTexture = LoadRenderTexture(width, height);
    RenderTexture2D *pRenderTexture = lua_newuserdata(L, sizeof(RenderTexture2D));
    *pRenderTexture = renderTexture;
    luaL_setmetatable(L, "RenderTexture2D");
    return 1;
}

int lua_IsTextureValid(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture2D");
    lua_pushboolean(L, IsTextureValid(*texture));
    return 1;
}

int lua_IsRenderTextureValid(lua_State *L) {
    RenderTexture2D *renderTexture = luaL_checkudata(L, 1, "RenderTexture2D");
    lua_pushboolean(L, IsRenderTextureValid(*renderTexture));
    return 1;
}

int lua_UnloadRenderTexture(lua_State *L) {
    RenderTexture2D *renderTexture = luaL_checkudata(L, 1, "RenderTexture2D");
    UnloadRenderTexture(*renderTexture);
    return 0;
}

int lua_SetTextureFilter(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture2D");
    int filter = luaL_checkinteger(L, 2);
    SetTextureFilter(*texture, filter);
    return 0;
}

int lua_SetTextureWrap(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture2D");
    int wrap = luaL_checkinteger(L, 2);
    SetTextureWrap(*texture, wrap);
    return 0;
}

int lua_DrawTexture(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture2D");
    int posX = luaL_checkinteger(L, 2);
    int posY = luaL_checkinteger(L, 3);
    Color color = get_color_from_table(L, 4);
    DrawTexture(*texture, posX, posY, color);
    return 0;
}

int lua_DrawTextureV(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture2D");
    Vector2 position = get_vector2_from_table(L, 2);
    Color color = get_color_from_table(L, 3);
    DrawTextureV(*texture, position, color);
    return 0;
}

int lua_DrawTextureEx(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture2D");
    Vector2 position = get_vector2_from_table(L, 2);
    float rotation = luaL_checknumber(L, 3);
    float scale = luaL_checknumber(L, 4);
    Color color = get_color_from_table(L, 5);
    DrawTextureEx(*texture, position, rotation, scale, color);
    return 0;
}

int lua_DrawTextureRec(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture2D");
    Rectangle source = get_rectangle_from_table(L, 2);
    Vector2 position = get_vector2_from_table(L, 3);
    Color color = get_color_from_table(L, 4);
    DrawTextureRec(*texture, source, position, color);
    return 0;
}

int lua_DrawTexturePro(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture2D");
    Rectangle source = get_rectangle_from_table(L, 2);
    Rectangle dest = get_rectangle_from_table(L, 3);
    Vector2 origin = get_vector2_from_table(L, 4);
    float rotation = luaL_checknumber(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawTexturePro(*texture, source, dest, origin, rotation, color);
    return 0;
}

int lua_DrawTextureNPatch(lua_State *L) {
    Texture2D *texture = luaL_checkudata(L, 1, "Texture2D");
    NPatchInfo nPatchInfo = get_npatchinfo_from_table(L, 2);
    Rectangle dest = get_rectangle_from_table(L, 3);
    Vector2 origin = get_vector2_from_table(L, 4);
    float rotation = luaL_checknumber(L, 5);
    Color color = get_color_from_table(L, 6);
    DrawTextureNPatch(*texture, nPatchInfo, dest, origin, rotation, color);
    return 0;
}

int lua_ColorIsEqual(lua_State *L) {
    Color col1 = get_color_from_table(L, 1);
    Color col2 = get_color_from_table(L, 2);
    lua_pushboolean(L, ColorIsEqual(col1, col2));
    return 1;
}

int lua_Fade(lua_State *L) {
    Color color = get_color_from_table(L, 1);
    float alpha = luaL_checknumber(L, 2);
    Color fadedColor = Fade(color, alpha);
    push_color_to_table(L, fadedColor);
    return 1;
}

int lua_ColorToInt(lua_State *L) {
    Color color = get_color_from_table(L, 1);
    int colorInt = ColorToInt(color);
    lua_pushinteger(L, colorInt);
    return 1;
}

int lua_ColorNormalize(lua_State *L) {
    Color color = get_color_from_table(L, 1);
    Vector4 normalized = ColorNormalize(color);
    push_vector4_to_table(L, normalized);
    return 1;
}

int lua_ColorFromNormalized(lua_State *L) {
    Vector4 normalized = get_vector4_from_table(L, 1);
    Color color = ColorFromNormalized(normalized);
    push_color_to_table(L, color);
    return 1;
}

int lua_ColorToHSV(lua_State *L) {
    Color color = get_color_from_table(L, 1);
    Vector3 hsv = ColorToHSV(color);
    push_vector3_to_table(L, hsv);
    return 1;
}

int lua_ColorFromHSV(lua_State *L) {
    float hue = luaL_checknumber(L, 1);
    float saturation = luaL_checknumber(L, 2);
    float value = luaL_checknumber(L, 3);
    Color color = ColorFromHSV(hue, saturation, value);
    push_color_to_table(L, color);
    return 1;
}

int lua_ColorTint(lua_State *L) {
    Color color = get_color_from_table(L, 1);
    Color tint = get_color_from_table(L, 2);
    Color tintedColor = ColorTint(color, tint);
    push_color_to_table(L, tintedColor);
    return 1;
}

int lua_ColorBrightness(lua_State *L) {
    Color color = get_color_from_table(L, 1);
    float factor = luaL_checknumber(L, 2);
    Color result = ColorBrightness(color, factor);
    push_color_to_table(L, result);
    return 1;
}

int lua_ColorContrast(lua_State *L) {
    Color color = get_color_from_table(L, 1);
    float contrast = luaL_checknumber(L, 2);
    Color result = ColorContrast(color, contrast);
    push_color_to_table(L, result);
    return 1;
}

int lua_ColorAlpha(lua_State *L) {
    Color color = get_color_from_table(L, 1);
    float alpha = luaL_checknumber(L, 2);
    Color result = ColorAlpha(color, alpha);
    push_color_to_table(L, result);
    return 1;
}

int lua_ColorAlphaBlend(lua_State *L) {
    Color dst = get_color_from_table(L, 1);
    Color src = get_color_from_table(L, 2);
    Color tint = get_color_from_table(L, 3);
    Color result = ColorAlphaBlend(dst, src, tint);
    push_color_to_table(L, result);
    return 1;
}

int lua_ColorLerp(lua_State *L) {
    Color color1 = get_color_from_table(L, 1);
    Color color2 = get_color_from_table(L, 2);
    float factor = luaL_checknumber(L, 3);
    Color result = ColorLerp(color1, color2, factor);
    push_color_to_table(L, result);
    return 1;
}

int lua_GetColor(lua_State *L) {
    unsigned int hexValue = luaL_checkinteger(L, 1);
    Color result = GetColor(hexValue);
    push_color_to_table(L, result);
    return 1;
}

int lua_GetPixelColor(lua_State *L) {
    void *srcPtr = lua_touserdata(L, 1);
    int format = luaL_checkinteger(L, 2);
    Color result = GetPixelColor(srcPtr, format);
    push_color_to_table(L, result);
    return 1;
}

int lua_SetPixelColor(lua_State *L) {
    void *dstPtr = lua_touserdata(L, 1);
    Color color = get_color_from_table(L, 2);
    int format = luaL_checkinteger(L, 3);
    SetPixelColor(dstPtr, color, format);
    return 0;
}

int lua_GetPixelDataSize(lua_State *L) {
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    int format = luaL_checkinteger(L, 3);
    int result = GetPixelDataSize(width, height, format);
    lua_pushinteger(L, result);
    return 1;
}
