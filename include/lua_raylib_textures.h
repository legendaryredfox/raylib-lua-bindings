#ifndef LUA_RAYLIB_TEXTURES_H
#define LUA_RAYLIB_TEXTURES_H

#include "lua_raylib.h"

/**
 * @brief Loads an image from a file.
 * 
 * Loads an image from the specified file path and returns it as an Image object.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `const char *filePath`: The path to the image file.
 * 
 * @return int Always returns 1 (Image result) — The loaded Image object.
 * 
 * @usage
 * ```lua
 * local image = raylib.LoadImage("resources/image.png")
 * print(image) -- Outputs: Image object
 * ```
 * 
 * @note Supported image formats include PNG, BMP, TGA, JPG, and more.
 */
int lua_LoadImage(lua_State *L);

/**
 * @brief Unloads an image from memory.
 * 
 * Frees the memory allocated for an Image object.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Image image`: The Image object to unload.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local image = raylib.LoadImage("resources/image.png")
 * raylib.UnloadImage(image)
 * ```
 * 
 * @note This function should be called to avoid memory leaks after the image is no longer needed.
 */
int lua_UnloadImage(lua_State *L);

/**
 * @brief Loads a texture from a file.
 * 
 * Loads an image from the specified file and converts it into a GPU texture.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `const char *filePath`: The path to the image file to load as a texture.
 * 
 * @return int Always returns 1 (Texture2D result) — The loaded Texture2D object.
 * 
 * @usage
 * ```lua
 * local texture = raylib.LoadTexture("resources/texture.png")
 * print(texture) -- Outputs: Texture2D object
 * ```
 * 
 * @note The texture is uploaded to the GPU, and the image data in RAM is no longer needed.
 */
int lua_LoadTexture(lua_State *L);

/**
 * @brief Loads a texture from an existing image.
 * 
 * Converts an existing Image object into a GPU texture.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Image image`: The Image object to convert into a Texture2D.
 * 
 * @return int Always returns 1 (Texture2D result) — The loaded Texture2D object.
 * 
 * @usage
 * ```lua
 * local image = raylib.LoadImage("resources/image.png")
 * local texture = raylib.LoadTextureFromImage(image)
 * print(texture) -- Outputs: Texture2D object
 * ```
 * 
 * @note The texture is uploaded to the GPU, and the image can be unloaded from memory.
 */
int lua_LoadTextureFromImage(lua_State *L);

/**
 * @brief Unloads a texture from GPU memory.
 * 
 * Frees the GPU memory allocated for a Texture2D object.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Texture2D texture`: The Texture2D object to unload.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local texture = raylib.LoadTexture("resources/texture.png")
 * raylib.UnloadTexture(texture)
 * ```
 * 
 * @note This function should be called to avoid memory leaks after the texture is no longer needed.
 */
int lua_UnloadTexture(lua_State *L);

/**
 * @brief Updates the contents of a texture with new data.
 * 
 * Updates the pixel data of an existing Texture2D object with the provided data.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Texture2D texture`: The Texture2D object to update.
 *  - `void *data`: The new pixel data to update the texture.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local texture = raylib.LoadTexture("resources/texture.png")
 * raylib.UpdateTexture(texture, pixelData) -- `pixelData` should be in the correct format.
 * ```
 * 
 * @note The format of `data` should match the pixel format of the texture.
 */
int lua_UpdateTexture(lua_State *L);

/**
 * @brief Generates mipmaps for a texture.
 * 
 * Generates mipmaps for a Texture2D object to improve rendering performance.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Texture2D texture`: The Texture2D object to generate mipmaps for.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local texture = raylib.LoadTexture("resources/texture.png")
 * raylib.GenTextureMipmaps(texture)
 * ```
 * 
 * @note Mipmaps are lower-resolution versions of a texture, automatically used for distant objects.
 */
int lua_GenTextureMipmaps(lua_State *L);

/**
 * @brief Resizes an image to the specified dimensions.
 * 
 * Resizes an Image object to the specified width and height.
 * 
 * @param L A pointer to the current Lua state. Expects 3 arguments:
 *  - `Image image`: The Image object to resize.
 *  - `int newWidth`: The new width of the image.
 *  - `int newHeight`: The new height of the image.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local image = raylib.LoadImage("resources/image.png")
 * raylib.ImageResize(image, 128, 128) -- Resizes the image to 128x128
 * ```
 * 
 * @note This function modifies the image in place, and the original size is lost.
 */
int lua_ImageResize(lua_State *L);
/**
 * @brief Flips an image horizontally.
 * 
 * Flips an Image object horizontally, reversing its contents from left to right.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Image image`: The Image object to flip.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local image = raylib.LoadImage("resources/image.png")
 * raylib.ImageFlipHorizontal(image)
 * ```
 * 
 * @note This operation modifies the image in place.
 */
int lua_ImageFlipHorizontal(lua_State *L);

/**
 * @brief Flips an image vertically.
 * 
 * Flips an Image object vertically, reversing its contents from top to bottom.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Image image`: The Image object to flip.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local image = raylib.LoadImage("resources/image.png")
 * raylib.ImageFlipVertical(image)
 * ```
 * 
 * @note This operation modifies the image in place.
 */
int lua_ImageFlipVertical(lua_State *L);

/**
 * @brief Creates a copy of an image.
 * 
 * Creates a duplicate copy of an Image object.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Image image`: The Image object to copy.
 * 
 * @return int Always returns 1 (Image result).
 * 
 * @usage
 * ```lua
 * local image = raylib.LoadImage("resources/image.png")
 * local copy = raylib.ImageCopy(image)
 * ```
 * 
 * @note The returned image is a separate copy, and changes made to it will not affect the original image.
 */
int lua_ImageCopy(lua_State *L);

/**
 * @brief Crops an image to the specified rectangle.
 * 
 * Crops an Image object to a specified rectangle, modifying the image in place.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Image image`: The Image object to crop.
 *  - `Rectangle cropRect`: The Rectangle defining the area to crop.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local image = raylib.LoadImage("resources/image.png")
 * raylib.ImageCrop(image, { x = 0, y = 0, width = 100, height = 100 }) -- Crops a 100x100 area from top-left
 * ```
 * 
 * @note The image is modified in place, and the original size is lost.
 */
