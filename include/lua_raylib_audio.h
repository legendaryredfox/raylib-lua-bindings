#ifndef LUA_RAYLIB_AUDIO_H
#define LUA_RAYLIB_AUDIO_H

#include "lua_raylib.h"

extern lua_State *globalLuaState;

void audioStreamProcessorWrapper(void *buffer, unsigned int frames);
void audioMixedProcessorWrapper(void *buffer, unsigned int frames);
void audioStreamCallbackWrapper(void *buffer, unsigned int frames);

/**
 * @brief Loads a sound from a file into memory.
 * 
 * This function loads an audio file (e.g., .wav, .ogg, .mp3) into memory as a Sound object 
 * that can be played, paused, stopped, and manipulated. It is useful for background music, 
 * sound effects, and UI feedback sounds.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing the Sound object onto the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `fileName` (string) - Path to the audio file to be loaded.
 * 
 * @usage
 * ```lua
 * local sound = raylib.LoadSound("resources/jump.wav")
 * raylib.PlaySound(sound)
 * ```
 */
int lua_LoadSound(lua_State *L);

/**
 * @brief Plays a loaded sound.
 * 
 * This function plays a sound that has been loaded into memory. If the sound is already 
 * playing, it will be restarted from the beginning. It is useful for playing short 
 * sound effects, like button clicks or character footsteps.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `sound` (Sound) - A Sound object returned from `LoadSound()`.
 * 
 * @usage
 * ```lua
 * local sound = raylib.LoadSound("resources/jump.wav")
 * raylib.PlaySound(sound)
 * ```
 */
int lua_PlaySound(lua_State *L);

/**
 * @brief Stops a currently playing sound.
 * 
 * This function stops a sound that is currently playing. It is useful for stopping 
 * looping sounds, background audio, or halting sound effects mid-play.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `sound` (Sound) - A Sound object returned from `LoadSound()`.
 * 
 * @usage
 * ```lua
 * local sound = raylib.LoadSound("resources/jump.wav")
 * raylib.PlaySound(sound)
 * -- Later in the script
 * raylib.StopSound(sound)
 * ```
 */
int lua_StopSound(lua_State *L);

/**
 * @brief Unloads a loaded sound from memory.
 * 
 * This function releases the memory used by a previously loaded Sound object. 
 * After calling this function, the sound can no longer be played until it is reloaded.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `sound` (Sound) - A Sound object returned from `LoadSound()`.
 * 
 * @usage
 * ```lua
 * local sound = raylib.LoadSound("resources/jump.wav")
 * raylib.PlaySound(sound)
 * -- Later in the script, free the memory
 * raylib.UnloadSound(sound)
 * ```
 */
int lua_UnloadSound(lua_State *L);

/**
 * @brief Loads a music stream from a file into memory.
 * 
 * This function loads an audio file (e.g., .wav, .ogg, .mp3) as a music stream. 
 * Unlike `LoadSound`, music streams are loaded in chunks while they are being played, 
 * making them more memory-efficient for large audio files.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing the Music object onto the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `fileName` (string) - Path to the audio file to be loaded.
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/ambient.ogg")
 * raylib.PlayMusicStream(music)
 * ```
 */
int lua_LoadMusicStream(lua_State *L);

/**
 * @brief Plays a loaded music stream.
 * 
 * This function starts playback of a music stream. If the music is already 
 * playing, it will continue from where it left off. Use `StopMusicStream()` 
 * to reset the play position to the beginning.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `music` (Music) - A Music object returned from `LoadMusicStream()`.
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/ambient.ogg")
 * raylib.PlayMusicStream(music)
 * ```
 */
int lua_PlayMusicStream(lua_State *L);

/**
 * @brief Stops a currently playing music stream.
 * 
 * This function stops the playback of a music stream and resets its 
 * position to the beginning. This is useful for stopping background music 
 * when changing game scenes or levels.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `music` (Music) - A Music object returned from `LoadMusicStream()`.
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/ambient.ogg")
 * raylib.PlayMusicStream(music)
 * -- Later in the script
 * raylib.StopMusicStream(music)
 * ```
 */
int lua_StopMusicStream(lua_State *L);

/**
 * @brief Updates the buffers for a music stream.
 * 
 * This function updates the internal buffers of the music stream, 
 * allowing it to continue playing. It must be called periodically 
 * in the main game loop to ensure smooth playback.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `music` (Music) - A Music object returned from `LoadMusicStream()`.
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/ambient.ogg")
 * raylib.PlayMusicStream(music)
 * 
 * while true do
 *     raylib.UpdateMusicStream(music)
 * end
 * ```
 */

int lua_UpdateMusicStream(lua_State *L);

