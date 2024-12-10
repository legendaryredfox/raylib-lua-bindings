#include "lua_raylib_audio.h"

lua_State *globalLuaState = NULL;

int lua_LoadSound(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    Sound sound = LoadSound(fileName);
    Sound *pSound = lua_newuserdata(L, sizeof(Sound));
    *pSound = sound;
    luaL_setmetatable(L, "Sound");
    return 1;
}

int lua_PlaySound(lua_State *L) {
    Sound *sound = luaL_checkudata(L, 1, "Sound");
    PlaySound(*sound);
    return 0;
}

int lua_StopSound(lua_State *L) {
    Sound *sound = luaL_checkudata(L, 1, "Sound");
    StopSound(*sound);
    return 0;
}

int lua_UnloadSound(lua_State *L) {
    Sound *sound = luaL_checkudata(L, 1, "Sound");
    UnloadSound(*sound);
    return 0;
}

int lua_SetSoundVolume(lua_State *L) {
    Sound *sound = luaL_checkudata(L, 1, "Sound");
    float volume = luaL_checknumber(L, 2);
    SetSoundVolume(*sound, volume);
    return 0;
}

int lua_LoadMusicStream(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    Music music = LoadMusicStream(fileName);
    Music *pMusic = lua_newuserdata(L, sizeof(Music));
    *pMusic = music;
    luaL_setmetatable(L, "Music");
    return 1;
}

int lua_PlayMusicStream(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    PlayMusicStream(*music);
    return 0;
}

int lua_StopMusicStream(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    StopMusicStream(*music);
    return 0;
}

int lua_UpdateMusicStream(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    UpdateMusicStream(*music);
    return 0;
}

int lua_SetMusicVolume(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    float volume = luaL_checknumber(L, 2);
    SetMusicVolume(*music, volume);
    return 0;
}

int lua_IsSoundPlaying(lua_State *L) {
    Sound *sound = luaL_checkudata(L, 1, "Sound");
    lua_pushboolean(L, IsSoundPlaying(*sound));
    return 1;
}

int lua_InitAudioDevice(lua_State *L) {
    InitAudioDevice();
    return 0;
}

int lua_CloseAudioDevice(lua_State *L) {
    CloseAudioDevice();
    return 0;
}

int lua_IsAudioDeviceReady(lua_State *L) {
    lua_pushboolean(L, IsAudioDeviceReady());
    return 1;
}

int lua_SetMasterVolume(lua_State *L) {
    float volume = luaL_checknumber(L, 1);
    SetMasterVolume(volume);
    return 0;
}

int lua_GetMasterVolume(lua_State *L) {
    lua_pushnumber(L, GetMasterVolume());
    return 1;
}

int lua_LoadWave(lua_State *L) {
    const char *fileName = luaL_checkstring(L, 1);
    Wave wave = LoadWave(fileName);
    Wave *pWave = lua_newuserdata(L, sizeof(Wave));
    *pWave = wave;
    luaL_setmetatable(L, "Wave");
    return 1;
}

int lua_LoadWaveFromMemory(lua_State *L) {
    const char *fileType = luaL_checkstring(L, 1);
    const char *fileData = luaL_checkstring(L, 2);
    int dataSize = luaL_checkinteger(L, 3);
    Wave wave = LoadWaveFromMemory(fileType, (unsigned char *)fileData, dataSize);
    Wave *pWave = lua_newuserdata(L, sizeof(Wave));
    *pWave = wave;
    luaL_setmetatable(L, "Wave");
    return 1;
}

int lua_IsWaveValid(lua_State *L) {
    Wave *wave = luaL_checkudata(L, 1, "Wave");
    lua_pushboolean(L, IsWaveValid(*wave));
    return 1;
}

int lua_LoadSoundFromWave(lua_State *L) {
    Wave *wave = luaL_checkudata(L, 1, "Wave");
    Sound sound = LoadSoundFromWave(*wave);
    Sound *pSound = lua_newuserdata(L, sizeof(Sound));
    *pSound = sound;
    luaL_setmetatable(L, "Sound");
    return 1;
}

int lua_LoadSoundAlias(lua_State *L) {
    Sound *source = luaL_checkudata(L, 1, "Sound");
    Sound alias = LoadSoundAlias(*source);
    Sound *pAlias = lua_newuserdata(L, sizeof(Sound));
    *pAlias = alias;
    luaL_setmetatable(L, "Sound");
    return 1;
}