int lua_ImageCrop(lua_State *L);
/**
 * @brief Tints an image with a specified color.
 * 
 * Applies a color tint to an Image object, modifying its pixels based on the provided color.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Image image`: The Image object to tint.
 *  - `Color color`: The color to use for tinting.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local image = raylib.LoadImage("resources/image.png")
 * raylib.ImageColorTint(image, { r = 255, g = 0, b = 0, a = 255 }) -- Apply a red tint
 * ```
 * 
 * @note The image is modified in place. The color tint is applied using a blending operation.
 */
int lua_ImageColorTint(lua_State *L);

/**
 * @brief Inverts the colors of an image.
 * 
 * Inverts the colors of an Image object, swapping the RGB values of each pixel to their opposites.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Image image`: The Image object to invert.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local image = raylib.LoadImage("resources/image.png")
 * raylib.ImageColorInvert(image) -- Invert the image colors
 * ```
 * 
 * @note This operation modifies the image in place.
 */
int lua_ImageColorInvert(lua_State *L);

/**
 * @brief Converts an image to grayscale.
 * 
 * Converts an Image object to grayscale by applying a grayscale filter to each pixel.
 * 
 * @param L A pointer to the current Lua state. Expects 1 argument:
 *  - `Image image`: The Image object to convert to grayscale.
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local image = raylib.LoadImage("resources/image.png")
 * raylib.ImageColorGrayscale(image) -- Convert the image to grayscale
 * ```
 * 
 * @note This operation modifies the image in place.
 */
int lua_ImageColorGrayscale(lua_State *L);

/**
 * @brief Adjusts the brightness of an image.
 * 
 * Adjusts the brightness of an Image object by increasing or decreasing the brightness of its pixels.
 * 
 * @param L A pointer to the current Lua state. Expects 2 arguments:
 *  - `Image image`: The Image object to adjust.
 *  - `float brightness`: The brightness adjustment value (positive to increase, negative to decrease).
 * 
 * @return int Always returns 0.
 * 
 * @usage
 * ```lua
 * local image = raylib.LoadImage("resources/image.png")
 * raylib.ImageColorBrightness(image, 50) -- Increase brightness
 * raylib.ImageColorBrightness(image, -50) -- Decrease brightness
 * ```
 * 
 * @note This operation modifies the image in place. The brightness value is clamped to avoid overflow.
 */
int lua_ImageColorBrightness(lua_State *L);
/**
 * @brief Adjusts the contrast of an image.
 * 
 * This function modifies the contrast of an image by adjusting the intensity of its pixels.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("example.png")
 * raylib.ImageColorContrast(image, 1.5) -- Increase contrast
 * ```
 */
int lua_ImageColorContrast(lua_State *L);

/**
 * @brief Replaces a color in an image with another color.
 * 
 * Replaces all occurrences of a specified color in an image with another color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("example.png")
 * raylib.ImageColorReplace(image, {r=255, g=0, b=0, a=255}, {r=0, g=255, b=0, a=255}) -- Replace red with green
 * ```
 */
int lua_ImageColorReplace(lua_State *L);

/**
 * @brief Loads a cubemap texture from an image.
 * 
 * This function loads a cubemap texture from a given image and layout.
 * 
 * @param L Lua state
 * @return int Always returns 1 (TextureCubemap result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("cubemap.png")
 * local cubemap = raylib.LoadTextureCubemap(image, raylib.CUBEMAP_LAYOUT_AUTO_DETECT)
 * ```
 */
int lua_LoadTextureCubemap(lua_State *L);

/**
 * @brief Updates a specific region of a texture with new data.
 * 
 * This function updates a portion of the texture with new pixel data.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local texture = raylib.LoadTexture("example.png")
 * local data = { pixel data }
 * raylib.UpdateTextureRec(texture, {x=0, y=0, width=64, height=64}, data)
 * ```
 */
int lua_UpdateTextureRec(lua_State *L);
/**
 * @brief Loads an image from raw pixel data.
 * 
 * This function loads an image from raw pixel data, with specified width, height, and format.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local rawData = raylib.LoadFileData("image.raw")
 * local image = raylib.LoadImageRaw(rawData, 128, 128, raylib.PIXELFORMAT_UNCOMPRESSED_R8G8B8, 0)
 * ```
 */
int lua_LoadImageRaw(lua_State *L);

/**
 * @brief Loads an animated image (GIF) from a file.
 * 
 * This function loads an animated image from a file, supporting multiple frames.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImageAnim("example.gif")
 * local frameCount = raylib.GetImageFrameCount(image)
 * print("Total frames:", frameCount)
 * ```
 */
int lua_LoadImageAnim(lua_State *L);

/**
 * @brief Loads an animated image (GIF) from memory.
 * 
 * This function loads an animated image from a memory buffer, supporting multiple frames.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local data = raylib.LoadFileData("example.gif")
 * local image = raylib.LoadImageAnimFromMemory(".gif", data)
 * local frameCount = raylib.GetImageFrameCount(image)
 * print("Total frames:", frameCount)
 * ```
 */
int lua_LoadImageAnimFromMemory(lua_State *L);

/**
 * @brief Loads an image from memory data.
 * 
 * This function loads an image from a memory buffer, supporting common image formats like PNG and JPEG.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local data = raylib.LoadFileData("example.png")
 * local image = raylib.LoadImageFromMemory(".png", data)
 * ```
 */
int lua_LoadImageFromMemory(lua_State *L);
/**
 * @brief Loads an image from a texture.
 * 
 * This function extracts image data from an existing texture, allowing manipulation of texture content as an image.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local texture = raylib.LoadTexture("example.png")
 * local image = raylib.LoadImageFromTexture(texture)
 * raylib.ExportImage(image, "exported_image.png")
 * ```
 */
int lua_LoadImageFromTexture(lua_State *L);

/**
 * @brief Loads an image from the current screen content.
 * 
 * This function captures the current screen content and converts it into an image.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * raylib.BeginDrawing()
 * raylib.ClearBackground(raylib.RAYWHITE)
 * raylib.DrawText("Hello, world!", 190, 200, 20, raylib.MAROON)
 * raylib.EndDrawing()
 * 
 * local image = raylib.LoadImageFromScreen()
 * raylib.ExportImage(image, "screenshot.png")
 * ```
 */
int lua_LoadImageFromScreen(lua_State *L);

/**
 * @brief Checks if an image is valid.
 * 
 * This function verifies if an image is valid and properly loaded.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("example.png")
 * local isValid = raylib.IsImageValid(image)
 * print("Is image valid?", isValid)
 * ```
 */
int lua_IsImageValid(lua_State *L);

