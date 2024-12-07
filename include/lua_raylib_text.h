#ifndef LUA_RAYLIB_TEXT_H
#define LUA_RAYLIB_TEXT_H

#include "lua.h"
#include "raylib.h"

/**
 * @brief Gets the default font.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Font result)
 */
int lua_GetFontDefault(lua_State *L);

/**
 * @brief Loads a font from a file.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Font result)
 */
int lua_LoadFont(lua_State *L);

/**
 * @brief Loads a font from a file with extended parameters.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Font result)
 */
int lua_LoadFontEx(lua_State *L);

/**
 * @brief Loads a font from an image.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Font result)
 */
int lua_LoadFontFromImage(lua_State *L);

/**
 * @brief Loads a font from memory.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Font result)
 */
int lua_LoadFontFromMemory(lua_State *L);

/**
 * @brief Checks if a font is valid.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsFontValid(lua_State *L);

/**
 * @brief Unloads a font from memory.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UnloadFont(lua_State *L);

/**
 * @brief Exports a font as code.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_ExportFontAsCode(lua_State *L);

/**
 * @brief Draws the current FPS on the screen.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawFPS(lua_State *L);

/**
 * @brief Draws text on the screen.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawText(lua_State *L);

/**
 * @brief Draws text on the screen with extended parameters.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawTextEx(lua_State *L);

/**
 * @brief Draws text on the screen with additional options.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawTextPro(lua_State *L);

/**
 * @brief Draws a single codepoint as text on the screen.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawTextCodepoint(lua_State *L);

/**
 * @brief Draws multiple codepoints as text on the screen.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DrawTextCodepoints(lua_State *L);

/**
 * @brief Sets the line spacing for text.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetTextLineSpacing(lua_State *L);

/**
 * @brief Measures the width of the text.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_MeasureText(lua_State *L);

/**
 * @brief Measures the size of the text with extended parameters.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Vector2 result)
 */
int lua_MeasureTextEx(lua_State *L);

/**
 * @brief Gets the index of a glyph in the font.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetGlyphIndex(lua_State *L);

/**
 * @brief Gets information about a glyph in the font.
 * 
 * @param L Lua state
 * @return int Always returns 1 (GlyphInfo result)
 */
int lua_GetGlyphInfo(lua_State *L);

/**
 * @brief Gets the atlas rectangle of a glyph in the font.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Rectangle result)
 */
int lua_GetGlyphAtlasRec(lua_State *L);

/**
 * @brief Loads a UTF-8 string.
 * 
 * @param L Lua state
 * @return int Always returns 1 (string result)
 */
int lua_LoadUTF8(lua_State *L);

/**
 * @brief Unloads a UTF-8 string from memory.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UnloadUTF8(lua_State *L);

/**
 * @brief Loads codepoints from a UTF-8 string.
 * 
 * @param L Lua state
 * @return int Always returns 1 (codepoints result)
 */
int lua_LoadCodepoints(lua_State *L);

/**
 * @brief Unloads codepoints from memory.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UnloadCodepoints(lua_State *L);

/**
 * @brief Gets the count of codepoints in a UTF-8 string.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetCodepointCount(lua_State *L);

/**
 * @brief Gets a codepoint from a UTF-8 string.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetCodepoint(lua_State *L);

/**
 * @brief Gets the next codepoint in a UTF-8 string.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetCodepointNext(lua_State *L);

/**
 * @brief Gets the previous codepoint in a UTF-8 string.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_GetCodepointPrevious(lua_State *L);

/**
 * @brief Converts a codepoint to a UTF-8 string.
 * 
 * @param L Lua state
 * @return int Always returns 1 (string result)
 */
int lua_CodepointToUTF8(lua_State *L);

/**
 * @brief Copies text from one string to another.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_TextCopy(lua_State *L);

/**
 * @brief Checks if two strings are equal.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_TextIsEqual(lua_State *L);

/**
 * @brief Gets the length of a text string.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_TextLength(lua_State *L);

/**
 * @brief Formats a text string.
 * 
 * @param L Lua state
 * @return int Always returns 1 (string result)
 */
int lua_TextFormat(lua_State *L);

/**
 * @brief Gets a subtext from a text string.
 * 
 * @param L Lua state
 * @return int Always returns 1 (string result)
 */
int lua_TextSubtext(lua_State *L);

/**
 * @brief Replaces text in a string.
 * 
 * @param L Lua state
 * @return int Always returns 1 (string result)
 */
int lua_TextReplace(lua_State *L);

/**
 * @brief Inserts text into a string.
 * 
 * @param L Lua state
 * @return int Always returns 1 (string result)
 */
int lua_TextInsert(lua_State *L);

/**
 * @brief Joins text strings.
 * 
 * @param L Lua state
 * @return int Always returns 1 (string result)
 */
int lua_TextJoin(lua_State *L);

/**
 * @brief Splits a text string.
 * 
 * @param L Lua state
 * @return int Always returns 1 (table result)
 */
int lua_TextSplit(lua_State *L);

/**
 * @brief Appends text to a string.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_TextAppend(lua_State *L);

/**
 * @brief Finds the index of a substring in a text string.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_TextFindIndex(lua_State *L);

/**
 * @brief Converts a text string to uppercase.
 * 
 * @param L Lua state
 * @return int Always returns 1 (string result)
 */
int lua_TextToUpper(lua_State *L);

/**
 * @brief Converts a text string to lowercase.
 * 
 * @param L Lua state
 * @return int Always returns 1 (string result)
 */
int lua_TextToLower(lua_State *L);

/**
 * @brief Converts a text string to Pascal case.
 * 
 * @param L Lua state
 * @return int Always returns 1 (string result)
 */
int lua_TextToPascal(lua_State *L);

/**
 * @brief Converts a text string to snake case.
 * 
 * @param L Lua state
 * @return int Always returns 1 (string result)
 */
int lua_TextToSnake(lua_State *L);

/**
 * @brief Converts a text string to camel case.
 * 
 * @param L Lua state
 * @return int Always returns 1 (string result)
 */
int lua_TextToCamel(lua_State *L);

/**
 * @brief Converts a text string to an integer.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 */
int lua_TextToInteger(lua_State *L);

/**
 * @brief Converts a text string to a float.
 * 
 * @param L Lua state
 * @return int Always returns 1 (float result)
 */
int lua_TextToFloat(lua_State *L);

#endif