int lua_IsSoundValid(lua_State *L) {
    Sound *sound = luaL_checkudata(L, 1, "Sound");
    lua_pushboolean(L, IsSoundValid(*sound));
    return 1;
}

int lua_UpdateSound(lua_State *L) {
    Sound *sound = luaL_checkudata(L, 1, "Sound");
    const void *data = lua_touserdata(L, 2);
    int sampleCount = luaL_checkinteger(L, 3);
    UpdateSound(*sound, data, sampleCount);
    return 0;
}

int lua_UnloadWave(lua_State *L) {
    Wave *wave = luaL_checkudata(L, 1, "Wave");
    UnloadWave(*wave);
    return 0;
}

int lua_UnloadSoundAlias(lua_State *L) {
    Sound *alias = luaL_checkudata(L, 1, "Sound");
    UnloadSoundAlias(*alias);
    return 0;
}

int lua_ExportWave(lua_State *L) {
    Wave *wave = luaL_checkudata(L, 1, "Wave");
    const char *fileName = luaL_checkstring(L, 2);
    lua_pushboolean(L, ExportWave(*wave, fileName));
    return 1;
}

int lua_ExportWaveAsCode(lua_State *L) {
    Wave *wave = luaL_checkudata(L, 1, "Wave");
    const char *fileName = luaL_checkstring(L, 2);
    lua_pushboolean(L, ExportWaveAsCode(*wave, fileName));
    return 1;
}

int lua_WaveCopy(lua_State *L) {
    Wave *wave = luaL_checkudata(L, 1, "Wave");
    Wave copiedWave = WaveCopy(*wave);
    Wave *pCopiedWave = lua_newuserdata(L, sizeof(Wave));
    *pCopiedWave = copiedWave;
    luaL_setmetatable(L, "Wave");
    return 1;
}

int lua_WaveCrop(lua_State *L) {
    Wave *wave = luaL_checkudata(L, 1, "Wave");
    int initFrame = luaL_checkinteger(L, 2);
    int finalFrame = luaL_checkinteger(L, 3);
    WaveCrop(wave, initFrame, finalFrame);
    return 0;
}

int lua_WaveFormat(lua_State *L) {
    Wave *wave = luaL_checkudata(L, 1, "Wave");
    int sampleRate = luaL_checkinteger(L, 2);
    int sampleSize = luaL_checkinteger(L, 3);
    int channels = luaL_checkinteger(L, 4);
    WaveFormat(wave, sampleRate, sampleSize, channels);
    return 0;
}

int lua_LoadWaveSamples(lua_State *L) {
    Wave *wave = luaL_checkudata(L, 1, "Wave");
    float *samples = LoadWaveSamples(*wave);
    lua_pushlightuserdata(L, samples);
    return 1;
}

int lua_UnloadWaveSamples(lua_State *L) {
    float *samples = (float *)lua_touserdata(L, 1);
    UnloadWaveSamples(samples);
    return 0;
}

int lua_IsMusicValid(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    lua_pushboolean(L, IsMusicValid(*music));
    return 1;
}

int lua_UnloadMusicStream(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    UnloadMusicStream(*music);
    return 0;
}

int lua_IsMusicStreamPlaying(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    lua_pushboolean(L, IsMusicStreamPlaying(*music));
    return 1;
}

int lua_PauseMusicStream(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    PauseMusicStream(*music);
    return 0;
}

int lua_ResumeMusicStream(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    ResumeMusicStream(*music);
    return 0;
}

int lua_SeekMusicStream(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    float position = luaL_checknumber(L, 2);
    SeekMusicStream(*music, position);
    return 0;
}

int lua_SetMusicPitch(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    float pitch = luaL_checknumber(L, 2);
    SetMusicPitch(*music, pitch);
    return 0;
}

int lua_SetMusicPan(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    float pan = luaL_checknumber(L, 2);
    SetMusicPan(*music, pan);
    return 0;
}

int lua_GetMusicTimeLength(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    lua_pushnumber(L, GetMusicTimeLength(*music));
    return 1;
}