/**
 * @brief Exports an image to a file.
 * 
 * This function saves an image to a file with a specified file name and format.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("example.png")
 * raylib.ExportImage(image, "exported_image.png")
 * ```
 */
int lua_ExportImage(lua_State *L);
/**
 * @brief Exports an image to memory.
 * 
 * This function encodes an image into memory instead of saving it to a file. The output format depends on the provided format argument.
 * 
 * @param L Lua state
 * @return int Always returns 1 (binary data result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("example.png")
 * local imageData = raylib.ExportImageToMemory(image, ".png")
 * -- Save or use imageData as needed
 * ```
 */
int lua_ExportImageToMemory(lua_State *L);

/**
 * @brief Exports an image as source code.
 * 
 * This function generates C code that represents the image as an array of pixel data, which can be used directly in C/C++ applications.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("example.png")
 * raylib.ExportImageAsCode(image, "image_code.h")
 * -- The file "image_code.h" now contains C code with the image data
 * ```
 */
int lua_ExportImageAsCode(lua_State *L);

/**
 * @brief Generates an image filled with a specific color.
 * 
 * This function creates a plain color image with the specified width, height, and color.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.GenImageColor(256, 256, raylib.RED)
 * raylib.ExportImage(image, "red_image.png")
 * ```
 */
int lua_GenImageColor(lua_State *L);

/**
 * @brief Generates a linear gradient image.
 * 
 * This function creates an image with a linear gradient, transitioning from one color to another across a specified direction.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.GenImageGradientLinear(256, 256, raylib.BLUE, raylib.GREEN)
 * raylib.ExportImage(image, "gradient_image.png")
 * ```
 */
int lua_GenImageGradientLinear(lua_State *L);
/**
 * @brief Generates a radial gradient image.
 * 
 * This function creates an image with a radial gradient, transitioning from one color at the center to another color at the edges.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.GenImageGradientRadial(256, 256, 0.5, raylib.RED, raylib.BLUE)
 * raylib.ExportImage(image, "radial_gradient.png")
 * ```
 */
int lua_GenImageGradientRadial(lua_State *L);

/**
 * @brief Generates a square gradient image.
 * 
 * This function creates an image with a square-shaped gradient, transitioning from one color at the center to another at the edges.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.GenImageGradientSquare(256, 256, 0.5, raylib.RED, raylib.GREEN)
 * raylib.ExportImage(image, "square_gradient.png")
 * ```
 */
int lua_GenImageGradientSquare(lua_State *L);

/**
 * @brief Generates an image with a checkered pattern.
 * 
 * This function creates an image with a checkered pattern of alternating colors.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.GenImageChecked(256, 256, 32, 32, raylib.RED, raylib.BLUE)
 * raylib.ExportImage(image, "checkered_pattern.png")
 * ```
 */
int lua_GenImageChecked(lua_State *L);

/**
 * @brief Generates an image with white noise.
 * 
 * This function creates an image with randomly generated noise pixels.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.GenImageWhiteNoise(256, 256, 0.5)
 * raylib.ExportImage(image, "white_noise.png")
 * ```
 */
int lua_GenImageWhiteNoise(lua_State *L);
/**
 * @brief Generates an image with Perlin noise.
 * 
 * This function creates an image filled with Perlin noise, often used for procedural textures.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.GenImagePerlinNoise(256, 256, 0, 0, 8.0)
 * raylib.ExportImage(image, "perlin_noise.png")
 * ```
 */
int lua_GenImagePerlinNoise(lua_State *L);

/**
 * @brief Generates an image with a cellular pattern.
 * 
 * This function creates an image with a cellular (Voronoi-like) pattern, useful for procedural texture generation.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.GenImageCellular(256, 256, 16)
 * raylib.ExportImage(image, "cellular_pattern.png")
 * ```
 */
int lua_GenImageCellular(lua_State *L);

/**
 * @brief Generates an image with text.
 * 
 * This function creates an image with the specified text drawn on it.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.GenImageText(256, 256, "Hello World!", raylib.RED)
 * raylib.ExportImage(image, "text_image.png")
 * ```
 */
int lua_GenImageText(lua_State *L);

/**
 * @brief Extracts a sub-image from an existing image.
 * 
 * This function extracts a portion of an existing image, defined by a source rectangle, and returns it as a new image.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local sourceImage = raylib.LoadImage("source.png")
 * local subImage = raylib.ImageFromImage(sourceImage, { x = 0, y = 0, width = 128, height = 128 })
 * raylib.ExportImage(subImage, "sub_image.png")
 * ```
 */
int lua_ImageFromImage(lua_State *L);
/**
 * @brief Extracts a specific color channel from an image.
 * 
 * This function extracts a specific color channel (like Red, Green, Blue, or Alpha) from an image 
 * and returns a new image with only that channel's values.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * local redChannelImage = raylib.ImageFromChannel(image, raylib.CHANNEL_RED)
 * raylib.ExportImage(redChannelImage, "red_channel.png")
 * ```
 */
int lua_ImageFromChannel(lua_State *L);

/**
 * @brief Generates an image with a text string.
 * 
 * This function creates an image with the specified text drawn on it using the default font.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.ImageText(256, 256, "Hello World!", raylib.RED)
 * raylib.ExportImage(image, "image_text.png")
 * ```
 */
int lua_ImageText(lua_State *L);

/**
 * @brief Generates an image with extended text options.
 * 
 * This function creates an image with the specified text drawn on it using a specified font, font size, and other customization options.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Image result)
 * 
 * **Usage:**
 * ```lua
 * local font = raylib.LoadFont("myfont.ttf")
 * local image = raylib.ImageTextEx(font, "Hello World!", 20, 2, raylib.RED)
 * raylib.ExportImage(image, "image_text_ex.png")
 * ```
 */
int lua_ImageTextEx(lua_State *L);

/**
 * @brief Converts the format of an image.
 * 
 * This function converts the pixel data format of an image to a specified format.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageFormat(image, raylib.PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)
 * raylib.ExportImage(image, "formatted_image.png")
 * ```
 */
int lua_ImageFormat(lua_State *L);
/**
 * @brief Converts an image to power-of-two dimensions.
 * 
 * This function resizes the image to the nearest larger power-of-two dimensions (width and height) 
 * while maintaining its content.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageToPOT(image, raylib.BLACK)
 * raylib.ExportImage(image, "image_pot.png")
 * ```
 */
int lua_ImageToPOT(lua_State *L);

