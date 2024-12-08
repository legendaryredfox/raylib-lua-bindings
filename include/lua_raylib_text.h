#ifndef LUA_RAYLIB_TEXT_H
#define LUA_RAYLIB_TEXT_H

#include "lua.h"
#include "raylib.h"

/**
 * @brief Gets the default font.
 * 
 * This function returns the default font used by Raylib.
 * 
 * @param L A pointer to the current Lua state.
 * 
 * @return int Always returns 1 (Font result) — the default font used by Raylib.
 * 
 * @usage
 * ```lua
 * local font = raylib.GetFontDefault()
 * print(font) -- Prints information about the default font
 * ```
 * 
 * @note The default font is always available and does not require loading.
 */
int lua_GetFontDefault(lua_State *L);

/**
 * @brief Loads a font from a file.
 * 
 * This function loads a font from a file located at a given path.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `string fileName`: The path to the font file to load.
 * 
 * @return int Always returns 1 (Font result) — the loaded font object.
 * 
 * @usage
 * ```lua
 * local font = raylib.LoadFont("resources/arial.ttf")
 * print(font) -- Prints information about the loaded font
 * ```
 * 
 * @note Supported font file formats include TTF, OTF, and other common font formats.
 */
int lua_LoadFont(lua_State *L);

/**
 * @brief Loads a font from a file with extended parameters.
 * 
 * This function loads a font from a file with specific parameters like font size and character range.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `string fileName`: The path to the font file to load.
 *  - `int fontSize`: The size of the font to load.
 *  - `int* charValues`: An array of characters to load.
 *  - `int charCount`: The number of characters in the charValues array.
 * 
 * @return int Always returns 1 (Font result) — the loaded font object.
 * 
 * @usage
 * ```lua
 * local font = raylib.LoadFontEx("resources/arial.ttf", 32, nil, 0)
 * print(font) -- Prints information about the loaded font
 * ```
 * 
 * @note This function provides more control over the font loading process, including font size and character set.
 */
int lua_LoadFontEx(lua_State *L);

/**
 * @brief Loads a font from an image.
 * 
 * This function loads a font from an image file where characters are defined in a grid.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Image image`: The image containing the characters of the font.
 *  - `Color key`: The color key used for transparency.
 * 
 * @return int Always returns 1 (Font result) — the loaded font object.
 * 
 * @usage
 * ```lua
 * local image = raylib.LoadImage("resources/font_image.png")
 * local font = raylib.LoadFontFromImage(image, raylib.Color.BLACK)
 * print(font) -- Prints information about the loaded font
 * ```
 * 
 * @note The image must have the characters arranged in a grid. The color key is used to identify transparent regions in the image.
 */
int lua_LoadFontFromImage(lua_State *L);

/**
 * @brief Loads a font from memory.
 * 
 * This function loads a font directly from a memory buffer. It allows for loading font data 
 * that might not exist as a file on the filesystem.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `string fileType`: The type of the font file (e.g., "ttf" or "otf").
 *  - `string data`: The binary data of the font file.
 *  - `int dataSize`: The size of the binary data in bytes.
 *  - `int fontSize`: The desired font size.
 * 
 * @return int Always returns 1 (Font result) — the loaded font object.
 * 
 * @usage
 * ```lua
 * local fontData = raylib.LoadFileData("resources/arial.ttf")
 * local font = raylib.LoadFontFromMemory("ttf", fontData, #fontData, 32)
 * print(font) -- Prints information about the loaded font
 * ```
 * 
 * @note This function is useful for loading fonts stored in memory (e.g., from an archive or a network source).
 */
int lua_LoadFontFromMemory(lua_State *L);

/**
 * @brief Checks if a font is valid.
 * 
 * This function verifies if a given font object is valid and usable.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Font font`: The font object to check.
 * 
 * @return int Always returns 1 (boolean result) — `true` if the font is valid, `false` otherwise.
 * 
 * @usage
 * ```lua
 * local font = raylib.LoadFont("resources/arial.ttf")
 * local isValid = raylib.IsFontValid(font)
 * print(isValid) -- Prints true if the font is valid, false otherwise
 * ```
 * 
 * @note Use this function to ensure that a font was successfully loaded before using it.
 */
