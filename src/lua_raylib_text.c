#include <stdlib.h>
#include <string.h>
#include "lua_raylib_text.h"
#include "raylib_wrappers.h"
#include "lauxlib.h"

int lua_GetFontDefault(lua_State *L) {
    Font font = GetFontDefault();
    Font *pFont = lua_newuserdata(L, sizeof(Font));
    *pFont = font;
    luaL_setmetatable(L, "Font");
    return 1;
}

int lua_LoadFont(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    Font font = LoadFont(fileName);
    Font *pFont = lua_newuserdata(L, sizeof(Font));
    *pFont = font;
    luaL_setmetatable(L, "Font");
    return 1;
}

int lua_LoadFontEx(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    int fontSize = luaL_checkinteger(L, 2);
    int *codepoints = NULL;
    int codepointCount = 0;

    if (!lua_isnil(L, 3)) {
        luaL_checktype(L, 3, LUA_TTABLE);
        codepointCount = lua_rawlen(L, 3);
        codepoints = (int *)malloc(sizeof(int) * codepointCount);

        for (int i = 0; i < codepointCount; i++) {
            lua_rawgeti(L, 3, i + 1);
            codepoints[i] = luaL_checkinteger(L, -1);
            lua_pop(L, 1);
        }
    }

    Font font = LoadFontEx(fileName, fontSize, codepoints, codepointCount);
    free(codepoints);

    Font *pFont = lua_newuserdata(L, sizeof(Font));
    *pFont = font;
    luaL_setmetatable(L, "Font");
    return 1;
}

int lua_LoadFontFromImage(lua_State *L) {
    Image *image = luaL_checkudata(L, 1, "Image");
    Color key = get_color_from_table(L, 2);
    int firstChar = luaL_checkinteger(L, 3);
    Font font = LoadFontFromImage(*image, key, firstChar);

    Font *pFont = lua_newuserdata(L, sizeof(Font));
    *pFont = font;
    luaL_setmetatable(L, "Font");
    return 1;
}

int lua_LoadFontFromMemory(lua_State *L) {
    const char *fileType = luaL_checkstring(L, 1);
    size_t dataSize;
    const char *fileData = luaL_checklstring(L, 2, &dataSize);
    int fontSize = luaL_checkinteger(L, 3);
    int *codepoints = NULL;
    int codepointCount = 0;

    if (!lua_isnil(L, 4)) {
        luaL_checktype(L, 4, LUA_TTABLE);
        codepointCount = lua_rawlen(L, 4);
        codepoints = (int *)malloc(sizeof(int) * codepointCount);

        for (int i = 0; i < codepointCount; i++) {
            lua_rawgeti(L, 4, i + 1);
            codepoints[i] = luaL_checkinteger(L, -1);
            lua_pop(L, 1);
        }
    }

    Font font = LoadFontFromMemory(fileType, (unsigned char *)fileData, (int)dataSize, fontSize, codepoints, codepointCount);
    free(codepoints);

    Font *pFont = lua_newuserdata(L, sizeof(Font));
    *pFont = font;
    luaL_setmetatable(L, "Font");
    return 1;
}

int lua_IsFontValid(lua_State *L) {
    Font *font = luaL_checkudata(L, 1, "Font");
    lua_pushboolean(L, IsFontValid(*font));
    return 1;
}

int lua_UnloadFont(lua_State *L) {
    Font *font = luaL_checkudata(L, 1, "Font");
    UnloadFont(*font);
    return 0;
}

int lua_ExportFontAsCode(lua_State *L) {
    Font *font = luaL_checkudata(L, 1, "Font");
    const char *fileName = luaL_checkstring(L, 2);
    lua_pushboolean(L, ExportFontAsCode(*font, fileName));
    return 1;
}