/**
 * @brief Sets the volume for a music stream.
 * 
 * This function adjusts the playback volume for a loaded music stream. 
 * The volume value ranges from 0.0 (mute) to 1.0 (maximum volume). 
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `music` (Music) - A Music object returned from `LoadMusicStream()`.
 *       - `volume` (number) - The desired volume level (range: 0.0 to 1.0).
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/ambient.ogg")
 * raylib.SetMusicVolume(music, 0.5) -- Sets music volume to 50%
 * ```
 */
int lua_SetMusicVolume(lua_State *L);

/**
 * @brief Sets the volume for a sound.
 * 
 * This function adjusts the playback volume for a loaded sound. 
 * The volume value ranges from 0.0 (mute) to 1.0 (maximum volume). 
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameters must be provided as follows:
 *       - `sound` (Sound) - A Sound object returned from `LoadSound()`.
 *       - `volume` (number) - The desired volume level (range: 0.0 to 1.0).
 * 
 * @usage
 * ```lua
 * local sound = raylib.LoadSound("resources/sfx_jump.wav")
 * raylib.SetSoundVolume(sound, 0.75) -- Sets sound volume to 75%
 * ```
 */
int lua_SetSoundVolume(lua_State *L);

/**
 * @brief Checks if a sound is currently playing.
 * 
 * This function returns `true` if a specified sound is currently being played, 
 * and `false` otherwise. It is useful for determining if a sound has finished playing.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing a boolean (true or false) onto the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `sound` (Sound) - A Sound object returned from `LoadSound()`.
 * 
 * @usage
 * ```lua
 * local sound = raylib.LoadSound("resources/sfx_jump.wav")
 * raylib.PlaySound(sound)
 * 
 * if raylib.IsSoundPlaying(sound) then
 *     print("Sound is still playing!")
 * end
 * ```
 */
int lua_IsSoundPlaying(lua_State *L);

/**
 * @brief Initializes the audio device.
 * 
 * This function initializes the audio device, allowing playback of sounds and music. 
 * It must be called before using any other audio-related functions. 
 * Once the game is finished, use `CloseAudioDevice()` to properly clean up resources.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note This function does not require any parameters.
 * 
 * @usage
 * ```lua
 * raylib.InitAudioDevice()
 * local sound = raylib.LoadSound("resources/sfx_jump.wav")
 * raylib.PlaySound(sound)
 * 
 * -- Call this before exiting the game
 * raylib.CloseAudioDevice()
 * ```
 */
int lua_InitAudioDevice(lua_State *L);

/**
 * @brief Closes the audio device.
 * 
 * This function properly closes the audio device, releasing any resources 
 * allocated for sound and music playback. It should be called before 
 * the program terminates to ensure proper cleanup.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note This function does not require any parameters.
 * 
 * @usage
 * ```lua
 * raylib.InitAudioDevice()
 * local sound = raylib.LoadSound("resources/sfx_jump.wav")
 * raylib.PlaySound(sound)
 * 
 * -- Call this before exiting the game
 * raylib.CloseAudioDevice()
 * ```
 */
int lua_CloseAudioDevice(lua_State *L);

/**
 * @brief Checks if the audio device is ready.
 * 
 * This function returns `true` if the audio device is initialized and ready 
 * to play sounds and music, otherwise it returns `false`.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing a boolean (true or false) onto the Lua stack.
 * 
 * @note This function does not require any parameters.
 * 
 * @usage
 * ```lua
 * raylib.InitAudioDevice()
 * if raylib.IsAudioDeviceReady() then
 *     print("Audio device is ready")
 * else
 *     print("Audio device is not ready")
 * end
 * ```
 */
int lua_IsAudioDeviceReady(lua_State *L);

/**
 * @brief Sets the master volume for all audio.
 * 
 * This function sets the global master volume for all sound and music playback.
 * The volume value ranges from 0.0 (mute) to 1.0 (maximum volume).
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, indicating successful execution.
 * 
 * @note The parameter must be provided as follows:
 *       - `volume` (number) - The desired master volume (range: 0.0 to 1.0).
 * 
 * @usage
 * ```lua
 * raylib.InitAudioDevice()
 * raylib.SetMasterVolume(0.75) -- Sets master volume to 75%
 * ```
 */
int lua_SetMasterVolume(lua_State *L);

/**
 * @brief Gets the master volume for all audio.
 * 
 * This function returns the current master volume, which ranges from 0.0 (mute) 
 * to 1.0 (maximum volume). It reflects the global volume level affecting 
 * all sounds and music.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing a float (volume level) onto the Lua stack.
 * 
 * @note This function does not require any parameters.
 * 
 * @usage
 * ```lua
 * raylib.InitAudioDevice()
 * local volume = raylib.GetMasterVolume()
 * print("Current master volume is:", volume)
 * ```
 */
int lua_GetMasterVolume(lua_State *L);