int lua_IsFontValid(lua_State *L);

/**
 * @brief Unloads a font from memory.
 * 
 * This function releases the memory allocated for a font object.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Font font`: The font object to unload.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local font = raylib.LoadFont("resources/arial.ttf")
 * raylib.UnloadFont(font)
 * print("Font unloaded")
 * ```
 * 
 * @note Call this function when the font is no longer needed to free up system memory.
 */
int lua_UnloadFont(lua_State *L);

/**
 * @brief Exports a font as C code.
 * 
 * This function generates a C source file containing the font data as code.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Font font`: The font object to export.
 *  - `string fileName`: The path where the C source file will be saved.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local font = raylib.LoadFont("resources/arial.ttf")
 * raylib.ExportFontAsCode(font, "output_font.c")
 * print("Font exported as C code")
 * ```
 * 
 * @note This function is useful for embedding font data directly into a C program.
 */
int lua_ExportFontAsCode(lua_State *L);

/**
 * @brief Draws the current FPS on the screen.
 * 
 * This function displays the current frames per second (FPS) at the top-left of the screen.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `int x`: The X position where the FPS will be drawn.
 *  - `int y`: The Y position where the FPS will be drawn.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawFPS(10, 10)
 * raylib.EndDrawing()
 * ```
 * 
 * @note Useful for debugging to see if the application is running smoothly.
 */
int lua_DrawFPS(lua_State *L);

/**
 * @brief Draws text on the screen.
 * 
 * This function draws a simple string of text on the screen at the specified position.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `string text`: The text to be drawn.
 *  - `int x`: The X position where the text will be drawn.
 *  - `int y`: The Y position where the text will be drawn.
 *  - `int fontSize`: The font size to use.
 *  - `Color color`: The color of the text.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawText("Hello, world!", 100, 100, 20, raylib.DARKGRAY)
 * raylib.EndDrawing()
 * ```
 * 
 * @note The font used is the default font unless another font is loaded.
 */
int lua_DrawText(lua_State *L);

/**
 * @brief Draws text on the screen with extended parameters.
 * 
 * This function draws text with more control over positioning and scaling.
 * 
 * @param L A pointer to the current Lua state. Expects 5 arguments:
 *  - `Font font`: The font to be used for the text.
 *  - `string text`: The text to be drawn.
 *  - `Vector2 position`: The position where the text will be drawn.
 *  - `float fontSize`: The font size.
 *  - `float spacing`: The spacing between characters.
 *  - `Color color`: The color of the text.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local font = raylib.LoadFont("resources/arial.ttf")
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawTextEx(font, "Hello, world!", { x = 100, y = 100 }, 20, 1.0, raylib.DARKGRAY)
 * raylib.EndDrawing()
 * raylib.UnloadFont(font)
 * ```
 * 
 * @note This function allows you to use custom fonts and specify more fine-grained control over text appearance.
 */
int lua_DrawTextEx(lua_State *L);

/**
 * @brief Draws text on the screen with additional options.
 * 
 * This function allows for more precise control of text alignment, rotation, and spacing.
 * 
 * @param L A pointer to the current Lua state. Expects 7 arguments:
 *  - `Font font`: The font to be used for the text.
 *  - `string text`: The text to be drawn.
 *  - `Vector2 position`: The position where the text will be drawn.
 *  - `Vector2 origin`: The point of origin for transformations (e.g., rotation).
 *  - `float rotation`: The rotation in degrees.
 *  - `float fontSize`: The font size.
 *  - `float spacing`: The spacing between characters.
 *  - `Color color`: The color of the text.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local font = raylib.LoadFont("resources/arial.ttf")
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawTextPro(font, "Hello, world!", { x = 100, y = 100 }, { x = 50, y = 50 }, 45.0, 20, 1.0, raylib.DARKGRAY)
 * raylib.EndDrawing()
 * raylib.UnloadFont(font)
 * ```
 * 
 * @note This function provides full control of text transformations, including rotation, origin, and scaling.
 */
