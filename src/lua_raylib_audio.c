#include <stdio.h>
#include "lua_raylib_audio.h"
#include "raylib_wrappers.h"

lua_State *globalLuaState = NULL;

static void detach_stream_slots(lua_State *L, const AudioStream *stream);

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
    memset(sound, 0, sizeof(*sound));  // prevent use-after-free if reused
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
    const void *data = get_data_buffer(L, 2);
    int sampleCount = luaL_checkinteger(L, 3);
    UpdateSound(*sound, data, sampleCount);
    return 0;
}

int lua_UnloadWave(lua_State *L) {
    Wave *wave = luaL_checkudata(L, 1, "Wave");
    UnloadWave(*wave);
    memset(wave, 0, sizeof(*wave));  // prevent use-after-free if reused
    return 0;
}

int lua_UnloadSoundAlias(lua_State *L) {
    Sound *alias = luaL_checkudata(L, 1, "Sound");
    UnloadSoundAlias(*alias);
    memset(alias, 0, sizeof(*alias));  // prevent use-after-free if reused
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
    memset(music, 0, sizeof(*music));  // prevent use-after-free if reused
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
    if (stream->buffer != NULL) detach_stream_slots(L, stream);  // free their Lua states
    UnloadAudioStream(*stream);
    memset(stream, 0, sizeof(*stream));  // prevent use-after-free if reused
    return 0;
}