/**
 * @brief Checks if a wave is valid.
 * 
 * This function verifies if the provided Wave object is valid and properly loaded. 
 * It returns `true` if the wave is valid, otherwise it returns `false`.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing a boolean (true or false) onto the Lua stack.
 * 
 * @note The parameter must be provided as follows:
 *       - `wave` (Wave) - The Wave object to check.
 * 
 * @usage
 * ```lua
 * local wave = raylib.LoadWave("resources/sound.wav")
 * if raylib.IsWaveValid(wave) then
 *     print("Wave is valid")
 * else
 *     print("Wave is not valid")
 * end
 * ```
 */
int lua_IsWaveValid(lua_State *L);

/**
 * @brief Loads a sound from a wave.
 * 
 * This function converts a previously loaded Wave into a Sound object. 
 * The resulting Sound can be played, paused, and manipulated at runtime.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing a Sound userdata onto the Lua stack.
 * 
 * @note The parameter must be provided as follows:
 *       - `wave` (Wave) - The source Wave object to convert into a Sound.
 * 
 * @usage
 * ```lua
 * local wave = raylib.LoadWave("resources/sound.wav")
 * local sound = raylib.LoadSoundFromWave(wave)
 * raylib.PlaySound(sound)
 * ```
 */
int lua_LoadSoundFromWave(lua_State *L);

/**
 * @brief Loads a wave from a file.
 * 
 * This function loads an audio Wave from a specified file and returns it as a 
 * Wave object. The wave can be used to create sounds or manipulate raw audio data.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing a Wave userdata onto the Lua stack.
 * 
 * @note The parameter must be provided as follows:
 *       - `fileName` (string) - The path to the audio file to load.
 * 
 * @usage
 * ```lua
 * local wave = raylib.LoadWave("resources/sound.wav")
 * ```
 */
int lua_LoadWave(lua_State *L);

/**
 * @brief Loads a wave from memory.
 * 
 * This function loads a Wave from a memory buffer. The memory buffer, file type, and 
 * buffer size are required as input. It allows loading of custom audio buffers 
 * from memory without a file.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing a Wave userdata onto the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `fileType` (string) - The file type/extension (e.g., "wav", "ogg", "mp3").
 *       - `fileData` (string) - The raw file data as a Lua string.
 *       - `dataSize` (integer) - The size of the file data buffer.
 * 
 * @usage
 * ```lua
 * local fileData = raylib.ReadFileToBuffer("resources/sound.wav")
 * local wave = raylib.LoadWaveFromMemory("wav", fileData, #fileData)
 * ```
 */
int lua_LoadWaveFromMemory(lua_State *L);

/**
 * @brief Loads a sound alias.
 * 
 * This function loads a sound alias, which allows referencing a sound 
 * by an alternative identifier. It provides a way to link an existing 
 * sound resource to a new name or identifier.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing a Sound userdata onto the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `alias` (string) - The alias name to associate with the sound.
 *       - `fileName` (string) - The path to the sound file to be loaded.
 * 
 * @usage
 * ```lua
 * local sound = raylib.LoadSoundAlias("explosion", "resources/explosion.wav")
 * raylib.PlaySound(sound)
 * ```
 */
int lua_LoadSoundAlias(lua_State *L);

/**
 * @brief Checks if a sound is valid.
 * 
 * This function checks if a Sound object is valid and properly loaded.
 * It returns `true` if the sound is valid, otherwise it returns `false`.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing a boolean (true or false) onto the Lua stack.
 * 
 * @note The parameter must be provided as follows:
 *       - `sound` (Sound) - The Sound object to validate.
 * 
 * @usage
 * ```lua
 * local sound = raylib.LoadSound("resources/sound.wav")
 * if raylib.IsSoundValid(sound) then
 *     print("Sound is valid")
 * else
 *     print("Sound is not valid")
 * end
 * ```
 */
int lua_IsSoundValid(lua_State *L);

/**
 * @brief Updates a sound buffer with new data.
 * 
 * This function updates the internal sound buffer with new data, which can 
 * be useful when streaming or modifying the sound content dynamically.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0.
 * 
 * @note The parameters must be provided as follows:
 *       - `sound` (Sound) - The Sound object to update.
 *       - `data` (string) - The new sound data to update the sound with.
 *       - `dataSize` (integer) - The size of the data buffer.
 * 
 * @usage
 * ```lua
 * local sound = raylib.LoadSound("resources/sound.wav")
 * local newData = raylib.GenerateCustomAudioData(44100, 2, 16) -- Simulating new sound data
 * raylib.UpdateSound(sound, newData, #newData)
 * ```
 */
int lua_UpdateSound(lua_State *L);

/**
 * @brief Unloads a wave from memory.
 * 
 * This function frees the memory associated with a loaded Wave object.
 * It ensures proper cleanup to avoid memory leaks.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0.
 * 
 * @note The parameter must be provided as follows:
 *       - `wave` (Wave) - The Wave object to unload.
 * 
 * @usage
 * ```lua
 * local wave = raylib.LoadWave("resources/sound.wav")
 * raylib.UnloadWave(wave)
 * ```
 */