int lua_DrawTextPro(lua_State *L);

/**
 * @brief Draws a single codepoint as text on the screen.
 * 
 * This function draws a single Unicode codepoint on the screen at the specified position.
 * 
 * @param L A pointer to the current Lua state. Expects 6 arguments:
 *  - `Font font`: The font to be used for the text.
 *  - `int codepoint`: The Unicode codepoint to be drawn.
 *  - `Vector2 position`: The position where the text will be drawn.
 *  - `float fontSize`: The font size.
 *  - `Color color`: The color of the text.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local font = raylib.LoadFont("resources/arial.ttf")
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawTextCodepoint(font, 65, { x = 100, y = 100 }, 20, raylib.DARKGRAY) -- Draws "A"
 * raylib.EndDrawing()
 * raylib.UnloadFont(font)
 * ```
 * 
 * @note Codepoints are Unicode character representations. Use this function to draw individual characters.
 */
int lua_DrawTextCodepoint(lua_State *L);

/**
 * @brief Draws multiple codepoints as text on the screen.
 * 
 * This function draws multiple Unicode codepoints on the screen using a font.
 * 
 * @param L A pointer to the current Lua state. Expects 6 arguments:
 *  - `Font font`: The font to be used for the text.
 *  - `int[] codepoints`: An array of Unicode codepoints to be drawn.
 *  - `Vector2 position`: The position where the text will be drawn.
 *  - `float fontSize`: The font size.
 *  - `float spacing`: The spacing between characters.
 *  - `Color color`: The color of the text.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local font = raylib.LoadFont("resources/arial.ttf")
 * local codepoints = { 65, 66, 67 } -- A, B, C
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawTextCodepoints(font, codepoints, { x = 100, y = 100 }, 20, 2.0, raylib.DARKGRAY)
 * raylib.EndDrawing()
 * raylib.UnloadFont(font)
 * ```
 * 
 * @note Useful for rendering multilingual or symbol-based text where you need to draw multiple characters at once.
 */
int lua_DrawTextCodepoints(lua_State *L);

/**
 * @brief Sets the line spacing for text.
 * 
 * This function sets the amount of space between lines of text.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `float spacing`: The amount of space to add between lines.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * raylib.SetTextLineSpacing(1.5)
 * ```
 * 
 * @note This affects all text rendering until the spacing is changed again.
 */
int lua_SetTextLineSpacing(lua_State *L);

/**
 * @brief Measures the width of the text.
 * 
 * This function returns the width of a text string when drawn with a given font size.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `string text`: The text to be measured.
 *  - `int fontSize`: The font size to measure the text at.
 * 
 * @return int Always returns 1 (integer result) — The width of the text.
 * 
 * @usage
 * ```lua
 * local width = raylib.MeasureText("Hello, world!", 20)
 * print("The width of the text is: ", width)
 * ```
 * 
 * @note Use this function to align or position text on the screen.
 */
int lua_MeasureText(lua_State *L);

/**
 * @brief Measures the size of the text with extended parameters.
 * 
 * This function returns the size (width and height) of a text string when drawn with a given font, font size, and spacing.
 * 
 * @param L A pointer to the current Lua state. Expects 4 arguments:
 *  - `Font font`: The font to be used for the text.
 *  - `string text`: The text to be measured.
 *  - `float fontSize`: The font size to measure the text at.
 *  - `float spacing`: The spacing between characters.
 * 
 * @return int Always returns 1 (Vector2 result) — The size of the text as a Vector2 (width, height).
 * 
 * @usage
 * ```lua
 * local font = raylib.LoadFont("resources/arial.ttf")
 * local textSize = raylib.MeasureTextEx(font, "Hello, world!", 20, 2.0)
 * print("The size of the text is: ", textSize.x, textSize.y)
 * raylib.UnloadFont(font)
 * ```
 * 
 * @note Use this function to calculate how much space text will occupy on the screen.
 */
int lua_MeasureTextEx(lua_State *L);