int lua_UpdateAudioStream(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    const void *data = get_data_buffer(L, 2);
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

// ---------------------------------------------------------------------------
// Audio processors and stream callbacks
//
// raylib invokes these on its audio thread while holding its internal audio
// mutex. The script's lua_State must never be touched from that thread, so each
// Lua handler is copied (lua_dump + load) into a private lua_State that only the
// audio thread ever runs. Handlers therefore cannot capture upvalues and do not
// see the script's globals; they keep their own state in their own globals.
//
// raylib identifies callbacks by function pointer and passes no user data, so a
// fixed pool of C trampolines maps 1:1 onto slots. Attach/Detach and
// SetAudioStreamCallback take the same mutex raylib holds while calling
// handlers, so once a detach returns the slot's handler is not running and its
// private state can be closed.
// ---------------------------------------------------------------------------

#define AUDIO_SLOT_COUNT 16
#define AUDIO_PROCESSOR_CHANNELS 2   // processors always get stereo float frames
#define SAMPLE_BUFFER_MT "AudioSampleBuffer"

typedef enum {
    AUDIO_SLOT_FREE = 0,
    AUDIO_SLOT_STREAM_PROCESSOR,
    AUDIO_SLOT_MIXED_PROCESSOR,
    AUDIO_SLOT_STREAM_CALLBACK
} AudioSlotKind;

// Samples handed to a handler: indexable 1..#buf, valid only during the call.
typedef struct {
    void *data;
    lua_Integer count;
    unsigned int sampleSize;   // bits: 8 (unsigned), 16 (signed), 32 (float)
} SampleBuffer;

typedef struct {
    AudioSlotKind kind;
    lua_State *L;              // private state, run only on the audio thread
    int handlerRef;            // handler, in L's registry
    SampleBuffer *samples;     // reusable buffer userdata, anchored in L's registry
    int ownerRef;              // original function, in the script state's registry
    AudioStream stream;        // stream the slot is bound to (zeroed for mixed)
    unsigned int channels;
    int failed;                // set on the audio thread after a handler error
} AudioSlot;

static AudioSlot audioSlots[AUDIO_SLOT_COUNT];

static void run_audio_slot(int index, void *data, unsigned int frames) {
    AudioSlot *slot = &audioSlots[index];
    size_t bytes = (size_t)frames*slot->channels*(slot->samples ? slot->samples->sampleSize/8 : 0);

    if (slot->L == NULL || slot->failed) {
        // A stream callback must fill the buffer: silence beats garbage.
        if (slot->kind == AUDIO_SLOT_STREAM_CALLBACK) memset(data, 0, bytes);
        return;
    }

    lua_State *L = slot->L;
    slot->samples->data = data;
    slot->samples->count = (lua_Integer)frames*slot->channels;

    lua_rawgeti(L, LUA_REGISTRYINDEX, slot->handlerRef);
    lua_pushlightuserdata(L, slot->samples);
    lua_rawget(L, LUA_REGISTRYINDEX);
    lua_pushinteger(L, frames);
    lua_pushinteger(L, slot->channels);
    if (lua_pcall(L, 3, 0, 0) != LUA_OK) {
        // Not TraceLog: a Lua-side SetTraceLogCallback would re-enter the
        // script state from this thread.
        fprintf(stderr, "raylib-lua: audio handler failed and was disabled: %s\n",
                lua_tostring(L, -1));
        lua_pop(L, 1);
        slot->failed = 1;
        if (slot->kind == AUDIO_SLOT_STREAM_CALLBACK) memset(data, 0, bytes);
    }

    // A handler that stashed the buffer must not reach freed memory later.
    slot->samples->data = NULL;
    slot->samples->count = 0;
}

#define AUDIO_TRAMPOLINE(n) \
    static void audio_trampoline_##n(void *data, unsigned int frames) { run_audio_slot(n, data, frames); }
AUDIO_TRAMPOLINE(0)  AUDIO_TRAMPOLINE(1)  AUDIO_TRAMPOLINE(2)  AUDIO_TRAMPOLINE(3)
AUDIO_TRAMPOLINE(4)  AUDIO_TRAMPOLINE(5)  AUDIO_TRAMPOLINE(6)  AUDIO_TRAMPOLINE(7)
AUDIO_TRAMPOLINE(8)  AUDIO_TRAMPOLINE(9)  AUDIO_TRAMPOLINE(10) AUDIO_TRAMPOLINE(11)
AUDIO_TRAMPOLINE(12) AUDIO_TRAMPOLINE(13) AUDIO_TRAMPOLINE(14) AUDIO_TRAMPOLINE(15)

static AudioCallback const audioTrampolines[AUDIO_SLOT_COUNT] = {
    audio_trampoline_0,  audio_trampoline_1,  audio_trampoline_2,  audio_trampoline_3,
    audio_trampoline_4,  audio_trampoline_5,  audio_trampoline_6,  audio_trampoline_7,
    audio_trampoline_8,  audio_trampoline_9,  audio_trampoline_10, audio_trampoline_11,
    audio_trampoline_12, audio_trampoline_13, audio_trampoline_14, audio_trampoline_15,
};

// --- SampleBuffer metamethods (run inside the private state) ---------------

static SampleBuffer *check_sample_index(lua_State *L, lua_Integer *i) {
    SampleBuffer *buf = luaL_checkudata(L, 1, SAMPLE_BUFFER_MT);
    *i = lua_isinteger(L, 2) ? lua_tointeger(L, 2) : 0;
    return buf;
}

static int sample_buffer_index(lua_State *L) {
    lua_Integer i;
    SampleBuffer *buf = check_sample_index(L, &i);
    if (buf->data == NULL || i < 1 || i > buf->count) { lua_pushnil(L); return 1; }
    switch (buf->sampleSize) {
        case 8:  lua_pushinteger(L, ((unsigned char *)buf->data)[i - 1]); break;
        case 16: lua_pushinteger(L, ((short *)buf->data)[i - 1]); break;
        default: lua_pushnumber(L, ((float *)buf->data)[i - 1]); break;
    }
    return 1;
}

static int sample_buffer_newindex(lua_State *L) {
    lua_Integer i;
    SampleBuffer *buf = check_sample_index(L, &i);
    lua_Number v = luaL_checknumber(L, 3);
    if (buf->data == NULL || i < 1 || i > buf->count)
        return luaL_error(L, "sample index %d out of range (1..%d)", (int)i, (int)buf->count);
    switch (buf->sampleSize) {
        case 8:
            if (v < 0) v = 0; else if (v > 255) v = 255;
            ((unsigned char *)buf->data)[i - 1] = (unsigned char)v;
            break;
        case 16:
            if (v < -32768) v = -32768; else if (v > 32767) v = 32767;
            ((short *)buf->data)[i - 1] = (short)v;
            break;
        default:
            ((float *)buf->data)[i - 1] = (float)v;
            break;
    }
    return 0;
}

static int sample_buffer_len(lua_State *L) {
    SampleBuffer *buf = luaL_checkudata(L, 1, SAMPLE_BUFFER_MT);
    lua_pushinteger(L, buf->count);
    return 1;
}

static const luaL_Reg sample_buffer_meta[] = {
    {"__index", sample_buffer_index},
    {"__newindex", sample_buffer_newindex},
    {"__len", sample_buffer_len},
    {NULL, NULL}
};

// --- Slot management (script thread only) ----------------------------------

typedef struct {
    char *data;
    size_t size, cap;
} DumpBuffer;

static int dump_writer(lua_State *L, const void *p, size_t sz, void *ud) {
    DumpBuffer *b = ud;
    if (sz == 0) return 0;
    if (b->size + sz > b->cap) {
        size_t cap = b->cap ? b->cap : 1024;
        while (cap < b->size + sz) cap *= 2;
        char *grown = realloc(b->data, cap);
        if (grown == NULL) return 1;
        b->data = grown;
        b->cap = cap;
    }
    memcpy(b->data + b->size, p, sz);
    b->size += sz;
    return 0;
}

// The handler is moved into another lua_State, so it may only reference
// globals (its _ENV upvalue becomes the private state's globals on load).
static void check_audio_handler(lua_State *L, int idx) {
    luaL_checktype(L, idx, LUA_TFUNCTION);
    if (lua_iscfunction(L, idx))
        luaL_argerror(L, idx, "audio handler must be a Lua function");
    for (int n = 1; ; n++) {
        const char *name = lua_getupvalue(L, idx, n);
        if (name == NULL) break;
        lua_pop(L, 1);
        if (strcmp(name, "_ENV") != 0)
            luaL_argerror(L, idx, lua_pushfstring(L,
                "audio handler cannot capture local '%s': it runs in a separate "
                "Lua state on the audio thread (keep its state in globals)", name));
    }
}

// Copies the handler at idx into a fresh slot. Raises a Lua error (leaving no
// slot claimed) on failure; the caller then attaches the slot's trampoline.
static int acquire_audio_slot(lua_State *L, int idx, AudioSlotKind kind,
                              const AudioStream *stream, unsigned int channels,
                              unsigned int sampleSize) {
    int index = -1;
    for (int i = 0; i < AUDIO_SLOT_COUNT; i++) {
        if (audioSlots[i].kind == AUDIO_SLOT_FREE) { index = i; break; }
    }
    if (index < 0) return luaL_error(L, "too many audio handlers attached (max %d)", AUDIO_SLOT_COUNT);

    DumpBuffer dump = { 0 };
    lua_pushvalue(L, idx);
    int dumpStatus = lua_dump(L, dump_writer, &dump, 0);
    lua_pop(L, 1);
    if (dumpStatus != 0) {
        free(dump.data);
        return luaL_error(L, "could not copy audio handler");
    }

    lua_State *A = luaL_newstate();
    if (A == NULL) {
        free(dump.data);
        return luaL_error(L, "could not create audio handler state");
    }
    luaL_openlibs(A);
    int loadStatus = luaL_loadbufferx(A, dump.data, dump.size, "=audio handler", "b");
    free(dump.data);
    if (loadStatus != LUA_OK) {
        lua_pushstring(L, lua_tostring(A, -1));
        lua_close(A);
        return lua_error(L);
    }

    AudioSlot *slot = &audioSlots[index];
    memset(slot, 0, sizeof(*slot));
    slot->handlerRef = luaL_ref(A, LUA_REGISTRYINDEX);

    luaL_newmetatable(A, SAMPLE_BUFFER_MT);
    luaL_setfuncs(A, sample_buffer_meta, 0);
    lua_pop(A, 1);
    slot->samples = lua_newuserdatauv(A, sizeof(SampleBuffer), 0);
    memset(slot->samples, 0, sizeof(SampleBuffer));
    slot->samples->sampleSize = sampleSize;
    luaL_setmetatable(A, SAMPLE_BUFFER_MT);
    // registry[lightuserdata(samples)] = samples: anchors it and lets the
    // audio thread push it without an extra ref field.
    lua_pushlightuserdata(A, slot->samples);
    lua_insert(A, -2);
    lua_rawset(A, LUA_REGISTRYINDEX);

    lua_pushvalue(L, idx);
    slot->ownerRef = luaL_ref(L, LUA_REGISTRYINDEX);
    if (stream != NULL) slot->stream = *stream;
    slot->channels = channels;
    slot->L = A;
    slot->kind = kind;
    return index;
}

static void release_audio_slot(lua_State *L, int index) {
    AudioSlot *slot = &audioSlots[index];
    if (slot->L != NULL) lua_close(slot->L);
    luaL_unref(L, LUA_REGISTRYINDEX, slot->ownerRef);
    memset(slot, 0, sizeof(*slot));
}

// Finds the slot of `kind` bound to `stream` (NULL: any) whose original
// function is the value at fnIdx (0: any). Returns -1 if none.
static int find_audio_slot(lua_State *L, AudioSlotKind kind, const AudioStream *stream, int fnIdx) {
    for (int i = 0; i < AUDIO_SLOT_COUNT; i++) {
        AudioSlot *slot = &audioSlots[i];
        if (slot->kind != kind) continue;
        if (stream != NULL && slot->stream.buffer != stream->buffer) continue;
        if (fnIdx != 0) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, slot->ownerRef);
            int same = lua_rawequal(L, -1, fnIdx);
            lua_pop(L, 1);
            if (!same) continue;
        }
        return i;
    }
    return -1;
}