/**
 * @brief Crops the image by removing transparent pixels around it.
 * 
 * This function removes the transparent pixels from the edges of the image, 
 * reducing its size to only contain visible pixels.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageAlphaCrop(image, 0.5)
 * raylib.ExportImage(image, "cropped_image.png")
 * ```
 */
int lua_ImageAlphaCrop(lua_State *L);

/**
 * @brief Clears alpha values from an image.
 * 
 * This function clears (removes) the alpha values of pixels in an image that 
 * match the specified color. 
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageAlphaClear(image, raylib.RAYWHITE, 0.5)
 * raylib.ExportImage(image, "alpha_cleared_image.png")
 * ```
 */
int lua_ImageAlphaClear(lua_State *L);

/**
 * @brief Applies an alpha mask to an image.
 * 
 * This function applies the alpha values of another image (mask) to the current image, 
 * using the grayscale values of the mask to set the alpha transparency.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * local mask = raylib.LoadImage("mask.png")
 * raylib.ImageAlphaMask(image, mask)
 * raylib.ExportImage(image, "masked_image.png")
 * ```
 */
int lua_ImageAlphaMask(lua_State *L);
/**
 * @brief Premultiplies the alpha channel of an image.
 * 
 * This function multiplies the RGB color components of the image by its alpha component, 
 * making it suitable for blending operations.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageAlphaPremultiply(image)
 * raylib.ExportImage(image, "premultiplied_alpha_image.png")
 * ```
 */
int lua_ImageAlphaPremultiply(lua_State *L);

/**
 * @brief Applies a Gaussian blur to an image.
 * 
 * This function smooths the image using a Gaussian blur filter, useful for creating 
 * soft effects or reducing image noise.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageBlurGaussian(image, 5) -- Applies a Gaussian blur with radius 5
 * raylib.ExportImage(image, "blurred_image.png")
 * ```
 */
int lua_ImageBlurGaussian(lua_State *L);

/**
 * @brief Applies a kernel convolution to an image.
 * 
 * This function processes the image with a custom kernel (filter), allowing for effects 
 * like edge detection, sharpening, and blurring.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * local kernel = {0, -1, 0, -1, 5, -1, 0, -1, 0} -- Sharpen kernel
 * raylib.ImageKernelConvolution(image, kernel, 3, 3)
 * raylib.ExportImage(image, "sharpened_image.png")
 * ```
 */
int lua_ImageKernelConvolution(lua_State *L);

/**
 * @brief Resizes an image using nearest-neighbor scaling.
 * 
 * This function resizes the image to the specified width and height using 
 * nearest-neighbor interpolation, which is fast but may produce jagged edges.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageResizeNN(image, 128, 128) -- Resizes the image to 128x128 pixels
 * raylib.ExportImage(image, "resized_image.png")
 * ```
 */
int lua_ImageResizeNN(lua_State *L);
/**
 * @brief Resizes the image canvas while maintaining the image's position.
 * 
 * This function resizes the image canvas to the specified width and height. 
 * The image is centered in the new canvas, and the remaining space is filled with a background color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageResizeCanvas(image, 256, 256, 10, 10, raylib.BLACK) -- Adds a 10-pixel border on all sides
 * raylib.ExportImage(image, "resized_canvas_image.png")
 * ```
 */
int lua_ImageResizeCanvas(lua_State *L);

/**
 * @brief Generates mipmaps for the image.
 * 
 * This function generates a series of smaller versions (mipmaps) of the image, 
 * which are used to improve rendering performance at different distances.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageMipmaps(image) -- Generates mipmaps for the image
 * raylib.ExportImage(image, "image_with_mipmaps.png")
 * ```
 */
int lua_ImageMipmaps(lua_State *L);

/**
 * @brief Applies a dithering effect to the image.
 * 
 * This function reduces the number of colors in the image using dithering, 
 * which is useful for retro-style graphics or when reducing color depth.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDither(image, 256, 256, 4, 4) -- Reduces the color depth of the image
 * raylib.ExportImage(image, "dithered_image.png")
 * ```
 */
int lua_ImageDither(lua_State *L);

/**
 * @brief Rotates the image by a specified angle.
 * 
 * This function rotates the image clockwise by the specified angle (in degrees).
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageRotate(image, 45) -- Rotates the image by 45 degrees clockwise
 * raylib.ExportImage(image, "rotated_image.png")
 * ```
 */
int lua_ImageRotate(lua_State *L);
/**
 * @brief Resizes the image canvas while maintaining the image's position.
 * 
 * This function resizes the image canvas to the specified width and height. 
 * The image is centered in the new canvas, and the remaining space is filled with a background color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageResizeCanvas(image, 256, 256, 10, 10, raylib.BLACK) -- Adds a 10-pixel border on all sides
 * raylib.ExportImage(image, "resized_canvas_image.png")
 * ```
 */
int lua_ImageResizeCanvas(lua_State *L);

/**
 * @brief Generates mipmaps for the image.
 * 
 * This function generates a series of smaller versions (mipmaps) of the image, 
 * which are used to improve rendering performance at different distances.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageMipmaps(image) -- Generates mipmaps for the image
 * raylib.ExportImage(image, "image_with_mipmaps.png")
 * ```
 */
int lua_ImageMipmaps(lua_State *L);

/**
 * @brief Applies a dithering effect to the image.
 * 
 * This function reduces the number of colors in the image using dithering, 
 * which is useful for retro-style graphics or when reducing color depth.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDither(image, 256, 256, 4, 4) -- Reduces the color depth of the image
 * raylib.ExportImage(image, "dithered_image.png")
 * ```
 */
int lua_ImageDither(lua_State *L);

/**
 * @brief Rotates the image by a specified angle.
 * 
 * This function rotates the image clockwise by the specified angle (in degrees).
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageRotate(image, 45) -- Rotates the image by 45 degrees clockwise
 * raylib.ExportImage(image, "rotated_image.png")
 * ```
 */
int lua_ImageRotate(lua_State *L);
/**
 * @brief Rotates the image 90 degrees clockwise.
 * 
 * This function rotates the image 90 degrees clockwise (rightward) in place.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageRotateCW(image) -- Rotates the image 90 degrees clockwise
 * raylib.ExportImage(image, "rotated_cw_image.png")
 * ```
 */
int lua_ImageRotateCW(lua_State *L);