/**
 * @brief Gets the index of a glyph in the font.
 * 
 * This function returns the index of a specific glyph within a font.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Font font`: The font to look for the glyph in.
 *  - `int codepoint`: The Unicode codepoint of the glyph.
 * 
 * @return int Always returns 1 (integer result) — The index of the glyph in the font.
 * 
 * @usage
 * ```lua
 * local font = raylib.LoadFont("resources/arial.ttf")
 * local index = raylib.GetGlyphIndex(font, 65) -- Get index for 'A'
 * print("The index of the glyph for 'A' is: ", index)
 * raylib.UnloadFont(font)
 * ```
 * 
 * @note Use this function to identify the position of a specific character in a font.
 */
int lua_GetGlyphIndex(lua_State *L);

/**
 * @brief Gets information about a glyph in the font.
 * 
 * This function returns detailed information about a specific glyph in a font.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Font font`: The font to get the glyph from.
 *  - `int codepoint`: The Unicode codepoint of the glyph.
 * 
 * @return int Always returns 1 (GlyphInfo result) — Information about the glyph, including offset, dimensions, and advance width.
 * 
 * @usage
 * ```lua
 * local font = raylib.LoadFont("resources/arial.ttf")
 * local glyphInfo = raylib.GetGlyphInfo(font, 65) -- Get glyph info for 'A'
 * print("The glyph info for 'A' is: ", glyphInfo)
 * raylib.UnloadFont(font)
 * ```
 * 
 * @note Use this function to access detailed information about a character, such as its size and positioning.
 */
int lua_GetGlyphInfo(lua_State *L);

/**
 * @brief Gets the atlas rectangle of a glyph in the font.
 * 
 * This function returns the rectangle on the font's texture atlas where the glyph is stored.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Font font`: The font to get the atlas rectangle from.
 *  - `int codepoint`: The Unicode codepoint of the glyph.
 * 
 * @return int Always returns 1 (Rectangle result) — The position and size of the glyph on the font's texture atlas.
 * 
 * @usage
 * ```lua
 * local font = raylib.LoadFont("resources/arial.ttf")
 * local atlasRec = raylib.GetGlyphAtlasRec(font, 65) -- Get atlas rectangle for 'A'
 * print("The atlas rectangle for 'A' is: ", atlasRec)
 * raylib.UnloadFont(font)
 * ```
 * 
 * @note This function is useful for custom text rendering or debugging font textures.
 */
int lua_GetGlyphAtlasRec(lua_State *L);

/**
 * @brief Loads a UTF-8 string.
 * 
 * This function takes a sequence of codepoints and converts it into a UTF-8 encoded string.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `const int *codepoints`: An array of Unicode codepoints.
 * 
 * @return int Always returns 1 (string result) — The UTF-8 encoded string corresponding to the codepoints.
 * 
 * @usage
 * ```lua
 * local codepoints = {65, 66, 67} -- Represents 'A', 'B', 'C'
 * local utf8String = raylib.LoadUTF8(codepoints)
 * print("The UTF-8 string is: ", utf8String) -- Outputs: "ABC"
 * ```
 * 
 * @note Use this function to create a UTF-8 encoded string from an array of Unicode codepoints.
 */
int lua_LoadUTF8(lua_State *L);

/**
 * @brief Unloads a UTF-8 string from memory.
 * 
 * This function frees memory allocated for a UTF-8 string.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `char *utf8`: The UTF-8 string to be unloaded.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local utf8String = raylib.LoadUTF8({65, 66, 67}) -- "ABC"
 * raylib.UnloadUTF8(utf8String) -- Frees the memory allocated for the string
 * ```
 * 
 * @note Use this function to free memory for a UTF-8 string created with `raylib.LoadUTF8`.
 */
int lua_UnloadUTF8(lua_State *L);

/**
 * @brief Loads codepoints from a UTF-8 string.
 * 
 * This function takes a UTF-8 encoded string and extracts the Unicode codepoints.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `const char *utf8`: A UTF-8 encoded string.
 * 
 * @return int Always returns 1 (codepoints result) — An array of codepoints corresponding to the characters in the UTF-8 string.
 * 
 * @usage
 * ```lua
 * local utf8String = "ABC"
 * local codepoints = raylib.LoadCodepoints(utf8String)
 * print("The codepoints are: ", table.concat(codepoints, ", ")) -- Outputs: "65, 66, 67"
 * ```
 * 
 * @note Use this function to convert a UTF-8 encoded string into a list of Unicode codepoints.
 */