static void detach_stream_slots(lua_State *L, const AudioStream *stream) {
    int i;
    while ((i = find_audio_slot(L, AUDIO_SLOT_STREAM_PROCESSOR, stream, 0)) >= 0) {
        DetachAudioStreamProcessor(*stream, audioTrampolines[i]);
        release_audio_slot(L, i);
    }
    if ((i = find_audio_slot(L, AUDIO_SLOT_STREAM_CALLBACK, stream, 0)) >= 0) {
        SetAudioStreamCallback(*stream, NULL);
        release_audio_slot(L, i);
    }
}

static AudioStream *check_loaded_stream(lua_State *L, int idx) {
    AudioStream *stream = luaL_checkudata(L, idx, "AudioStream");
    if (stream->buffer == NULL) luaL_argerror(L, idx, "audio stream is not loaded");
    return stream;
}

// processor(samples, frames, channels): samples are stereo floats, edited in place.
int lua_AttachAudioStreamProcessor(lua_State *L) {
    AudioStream *stream = check_loaded_stream(L, 1);
    check_audio_handler(L, 2);
    int i = acquire_audio_slot(L, 2, AUDIO_SLOT_STREAM_PROCESSOR, stream, AUDIO_PROCESSOR_CHANNELS, 32);
    AttachAudioStreamProcessor(*stream, audioTrampolines[i]);
    return 0;
}