/**
 * @brief Rotates the image 90 degrees counterclockwise.
 * 
 * This function rotates the image 90 degrees counterclockwise (leftward) in place.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageRotateCCW(image) -- Rotates the image 90 degrees counterclockwise
 * raylib.ExportImage(image, "rotated_ccw_image.png")
 * ```
 */
int lua_ImageRotateCCW(lua_State *L);

/**
 * @brief Loads the color data from an image.
 * 
 * This function extracts the color data from the image as an array of Color values.
 * 
 * @param L Lua state
 * @return int Always returns 1 (table of colors)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * local colors = raylib.LoadImageColors(image) -- Extracts the image's color data
 * for i, color in ipairs(colors) do
 *     print(color.r, color.g, color.b, color.a)
 * end
 * ```
 */
int lua_LoadImageColors(lua_State *L);

/**
 * @brief Loads the palette from an image.
 * 
 * This function extracts a palette from the image as an array of Color values with a maximum size.
 * 
 * @param L Lua state
 * @return int Always returns 1 (table of colors)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * local palette, colorsCount = raylib.LoadImagePalette(image, 16) -- Extracts a palette with up to 16 colors
 * for i, color in ipairs(palette) do
 *     print(color.r, color.g, color.b, color.a)
 * end
 * ```
 */
int lua_LoadImagePalette(lua_State *L);
/**
 * @brief Unloads the color data from memory.
 * 
 * This function releases the memory used by the color data extracted from an image.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * local colors = raylib.LoadImageColors(image)
 * raylib.UnloadImageColors(colors) -- Frees the memory used for the color data
 * ```
 */
int lua_UnloadImageColors(lua_State *L);

/**
 * @brief Unloads the image palette from memory.
 * 
 * This function releases the memory used by the palette extracted from an image.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * local palette, count = raylib.LoadImagePalette(image, 16)
 * raylib.UnloadImagePalette(palette) -- Frees the memory used for the image palette
 * ```
 */
int lua_UnloadImagePalette(lua_State *L);

/**
 * @brief Gets the alpha border rectangle of an image.
 * 
 * This function calculates the minimum bounding rectangle that encloses all the non-transparent pixels in the image.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Rectangle result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * local alphaBorder = raylib.GetImageAlphaBorder(image, 0.5) -- Gets a rectangle around non-transparent pixels
 * print("Border:", alphaBorder.x, alphaBorder.y, alphaBorder.width, alphaBorder.height)
 * ```
 */
int lua_GetImageAlphaBorder(lua_State *L);

/**
 * @brief Gets the color of a specific pixel in an image.
 * 
 * This function retrieves the color of the pixel at the specified (x, y) position in the image.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Color result)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * local color = raylib.GetImageColor(image, 10, 20) -- Gets the color of the pixel at (10, 20)
 * print("Color:", color.r, color.g, color.b, color.a)
 * ```
 */
int lua_GetImageColor(lua_State *L);
/**
 * @brief Clears the background of an image with a specified color.
 * 
 * This function fills the entire image with a solid color, effectively resetting its contents.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageClearBackground(image, { r = 255, g = 0, b = 0, a = 255 }) -- Clears the image with red color
 * ```
 */
int lua_ImageClearBackground(lua_State *L);

/**
 * @brief Draws a pixel at the specified position in an image.
 * 
 * This function modifies the pixel color at the specified (x, y) position in the image.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawPixel(image, 10, 20, { r = 0, g = 255, b = 0, a = 255 }) -- Draws a green pixel at position (10, 20)
 * ```
 */
int lua_ImageDrawPixel(lua_State *L);

/**
 * @brief Draws a pixel at the specified position (Vector2) in an image.
 * 
 * This function modifies the pixel color at the position given by a Vector2 in the image.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawPixelV(image, { x = 50, y = 50 }, { r = 255, g = 255, b = 0, a = 255 }) -- Draws a yellow pixel at (50, 50)
 * ```
 */
int lua_ImageDrawPixelV(lua_State *L);

/**
 * @brief Draws a line between two points in an image.
 * 
 * This function draws a straight line between the points (x1, y1) and (x2, y2) in the image.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawLine(image, 10, 20, 100, 120, { r = 0, g = 0, b = 255, a = 255 }) -- Draws a blue line from (10, 20) to (100, 120)
 * ```
 */
int lua_ImageDrawLine(lua_State *L);
/**
 * @brief Draws a line between two points (Vector2) in an image.
 * 
 * This function draws a straight line between the points specified by two Vector2 objects.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawLineV(image, { x = 10, y = 20 }, { x = 100, y = 120 }, { r = 0, g = 0, b = 255, a = 255 }) -- Draws a blue line
 * ```
 */
int lua_ImageDrawLineV(lua_State *L);

/**
 * @brief Draws a line between two points with extended parameters in an image.
 * 
 * This function draws a line with thickness between two points (Vector2) in the image.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawLineEx(image, { x = 10, y = 20 }, { x = 100, y = 120 }, 5, { r = 255, g = 0, b = 0, a = 255 }) -- Draws a thick red line
 * ```
 */
int lua_ImageDrawLineEx(lua_State *L);

/**
 * @brief Draws a circle in an image at a specified position.
 * 
 * This function draws a circle at the given (x, y) position with the specified radius and color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawCircle(image, 50, 50, 25, { r = 0, g = 255, b = 0, a = 255 }) -- Draws a green circle at (50, 50) with a radius of 25
 * ```
 */
int lua_ImageDrawCircle(lua_State *L);

/**
 * @brief Draws a circle in an image at a specified position (Vector2).
 * 
 * This function draws a circle at the position specified by a Vector2 with the given radius and color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawCircleV(image, { x = 75, y = 75 }, 30, { r = 255, g = 255, b = 0, a = 255 }) -- Draws a yellow circle
 * ```
 */
int lua_ImageDrawCircleV(lua_State *L);
/**
 * @brief Draws the outline of a circle in an image at a specified position.
 * 
 * This function draws the outline of a circle at the given (x, y) position with the specified radius and color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawCircleLines(image, 50, 50, 25, { r = 0, g = 0, b = 255, a = 255 }) -- Draws a blue circle outline at (50, 50) with a radius of 25
 * ```
 */
int lua_ImageDrawCircleLines(lua_State *L);

/**
 * @brief Draws the outline of a circle in an image at a specified position (Vector2).
 * 
 * This function draws the outline of a circle at the position specified by a Vector2 with the given radius and color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawCircleLinesV(image, { x = 75, y = 75 }, 30, { r = 255, g = 0, b = 0, a = 255 }) -- Draws a red circle outline
 * ```
 */
