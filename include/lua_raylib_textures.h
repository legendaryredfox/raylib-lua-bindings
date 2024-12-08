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
int lua_ImageAlphaPremultiply(lua_State *L);
int lua_ImageBlurGaussian(lua_State *L);
int lua_ImageKernelConvolution(lua_State *L);
int lua_ImageResizeNN(lua_State *L);
int lua_ImageResizeCanvas(lua_State *L);
int lua_ImageMipmaps(lua_State *L);
int lua_ImageDither(lua_State *L);
int lua_ImageRotate(lua_State *L);
int lua_ImageRotateCW(lua_State *L);
int lua_ImageRotateCCW(lua_State *L);
int lua_LoadImageColors(lua_State *L);
int lua_LoadImagePalette(lua_State *L);
int lua_UnloadImageColors(lua_State *L);
int lua_UnloadImagePalette(lua_State *L);
int lua_GetImageAlphaBorder(lua_State *L);
int lua_GetImageColor(lua_State *L);
int lua_ImageClearBackground(lua_State *L);
int lua_ImageDrawPixel(lua_State *L);
int lua_ImageDrawPixelV(lua_State *L);
int lua_ImageDrawLine(lua_State *L);
int lua_ImageDrawLineV(lua_State *L);
int lua_ImageDrawLineEx(lua_State *L);
int lua_ImageDrawCircle(lua_State *L);
int lua_ImageDrawCircleV(lua_State *L);
int lua_ImageDrawCircleLines(lua_State *L);
int lua_ImageDrawCircleLinesV(lua_State *L);
int lua_ImageDrawRectangle(lua_State *L);
int lua_ImageDrawRectangleV(lua_State *L);
int lua_ImageDrawRectangleRec(lua_State *L);
int lua_ImageDrawRectangleLines(lua_State *L);
int lua_ImageDrawTriangle(lua_State *L);
int lua_ImageDrawTriangleEx(lua_State *L);
int lua_ImageDrawTriangleLines(lua_State *L);
int lua_ImageDrawTriangleFan(lua_State *L);
int lua_ImageDrawTriangleStrip(lua_State *L);
int lua_ImageDraw(lua_State *L);
int lua_ImageDrawText(lua_State *L);
int lua_ImageDrawTextEx(lua_State *L);
int lua_LoadRenderTexture(lua_State *L);
int lua_IsTextureValid(lua_State *L);
int lua_IsRenderTextureValid(lua_State *L);
int lua_UnloadRenderTexture(lua_State *L);
int lua_SetTextureFilter(lua_State *L);
int lua_SetTextureWrap(lua_State *L);
int lua_DrawTexture(lua_State *L);
int lua_DrawTextureV(lua_State *L);
int lua_DrawTextureEx(lua_State *L);
int lua_DrawTextureRec(lua_State *L);
int lua_DrawTexturePro(lua_State *L);
int lua_DrawTextureNPatch(lua_State *L);
int lua_ColorIsEqual(lua_State *L);
int lua_Fade(lua_State *L);
int lua_ColorToInt(lua_State *L);
int lua_ColorNormalize(lua_State *L);
int lua_ColorFromNormalized(lua_State *L);
int lua_ColorToHSV(lua_State *L);
int lua_ColorFromHSV(lua_State *L);
int lua_ColorTint(lua_State *L);
int lua_ColorBrightness(lua_State *L);
int lua_ColorContrast(lua_State *L);
int lua_ColorAlpha(lua_State *L);
int lua_ColorAlphaBlend(lua_State *L);
int lua_ColorLerp(lua_State *L);
int lua_GetColor(lua_State *L);
int lua_GetPixelColor(lua_State *L);
int lua_SetPixelColor(lua_State *L);
int lua_GetPixelDataSize(lua_State *L);

#endif