int lua_UnloadWave(lua_State *L);

/**
 * @brief Unloads a sound alias from memory.
 * 
 * This function removes a sound alias from memory, freeing up the 
 * resources used by the alias. It ensures proper cleanup to avoid 
 * memory leaks or invalid references.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0.
 * 
 * @note The parameter must be provided as follows:
 *       - `alias` (string) - The name of the sound alias to unload.
 * 
 * @usage
 * ```lua
 * raylib.LoadSoundAlias("explosion", "resources/explosion.wav")
 * raylib.UnloadSoundAlias("explosion")
 * ```
 */
int lua_UnloadSoundAlias(lua_State *L);

/**
 * @brief Exports a wave to a file.
 * 
 * This function writes a Wave object to a file in the specified format.
 * It is useful for saving modified or generated wave data to disk.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0.
 * 
 * @note The parameters must be provided as follows:
 *       - `wave` (Wave) - The Wave object to export.
 *       - `fileName` (string) - The name of the file to save the wave to (e.g., "output.wav").
 * 
 * @usage
 * ```lua
 * local wave = raylib.LoadWave("resources/sound.wav")
 * raylib.ExportWave(wave, "output.wav")
 * ```
 */
int lua_ExportWave(lua_State *L);

/**
 * @brief Exports a wave as C code.
 * 
 * This function exports a Wave object as C code, allowing the wave data 
 * to be embedded directly into source code. This is useful for embedding 
 * assets into applications.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0.
 * 
 * @note The parameters must be provided as follows:
 *       - `wave` (Wave) - The Wave object to export as code.
 *       - `fileName` (string) - The name of the file to save the code to (e.g., "wave_data.c").
 * 
 * @usage
 * ```lua
 * local wave = raylib.LoadWave("resources/sound.wav")
 * raylib.ExportWaveAsCode(wave, "wave_data.c")
 * ```
 */
int lua_ExportWaveAsCode(lua_State *L);

/**
 * @brief Copies a wave.
 * 
 * This function creates an exact copy of the provided Wave object.
 * It is useful for creating independent duplicates that can be modified
 * without affecting the original.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1 (Wave result).
 * 
 * @note The parameter must be provided as follows:
 *       - `wave` (Wave) - The Wave object to be copied.
 * 
 * @usage
 * ```lua
 * local wave = raylib.LoadWave("resources/sound.wav")
 * local waveCopy = raylib.WaveCopy(wave)
 * ```
 */
int lua_WaveCopy(lua_State *L);

/**
 * @brief Crops a wave.
 * 
 * This function crops a Wave object, removing unwanted portions of the 
 * wave at the beginning or end. It modifies the existing Wave in place.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0.
 * 
 * @note The parameters must be provided as follows:
 *       - `wave` (Wave) - The Wave object to crop.
 *       - `initSample` (integer) - The starting sample index to keep.
 *       - `finalSample` (integer) - The ending sample index to keep.
 * 
 * @usage
 * ```lua
 * local wave = raylib.LoadWave("resources/sound.wav")
 * raylib.WaveCrop(wave, 1000, 5000) -- Keep only samples from 1000 to 5000
 * ```
 */
int lua_WaveCrop(lua_State *L);

/**
 * @brief Formats a wave.
 * 
 * This function reformats a Wave object, changing its bit depth, 
 * channel count, and sample rate. It modifies the existing Wave in place.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0.
 * 
 * @note The parameters must be provided as follows:
 *       - `wave` (Wave) - The Wave object to format.
 *       - `sampleRate` (integer) - The new sample rate (e.g., 44100).
 *       - `sampleSize` (integer) - The new sample size in bits (e.g., 16, 24, 32).
 *       - `channels` (integer) - The number of audio channels (e.g., 1 for mono, 2 for stereo).
 * 
 * @usage
 * ```lua
 * local wave = raylib.LoadWave("resources/sound.wav")
 * raylib.WaveFormat(wave, 44100, 16, 2) -- Change to 44.1kHz, 16-bit, stereo
 * ```
 */
int lua_WaveFormat(lua_State *L);
/**
 * @brief Loads wave samples.
 * 
 * This function extracts raw sample data from a Wave object. 
 * The returned data is an array of float samples, with each sample normalized 
 * between -1.0f and 1.0f.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1 (samples result).
 * 
 * @note The parameters must be provided as follows:
 *       - `wave` (Wave) - The Wave object from which to extract samples.
 * 
 * @usage
 * ```lua
 * local wave = raylib.LoadWave("resources/sound.wav")
 * local samples = raylib.LoadWaveSamples(wave)
 * ```
 * 
 * @warning This function allocates memory for the samples. 
 * The memory should be released using `raylib.UnloadWaveSamples(samples)`.
 */