int lua_LoadCodepoints(lua_State *L);

/**
 * @brief Unloads codepoints from memory.
 * 
 * This function frees memory allocated for an array of Unicode codepoints.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `int *codepoints`: An array of codepoints to be unloaded.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local utf8String = "ABC"
 * local codepoints = raylib.LoadCodepoints(utf8String)
 * raylib.UnloadCodepoints(codepoints) -- Frees the memory allocated for the codepoints
 * ```
 * 
 * @note Use this function to free memory for an array of Unicode codepoints created with `raylib.LoadCodepoints`.
 */
int lua_UnloadCodepoints(lua_State *L);

/**
 * @brief Gets the count of codepoints in a UTF-8 string.
 * 
 * This function returns the number of Unicode codepoints in a UTF-8 encoded string.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `const char *utf8`: A UTF-8 encoded string.
 * 
 * @return int Always returns 1 (integer result) — The total number of codepoints in the UTF-8 string.
 * 
 * @usage
 * ```lua
 * local utf8String = "ABC"
 * local count = raylib.GetCodepointCount(utf8String)
 * print("Number of codepoints: ", count) -- Outputs: 3
 * ```
 * 
 * @note This function counts the Unicode codepoints, not bytes. Multi-byte characters are counted as one codepoint.
 */
int lua_GetCodepointCount(lua_State *L);

/**
 * @brief Gets a codepoint from a UTF-8 string.
 * 
 * This function extracts a specific Unicode codepoint from a UTF-8 encoded string.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `const char *utf8`: A UTF-8 encoded string.
 *  - `int index`: The position (index) of the codepoint to extract (starting from 1).
 * 
 * @return int Always returns 1 (integer result) — The Unicode codepoint at the specified index.
 * 
 * @usage
 * ```lua
 * local utf8String = "ABC"
 * local codepoint = raylib.GetCodepoint(utf8String, 2)
 * print("Codepoint at index 2: ", codepoint) -- Outputs: 66 (for 'B')
 * ```
 * 
 * @note This function extracts a single Unicode codepoint, not a byte. For multi-byte characters, it returns the codepoint, not the UTF-8 byte sequence.
 */
int lua_GetCodepoint(lua_State *L);

/**
 * @brief Gets the next codepoint in a UTF-8 string.
 * 
 * This function returns the next Unicode codepoint in a UTF-8 string, given the current position.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `const char *utf8`: A UTF-8 encoded string.
 *  - `int position`: The current position (byte index) in the string (starting from 1).
 * 
 * @return int Always returns 1 (integer result) — The Unicode codepoint at the next position.
 * 
 * @usage
 * ```lua
 * local utf8String = "ABC"
 * local nextCodepoint = raylib.GetCodepointNext(utf8String, 1)
 * print("Next codepoint after index 1: ", nextCodepoint) -- Outputs: 66 (for 'B')
 * ```
 * 
 * @note This function moves forward by one codepoint in a UTF-8 string. Multi-byte characters are counted as one codepoint.
 */
int lua_GetCodepointNext(lua_State *L);

/**
 * @brief Gets the previous codepoint in a UTF-8 string.
 * 
 * This function returns the previous Unicode codepoint in a UTF-8 string, given the current position.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `const char *utf8`: A UTF-8 encoded string.
 *  - `int position`: The current position (byte index) in the string (starting from 1).
 * 
 * @return int Always returns 1 (integer result) — The Unicode codepoint at the previous position.
 * 
 * @usage
 * ```lua
 * local utf8String = "ABC"
 * local prevCodepoint = raylib.GetCodepointPrevious(utf8String, 3)
 * print("Previous codepoint before index 3: ", prevCodepoint) -- Outputs: 66 (for 'B')
 * ```
 * 
 * @note This function moves backward by one codepoint in a UTF-8 string. Multi-byte characters are counted as one codepoint.
 */