int lua_ImageDrawCircleLinesV(lua_State *L);

/**
 * @brief Draws a rectangle in an image at a specified position.
 * 
 * This function draws a rectangle at the given (x, y) position with the specified width, height, and color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawRectangle(image, 10, 20, 100, 50, { r = 0, g = 255, b = 0, a = 255 }) -- Draws a green rectangle at (10, 20) with a width of 100 and height of 50
 * ```
 */
int lua_ImageDrawRectangle(lua_State *L);

/**
 * @brief Draws a rectangle in an image at a specified position (Vector2).
 * 
 * This function draws a rectangle at the position specified by a Vector2 with the given size (Vector2) and color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawRectangleV(image, { x = 20, y = 40 }, { x = 150, y = 80 }, { r = 255, g = 0, b = 0, a = 255 }) -- Draws a red rectangle at (20, 40) with size (150, 80)
 * ```
 */
int lua_ImageDrawRectangleV(lua_State *L);
/**
 * @brief Draws a rectangle in an image using a Rectangle structure.
 * 
 * This function draws a rectangle in an image using a `Rectangle` structure to specify the position and size.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawRectangleRec(image, { x = 30, y = 40, width = 100, height = 50 }, { r = 255, g = 255, b = 0, a = 255 }) -- Draws a yellow rectangle at (30, 40) with width 100 and height 50
 * ```
 */
int lua_ImageDrawRectangleRec(lua_State *L);

/**
 * @brief Draws the outline of a rectangle in an image.
 * 
 * This function draws the outline of a rectangle at the given position (x, y) with the specified width, height, and color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawRectangleLines(image, 50, 50, 150, 100, { r = 255, g = 0, b = 0, a = 255 }) -- Draws a red rectangle outline at (50, 50) with width 150 and height 100
 * ```
 */
int lua_ImageDrawRectangleLines(lua_State *L);

/**
 * @brief Draws a triangle in an image using three points.
 * 
 * This function draws a filled triangle in an image using three points (Vector2) and a color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawTriangle(image, { x = 100, y = 100 }, { x = 150, y = 50 }, { x = 200, y = 100 }, { r = 0, g = 0, b = 255, a = 255 }) -- Draws a blue triangle
 * ```
 */
int lua_ImageDrawTriangle(lua_State *L);

/**
 * @brief Draws a triangle in an image using extended parameters.
 * 
 * This function draws a filled triangle in an image using three points (Vector2) and a color with extended options for customization.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawTriangleEx(image, { x = 100, y = 150 }, { x = 200, y = 50 }, { x = 250, y = 150 }, { r = 0, g = 255, b = 0, a = 255 }) -- Draws a green triangle
 * ```
 */
int lua_ImageDrawTriangleEx(lua_State *L);
/**
 * @brief Draws the outline of a triangle in an image.
 * 
 * This function draws the outline of a triangle in an image using three points (Vector2) and a color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawTriangleLines(image, { x = 100, y = 50 }, { x = 150, y = 150 }, { x = 200, y = 50 }, { r = 255, g = 255, b = 0, a = 255 }) -- Draws a yellow triangle outline
 * ```
 */
int lua_ImageDrawTriangleLines(lua_State *L);

/**
 * @brief Draws a triangle fan in an image.
 * 
 * This function draws a fan-shaped collection of triangles in an image using an array of points (Vector2) and a color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * local points = { { x = 100, y = 100 }, { x = 150, y = 50 }, { x = 200, y = 100 }, { x = 150, y = 150 } }
 * raylib.ImageDrawTriangleFan(image, points, { r = 0, g = 255, b = 0, a = 255 }) -- Draws a green triangle fan
 * ```
 */
int lua_ImageDrawTriangleFan(lua_State *L);

/**
 * @brief Draws a triangle strip in an image.
 * 
 * This function draws a connected series of triangles in an image using an array of points (Vector2) and a color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * local points = { { x = 100, y = 50 }, { x = 150, y = 100 }, { x = 200, y = 50 }, { x = 250, y = 100 } }
 * raylib.ImageDrawTriangleStrip(image, points, { r = 0, g = 0, b = 255, a = 255 }) -- Draws a blue triangle strip
 * ```
 */
int lua_ImageDrawTriangleStrip(lua_State *L);

/**
 * @brief Draws an image onto another image.
 * 
 * This function draws an image onto another image at a specified position and color tint.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local targetImage = raylib.LoadImage("background.png")
 * local sourceImage = raylib.LoadImage("sprite.png")
 * raylib.ImageDraw(targetImage, sourceImage, { x = 50, y = 50 }, { r = 255, g = 255, b = 255, a = 255 }) -- Draws the source image onto the target at position (50, 50)
 * ```
 */
int lua_ImageDraw(lua_State *L);
/**
 * @brief Draws text on an image.
 * 
 * This function draws a string of text on an image at a specified position using a given font size and color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * raylib.ImageDrawText(image, "Hello, World!", 50, 50, 20, { r = 255, g = 0, b = 0, a = 255 }) -- Draws red text at position (50, 50)
 * ```
 */
int lua_ImageDrawText(lua_State *L);

/**
 * @brief Draws text on an image using extended parameters.
 * 
 * This function draws a string of text on an image using a specified font, position, font size, spacing, and color.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("source.png")
 * local font = raylib.LoadFont("font.ttf")
 * raylib.ImageDrawTextEx(image, font, "Hello, World!", { x = 50, y = 50 }, 20, 2, { r = 0, g = 0, b = 255, a = 255 }) -- Draws blue text at position (50, 50) with custom font
 * ```
 */
int lua_ImageDrawTextEx(lua_State *L);

/**
 * @brief Loads a render texture.
 * 
 * This function creates a new render texture with the specified width and height.
 * 
 * @param L Lua state
 * @return int Always returns 1 (RenderTexture result)
 * 
 * **Usage:**
 * ```lua
 * local renderTexture = raylib.LoadRenderTexture(800, 600) -- Creates a render texture of size 800x600
 * ```
 */
int lua_LoadRenderTexture(lua_State *L);

/**
 * @brief Checks if a texture is valid.
 * 
 * This function checks if a given texture is valid.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 * 
 * **Usage:**
 * ```lua
 * local texture = raylib.LoadTexture("image.png")
 * local isValid = raylib.IsTextureValid(texture) -- Returns true if the texture is valid
 * ```
 */
