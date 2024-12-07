#include <lua.h>
#include <lauxlib.h>
#include "raylib_wrappers.h"
#include "lua_raylib_core.h"
#include "lua_raylib_draw.h"
#include "lua_raylib_audio.h"
#include "lua_raylib_textures.h"
#include "lua_raylib_models.h"
#include "lua_raylib_text.h"
#include "lua_raylib_shapes.h"

// Register bindings
static const luaL_Reg raylib_functions[] = {

    // Core
    {"InitWindow", lua_InitWindow},
    {"CloseWindow", lua_CloseWindow},
    {"WindowShouldClose", lua_WindowShouldClose},
    {"GetClipboardImage", lua_GetClipboardImage},
    {"SetWindowIcon", lua_SetWindowIcon},
    {"TakeScreenshot", lua_TakeScreenshot},
    {"GetFPS", lua_GetFPS},
    {"IsWindowMinimized", lua_IsWindowMinimized},
    {"IsWindowMaximized", lua_IsWindowMaximized},
    {"RestoreWindow", lua_RestoreWindow},
    {"ToggleFullscreen", lua_ToggleFullscreen},
    {"SetClipboardText", lua_SetClipboardText},
    {"GetClipboardText", lua_GetClipboardText},
    {"GetMouseX", lua_GetMouseX},
    {"GetMouseY", lua_GetMouseY},
    {"GetMousePosition", lua_GetMousePosition},
    {"GetMouseWheelMove", lua_GetMouseWheelMove},
    {"GetFrameTime", lua_GetFrameTime},
    {"IsKeyReleased", lua_IsKeyReleased},
    {"GetMonitorWidth", lua_GetMonitorWidth},
    {"GetMonitorHeight", lua_GetMonitorHeight},
    {"MaximizeWindow", lua_MaximizeWindow},
    {"MinimizeWindow", lua_MinimizeWindow},
    {"SetWindowTitle", lua_SetWindowTitle},
    {"SetWindowPosition", lua_SetWindowPosition},
    {"SetWindowMonitor", lua_SetWindowMonitor},
    {"SetWindowSize", lua_SetWindowSize},
    {"SetConfigFlags", lua_SetConfigFlags},
    {"GetScreenWidth", lua_GetScreenWidth},
    {"GetScreenHeight", lua_GetScreenHeight},
    {"GetMonitorCount", lua_GetMonitorCount},
    {"GetMonitorName", lua_GetMonitorName},
    {"GetMonitorPhysicalWidth", lua_GetMonitorPhysicalWidth},
    {"GetMonitorPhysicalHeight", lua_GetMonitorPhysicalHeight},
    {"GetMonitorRefreshRate", lua_GetMonitorRefreshRate},
    {"GetMonitorPosition", lua_GetMonitorPosition},
    {"GetTime", lua_GetTime},
    {"GetRandomValue", lua_GetRandomValue},
    {"SetTargetFPS", lua_SetTargetFPS},
    {"GetTargetFPS", lua_GetTargetFPS},
    {"IsKeyDown", lua_IsKeyDown},
    {"IsKeyUp", lua_IsKeyUp},
    {"IsMouseButtonDown", lua_IsMouseButtonDown},
    {"IsMouseButtonUp", lua_IsMouseButtonUp},
    {"SetMousePosition", lua_SetMousePosition},
    {"SetMouseOffset", lua_SetMouseOffset},
    {"SetMouseScale", lua_SetMouseScale},
    {"GetTouchPosition", lua_GetTouchPosition},
    {"ShowCursor", lua_ShowCursor},
    {"HideCursor", lua_HideCursor},
    {"IsCursorHidden", lua_IsCursorHidden},
    {"EnableCursor", lua_EnableCursor},
    {"DisableCursor", lua_DisableCursor},
    {"GetClipboardTextLength", lua_GetClipboardTextLength},
    {"IsWindowReady", lua_IsWindowReady},
    {"IsWindowFocused", lua_IsWindowFocused},
    {"IsWindowFullscreen", lua_IsWindowFullscreen},
    {"IsWindowHidden", lua_IsWindowHidden},
    {"IsWindowResized", lua_IsWindowResized},
    {"SetWindowState", lua_SetWindowState},
    {"ClearWindowState", lua_ClearWindowState},
    {"ToggleBorderlessWindowed", lua_ToggleBorderlessWindowed},
    {"SetWindowMinSize", lua_SetWindowMinSize},
    {"SetWindowMaxSize", lua_SetWindowMaxSize},
    {"SetWindowOpacity", lua_SetWindowOpacity},
    {"SetWindowFocused", lua_SetWindowFocused},
    {"GetWindowHandle", lua_GetWindowHandle},
    {"GetCurrentMonitor", lua_GetCurrentMonitor},
    {"GetWindowScaleDPI", lua_GetWindowScaleDPI},
    {"GetClipboardImage", lua_GetClipboardImage},
    {"EnableEventWaiting", lua_EnableEventWaiting},
    {"DisableEventWaiting", lua_DisableEventWaiting},
    {"IsCursorOnScreen", lua_IsCursorOnScreen},

    //Draw
    {"BeginDrawing", lua_BeginDrawing},
    {"EndDrawing", lua_EndDrawing},
    {"ClearBackground", lua_ClearBackground},
    {"DrawRectangle", lua_DrawRectangle},
    {"DrawRectangleLines", lua_DrawRectangleLines},
    {"DrawRectangleGradientV", lua_DrawRectangleGradientV},
    {"DrawRectangleGradientEx", lua_DrawRectangleGradientEx},
    {"DrawRectangleRounded", lua_DrawRectangleRounded},
    {"DrawTriangle", lua_DrawTriangle},
    {"DrawTriangleLines", lua_DrawTriangleLines},
    {"DrawTriangleStrip", lua_DrawTriangleStrip},
    {"DrawPoly", lua_DrawPoly},
    {"DrawPolyLines", lua_DrawPolyLines},
    {"DrawPolyLinesEx", lua_DrawPolyLinesEx},
    {"DrawCircle", lua_DrawCircle},
    {"DrawCircleSector", lua_DrawCircleSector},
    {"DrawCircleSectorLines", lua_DrawCircleSectorLines},
    {"DrawCircleGradient", lua_DrawCircleGradient},
    {"DrawRing", lua_DrawRing},
    {"DrawRingLines", lua_DrawRingLines},
    {"DrawLine", lua_DrawLine},
    {"DrawLineEx", lua_DrawLineEx},
    {"DrawLineBezier", lua_DrawLineBezier},
    {"DrawLineStrip", lua_DrawLineStrip},
    {"DrawEllipse", lua_DrawEllipse},
    {"DrawRingLines", lua_DrawRingLines},
    {"DrawGrid", lua_DrawGrid},

    //Audio
    {"LoadSound", lua_LoadSound},
    {"PlaySound", lua_PlaySound},
    {"StopSound", lua_StopSound},
    {"UnloadSound", lua_UnloadSound},
    {"LoadMusicStream", lua_LoadMusicStream},
    {"PlayMusicStream", lua_PlayMusicStream},
    {"StopMusicStream", lua_StopMusicStream},
    {"UpdateMusicStream", lua_UpdateMusicStream},
    {"SetMusicVolume", lua_SetMusicVolume},
    {"SetSoundVolume", lua_SetSoundVolume},
    {"IsSoundPlaying", lua_IsSoundPlaying},
    {"InitAudioDevice", lua_InitAudioDevice},
    {"CloseAudioDevice", lua_CloseAudioDevice},
    {"IsAudioDeviceReady", lua_IsAudioDeviceReady},
    {"SetMasterVolume", lua_SetMasterVolume},
    {"GetMasterVolume", lua_GetMasterVolume},
    {"LoadWave", lua_LoadWave},
    {"LoadWaveFromMemory", lua_LoadWaveFromMemory},
    {"IsWaveValid", lua_IsWaveValid},
    {"LoadSoundFromWave", lua_LoadSoundFromWave},
    {"LoadSoundAlias", lua_LoadSoundAlias},
    {"IsSoundValid", lua_IsSoundValid},
    {"UpdateSound", lua_UpdateSound},
    {"UnloadWave", lua_UnloadWave},
    {"UnloadSoundAlias", lua_UnloadSoundAlias},
    {"ExportWave", lua_ExportWave},
    {"ExportWaveAsCode", lua_ExportWaveAsCode},
    {"WaveCopy", lua_WaveCopy},
    {"WaveCrop", lua_WaveCrop},
    {"WaveFormat", lua_WaveFormat},
    {"LoadWaveSamples", lua_LoadWaveSamples},
    {"UnloadWaveSamples", lua_UnloadWaveSamples},
    {"IsMusicValid", lua_IsMusicValid},
    {"UnloadMusicStream", lua_UnloadMusicStream},
    {"IsMusicStreamPlaying", lua_IsMusicStreamPlaying},
    {"PauseMusicStream", lua_PauseMusicStream},
    {"ResumeMusicStream", lua_ResumeMusicStream},
    {"SeekMusicStream", lua_SeekMusicStream},
    {"SetMusicPitch", lua_SetMusicPitch},
    {"SetMusicPan", lua_SetMusicPan},
    {"GetMusicTimeLength", lua_GetMusicTimeLength},
    {"GetMusicTimePlayed", lua_GetMusicTimePlayed},
    {"LoadAudioStream", lua_LoadAudioStream},
    {"IsAudioStreamValid", lua_IsAudioStreamValid},
    {"UnloadAudioStream", lua_UnloadAudioStream},
    {"UpdateAudioStream", lua_UpdateAudioStream},
    {"IsAudioStreamProcessed", lua_IsAudioStreamProcessed},
    {"PlayAudioStream", lua_PlayAudioStream},
    {"PauseAudioStream", lua_PauseAudioStream},
    {"ResumeAudioStream", lua_ResumeAudioStream},
    {"IsAudioStreamPlaying", lua_IsAudioStreamPlaying},
    {"StopAudioStream", lua_StopAudioStream},
    {"SetAudioStreamVolume", lua_SetAudioStreamVolume},
    {"SetAudioStreamPitch", lua_SetAudioStreamPitch},
    {"SetAudioStreamPan", lua_SetAudioStreamPan},
    {"SetAudioStreamBufferSizeDefault", lua_SetAudioStreamBufferSizeDefault},
    {"SetAudioStreamCallback", lua_SetAudioStreamCallback},

    //Textures
    {"LoadImage", lua_LoadImage},
    {"UnloadImage", lua_UnloadImage},
    {"LoadTexture", lua_LoadTexture},
    {"LoadTextureFromImage", lua_LoadTextureFromImage},
    {"UnloadTexture", lua_UnloadTexture},
    {"UpdateTexture", lua_UpdateTexture},
    {"GenTextureMipmaps", lua_GenTextureMipmaps},
    {"ImageResize", lua_ImageResize},
    {"ImageFlipHorizontal", lua_ImageFlipHorizontal},
    {"ImageFlipVertical", lua_ImageFlipVertical},
    {"ImageCopy", lua_ImageCopy},
    {"ImageCrop", lua_ImageCrop},
    {"ImageColorTint", lua_ImageColorTint},
    {"ImageColorInvert", lua_ImageColorInvert},
    {"ImageColorGrayscale", lua_ImageColorGrayscale},
    {"ImageColorBrightness", lua_ImageColorBrightness},
    {"ImageColorContrast", lua_ImageColorContrast},
    {"ImageColorReplace", lua_ImageColorReplace},
    {"LoadTextureCubemap", lua_LoadTextureCubemap},
    {"UpdateTextureRec", lua_UpdateTextureRec},
    {"LoadImageRaw", lua_LoadImageRaw},
    {"LoadImageAnim", lua_LoadImageAnim},
    {"LoadImageAnimFromMemory", lua_LoadImageAnimFromMemory},
    {"LoadImageFromMemory", lua_LoadImageFromMemory},
    {"LoadImageFromTexture", lua_LoadImageFromTexture},
    {"LoadImageFromScreen", lua_LoadImageFromScreen},
    {"IsImageValid", lua_IsImageValid},
    {"ExportImage", lua_ExportImage},
    {"ExportImageToMemory", lua_ExportImageToMemory},
    {"ExportImageAsCode", lua_ExportImageAsCode},
    {"GenImageColor", lua_GenImageColor},
    {"GenImageGradientLinear", lua_GenImageGradientLinear},
    {"GenImageGradientRadial", lua_GenImageGradientRadial},
    {"GenImageGradientSquare", lua_GenImageGradientSquare},
    {"GenImageChecked", lua_GenImageChecked},
    {"GenImageWhiteNoise", lua_GenImageWhiteNoise},
    {"GenImagePerlinNoise", lua_GenImagePerlinNoise},
    {"GenImageCellular", lua_GenImageCellular},
    {"GenImageText", lua_GenImageText},
    {"ImageFromImage", lua_ImageFromImage},
    {"ImageFromChannel", lua_ImageFromChannel},
    {"ImageText", lua_ImageText},
    {"ImageTextEx", lua_ImageTextEx},
    {"ImageFormat", lua_ImageFormat},
    {"ImageToPOT", lua_ImageToPOT},
    {"ImageAlphaCrop", lua_ImageAlphaCrop},
    {"ImageAlphaClear", lua_ImageAlphaClear},
    {"ImageAlphaMask", lua_ImageAlphaMask},
    {"ImageAlphaPremultiply", lua_ImageAlphaPremultiply},
    {"ImageBlurGaussian", lua_ImageBlurGaussian},
    {"ImageKernelConvolution", lua_ImageKernelConvolution},
    {"ImageResizeNN", lua_ImageResizeNN},
    {"ImageResizeCanvas", lua_ImageResizeCanvas},
    {"ImageMipmaps", lua_ImageMipmaps},
    {"ImageDither", lua_ImageDither},
    {"ImageRotate", lua_ImageRotate},
    {"ImageRotateCW", lua_ImageRotateCW},
    {"ImageRotateCCW", lua_ImageRotateCCW},
    {"LoadImageColors", lua_LoadImageColors},
    {"ImageClearBackground", lua_ImageClearBackground},
    {"ImageDrawPixel", lua_ImageDrawPixel},
    {"ImageDrawPixelV", lua_ImageDrawPixelV},
    {"ImageDrawLine", lua_ImageDrawLine},
    {"ImageDrawLineV", lua_ImageDrawLineV},
    {"ImageDrawCircle", lua_ImageDrawCircle},
    {"ImageDrawCircleV", lua_ImageDrawCircleV},
    {"ImageDrawRectangle", lua_ImageDrawRectangle},
    {"ImageDrawRectangleV", lua_ImageDrawRectangleV},
    {"ImageDrawRectangleRec", lua_ImageDrawRectangleRec},
    {"ImageDrawRectangleLines", lua_ImageDrawRectangleLines},
    {"ImageDrawTriangle", lua_ImageDrawTriangle},
    {"ImageDrawTriangleEx", lua_ImageDrawTriangleEx},
    {"ImageDrawTriangleLines", lua_ImageDrawTriangleLines},
    {"ImageDrawTriangleFan", lua_ImageDrawTriangleFan},
    {"ImageDrawTriangleStrip", lua_ImageDrawTriangleStrip},
    {"ImageDraw", lua_ImageDraw},
    {"ImageDrawText", lua_ImageDrawText},
    {"ImageDrawTextEx", lua_ImageDrawTextEx},
    {"LoadRenderTexture", lua_LoadRenderTexture},
    {"IsTextureValid", lua_IsTextureValid},
    {"IsRenderTextureValid", lua_IsRenderTextureValid},
    {"UnloadRenderTexture", lua_UnloadRenderTexture},
    {"SetTextureFilter", lua_SetTextureFilter},
    {"SetTextureWrap", lua_SetTextureWrap},
    {"DrawTexture", lua_DrawTexture},
    {"DrawTextureV", lua_DrawTextureV},
    {"DrawTextureEx", lua_DrawTextureEx},
    {"DrawTextureRec", lua_DrawTextureRec},
    {"DrawTexturePro", lua_DrawTexturePro},
    {"DrawTextureNPatch", lua_DrawTextureNPatch},
    {"ColorIsEqual", lua_ColorIsEqual},
    {"Fade", lua_Fade},
    {"ColorToInt", lua_ColorToInt},
    {"ColorNormalize", lua_ColorNormalize},
    {"ColorFromNormalized", lua_ColorFromNormalized},
    {"ColorToHSV", lua_ColorToHSV},
    {"ColorFromHSV", lua_ColorFromHSV},
    {"ColorTint", lua_ColorTint},
    {"ColorBrightness", lua_ColorBrightness},
    {"ColorContrast", lua_ColorContrast},
    {"ColorAlpha", lua_ColorAlpha},
    {"ColorAlphaBlend", lua_ColorAlphaBlend},
    {"ColorLerp", lua_ColorLerp},
    {"GetColor", lua_GetColor},
    {"GetPixelColor", lua_GetPixelColor},
    {"SetPixelColor", lua_SetPixelColor},
    {"GetPixelDataSize", lua_GetPixelDataSize},

    //Models
    {"LoadModel", lua_LoadModel},
    {"DrawModel", lua_DrawModel},
    {"DrawModelEx", lua_DrawModelEx},
    {"UnloadModel", lua_UnloadModel},
    {"UpdateModelAnimation", lua_UpdateModelAnimation},
    {"DrawMesh", lua_DrawMesh},
    {"UnloadMesh", lua_UnloadMesh},
    {"GenMeshCube", lua_GenMeshCube},
    {"GenMeshSphere", lua_GenMeshSphere},
    {"GenMeshPlane", lua_GenMeshPlane},
    {"DrawLine3D", lua_DrawLine3D},
    {"DrawPoint3D", lua_DrawPoint3D},
    {"DrawCircle3D", lua_DrawCircle3D},
    {"DrawTriangle3D", lua_DrawTriangle3D},
    {"DrawTriangleStrip3D", lua_DrawTriangleStrip3D},
    {"DrawCube", lua_DrawCube},
    {"DrawCubeV", lua_DrawCubeV},
    {"DrawCubeWires", lua_DrawCubeWires},
    {"DrawCubeWiresV", lua_DrawCubeWiresV},
    {"DrawSphereWires", lua_DrawSphereWires},
    {"DrawCylinder", lua_DrawCylinder},
    {"DrawCylinderEx", lua_DrawCylinderEx},
    {"DrawCylinderWires", lua_DrawCylinderWires},
    {"DrawCylinderWiresEx", lua_DrawCylinderWiresEx},
    {"DrawCapsule", lua_DrawCapsule},
    {"DrawCapsuleWires", lua_DrawCapsuleWires},
    {"DrawPlane", lua_DrawPlane},
    {"DrawRay", lua_DrawRay},
    {"LoadModelFromMesh", lua_LoadModelFromMesh},
    {"IsModelValid", lua_IsModelValid},
    {"GetModelBoundingBox", lua_GetModelBoundingBox},
    {"DrawBoundingBox", lua_DrawBoundingBox},
    {"DrawBillboard", lua_DrawBillboard},
    {"DrawBillboardRec", lua_DrawBillboardRec},
    {"DrawBillboardPro", lua_DrawBillboardPro},
    {"UploadMesh", lua_UploadMesh},
    {"UpdateMeshBuffer", lua_UpdateMeshBuffer},
    {"GetMeshBoundingBox", lua_GetMeshBoundingBox},
    {"GenMeshTangents", lua_GenMeshTangents},
    {"ExportMesh", lua_ExportMesh},
    {"ExportMeshAsCode", lua_ExportMeshAsCode},
    {"GenMeshPoly", lua_GenMeshPoly},
    {"GenMeshHemiSphere", lua_GenMeshHemiSphere},
    {"GenMeshCylinder", lua_GenMeshCylinder},
    {"GenMeshCone", lua_GenMeshCone},
    {"GenMeshTorus", lua_GenMeshTorus},
    {"GenMeshKnot", lua_GenMeshKnot},
    {"GenMeshHeightmap", lua_GenMeshHeightmap},
    {"GenMeshCubicmap", lua_GenMeshCubicmap},
    {"LoadMaterials", lua_LoadMaterials},
    {"LoadMaterialDefault", lua_LoadMaterialDefault},
    {"IsMaterialValid", lua_IsMaterialValid},
    {"UnloadMaterial", lua_UnloadMaterial},
    {"LoadModelAnimations", lua_LoadModelAnimations},
    {"UnloadModelAnimation", lua_UnloadModelAnimation},
    {"UnloadModelAnimations", lua_UnloadModelAnimations},
    {"IsModelAnimationValid", lua_IsModelAnimationValid},
    {"CheckCollisionSpheres", lua_CheckCollisionSpheres},
    {"CheckCollisionBoxes", lua_CheckCollisionBoxes},
    {"CheckCollisionBoxSphere", lua_CheckCollisionBoxSphere},
    {"GetRayCollisionSphere", lua_GetRayCollisionSphere},
    {"GetRayCollisionBox", lua_GetRayCollisionBox},
    {"GetRayCollisionMesh", lua_GetRayCollisionMesh},
    {"GetRayCollisionTriangle", lua_GetRayCollisionTriangle},
    {"GetRayCollisionQuad", lua_GetRayCollisionQuad},

    //Text
    {"GetFontDefault", lua_GetFontDefault},
    {"LoadFont", lua_LoadFont},
    {"LoadFontEx", lua_LoadFontEx},
    {"LoadFontFromImage", lua_LoadFontFromImage},
    {"LoadFontFromMemory", lua_LoadFontFromMemory},
    {"IsFontValid", lua_IsFontValid},
    {"UnloadFont", lua_UnloadFont},
    {"ExportFontAsCode", lua_ExportFontAsCode},
    {"DrawFPS", lua_DrawFPS},
    {"DrawText", lua_DrawText},
    {"DrawTextEx", lua_DrawTextEx},
    {"DrawTextPro", lua_DrawTextPro},
    {"DrawTextCodepoint", lua_DrawTextCodepoint},
    {"DrawTextCodepoints", lua_DrawTextCodepoints},
    {"SetTextLineSpacing", lua_SetTextLineSpacing},
    {"MeasureText", lua_MeasureText},
    {"MeasureTextEx", lua_MeasureTextEx},
    {"GetGlyphIndex", lua_GetGlyphIndex},
    {"GetGlyphInfo", lua_GetGlyphInfo},
    {"GetGlyphAtlasRec", lua_GetGlyphAtlasRec},
    {"LoadUTF8", lua_LoadUTF8},
    {"UnloadUTF8", lua_UnloadUTF8},
    {"LoadCodepoints", lua_LoadCodepoints},
    {"UnloadCodepoints", lua_UnloadCodepoints},
    {"GetCodepointCount", lua_GetCodepointCount},
    {"GetCodepoint", lua_GetCodepoint},
    {"GetCodepointNext", lua_GetCodepointNext},
    {"GetCodepointPrevious", lua_GetCodepointPrevious},
    {"CodepointToUTF8", lua_CodepointToUTF8},
    {"TextCopy", lua_TextCopy},
    {"TextIsEqual", lua_TextIsEqual},
    {"TextLength", lua_TextLength},
    {"TextFormat", lua_TextFormat},
    {"TextSubtext", lua_TextSubtext},
    {"TextReplace", lua_TextReplace},
    {"TextInsert", lua_TextInsert},
    {"TextJoin", lua_TextJoin},
    {"TextSplit", lua_TextSplit},
    {"TextAppend", lua_TextAppend},
    {"TextFindIndex", lua_TextFindIndex},
    {"TextToUpper", lua_TextToUpper},
    {"TextToLower", lua_TextToLower},
    {"TextToPascal", lua_TextToPascal},
    {"TextToSnake", lua_TextToSnake},
    {"TextToCamel", lua_TextToCamel},
    {"TextToInteger", lua_TextToInteger},
    {"TextToFloat", lua_TextToFloat},
    
    //Shapes
    {"SetShapesTexture", lua_SetShapesTexture},
    {"GetShapesTexture", lua_GetShapesTexture},
    {"GetShapesTextureRectangle", lua_GetShapesTextureRectangle},
    {"DrawPixel", lua_DrawPixel},
    {"DrawPixelV", lua_DrawPixelV},
    {"DrawLineV", lua_DrawLineV},
    {"DrawCircleV", lua_DrawCircleV},
    {"DrawCircleLines", lua_DrawCircleLines},
    {"DrawCircleLinesV", lua_DrawCircleLinesV},
    {"DrawEllipseLines", lua_DrawEllipseLines},
    {"DrawRectangleV", lua_DrawRectangleV},
    {"DrawRectangleRec", lua_DrawRectangleRec},
    {"DrawRectangleLines", lua_DrawRectangleLines},
    {"DrawRectanglePro", lua_DrawRectanglePro},
    {"DrawRectangleGradientH", lua_DrawRectangleGradientH},
    {"DrawRectangleLinesEx", lua_DrawRectangleLinesEx},
    {"DrawRectangleGradient", lua_DrawRectangleGradient},
    {"DrawRectangleGradientV", lua_DrawRectangleGradientV},
    {"DrawRectangleGradientEx", lua_DrawRectangleGradientEx},
    {"DrawRectangleRounded", lua_DrawRectangleRounded},
    {"DrawTriangleStrip", lua_DrawTriangleStrip},
    {"DrawSplineSegmentBezierCubic", lua_DrawSplineSegmentBezierCubic},
    {"GetSplinePointLinear", lua_GetSplinePointLinear},
    {"GetSplinePointBasis", lua_GetSplinePointBasis},
    {"GetSplinePointCatmullRom", lua_GetSplinePointCatmullRom},
    {"GetSplinePointBezierQuad", lua_GetSplinePointBezierQuad},
    {"GetSplinePointBezierCubic", lua_GetSplinePointBezierCubic},
    {"CheckCollisionRecs", lua_CheckCollisionRecs},
    {"CheckCollisionCircles", lua_CheckCollisionCircles},
    {"CheckCollisionCircleRec", lua_CheckCollisionCircleRec},
    {"CheckCollisionCircleLine", lua_CheckCollisionCircleLine},
    {"CheckCollisionPointRec", lua_CheckCollisionPointRec},
    {"CheckCollisionPointCircle", lua_CheckCollisionPointCircle},
    {"CheckCollisionPointTriangle", lua_CheckCollisionPointTriangle},
    {"CheckCollisionPointLine", lua_CheckCollisionPointLine},
    {"CheckCollisionPointPoly", lua_CheckCollisionPointPoly},
    {"CheckCollisionLines", lua_CheckCollisionLines},
    {"GetCollisionRec", lua_GetCollisionRec},

    {NULL, NULL} 
};

int luaopen_raylib(lua_State *L) {
    luaL_newlib(L, raylib_functions);
    return 1;
}