int lua_LoadWaveSamples(lua_State *L);

/**
 * @brief Unloads wave samples from memory.
 * 
 * This function frees the memory allocated for an array of wave samples. 
 * It should be used to prevent memory leaks after processing the loaded samples.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0.
 * 
 * @note The parameters must be provided as follows:
 *       - `samples` (table) - The array of wave samples to unload.
 * 
 * @usage
 * ```lua
 * local wave = raylib.LoadWave("resources/sound.wav")
 * local samples = raylib.LoadWaveSamples(wave)
 * raylib.UnloadWaveSamples(samples)
 * ```
 * 
 * @warning Failing to unload wave samples can result in memory leaks.
 */
int lua_UnloadWaveSamples(lua_State *L);

/**
 * @brief Checks if a music object is valid.
 * 
 * This function checks whether a given music object is valid and properly initialized.
 * It ensures that the music object is usable before attempting to play or manipulate it.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1 (boolean result) indicating `true` if the music is valid, `false` otherwise.
 * 
 * @note The parameters must be provided as follows:
 *       - `music` (Music) - The music object to be checked.
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/music.mp3")
 * if raylib.IsMusicValid(music) then
 *     print("Music is valid and ready to play.")
 * end
 * ```
 */
int lua_IsMusicValid(lua_State *L);

/**
 * @brief Unloads a music stream from memory.
 * 
 * This function releases memory used by a music stream and stops any playback if the stream is currently playing.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0.
 * 
 * @note The parameters must be provided as follows:
 *       - `music` (Music) - The music stream to be unloaded.
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/music.mp3")
 * raylib.UnloadMusicStream(music)
 * ```
 * 
 * @warning Failing to unload a music stream after use can result in memory leaks.
 */
int lua_UnloadMusicStream(lua_State *L);

/**
 * @brief Checks if a music stream is currently playing.
 * 
 * This function checks if a music stream is actively playing.
 * It returns `true` if the music stream is currently being played, and `false` otherwise.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1 (boolean result) indicating `true` if the music stream is playing, `false` otherwise.
 * 
 * @note The parameters must be provided as follows:
 *       - `music` (Music) - The music stream to check for playback status.
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/music.mp3")
 * raylib.PlayMusicStream(music)
 * 
 * if raylib.IsMusicStreamPlaying(music) then
 *     print("Music is currently playing.")
 * end
 * ```
 */
int lua_IsMusicStreamPlaying(lua_State *L);

/**
 * @brief Pauses the currently playing music stream.
 * 
 * This function pauses a music stream that is currently playing. 
 * Playback can be resumed later using `lua_ResumeMusicStream`.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0.
 * 
 * @note The parameters must be provided as follows:
 *       - `music` (Music) - The music stream to be paused.
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/music.mp3")
 * raylib.PlayMusicStream(music)
 * raylib.PauseMusicStream(music)
 * ```
 */
int lua_PauseMusicStream(lua_State *L);

/**
 * @brief Resumes the paused music stream.
 * 
 * This function resumes a music stream that was previously paused using `lua_PauseMusicStream`.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0.
 * 
 * @note The parameters must be provided as follows:
 *       - `music` (Music) - The music stream to be resumed.
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/music.mp3")
 * raylib.PlayMusicStream(music)
 * raylib.PauseMusicStream(music)
 * raylib.ResumeMusicStream(music)
 * ```
 */
int lua_ResumeMusicStream(lua_State *L);

/**
 * @brief Seeks to a specific position in the music stream.
 * 
 * This function allows you to jump to a specific position in the music stream, useful for skipping parts of the track.
 * The position is specified in seconds relative to the start of the stream.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0.
 * 
 * @note The parameters must be provided as follows:
 *       - `music` (Music) - The music stream where the position will be set.
 *       - `position` (float) - The position (in seconds) to seek to in the music stream.
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/music.mp3")
 * raylib.PlayMusicStream(music)
 * raylib.SeekMusicStream(music, 30.0) -- Skip to 30 seconds
 * ```
 * 
 * @warning Ensure the position is within the bounds of the music stream's duration to avoid unexpected behavior.
 */
int lua_SeekMusicStream(lua_State *L);

/**
 * @brief Sets the pitch for the music stream.
 * 
 * This function allows you to change the pitch of the music stream. A pitch of `1.0` represents normal speed, 
 * while values higher than `1.0` increase the pitch (faster playback), and values lower than `1.0` decrease the pitch (slower playback).
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0.
 * 
 * @note The parameters must be provided as follows:
 *       - `music` (Music) - The music stream whose pitch will be changed.
 *       - `pitch` (float) - The new pitch value (e.g., 1.0 for normal pitch, 2.0 for double speed, 0.5 for half speed).
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/music.mp3")
 * raylib.PlayMusicStream(music)
 * raylib.SetMusicPitch(music, 1.5) -- Speed up the music playback
 * ```
 * 
 * @warning Setting pitch values that are too high or too low may cause the audio to sound unnatural.
 */