int lua_GetCodepointPrevious(lua_State *L);

/**
 * @brief Converts a codepoint to a UTF-8 string.
 * 
 * Converts a Unicode codepoint into a UTF-8 encoded string.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `int codepoint`: The Unicode codepoint to convert.
 * 
 * @return int Always returns 1 (string result) — The UTF-8 encoded string representing the codepoint.
 * 
 * @usage
 * ```lua
 * local utf8Char = raylib.CodepointToUTF8(65) -- Codepoint for 'A'
 * print(utf8Char) -- Outputs: A
 * ```
 * 
 * @note This function can handle any valid Unicode codepoint, including multi-byte characters.
 */
int lua_CodepointToUTF8(lua_State *L);

/**
 * @brief Copies text from one string to another.
 * 
 * Copies a text string to another text buffer.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `const char *destination`: The destination string where the text will be copied.
 *  - `const char *source`: The source string to copy from.
 * 
 * @return int Always returns 1 (boolean result) — `true` if the copy was successful, `false` otherwise.
 * 
 * @usage
 * ```lua
 * local success = raylib.TextCopy("destination", "source")
 * print(success) -- Outputs: true
 * ```
 * 
 * @note This function is generally used for text manipulation and does not modify Lua strings directly.
 */
int lua_TextCopy(lua_State *L);

/**
 * @brief Checks if two strings are equal.
 * 
 * Compares two text strings and returns `true` if they are equal.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `const char *text1`: The first string to compare.
 *  - `const char *text2`: The second string to compare.
 * 
 * @return int Always returns 1 (boolean result) — `true` if the strings are equal, `false` otherwise.
 * 
 * @usage
 * ```lua
 * local isEqual = raylib.TextIsEqual("Hello", "Hello")
 * print(isEqual) -- Outputs: true
 * ```
 * 
 * @note This comparison is case-sensitive.
 */
int lua_TextIsEqual(lua_State *L);

/**
 * @brief Gets the length of a text string.
 * 
 * Calculates the length of a text string, counting the number of characters.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `const char *text`: The string to calculate the length of.
 * 
 * @return int Always returns 1 (integer result) — The length of the string.
 * 
 * @usage
 * ```lua
 * local length = raylib.TextLength("Hello")
 * print("Length: ", length) -- Outputs: 5
 * ```
 * 
 * @note This function counts characters, not bytes, so multi-byte UTF-8 characters are counted as one character.
 */
int lua_TextLength(lua_State *L);

/**
 * @brief Formats a text string.
 * 
 * Formats a text string with specified arguments, similar to `printf`-style formatting.
 * 
 * @param L A pointer to the current Lua state. Expects 1 or more arguments:
 *  - `const char *format`: The format string.
 *  - Additional arguments matching the format specifiers in the format string.
 * 
 * @return int Always returns 1 (string result) — The formatted text string.
 * 
 * @usage
 * ```lua
 * local formattedText = raylib.TextFormat("Score: %d", 100)
 * print(formattedText) -- Outputs: Score: 100
 * ```
 * 
 * @note Supported format specifiers include `%d`, `%f`, `%s`, and others typically supported by C's `printf`.
 */
int lua_TextFormat(lua_State *L);

/**
 * @brief Gets a subtext from a text string.
 * 
 * Extracts a substring from a given text string, starting from a specific position and ending at another.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `const char *text`: The original text string.
 *  - `int position`: The starting position (zero-indexed).
 *  - `int length`: The length of the substring to extract.
 * 
 * @return int Always returns 1 (string result) — The extracted substring.
 * 
 * @usage
 * ```lua
 * local subtext = raylib.TextSubtext("Hello, World!", 7, 5)
 * print(subtext) -- Outputs: World
 * ```
 * 
 * @note If the position or length goes out of bounds, the function adjusts to fit the available text.
 */
int lua_TextSubtext(lua_State *L);