int lua_IsTextureValid(lua_State *L);
/**
 * @brief Checks if a render texture is valid.
 * 
 * This function checks if a given render texture is valid.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 * 
 * **Usage:**
 * ```lua
 * local renderTexture = raylib.LoadRenderTexture(800, 600)
 * local isValid = raylib.IsRenderTextureValid(renderTexture) -- Returns true if the render texture is valid
 * ```
 */
int lua_IsRenderTextureValid(lua_State *L);

/**
 * @brief Unloads a render texture from memory.
 * 
 * This function releases all resources used by a render texture.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local renderTexture = raylib.LoadRenderTexture(800, 600)
 * raylib.UnloadRenderTexture(renderTexture) -- Frees the render texture from memory
 * ```
 */
int lua_UnloadRenderTexture(lua_State *L);

/**
 * @brief Sets the filter mode for a texture.
 * 
 * This function allows you to set a texture's filtering mode, such as `POINT`, `BILINEAR`, or `TRILINEAR`.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local texture = raylib.LoadTexture("image.png")
 * raylib.SetTextureFilter(texture, raylib.FILTER_BILINEAR) -- Applies bilinear filtering to the texture
 * ```
 */
int lua_SetTextureFilter(lua_State *L);

/**
 * @brief Sets the wrap mode for a texture.
 * 
 * This function sets the wrapping mode for a texture, such as `WRAP_REPEAT`, `WRAP_CLAMP`, or `WRAP_MIRROR`.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local texture = raylib.LoadTexture("image.png")
 * raylib.SetTextureWrap(texture, raylib.WRAP_REPEAT) -- Sets the texture to repeat mode
 * ```
 */
int lua_SetTextureWrap(lua_State *L);
/**
 * @brief Draws a texture at a specified position.
 * 
 * This function draws a texture at the given x and y position on the screen.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local texture = raylib.LoadTexture("image.png")
 * raylib.DrawTexture(texture, 100, 50, raylib.WHITE) -- Draws the texture at position (100, 50)
 * ```
 */
int lua_DrawTexture(lua_State *L);

/**
 * @brief Draws a texture at a specified position using a Vector2.
 * 
 * This function draws a texture at a given position using a Vector2 to specify the position.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local texture = raylib.LoadTexture("image.png")
 * raylib.DrawTextureV(texture, { x = 100, y = 50 }, raylib.WHITE) -- Draws the texture at position (100, 50) using a Vector2
 * ```
 */
int lua_DrawTextureV(lua_State *L);

/**
 * @brief Draws a texture with extended parameters.
 * 
 * This function draws a texture with extra parameters like rotation and scaling.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local texture = raylib.LoadTexture("image.png")
 * raylib.DrawTextureEx(texture, { x = 100, y = 50 }, 45.0, 1.5, raylib.WHITE) -- Draws the texture at (100, 50), rotates 45 degrees, scales by 1.5x
 * ```
 */
int lua_DrawTextureEx(lua_State *L);

/**
 * @brief Draws a part of a texture.
 * 
 * This function draws a portion of a texture defined by a rectangle.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local texture = raylib.LoadTexture("image.png")
 * local sourceRec = { x = 0, y = 0, width = 64, height = 64 }
 * raylib.DrawTextureRec(texture, sourceRec, { x = 100, y = 50 }, raylib.WHITE) -- Draws a 64x64 section of the texture at (100, 50)
 * ```
 */
int lua_DrawTextureRec(lua_State *L);
/**
 * @brief Draws a texture with extended parameters.
 * 
 * This function draws a texture with detailed control over position, rotation, origin, and scaling.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local texture = raylib.LoadTexture("image.png")
 * local sourceRec = { x = 0, y = 0, width = 64, height = 64 }
 * local destRec = { x = 200, y = 100, width = 128, height = 128 }
 * local origin = { x = 32, y = 32 }
 * raylib.DrawTexturePro(texture, sourceRec, destRec, origin, 45.0, raylib.WHITE) -- Draws the texture with rotation, scaling, and position adjustments
 * ```
 */
int lua_DrawTexturePro(lua_State *L);

/**
 * @brief Draws a texture using N-patch information.
 * 
 * This function draws a texture following the rules of N-patch, which allows scaling while preserving corners, edges, and center.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * local texture = raylib.LoadTexture("npatch.png")
 * local nPatchInfo = { sourceRec = { x = 0, y = 0, width = 64, height = 64 }, left = 8, top = 8, right = 8, bottom = 8, type = raylib.NPATCH_NINE_PATCH }
 * local destRec = { x = 100, y = 100, width = 128, height = 128 }
 * raylib.DrawTextureNPatch(texture, nPatchInfo, destRec, { x = 0, y = 0 }, 0.0, raylib.WHITE) -- Draws an N-patch texture with controlled scaling
 * ```
 */
int lua_DrawTextureNPatch(lua_State *L);

/**
 * @brief Checks if two colors are equal.
 * 
 * This function checks if two Color values are equal.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 * 
 * **Usage:**
 * ```lua
 * local color1 = raylib.RED
 * local color2 = raylib.RED
 * local isEqual = raylib.ColorIsEqual(color1, color2) -- Returns true since both colors are red
 * print(isEqual)
 * ```
 */
int lua_ColorIsEqual(lua_State *L);

/**
 * @brief Applies fade effect to a color.
 * 
 * This function adjusts the alpha value of a color to apply a fade effect.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Color result)
 * 
 * **Usage:**
 * ```lua
 * local color = raylib.RED
 * local fadedColor = raylib.Fade(color, 0.5) -- Fades the color to 50% opacity
 * print(fadedColor)
 * ```
 */
int lua_Fade(lua_State *L);
/**
 * @brief Converts a Color to an integer representation.
 * 
 * This function converts a Color to an integer where the color channels are packed into a single integer value.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 * 
 * **Usage:**
 * ```lua
 * local color = raylib.RED
 * local colorInt = raylib.ColorToInt(color) -- Converts the color to an integer
 * print(colorInt)
 * ```
 */
int lua_ColorToInt(lua_State *L);

/**
 * @brief Normalizes a Color to a Vector4.
 * 
 * This function normalizes a Color's RGBA channels to a Vector4 where each channel ranges from 0.0 to 1.0.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Vector4 result)
 * 
 * **Usage:**
 * ```lua
 * local color = raylib.RED
 * local normalizedColor = raylib.ColorNormalize(color) -- Normalizes the color
 * print(normalizedColor)
 * ```
 */
int lua_ColorNormalize(lua_State *L);