int lua_GetMusicTimePlayed(lua_State *L) {
    Music *music = luaL_checkudata(L, 1, "Music");
    lua_pushnumber(L, GetMusicTimePlayed(*music));
    return 1;
}

int lua_LoadAudioStream(lua_State *L) {
    unsigned int sampleRate = luaL_checkinteger(L, 1);
    unsigned int sampleSize = luaL_checkinteger(L, 2);
    unsigned int channels = luaL_checkinteger(L, 3);
    AudioStream stream = LoadAudioStream(sampleRate, sampleSize, channels);
    AudioStream *pStream = lua_newuserdata(L, sizeof(AudioStream));
    *pStream = stream;
    luaL_setmetatable(L, "AudioStream");
    return 1;
}

int lua_IsAudioStreamValid(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    lua_pushboolean(L, IsAudioStreamValid(*stream));
    return 1;
}

int lua_UnloadAudioStream(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    UnloadAudioStream(*stream);
    return 0;
}

int lua_UpdateAudioStream(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    const void *data = lua_touserdata(L, 2);
    int frameCount = luaL_checkinteger(L, 3);
    UpdateAudioStream(*stream, data, frameCount);
    return 0;
}

int lua_IsAudioStreamProcessed(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    lua_pushboolean(L, IsAudioStreamProcessed(*stream));
    return 1;
}

int lua_PlayAudioStream(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    PlayAudioStream(*stream);
    return 0;
}

int lua_PauseAudioStream(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    PauseAudioStream(*stream);
    return 0;
}

int lua_ResumeAudioStream(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    ResumeAudioStream(*stream);
    return 0;
}

int lua_IsAudioStreamPlaying(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    lua_pushboolean(L, IsAudioStreamPlaying(*stream));
    return 1;
}

int lua_StopAudioStream(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    StopAudioStream(*stream);
    return 0;
}

int lua_SetAudioStreamVolume(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    float volume = luaL_checknumber(L, 2);
    SetAudioStreamVolume(*stream, volume);
    return 0;
}

int lua_SetAudioStreamPitch(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    float pitch = luaL_checknumber(L, 2);
    SetAudioStreamPitch(*stream, pitch);
    return 0;
}

int lua_SetAudioStreamPan(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    float pan = luaL_checknumber(L, 2);
    SetAudioStreamPan(*stream, pan);
    return 0;
}

int lua_SetAudioStreamBufferSizeDefault(lua_State *L) {
    int size = luaL_checkinteger(L, 1);
    SetAudioStreamBufferSizeDefault(size);
    return 0;
}

int lua_AttachAudioStreamProcessor(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    AttachAudioStreamProcessor(*stream, audioStreamProcessorWrapper);
    return 0;
}

int lua_DetachAudioStreamProcessor(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    DetachAudioStreamProcessor(*stream, audioStreamProcessorWrapper);
    return 0;
}

int lua_AttachAudioMixedProcessor(lua_State *L) {
    AttachAudioMixedProcessor(audioMixedProcessorWrapper);
    return 0;
}

int lua_DetachAudioMixedProcessor(lua_State *L) {
    DetachAudioMixedProcessor(audioMixedProcessorWrapper);
    return 0;
}

int lua_SetAudioStreamCallback(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    SetAudioStreamCallback(*stream, audioStreamCallbackWrapper);
    return 0;
}

void audioStreamProcessorWrapper(void *buffer, unsigned int frames) {
    lua_getglobal(globalLuaState, "audioStreamProcessorWrapper");
    lua_pushlightuserdata(globalLuaState, buffer);
    lua_pushinteger(globalLuaState, frames);
    lua_pcall(globalLuaState, 2, 0, 0);
}

void audioMixedProcessorWrapper(void *buffer, unsigned int frames) {
    lua_getglobal(globalLuaState, "audioMixedProcessorWrapper");
    lua_pushlightuserdata(globalLuaState, buffer);
    lua_pushinteger(globalLuaState, frames);
    lua_pcall(globalLuaState, 2, 0, 0);
}

void audioStreamCallbackWrapper(void *buffer, unsigned int frames) {
    lua_getglobal(globalLuaState, "audioStreamCallbackWrapper");
    lua_pushlightuserdata(globalLuaState, buffer);
    lua_pushinteger(globalLuaState, frames);
    lua_pcall(globalLuaState, 2, 0, 0);
}