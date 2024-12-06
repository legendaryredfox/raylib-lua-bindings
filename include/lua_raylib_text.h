#ifndef LUA_RAYLIB_TEXT_H
#define LUA_RAYLIB_TEXT_H

#include "lua.h"
#include "raylib.h"

int lua_GetFontDefault(lua_State *L);
int lua_LoadFont(lua_State *L);
int lua_LoadFontEx(lua_State *L);
int lua_LoadFontFromImage(lua_State *L);
int lua_LoadFontFromMemory(lua_State *L);
int lua_IsFontValid(lua_State *L);
int lua_UnloadFont(lua_State *L);
int lua_ExportFontAsCode(lua_State *L);
int lua_DrawFPS(lua_State *L);
int lua_DrawText(lua_State *L);
int lua_DrawTextEx(lua_State *L);
int lua_DrawTextPro(lua_State *L);
int lua_DrawTextCodepoint(lua_State *L);
int lua_DrawTextCodepoints(lua_State *L);
int lua_SetTextLineSpacing(lua_State *L);
int lua_MeasureText(lua_State *L);
int lua_MeasureTextEx(lua_State *L);
int lua_GetGlyphIndex(lua_State *L);
int lua_GetGlyphInfo(lua_State *L);
int lua_GetGlyphAtlasRec(lua_State *L);
int lua_LoadUTF8(lua_State *L);
int lua_UnloadUTF8(lua_State *L);
int lua_LoadCodepoints(lua_State *L);
int lua_UnloadCodepoints(lua_State *L);
int lua_GetCodepointCount(lua_State *L);
int lua_GetCodepoint(lua_State *L);
int lua_GetCodepointNext(lua_State *L);
int lua_GetCodepointPrevious(lua_State *L);
int lua_CodepointToUTF8(lua_State *L);
int lua_TextCopy(lua_State *L);
int lua_TextIsEqual(lua_State *L);
int lua_TextLength(lua_State *L);
int lua_TextFormat(lua_State *L);
int lua_TextSubtext(lua_State *L);
int lua_TextReplace(lua_State *L);
int lua_TextInsert(lua_State *L);
int lua_TextJoin(lua_State *L);
int lua_TextSplit(lua_State *L);
int lua_TextAppend(lua_State *L);
int lua_TextFindIndex(lua_State *L);
int lua_TextToUpper(lua_State *L);
int lua_TextToLower(lua_State *L);
int lua_TextToPascal(lua_State *L);
int lua_TextToSnake(lua_State *L);
int lua_TextToCamel(lua_State *L);
int lua_TextToInteger(lua_State *L);
int lua_TextToFloat(lua_State *L);

#endif