/**
 * @brief Converts a normalized Vector4 to a Color.
 * 
 * This function converts a normalized Vector4 to a Color, scaling each channel from 0.0-1.0 back to 0-255.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Color result)
 * 
 * **Usage:**
 * ```lua
 * local normalizedColor = { x = 1.0, y = 0.0, z = 0.0, w = 1.0 } -- Normalized red color
 * local color = raylib.ColorFromNormalized(normalizedColor) -- Converts back to Color
 * print(color)
 * ```
 */
int lua_ColorFromNormalized(lua_State *L);

/**
 * @brief Converts a Color to HSV.
 * 
 * This function converts a Color to its HSV (Hue, Saturation, Value) representation.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Vector3 result)
 * 
 * **Usage:**
 * ```lua
 * local color = raylib.RED
 * local hsv = raylib.ColorToHSV(color) -- Converts the color to HSV
 * print(hsv)
 * ```
 */
int lua_ColorToHSV(lua_State *L);
/**
 * @brief Converts HSV (Hue, Saturation, Value) to a Color.
 * 
 * This function converts an HSV value to a Color. The HSV model is often used in color selection and manipulation.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Color result)
 * 
 * **Usage:**
 * ```lua
 * local hsv = { h = 0.0, s = 1.0, v = 1.0 } -- Red color in HSV
 * local color = raylib.ColorFromHSV(hsv) -- Converts HSV to Color
 * print(color)
 * ```
 */
int lua_ColorFromHSV(lua_State *L);

/**
 * @brief Tints a Color with another Color.
 * 
 * This function applies a tint to a Color, mixing it with another Color. The resulting color is a blend of both.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Color result)
 * 
 * **Usage:**
 * ```lua
 * local color = raylib.RED
 * local tint = raylib.GREEN
 * local tintedColor = raylib.ColorTint(color, tint) -- Apply tint to color
 * print(tintedColor)
 * ```
 */
int lua_ColorTint(lua_State *L);

/**
 * @brief Adjusts the brightness of a Color.
 * 
 * This function adjusts the brightness of a Color by a given factor. A factor > 1.0 brightens the color, while a factor < 1.0 darkens it.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Color result)
 * 
 * **Usage:**
 * ```lua
 * local color = raylib.RED
 * local brightenedColor = raylib.ColorBrightness(color, 1.5) -- Increases brightness
 * print(brightenedColor)
 * ```
 */
int lua_ColorBrightness(lua_State *L);

/**
 * @brief Adjusts the contrast of a Color.
 * 
 * This function adjusts the contrast of a Color by a given factor. A factor > 1.0 increases contrast, while a factor < 1.0 reduces it.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Color result)
 * 
 * **Usage:**
 * ```lua
 * local color = raylib.RED
 * local contrastedColor = raylib.ColorContrast(color, 2.0) -- Increases contrast
 * print(contrastedColor)
 * ```
 */
int lua_ColorContrast(lua_State *L);
/**
 * @brief Adjusts the alpha (transparency) of a Color.
 * 
 * This function sets the alpha channel (transparency) of a Color, while keeping the RGB values intact. A value of 0 means fully transparent, and 255 means fully opaque.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Color result)
 * 
 * **Usage:**
 * ```lua
 * local color = raylib.RED
 * local transparentColor = raylib.ColorAlpha(color, 128) -- Set alpha to 128 (semi-transparent)
 * print(transparentColor)
 * ```
 */
int lua_ColorAlpha(lua_State *L);

/**
 * @brief Blends two Colors based on alpha blending.
 * 
 * This function blends two Colors together based on their alpha values. It performs an alpha blend between the original Color and the blend Color.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Color result)
 * 
 * **Usage:**
 * ```lua
 * local color1 = raylib.RED
 * local color2 = raylib.GREEN
 * local blendedColor = raylib.ColorAlphaBlend(color1, color2) -- Blend two colors based on alpha
 * print(blendedColor)
 * ```
 */
int lua_ColorAlphaBlend(lua_State *L);

/**
 * @brief Linearly interpolates between two Colors.
 * 
 * This function interpolates between two Colors based on a given factor. A factor of 0 returns the first color, and a factor of 1 returns the second color. Intermediate values return a blend.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Color result)
 * 
 * **Usage:**
 * ```lua
 * local color1 = raylib.RED
 * local color2 = raylib.BLUE
 * local lerpedColor = raylib.ColorLerp(color1, color2, 0.5) -- Interpolate halfway between red and blue
 * print(lerpedColor)
 * ```
 */
int lua_ColorLerp(lua_State *L);

/**
 * @brief Gets the integer representation of a Color.
 * 
 * This function converts a Color into its integer representation, using a format like RGBA where each channel is a byte.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result)
 * 
 * **Usage:**
 * ```lua
 * local color = raylib.RED
 * local colorInt = raylib.GetColor(color) -- Convert color to integer representation
 * print(colorInt)
 * ```
 */
int lua_GetColor(lua_State *L);
/**
 * @brief Gets the color of a pixel from the screen at a given position.
 * 
 * This function retrieves the color of a pixel at a specified position on the screen or render target. The color is returned in the form of a Color structure.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Color result)
 * 
 * **Usage:**
 * ```lua
 * local pixelColor = raylib.GetPixelColor(100, 200) -- Get color of the pixel at position (100, 200)
 * print(pixelColor)
 * ```
 */
int lua_GetPixelColor(lua_State *L);

/**
 * @brief Sets the color of a specific pixel on the screen or render target.
 * 
 * This function allows setting a pixel's color at a specific position. It modifies the pixel data of the screen or render target.
 * 
 * @param L Lua state
 * @return int Always returns 0
 * 
 * **Usage:**
 * ```lua
 * raylib.SetPixelColor(100, 200, raylib.RED) -- Set the pixel at position (100, 200) to red
 * ```
 */
int lua_SetPixelColor(lua_State *L);

/**
 * @brief Gets the size of the pixel data in memory for an image or texture.
 * 
 * This function returns the size of the pixel data in memory for a given image or texture, in bytes.
 * 
 * @param L Lua state
 * @return int Always returns 1 (integer result representing the data size in bytes)
 * 
 * **Usage:**
 * ```lua
 * local image = raylib.LoadImage("image.png")
 * local dataSize = raylib.GetPixelDataSize(image) -- Get the size of the pixel data for the image
 * print(dataSize)
 * ```
 */
int lua_GetPixelDataSize(lua_State *L);

#endif