int lua_DrawFPS(lua_State *L) {
    int posX = luaL_checkinteger(L, 1);
    int posY = luaL_checkinteger(L, 2);
    DrawFPS(posX, posY);
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

int lua_DrawTextEx(lua_State *L) {
    Font *font = luaL_checkudata(L, 1, "Font");
    const char *text = luaL_checkstring(L, 2);
    Vector2 position = get_vector2_from_table(L, 3);
    float fontSize = luaL_checknumber(L, 4);
    float spacing = luaL_checknumber(L, 5);
    Color tint = get_color_from_table(L, 6);
    DrawTextEx(*font, text, position, fontSize, spacing, tint);
    return 0;
}

int lua_DrawTextPro(lua_State *L) {
    Font *font = luaL_checkudata(L, 1, "Font");
    const char *text = luaL_checkstring(L, 2);
    Vector2 position = get_vector2_from_table(L, 3);
    Vector2 origin = get_vector2_from_table(L, 4);
    float rotation = luaL_checknumber(L, 5);
    float fontSize = luaL_checknumber(L, 6);
    float spacing = luaL_checknumber(L, 7);
    Color tint = get_color_from_table(L, 8);
    DrawTextPro(*font, text, position, origin, rotation, fontSize, spacing, tint);
    return 0;
}

int lua_DrawTextCodepoint(lua_State *L) {
    Font *font = luaL_checkudata(L, 1, "Font");
    int codepoint = luaL_checkinteger(L, 2);
    Vector2 position = get_vector2_from_table(L, 3);
    float fontSize = luaL_checknumber(L, 4);
    Color tint = get_color_from_table(L, 5);
    DrawTextCodepoint(*font, codepoint, position, fontSize, tint);
    return 0;
}

int lua_DrawTextCodepoints(lua_State *L) {
    Font *font = luaL_checkudata(L, 1, "Font");
    luaL_checktype(L, 2, LUA_TTABLE);
    int codepointCount = lua_rawlen(L, 2);
    int *codepoints = (int *)malloc(sizeof(int) * codepointCount);

    for (int i = 0; i < codepointCount; i++) {
        lua_rawgeti(L, 2, i + 1);
        codepoints[i] = luaL_checkinteger(L, -1);
        lua_pop(L, 1);
    }

    Vector2 position = get_vector2_from_table(L, 3);
    float fontSize = luaL_checknumber(L, 4);
    float spacing = luaL_checknumber(L, 5);
    Color tint = get_color_from_table(L, 6);

    DrawTextCodepoints(*font, codepoints, codepointCount, position, fontSize, spacing, tint);

    free(codepoints);
    return 0;
}

int lua_SetTextLineSpacing(lua_State *L) {
    int spacing = luaL_checkinteger(L, 1);
    SetTextLineSpacing(spacing);
    return 0;
}

int lua_MeasureText(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    int fontSize = luaL_checkinteger(L, 2);
    lua_pushinteger(L, MeasureText(text, fontSize));
    return 1;
}

int lua_MeasureTextEx(lua_State *L) {
    Font *font = luaL_checkudata(L, 1, "Font");
    const char *text = luaL_checkstring(L, 2);
    float fontSize = luaL_checknumber(L, 3);
    float spacing = luaL_checknumber(L, 4);
    Vector2 size = MeasureTextEx(*font, text, fontSize, spacing);
    push_vector2_to_table(L, size);
    return 1;
}

int lua_GetGlyphIndex(lua_State *L) {
    Font *font = luaL_checkudata(L, 1, "Font");
    int codepoint = luaL_checkinteger(L, 2);
    lua_pushinteger(L, GetGlyphIndex(*font, codepoint));
    return 1;
}

int lua_GetGlyphInfo(lua_State *L) {
    Font *font = luaL_checkudata(L, 1, "Font");
    int codepoint = luaL_checkinteger(L, 2);
    GlyphInfo glyphInfo = GetGlyphInfo(*font, codepoint);

    GlyphInfo *pGlyphInfo = lua_newuserdata(L, sizeof(GlyphInfo));
    *pGlyphInfo = glyphInfo;
    luaL_setmetatable(L, "GlyphInfo");
    return 1;
}

int lua_GetGlyphAtlasRec(lua_State *L) {
    Font *font = luaL_checkudata(L, 1, "Font");
    int codepoint = luaL_checkinteger(L, 2);
    Rectangle rec = GetGlyphAtlasRec(*font, codepoint);
    push_rectangle_to_table(L, rec);
    return 1;
}

int lua_LoadUTF8(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    int length = lua_rawlen(L, 1);
    int *codepoints = malloc(sizeof(int) * length);

    for (int i = 0; i < length; i++) {
        lua_rawgeti(L, 1, i + 1);
        codepoints[i] = luaL_checkinteger(L, -1);
        lua_pop(L, 1);
    }

    char *text = LoadUTF8(codepoints, length);
    free(codepoints);
    lua_pushstring(L, text);
    UnloadUTF8(text);
    return 1;
}

int lua_UnloadUTF8(lua_State *L) {
    char *text = (char *)luaL_checkstring(L, 1);
    UnloadUTF8(text);
    return 0;
}

int lua_LoadCodepoints(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    int count;
    int *codepoints = LoadCodepoints(text, &count);

    lua_newtable(L);
    for (int i = 0; i < count; i++) {
        lua_pushinteger(L, codepoints[i]);
        lua_rawseti(L, -2, i + 1);
    }

    UnloadCodepoints(codepoints);
    return 1;
}

int lua_UnloadCodepoints(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    // No-op in Lua as we don't maintain allocated memory for this purpose.
    return 0;
}

int lua_GetCodepointCount(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    lua_pushinteger(L, GetCodepointCount(text));
    return 1;
}

int lua_GetCodepoint(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    int size;
    int codepoint = GetCodepoint(text, &size);
    lua_pushinteger(L, codepoint);
    lua_pushinteger(L, size);
    return 2;
}

int lua_GetCodepointNext(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    int size;
    int codepoint = GetCodepointNext(text, &size);
    lua_pushinteger(L, codepoint);
    lua_pushinteger(L, size);
    return 2;
}

int lua_GetCodepointPrevious(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    int size;
    int codepoint = GetCodepointPrevious(text, &size);
    lua_pushinteger(L, codepoint);
    lua_pushinteger(L, size);
    return 2;
}

int lua_CodepointToUTF8(lua_State *L) {
    int codepoint = luaL_checkinteger(L, 1);
    int size;
    const char *utf8Text = CodepointToUTF8(codepoint, &size);

    lua_pushstring(L, utf8Text);
    lua_pushinteger(L, size);
    return 2;
}

int lua_TextCopy(lua_State *L) {
    const char *src = luaL_checkstring(L, 1);
    char *dst = malloc(strlen(src) + 1);
    int bytesCopied = TextCopy(dst, src);
    lua_pushstring(L, dst);
    lua_pushinteger(L, bytesCopied);
    free(dst);
    return 2;
}

int lua_TextIsEqual(lua_State *L) {
    const char *text1 = luaL_checkstring(L, 1);
    const char *text2 = luaL_checkstring(L, 2);
    lua_pushboolean(L, TextIsEqual(text1, text2));
    return 1;
}

int lua_TextLength(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    lua_pushinteger(L, TextLength(text));
    return 1;
}

int lua_TextFormat(lua_State *L) {
    const char *formattedText = luaL_checkstring(L, 1);
    lua_pushstring(L, formattedText);
    return 1;
}

int lua_TextSubtext(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    int position = luaL_checkinteger(L, 2);
    int length = luaL_checkinteger(L, 3);
    lua_pushstring(L, TextSubtext(text, position, length));
    return 1;
}

int lua_TextReplace(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    const char *replace = luaL_checkstring(L, 2);
    const char *by = luaL_checkstring(L, 3);
    char *result = TextReplace(text, replace, by);
    lua_pushstring(L, result);
    free(result); // Free memory allocated by TextReplace
    return 1;
}

int lua_TextInsert(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    const char *insert = luaL_checkstring(L, 2);
    int position = luaL_checkinteger(L, 3);
    char *result = TextInsert(text, insert, position);
    lua_pushstring(L, result);
    free(result); // Free memory allocated by TextInsert
    return 1;
}

int lua_TextJoin(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    const char *delimiter = luaL_checkstring(L, 2);
    int count = lua_rawlen(L, 1);
    const char **textList = malloc(sizeof(char *) * count);

    for (int i = 0; i < count; i++) {
        lua_rawgeti(L, 1, i + 1);
        textList[i] = luaL_checkstring(L, -1);
        lua_pop(L, 1);
    }

    const char *result = TextJoin(textList, count, delimiter);
    lua_pushstring(L, result);
    free((void *)result); // Free memory allocated by TextJoin
    free(textList);
    return 1;
}

int lua_TextSplit(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    char delimiter = luaL_checkstring(L, 2)[0];
    int count;
    const char **result = TextSplit(text, delimiter, &count);

    lua_newtable(L);
    for (int i = 0; i < count; i++) {
        lua_pushstring(L, result[i]);
        lua_rawseti(L, -2, i + 1);
    }

    free(result); // Free memory allocated by TextSplit
    return 1;
}

int lua_TextAppend(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    const char *append = luaL_checkstring(L, 2);
    int position = luaL_checkinteger(L, 3);

    // Allocate buffer for appending
    size_t textLen = strlen(text);
    size_t appendLen = strlen(append);
    char *buffer = malloc(textLen + appendLen + 1);
    if (!buffer) {
        return luaL_error(L, "Memory allocation failed for TextAppend");
    }

    strcpy(buffer, text);
    TextAppend(buffer, append, &position);

    lua_pushstring(L, buffer);
    lua_pushinteger(L, position);
    free(buffer);
    return 2;
}


int lua_TextFindIndex(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    const char *find = luaL_checkstring(L, 2);

    int index = TextFindIndex(text, find);
    lua_pushinteger(L, index);
    return 1;
}

int lua_TextToUpper(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);

    const char *result = TextToUpper(text);
    lua_pushstring(L, result);
    free((void *)result); // Free memory allocated by raylib
    return 1;
}

int lua_TextToLower(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);

    const char *result = TextToLower(text);
    lua_pushstring(L, result);
    free((void *)result); // Free memory allocated by raylib
    return 1;
}

int lua_TextToPascal(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);

    const char *result = TextToPascal(text);
    lua_pushstring(L, result);
    free((void *)result); // Free memory allocated by raylib
    return 1;
}

int lua_TextToSnake(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);

    const char *result = TextToSnake(text);
    lua_pushstring(L, result);
    free((void *)result); // Free memory allocated by raylib
    return 1;
}

int lua_TextToCamel(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);

    const char *result = TextToCamel(text);
    lua_pushstring(L, result);
    free((void *)result); // Free memory allocated by raylib
    return 1;
}

int lua_TextToInteger(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    int value = TextToInteger(text);
    lua_pushinteger(L, value);
    return 1;
}

int lua_TextToFloat(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    float value = TextToFloat(text);
    lua_pushnumber(L, value);
    return 1;
}