/**
 * @brief Replaces text in a string.
 * 
 * Replaces all occurrences of a substring within a text string with another substring.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `const char *text`: The original text string.
 *  - `const char *replace`: The substring to search for.
 *  - `const char *by`: The substring to replace with.
 * 
 * @return int Always returns 1 (string result) — The resulting text with replacements applied.
 * 
 * @usage
 * ```lua
 * local replacedText = raylib.TextReplace("Hello, World!", "World", "Lua")
 * print(replacedText) -- Outputs: Hello, Lua!
 * ```
 * 
 * @note The function replaces **all** occurrences of the `replace` string with the `by` string.
 */
int lua_TextReplace(lua_State *L);

/**
 * @brief Inserts text into a string.
 * 
 * Inserts a string into another string at a specified position.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `const char *text`: The original text string.
 *  - `const char *insert`: The string to be inserted.
 *  - `int position`: The position (zero-indexed) at which to insert the new string.
 * 
 * @return int Always returns 1 (string result) — The resulting string after insertion.
 * 
 * @usage
 * ```lua
 * local result = raylib.TextInsert("Hello, Lua!", " World", 6)
 * print(result) -- Outputs: Hello, World Lua!
 * ```
 * 
 * @note If the position is out of bounds, the function appends the text at the end.
 */
int lua_TextInsert(lua_State *L);

/**
 * @brief Joins text strings.
 * 
 * Joins an array of strings into a single string using a specified delimiter.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `table textParts`: A table containing an array of strings to join.
 *  - `const char *delimiter`: The delimiter string to insert between the parts.
 * 
 * @return int Always returns 1 (string result) — The concatenated string.
 * 
 * @usage
 * ```lua
 * local joinedText = raylib.TextJoin({"Hello", "World", "Lua"}, " ")
 * print(joinedText) -- Outputs: Hello World Lua
 * ```
 * 
 * @note If the delimiter is an empty string, the parts are concatenated without separation.
 */
int lua_TextJoin(lua_State *L);

/**
 * @brief Splits a text string.
 * 
 * Splits a text string into an array of substrings using a specified delimiter.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `const char *text`: The original text string to split.
 *  - `const char *delimiter`: The delimiter to use for splitting.
 * 
 * @return int Always returns 1 (table result) — A Lua table containing the resulting substrings.
 * 
 * @usage
 * ```lua
 * local parts = raylib.TextSplit("Hello,World,Lua", ",")
 * for i, part in ipairs(parts) do
 *     print(part)
 * end
 * -- Outputs:
 * -- Hello
 * -- World
 * -- Lua
 * ```
 * 
 * @note If the delimiter is not found, the entire string is returned as the only element in the table.
 */
int lua_TextSplit(lua_State *L);

/**
 * @brief Appends text to a string.
 * 
 * Appends a string to another string.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `char *text`: The original text string (modifiable).
 *  - `const char *append`: The text string to append.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local text = "Hello"
 * raylib.TextAppend(text, ", World!")
 * print(text) -- Outputs: Hello, World!
 * ```
 * 
 * @note The original text must be modifiable. This function works on mutable C strings.
 */
int lua_TextAppend(lua_State *L);

/**
 * @brief Finds the index of a substring in a text string.
 * 
 * Finds the index of the first occurrence of a substring within a text string.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `const char *text`: The original text string.
 *  - `const char *substring`: The substring to search for.
 * 
 * @return int Always returns 1 (integer result) — The index of the substring (zero-indexed), or -1 if not found.
 * 
 * @usage
 * ```lua
 * local index = raylib.TextFindIndex("Hello, World!", "World")
 * print(index) -- Outputs: 7
 * ```
 * 
 * @note This function returns -1 if the substring is not found in the text.
 */
int lua_TextFindIndex(lua_State *L);

/**
 * @brief Converts a text string to uppercase.
 * 
 * Converts all lowercase letters in the input string to uppercase.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `const char *text`: The original text string to convert.
 * 
 * @return int Always returns 1 (string result) — The converted string in uppercase.
 * 
 * @usage
 * ```lua
 * local upperText = raylib.TextToUpper("hello world")
 * print(upperText) -- Outputs: HELLO WORLD
 * ```
 * 
 * @note Non-alphabetic characters are not affected.
 */