int lua_SetMusicPitch(lua_State *L);

/**
 * @brief Sets the pan for the music stream.
 * 
 * This function allows you to control the stereo panning of the music stream. A pan value of `0.0` centers the sound, 
 * `-1.0` pans the sound fully to the left, and `1.0` pans it fully to the right.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0.
 * 
 * @note The parameters must be provided as follows:
 *       - `music` (Music) - The music stream whose pan will be changed.
 *       - `pan` (float) - The new pan value (range: -1.0 to 1.0).
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/music.mp3")
 * raylib.PlayMusicStream(music)
 * raylib.SetMusicPan(music, -0.5) -- Pan the music to the left
 * raylib.SetMusicPan(music, 0.5)  -- Pan the music to the right
 * ```
 * 
 * @warning Values outside the range [-1.0, 1.0] may cause unexpected behavior.
 */
int lua_SetMusicPan(lua_State *L);

/**
 * @brief Gets the total length of the music stream.
 * 
 * This function retrieves the total duration of the music stream in seconds.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing a float to the Lua stack representing the total time in seconds.
 * 
 * @note The parameters must be provided as follows:
 *       - `music` (Music) - The music stream to get the duration of.
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/music.mp3")
 * local totalTime = raylib.GetMusicTimeLength(music)
 * print("Total time of music:", totalTime, "seconds")
 * ```
 */
int lua_GetMusicTimeLength(lua_State *L);

/**
 * @brief Gets the total time played of the music stream.
 * 
 * This function retrieves the current playback time of the music stream in seconds.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing a float to the Lua stack representing the elapsed playback time in seconds.
 * 
 * @note The parameters must be provided as follows:
 *       - `music` (Music) - The music stream to get the current playback time of.
 * 
 * @usage
 * ```lua
 * local music = raylib.LoadMusicStream("resources/music.mp3")
 * raylib.PlayMusicStream(music)
 * local playedTime = raylib.GetMusicTimePlayed(music)
 * print("Time played so far:", playedTime, "seconds")
 * ```
 * 
 * @warning If the music stream is not playing, the returned time will not change.
 */
int lua_GetMusicTimePlayed(lua_State *L);

/**
 * @brief Loads an audio stream with specified sample rate, sample size, and channel count.
 * 
 * This function creates an audio stream, allowing you to play dynamically generated audio or streamed audio data.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing an `AudioStream` to the Lua stack representing the created audio stream.
 * 
 * @note The parameters must be provided as follows:
 *       - `sampleRate` (int) - The sample rate of the audio stream (e.g., 44100 for standard audio).
 *       - `sampleSize` (int) - The bit depth of each sample (e.g., 16 or 32 bits).
 *       - `channels` (int) - The number of audio channels (e.g., 1 for mono, 2 for stereo).
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2) -- Create a stereo stream with 44.1kHz sample rate and 16-bit samples
 * print("Audio stream loaded:", stream)
 * ```
 * 
 * @warning Make sure to call `raylib.UnloadAudioStream(stream)` when you are finished with the stream to free memory.
 */
int lua_LoadAudioStream(lua_State *L);

/**
 * @brief Checks if an audio stream is valid.
 * 
 * This function determines whether a given audio stream is valid and usable.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing a boolean to the Lua stack indicating the validity of the stream.
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream to check for validity.
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * local isValid = raylib.IsAudioStreamValid(stream)
 * print("Is the audio stream valid?", isValid)
 * ```
 * 
 * @warning If the stream has been unloaded, this function will return `false`.
 */
int lua_IsAudioStreamValid(lua_State *L);

/**
 * @brief Unloads an audio stream from memory, freeing all associated resources.
 * 
 * This function releases memory used by an audio stream, making it unusable after the call.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream to be unloaded.
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * raylib.UnloadAudioStream(stream)
 * print("Audio stream unloaded.")
 * ```
 * 
 * @warning After calling this function, the stream can no longer be used.
 */
int lua_UnloadAudioStream(lua_State *L);

/**
 * @brief Updates an audio stream with new audio data.
 * 
 * This function feeds new audio data to an existing audio stream for playback.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream to update.
 *       - `data` (string) - A raw binary string containing the new audio data to be streamed.
 *       - `frameCount` (int) - The number of frames contained in the data.
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * local audioData = "..." -- raw binary audio data
 * raylib.UpdateAudioStream(stream, audioData, 1024) -- Update the stream with 1024 frames of data
 * ```
 * 
 * @warning Make sure the amount of data matches the stream's format, or it may result in audio glitches or crashes.
 */
int lua_UpdateAudioStream(lua_State *L);

