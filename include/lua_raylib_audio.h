#ifndef LUA_RAYLIB_AUDIO_H
#define LUA_RAYLIB_AUDIO_H

#include "lua_raylib.h"

extern lua_State *globalLuaState;

void audioStreamProcessorWrapper(void *buffer, unsigned int frames);
void audioMixedProcessorWrapper(void *buffer, unsigned int frames);
void audioStreamCallbackWrapper(void *buffer, unsigned int frames);

/**
 * @brief Loads a sound from a file.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Sound result)
 */
int lua_LoadSound(lua_State *L);

/**
 * @brief Plays a loaded sound.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_PlaySound(lua_State *L);

/**
 * @brief Stops a playing sound.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_StopSound(lua_State *L);

/**
 * @brief Unloads a loaded sound from memory.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UnloadSound(lua_State *L);

/**
 * @brief Loads music stream from a file.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Music result)
 */
int lua_LoadMusicStream(lua_State *L);

/**
 * @brief Plays a loaded music stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_PlayMusicStream(lua_State *L);

/**
 * @brief Stops a playing music stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_StopMusicStream(lua_State *L);

/**
 * @brief Updates buffers for a music stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UpdateMusicStream(lua_State *L);

/**
 * @brief Sets the volume for a music stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetMusicVolume(lua_State *L);

/**
 * @brief Sets the volume for a sound.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetSoundVolume(lua_State *L);

/**
 * @brief Checks if a sound is currently playing.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsSoundPlaying(lua_State *L);

/**
 * @brief Initializes the audio device.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_InitAudioDevice(lua_State *L);

/**
 * @brief Closes the audio device.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_CloseAudioDevice(lua_State *L);

/**
 * @brief Checks if the audio device is ready.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsAudioDeviceReady(lua_State *L);

/**
 * @brief Sets the master volume.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetMasterVolume(lua_State *L);

/**
 * @brief Gets the master volume.
 * 
 * @param L Lua state
 * @return int Always returns 1 (float result)
 */
int lua_GetMasterVolume(lua_State *L);

/**
 * @brief Loads a wave from a file.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Wave result)
 */
int lua_LoadWave(lua_State *L);

/**
 * @brief Loads a wave from memory.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Wave result)
 */
int lua_LoadWaveFromMemory(lua_State *L);

/**
 * @brief Checks if a wave is valid.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsWaveValid(lua_State *L);

/**
 * @brief Loads a sound from a wave.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Sound result)
 */
int lua_LoadSoundFromWave(lua_State *L);

/**
 * @brief Loads a sound alias.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Sound result)
 */
int lua_LoadSoundAlias(lua_State *L);

/**
 * @brief Checks if a sound is valid.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsSoundValid(lua_State *L);

/**
 * @brief Updates a sound buffer with new data.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UpdateSound(lua_State *L);

/**
 * @brief Unloads a wave from memory.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UnloadWave(lua_State *L);

/**
 * @brief Unloads a sound alias from memory.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UnloadSoundAlias(lua_State *L);

/**
 * @brief Exports a wave to a file.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_ExportWave(lua_State *L);

/**
 * @brief Exports a wave as code.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_ExportWaveAsCode(lua_State *L);

/**
 * @brief Copies a wave.
 * 
 * @param L Lua state
 * @return int Always returns 1 (Wave result)
 */
int lua_WaveCopy(lua_State *L);

/**
 * @brief Crops a wave.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_WaveCrop(lua_State *L);

/**
 * @brief Formats a wave.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_WaveFormat(lua_State *L);

/**
 * @brief Loads wave samples.
 * 
 * @param L Lua state
 * @return int Always returns 1 (samples result)
 */
int lua_LoadWaveSamples(lua_State *L);

/**
 * @brief Unloads wave samples from memory.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UnloadWaveSamples(lua_State *L);

/**
 * @brief Checks if music is valid.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsMusicValid(lua_State *L);

/**
 * @brief Unloads a music stream from memory.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UnloadMusicStream(lua_State *L);

/**
 * @brief Checks if a music stream is currently playing.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsMusicStreamPlaying(lua_State *L);

/**
 * @brief Pauses the currently playing music stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_PauseMusicStream(lua_State *L);

/**
 * @brief Resumes the paused music stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_ResumeMusicStream(lua_State *L);

/**
 * @brief Seeks to a specific position in the music stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SeekMusicStream(lua_State *L);

/**
 * @brief Sets the pitch for the music stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetMusicPitch(lua_State *L);

/**
 * @brief Sets the pan for the music stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetMusicPan(lua_State *L);

/**
 * @brief Gets the total length of the music stream.
 * 
 * @param L Lua state
 * @return int Always returns 1 (float result)
 */
int lua_GetMusicTimeLength(lua_State *L);

/**
 * @brief Gets the time played of the music stream.
 * 
 * @param L Lua state
 * @return int Always returns 1 (float result)
 */
int lua_GetMusicTimePlayed(lua_State *L);

/**
 * @brief Loads an audio stream.
 * 
 * @param L Lua state
 * @return int Always returns 1 (AudioStream result)
 */
int lua_LoadAudioStream(lua_State *L);

/**
 * @brief Checks if an audio stream is valid.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsAudioStreamValid(lua_State *L);

/**
 * @brief Unloads an audio stream from memory.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UnloadAudioStream(lua_State *L);

/**
 * @brief Updates an audio stream with new data.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_UpdateAudioStream(lua_State *L);

/**
 * @brief Checks if an audio stream is processed.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsAudioStreamProcessed(lua_State *L);

/**
 * @brief Plays an audio stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_PlayAudioStream(lua_State *L);

/**
 * @brief Pauses the currently playing audio stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_PauseAudioStream(lua_State *L);

/**
 * @brief Resumes the paused audio stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_ResumeAudioStream(lua_State *L);

/**
 * @brief Checks if an audio stream is currently playing.
 * 
 * @param L Lua state
 * @return int Always returns 1 (boolean result)
 */
int lua_IsAudioStreamPlaying(lua_State *L);

/**
 * @brief Stops the currently playing audio stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_StopAudioStream(lua_State *L);

/**
 * @brief Sets the volume for an audio stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetAudioStreamVolume(lua_State *L);

/**
 * @brief Sets the pitch for an audio stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetAudioStreamPitch(lua_State *L);

/**
 * @brief Sets the pan for an audio stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetAudioStreamPan(lua_State *L);

/**
 * @brief Sets the default buffer size for an audio stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetAudioStreamBufferSizeDefault(lua_State *L);

/**
 * @brief Sets a callback function for an audio stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_SetAudioStreamCallback(lua_State *L);

/**
 * @brief Attaches a processor to an audio stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_AttachAudioStreamProcessor(lua_State *L);

/**
 * @brief Detaches a processor from an audio stream.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DetachAudioStreamProcessor(lua_State *L);

/**
 * @brief Attaches a processor to the mixed audio.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_AttachAudioMixedProcessor(lua_State *L);

/**
 * @brief Detaches a processor from the mixed audio.
 * 
 * @param L Lua state
 * @return int Always returns 0
 */
int lua_DetachAudioMixedProcessor(lua_State *L);

#endif