int lua_TextToUpper(lua_State *L);

/**
 * @brief Converts a text string to lowercase.
 * 
 * Converts all uppercase letters in the input string to lowercase.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `const char *text`: The original text string to convert.
 * 
 * @return int Always returns 1 (string result) — The converted string in lowercase.
 * 
 * @usage
 * ```lua
 * local lowerText = raylib.TextToLower("HELLO WORLD")
 * print(lowerText) -- Outputs: hello world
 * ```
 * 
 * @note Non-alphabetic characters are not affected.
 */
int lua_TextToLower(lua_State *L);

/**
 * @brief Converts a text string to Pascal case.
 * 
 * Converts a text string to Pascal case where the first letter of each word is capitalized.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `const char *text`: The original text string to convert.
 * 
 * @return int Always returns 1 (string result) — The converted string in Pascal case.
 * 
 * @usage
 * ```lua
 * local pascalText = raylib.TextToPascal("hello world lua")
 * print(pascalText) -- Outputs: HelloWorldLua
 * ```
 * 
 * @note Spaces, dashes, and underscores are removed, and the first letter of each word is capitalized.
 */
int lua_TextToPascal(lua_State *L);

/**
 * @brief Converts a text string to snake case.
 * 
 * Converts a text string to snake case where words are separated by underscores and lowercase letters are used.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `const char *text`: The original text string to convert.
 * 
 * @return int Always returns 1 (string result) — The converted string in snake case.
 * 
 * @usage
 * ```lua
 * local snakeText = raylib.TextToSnake("Hello World Lua")
 * print(snakeText) -- Outputs: hello_world_lua
 * ```
 * 
 * @note Spaces, dashes, and special characters are replaced with underscores. Uppercase letters are converted to lowercase.
 */
int lua_TextToSnake(lua_State *L);

/**
 * @brief Converts a text string to camel case.
 * 
 * Converts a text string to camel case where the first letter of the first word is lowercase and 
 * the first letter of subsequent words is capitalized, with no spaces or special characters.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `const char *text`: The original text string to convert.
 * 
 * @return int Always returns 1 (string result) — The converted string in camel case.
 * 
 * @usage
 * ```lua
 * local camelText = raylib.TextToCamel("hello world lua")
 * print(camelText) -- Outputs: helloWorldLua
 * ```
 * 
 * @note Spaces, dashes, and underscores are removed, and the first letter of each subsequent word is capitalized.
 */
int lua_TextToCamel(lua_State *L);

/**
 * @brief Converts a text string to an integer.
 * 
 * Converts a text string to an integer value. If the text cannot be converted to an integer, 
 * the result is undefined or may return 0.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `const char *text`: The original text string to convert to an integer.
 * 
 * @return int Always returns 1 (integer result) — The integer value of the text.
 * 
 * @usage
 * ```lua
 * local number = raylib.TextToInteger("1234")
 * print(number) -- Outputs: 1234
 * 
 * local invalidNumber = raylib.TextToInteger("abc")
 * print(invalidNumber) -- Outputs: 0 (or undefined behavior)
 * ```
 * 
 * @note Non-numeric characters in the text may cause undefined behavior or result in 0.
 */
int lua_TextToInteger(lua_State *L);

/**
 * @brief Converts a text string to a float.
 * 
 * Converts a text string to a floating-point number. If the text cannot be converted to a float, 
 * the result is undefined or may return 0.0.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `const char *text`: The original text string to convert to a float.
 * 
 * @return int Always returns 1 (float result) — The float value of the text.
 * 
 * @usage
 * ```lua
 * local number = raylib.TextToFloat("12.34")
 * print(number) -- Outputs: 12.34
 * 
 * local invalidNumber = raylib.TextToFloat("abc")
 * print(invalidNumber) -- Outputs: 0.0 (or undefined behavior)
 * ```
 * 
 * @note Non-numeric characters in the text may cause undefined behavior or result in 0.0.
 */
int lua_TextToFloat(lua_State *L);

#endif