/**
 * @brief Checks if an audio stream is currently being processed.
 * 
 * This function checks if the audio stream has finished processing its current data buffer.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing a boolean to the Lua stack indicating if the stream is processed.
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream to check.
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * local isProcessed = raylib.IsAudioStreamProcessed(stream)
 * print("Is the audio stream processed?", isProcessed)
 * ```
 * 
 * @warning This function returns `false` if the audio stream is actively playing or has unprocessed data in its buffer.
 */
int lua_IsAudioStreamProcessed(lua_State *L);

/**
 * @brief Plays an audio stream, starting from the current buffer position.
 * 
 * This function begins playback of an audio stream, starting at its current position.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream to play.
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * raylib.PlayAudioStream(stream)
 * print("Audio stream is now playing.")
 * ```
 * 
 * @warning This function does not reset the buffer position, it continues from the last buffer point.
 */
int lua_PlayAudioStream(lua_State *L);

/**
 * @brief Pauses the currently playing audio stream.
 * 
 * This function pauses an audio stream that is currently playing.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream to pause.
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * raylib.PlayAudioStream(stream)
 * -- After some time
 * raylib.PauseAudioStream(stream)
 * print("Audio stream has been paused.")
 * ```
 * 
 * @warning After pausing, you must call `raylib.ResumeAudioStream()` to continue playback.
 */
int lua_PauseAudioStream(lua_State *L);

/**
 * @brief Resumes a paused audio stream, continuing playback from its current position.
 * 
 * This function resumes playback of an audio stream that was previously paused.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream to resume.
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * raylib.PlayAudioStream(stream)
 * -- Pause and then resume the stream
 * raylib.PauseAudioStream(stream)
 * raylib.ResumeAudioStream(stream)
 * print("Audio stream resumed.")
 * ```
 * 
 * @warning The stream must have been previously paused using `raylib.PauseAudioStream()` before calling this function.
 */
int lua_ResumeAudioStream(lua_State *L);

/**
 * @brief Checks if an audio stream is currently playing.
 * 
 * This function checks if the given audio stream is actively playing.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 1, pushing a boolean to the Lua stack indicating if the audio stream is playing (`true`) or not (`false`).
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream to check.
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * raylib.PlayAudioStream(stream)
 * local isPlaying = raylib.IsAudioStreamPlaying(stream)
 * print("Is the audio stream playing?", isPlaying)
 * ```
 * 
 * @warning This function returns `false` if the stream is paused, stopped, or if it has reached the end of its playback.
 */
int lua_IsAudioStreamPlaying(lua_State *L);

/**
 * @brief Stops the currently playing audio stream and resets its playback position.
 * 
 * This function stops the playback of an audio stream and resets its position to the beginning.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream to stop.
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * raylib.PlayAudioStream(stream)
 * -- Stop the stream after some time
 * raylib.StopAudioStream(stream)
 * print("Audio stream stopped.")
 * ```
 * 
 * @warning Once stopped, the stream's position is reset to the beginning, unlike `raylib.PauseAudioStream()`, which retains the position.
 */
int lua_StopAudioStream(lua_State *L);

/**
 * @brief Sets the volume for an audio stream.
 * 
 * This function adjusts the playback volume of a given audio stream. The volume is a normalized value from 0.0 (muted) to 1.0 (full volume).
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream for which the volume will be set.
 *       - `volume` (float) - The desired volume value (0.0 to 1.0).
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * raylib.PlayAudioStream(stream)
 * raylib.SetAudioStreamVolume(stream, 0.5) -- Set volume to 50%
 * print("Volume set to 50%.")
 * ```
 * 
 * @warning Values outside the range [0.0, 1.0] will be clamped to the nearest valid value.
 */
int lua_SetAudioStreamVolume(lua_State *L);

/**
 * @brief Sets the pitch for an audio stream.
 * 
 * This function changes the pitch of a given audio stream. The pitch is a multiplier where 1.0 is the default pitch. Higher values increase pitch, while lower values decrease it.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream for which the pitch will be set.
 *       - `pitch` (float) - The desired pitch multiplier (default is 1.0).
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * raylib.PlayAudioStream(stream)
 * raylib.SetAudioStreamPitch(stream, 1.5) -- Increase pitch by 50%
 * print("Pitch set to 1.5x.")
 * ```
 * 
 * @warning Extremely high or low pitch values may distort the audio output.
 */
int lua_SetAudioStreamPitch(lua_State *L);

/**
 * @brief Sets the pan for an audio stream.
 * 
 * This function adjusts the pan (left-right stereo balance) of an audio stream. The pan is a value between -1.0 (full left) and 1.0 (full right). 
 * A value of 0.0 centers the audio between the left and right channels.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream for which the pan will be set.
 *       - `pan` (float) - The desired pan value (-1.0 for left, 1.0 for right, 0.0 for center).
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * raylib.PlayAudioStream(stream)
 * raylib.SetAudioStreamPan(stream, -0.75) -- Pan 75% to the left
 * print("Audio panned to the left.")
 * ```
 * 
 * @warning Values outside the range [-1.0, 1.0] will be clamped to the nearest valid value.
 */
