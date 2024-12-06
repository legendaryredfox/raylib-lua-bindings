#ifndef LUA_RAYLIB_AUDIO_H
#define LUA_RAYLIB_AUDIO_H

#include "lua_raylib.h"

int lua_LoadSound(lua_State *L);
int lua_PlaySound(lua_State *L);
int lua_StopSound(lua_State *L);
int lua_UnloadSound(lua_State *L);

int lua_LoadMusicStream(lua_State *L);
int lua_PlayMusicStream(lua_State *L);
int lua_StopMusicStream(lua_State *L);
int lua_UpdateMusicStream(lua_State *L);
int lua_SetMusicVolume(lua_State *L);
int lua_SetSoundVolume(lua_State *L);
int lua_IsSoundPlaying(lua_State *L);

int lua_InitAudioDevice(lua_State *L);
int lua_CloseAudioDevice(lua_State *L);
int lua_IsAudioDeviceReady(lua_State *L);
int lua_SetMasterVolume(lua_State *L);
int lua_GetMasterVolume(lua_State *L);
int lua_LoadWave(lua_State *L);
int lua_LoadWaveFromMemory(lua_State *L);
int lua_IsWaveValid(lua_State *L);
int lua_LoadSoundFromWave(lua_State *L);
int lua_LoadSoundAlias(lua_State *L);
int lua_IsSoundValid(lua_State *L);
int lua_UpdateSound(lua_State *L);
int lua_UnloadWave(lua_State *L);
int lua_UnloadSoundAlias(lua_State *L);
int lua_ExportWave(lua_State *L);
int lua_ExportWaveAsCode(lua_State *L);
int lua_WaveCopy(lua_State *L);
int lua_WaveCrop(lua_State *L);
int lua_WaveFormat(lua_State *L);
int lua_LoadWaveSamples(lua_State *L);
int lua_UnloadWaveSamples(lua_State *L);
int lua_IsMusicValid(lua_State *L);
int lua_UnloadMusicStream(lua_State *L);
int lua_IsMusicStreamPlaying(lua_State *L);
int lua_PauseMusicStream(lua_State *L);
int lua_ResumeMusicStream(lua_State *L);
int lua_SeekMusicStream(lua_State *L);
int lua_SetMusicPitch(lua_State *L);
int lua_SetMusicPan(lua_State *L);
int lua_GetMusicTimeLength(lua_State *L);
int lua_GetMusicTimePlayed(lua_State *L);
int lua_LoadAudioStream(lua_State *L);
int lua_IsAudioStreamValid(lua_State *L);
int lua_UnloadAudioStream(lua_State *L);
int lua_UpdateAudioStream(lua_State *L);
int lua_IsAudioStreamProcessed(lua_State *L);
int lua_PlayAudioStream(lua_State *L);
int lua_PauseAudioStream(lua_State *L);
int lua_ResumeAudioStream(lua_State *L);
int lua_IsAudioStreamPlaying(lua_State *L);
int lua_StopAudioStream(lua_State *L);
int lua_SetAudioStreamVolume(lua_State *L);
int lua_SetAudioStreamPitch(lua_State *L);
int lua_SetAudioStreamPan(lua_State *L);
int lua_SetAudioStreamBufferSizeDefault(lua_State *L);
int lua_SetAudioStreamCallback(lua_State *L);
int lua_AttachAudioStreamProcessor(lua_State *L);
int lua_DetachAudioStreamProcessor(lua_State *L);
int lua_AttachAudioMixedProcessor(lua_State *L);
int lua_DetachAudioMixedProcessor(lua_State *L);


#endif