int lua_DetachAudioStreamProcessor(lua_State *L) {
    AudioStream *stream = luaL_checkudata(L, 1, "AudioStream");
    luaL_checktype(L, 2, LUA_TFUNCTION);
    int i = find_audio_slot(L, AUDIO_SLOT_STREAM_PROCESSOR, stream, 2);
    if (i >= 0) {
        DetachAudioStreamProcessor(*stream, audioTrampolines[i]);
        release_audio_slot(L, i);
    }
    return 0;
}

int lua_AttachAudioMixedProcessor(lua_State *L) {
    check_audio_handler(L, 1);
    int i = acquire_audio_slot(L, 1, AUDIO_SLOT_MIXED_PROCESSOR, NULL, AUDIO_PROCESSOR_CHANNELS, 32);
    AttachAudioMixedProcessor(audioTrampolines[i]);
    return 0;
}

int lua_DetachAudioMixedProcessor(lua_State *L) {
    luaL_checktype(L, 1, LUA_TFUNCTION);
    int i = find_audio_slot(L, AUDIO_SLOT_MIXED_PROCESSOR, NULL, 1);
    if (i >= 0) {
        DetachAudioMixedProcessor(audioTrampolines[i]);
        release_audio_slot(L, i);
    }
    return 0;
}

// callback(samples, frames, channels): fill samples in the stream's own format
// (8-bit unsigned, 16-bit signed or 32-bit float). nil removes the callback.
int lua_SetAudioStreamCallback(lua_State *L) {
    AudioStream *stream = check_loaded_stream(L, 1);
    int old = find_audio_slot(L, AUDIO_SLOT_STREAM_CALLBACK, stream, 0);

    if (lua_isnoneornil(L, 2)) {
        SetAudioStreamCallback(*stream, NULL);
    } else {
        check_audio_handler(L, 2);
        if (stream->sampleSize != 8 && stream->sampleSize != 16 && stream->sampleSize != 32)
            return luaL_argerror(L, 1, "stream sample size must be 8, 16 or 32");
        int i = acquire_audio_slot(L, 2, AUDIO_SLOT_STREAM_CALLBACK, stream,
                                   stream->channels, stream->sampleSize);
        SetAudioStreamCallback(*stream, audioTrampolines[i]);  // replaces any old one
    }

    if (old >= 0) release_audio_slot(L, old);
    return 0;
}