int lua_SetAudioStreamPan(lua_State *L);

/**
 * @brief Sets the default buffer size for an audio stream.
 * 
 * This function sets the default buffer size used by all audio streams. The buffer size determines how much audio data 
 * is preloaded into the stream's buffer, which affects performance and latency.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `bufferSize` (int) - The size of the buffer in samples.
 * 
 * @usage
 * ```lua
 * raylib.SetAudioStreamBufferSizeDefault(4096)
 * print("Default audio stream buffer size set to 4096 samples.")
 * ```
 * 
 * @warning Setting a buffer size too low may result in audio glitches. A larger buffer size increases latency.
 */
int lua_SetAudioStreamBufferSizeDefault(lua_State *L);

/**
 * @brief Sets a callback function for an audio stream.
 * 
 * This function sets a custom callback function for an audio stream. The callback is invoked to provide audio samples 
 * for the stream, allowing for real-time synthesis or manipulation of audio data.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream to which the callback will be attached.
 *       - `callback` (function) - A Lua function that will be called to provide audio samples for the stream.
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * raylib.SetAudioStreamCallback(stream, function()
 *     -- Custom audio processing logic here
 * end)
 * print("Custom audio stream callback set.")
 * ```
 * 
 * @warning The callback function must be lightweight and efficient to avoid introducing latency into the stream.
 */
int lua_SetAudioStreamCallback(lua_State *L);

/**
 * @brief Attaches a processor to an audio stream.
 * 
 * This function attaches a custom processor to an audio stream. The processor can modify audio data as it is streamed, 
 * allowing for effects such as filtering, equalization, and dynamic range compression.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream to which the processor will be attached.
 *       - `processor` (function) - A Lua function that processes audio samples in real time.
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * raylib.AttachAudioStreamProcessor(stream, function(samples)
 *     -- Apply an effect to the audio samples
 *     return samples
 * end)
 * print("Audio stream processor attached.")
 * ```
 * 
 * @warning Processor functions must be fast and efficient to avoid audio glitches or latency issues.
 */
int lua_AttachAudioStreamProcessor(lua_State *L);

/**
 * @brief Detaches a processor from an audio stream.
 * 
 * This function detaches a previously attached processor from an audio stream. Once detached, the processor 
 * will no longer be called to process the stream's audio data.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `stream` (AudioStream) - The audio stream from which the processor will be detached.
 *       - `processor` (function) - The specific Lua processor function to detach.
 * 
 * @usage
 * ```lua
 * local stream = raylib.LoadAudioStream(44100, 16, 2)
 * raylib.AttachAudioStreamProcessor(stream, customProcessor)
 * raylib.DetachAudioStreamProcessor(stream, customProcessor)
 * print("Processor detached from audio stream.")
 * ```
 * 
 * @warning If the specified processor is not attached to the stream, this function will have no effect.
 */
int lua_DetachAudioStreamProcessor(lua_State *L);

/**
 * @brief Attaches a processor to the mixed audio.
 * 
 * This function attaches a processor to the global mixed audio output. The processor can modify the final 
 * audio output before it is sent to the speakers. This is useful for effects like global equalization, 
 * reverb, or volume normalization.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `processor` (function) - A Lua function that processes the mixed audio data.
 * 
 * @usage
 * ```lua
 * raylib.AttachAudioMixedProcessor(function(samples)
 *     -- Apply a low-pass filter to the mixed audio
 *     return samples
 * end)
 * print("Processor attached to mixed audio.")
 * ```
 * 
 * @warning The processor function must be efficient to avoid audio latency or glitches in the final mixed output.
 */
int lua_AttachAudioMixedProcessor(lua_State *L);

/**
 * @brief Detaches a processor from the mixed audio.
 * 
 * This function detaches a previously attached processor from the mixed audio output. Once detached, the 
 * processor will no longer be called to process the global mixed audio.
 * 
 * @param L A pointer to the current Lua state. This allows access to the Lua stack and other Lua-related operations.
 * 
 * @return int Always returns 0, with no values pushed to the Lua stack.
 * 
 * @note The parameters must be provided as follows:
 *       - `processor` (function) - The Lua processor function to be detached from the mixed audio.
 * 
 * @usage
 * ```lua
 * raylib.AttachAudioMixedProcessor(globalProcessor)
 * raylib.DetachAudioMixedProcessor(globalProcessor)
 * print("Processor detached from mixed audio.")
 * ```
 * 
 * @warning If the specified processor is not attached to the mixed audio, this function will have no effect.
 */
int lua_DetachAudioMixedProcessor(lua_State *L);

#endif