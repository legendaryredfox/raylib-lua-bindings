// lua_raylib_rlgl_buffers.c
//
// Handwritten rlgl bindings for functions that take or return buffers, arrays or
// render batches. The scalar ones are generated into lua_raylib_rlgl.c.
//
// Conventions:
//  * data in:  a Lua string (or a raw pointer userdata); nil means NULL where rlgl
//              allows it. String sizes are validated against what rlgl will read.
//  * data out: returned as a Lua string; the temporary C buffer is released here.
//  * arrays:   Lua tables of numbers / Matrix tables, copied into GC-managed memory.

#include <string.h>
#include <limits.h>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <lua.h>
#include <lauxlib.h>
#include "raylib_wrappers.h"

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static int check_nonneg_int(lua_State *L, int arg) {
    lua_Integer v = luaL_checkinteger(L, arg);
    luaL_argcheck(L, v >= 0 && v <= INT_MAX, arg, "value must be a non-negative int");
    return (int)v;
}

static int check_positive_int(lua_State *L, int arg) {
    lua_Integer v = luaL_checkinteger(L, arg);
    luaL_argcheck(L, v > 0 && v <= INT_MAX, arg, "value must be a positive int");
    return (int)v;
}

static unsigned int check_uint(lua_State *L, int arg) {
    lua_Integer v = luaL_checkinteger(L, arg);
    luaL_argcheck(L, v >= 0 && v <= (lua_Integer)UINT_MAX, arg, "value out of range for an unsigned int");
    return (unsigned int)v;
}

// Optional data argument: nil -> NULL, otherwise a buffer holding at least `need` bytes.
static const void *opt_data(lua_State *L, int arg, size_t need) {
    if (lua_isnoneornil(L, arg)) return NULL;
    return get_data_buffer_checked(L, arg, need);
}

// Pixel data size of one image/texture level; GetPixelDataSize returns 0 for unknown formats.
static size_t pixel_size(int width, int height, int format) {
    int s = GetPixelDataSize(width, height, format);
    return s > 0 ? (size_t)s : 0;
}

// Reads n numbers from the table at `arg` into out[0..n); errors if it is too short.
static void read_numbers(lua_State *L, int arg, int n, double *out) {
    luaL_checktype(L, arg, LUA_TTABLE);
    luaL_argcheck(L, (lua_Integer)luaL_len(L, arg) >= n, arg, "table has fewer values than required");
    for (int i = 0; i < n; i++) {
        lua_rawgeti(L, arg, i + 1);
        out[i] = luaL_checknumber(L, -1);
        lua_pop(L, 1);
    }
}

// ---------------------------------------------------------------------------
// Matrix
// ---------------------------------------------------------------------------

// Accepts a Matrix table (m0..m15) or an array of 16 numbers in column-major order.
static int rlw_rlMultMatrixf(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    float f[16];
    if (luaL_len(L, 1) == 16) {
        double v[16];
        read_numbers(L, 1, 16, v);
        for (int i = 0; i < 16; i++) f[i] = (float)v[i];
    } else {
        float16 m = MatrixToFloatV(get_matrix_from_table(L, 1));
        memcpy(f, m.v, sizeof f);
    }
    rlMultMatrixf(f);
    return 0;
}

// ---------------------------------------------------------------------------
// Render batches: userdata "rlRenderBatch"; the active batch is anchored in the
// registry so rlgl never keeps a pointer into collected memory.
// ---------------------------------------------------------------------------

static rlRenderBatch *active_batch = NULL;
static int active_batch_ref = LUA_NOREF;

static rlRenderBatch *check_batch(lua_State *L, int arg) {
    rlRenderBatch *b = luaL_checkudata(L, arg, "rlRenderBatch");
    luaL_argcheck(L, b->vertexBuffer != NULL, arg, "render batch was already unloaded");
    return b;
}

static void clear_active_batch(lua_State *L) {
    rlSetRenderBatchActive(NULL);
    luaL_unref(L, LUA_REGISTRYINDEX, active_batch_ref);
    active_batch_ref = LUA_NOREF;
    active_batch = NULL;
}

static int rlw_rlLoadRenderBatch(lua_State *L) {
    int numBuffers = check_positive_int(L, 1);
    int bufferElements = check_positive_int(L, 2);
    rlRenderBatch *p = lua_newuserdata(L, sizeof(rlRenderBatch));
    *p = rlLoadRenderBatch(numBuffers, bufferElements);
    luaL_setmetatable(L, "rlRenderBatch");
    return 1;
}

static int rlw_rlUnloadRenderBatch(lua_State *L) {
    rlRenderBatch *b = luaL_checkudata(L, 1, "rlRenderBatch");
    if (b->vertexBuffer == NULL) return 0;          // already unloaded: no-op
    if (b == active_batch) clear_active_batch(L);
    rlUnloadRenderBatch(*b);
    memset(b, 0, sizeof *b);
    return 0;
}

static int rlw_rlDrawRenderBatch(lua_State *L) {
    rlDrawRenderBatch(check_batch(L, 1));
    return 0;
}

// rlSetRenderBatchActive(batch) or rlSetRenderBatchActive(nil) for the default batch
static int rlw_rlSetRenderBatchActive(lua_State *L) {
    if (lua_isnoneornil(L, 1)) {
        clear_active_batch(L);
        return 0;
    }
    rlRenderBatch *b = check_batch(L, 1);
    rlSetRenderBatchActive(b);
    luaL_unref(L, LUA_REGISTRYINDEX, active_batch_ref);
    lua_pushvalue(L, 1);
    active_batch_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    active_batch = b;
    return 0;
}

// ---------------------------------------------------------------------------
// Vertex buffers and attributes
// ---------------------------------------------------------------------------

// rlLoadVertexBuffer(data|nil, size, dynamic)
static int rlw_rlLoadVertexBuffer(lua_State *L) {
    int size = check_nonneg_int(L, 2);
    const void *data = opt_data(L, 1, (size_t)size);
    lua_pushinteger(L, rlLoadVertexBuffer(data, size, lua_toboolean(L, 3)));
    return 1;
}

static int rlw_rlLoadVertexBufferElement(lua_State *L) {
    int size = check_nonneg_int(L, 2);
    const void *data = opt_data(L, 1, (size_t)size);
    lua_pushinteger(L, rlLoadVertexBufferElement(data, size, lua_toboolean(L, 3)));
    return 1;
}

// rlUpdateVertexBuffer(id, data, dataSize, offset)
static int rlw_rlUpdateVertexBuffer(lua_State *L) {
    unsigned int id = check_uint(L, 1);
    int dataSize = check_nonneg_int(L, 3);
    int offset = check_nonneg_int(L, 4);
    rlUpdateVertexBuffer(id, get_data_buffer_checked(L, 2, (size_t)dataSize), dataSize, offset);
    return 0;
}

static int rlw_rlUpdateVertexBufferElements(lua_State *L) {
    unsigned int id = check_uint(L, 1);
    int dataSize = check_nonneg_int(L, 3);
    int offset = check_nonneg_int(L, 4);
    rlUpdateVertexBufferElements(id, get_data_buffer_checked(L, 2, (size_t)dataSize), dataSize, offset);
    return 0;
}

// rlSetVertexAttributeDefault(locIndex, {values}, attribType, count): count floats, 1..4
static int rlw_rlSetVertexAttributeDefault(lua_State *L) {
    int locIndex = check_nonneg_int(L, 1);
    int attribType = (int)luaL_checkinteger(L, 3);
    int count = (int)luaL_checkinteger(L, 4);
    luaL_argcheck(L, count >= 1 && count <= 4, 4, "count must be 1..4");
    double v[4];
    read_numbers(L, 2, count, v);
    float f[4] = { (float)v[0], (float)v[1], (float)v[2], (float)v[3] };
    rlSetVertexAttributeDefault(locIndex, f, attribType, count);
    return 0;
}

// rlDrawVertexArrayElements(offset, count [, indices]): indices are 16-bit values packed in a
// Lua string; nil uses the currently bound element buffer.
static int rlw_rlDrawVertexArrayElements(lua_State *L) {
    int offset = check_nonneg_int(L, 1);
    int count = check_nonneg_int(L, 2);
    const void *buffer = opt_data(L, 3, ((size_t)offset + (size_t)count) * sizeof(unsigned short));
    rlDrawVertexArrayElements(offset, count, buffer);
    return 0;
}

static int rlw_rlDrawVertexArrayElementsInstanced(lua_State *L) {
    int offset = check_nonneg_int(L, 1);
    int count = check_nonneg_int(L, 2);
    int instances = check_nonneg_int(L, 4);
    const void *buffer = opt_data(L, 3, ((size_t)offset + (size_t)count) * sizeof(unsigned short));
    rlDrawVertexArrayElementsInstanced(offset, count, buffer, instances);
    return 0;
}

// ---------------------------------------------------------------------------
// Textures
// ---------------------------------------------------------------------------

// rlLoadTexture(data|nil, width, height, format, mipmapCount)
static int rlw_rlLoadTexture(lua_State *L) {
    int width = check_positive_int(L, 2);
    int height = check_positive_int(L, 3);
    int format = (int)luaL_checkinteger(L, 4);
    int mipmaps = check_positive_int(L, 5);
    luaL_argcheck(L, mipmaps <= 32, 5, "too many mipmap levels");
    size_t need = 0;
    int w = width, h = height;
    for (int i = 0; i < mipmaps; i++) {          // rlgl walks the whole mip chain
        need += pixel_size(w, h, format);
        if (w > 1) w /= 2;
        if (h > 1) h /= 2;
    }
    const void *data = opt_data(L, 1, need);
    lua_pushinteger(L, rlLoadTexture(data, width, height, format, mipmaps));
    return 1;
}

// rlLoadTextureCubemap(data|nil, size, format, mipmapCount): six faces, one after another
static int rlw_rlLoadTextureCubemap(lua_State *L) {
    int size = check_positive_int(L, 2);
    int format = (int)luaL_checkinteger(L, 3);
    int mipmaps = check_positive_int(L, 4);
    luaL_argcheck(L, mipmaps <= 32, 4, "too many mipmap levels");
    const void *data = opt_data(L, 1, 6 * pixel_size(size, size, format));
    lua_pushinteger(L, rlLoadTextureCubemap(data, size, format, mipmaps));
    return 1;
}

// rlUpdateTexture(id, offsetX, offsetY, width, height, format, data)
static int rlw_rlUpdateTexture(lua_State *L) {
    unsigned int id = check_uint(L, 1);
    int offsetX = check_nonneg_int(L, 2);
    int offsetY = check_nonneg_int(L, 3);
    int width = check_positive_int(L, 4);
    int height = check_positive_int(L, 5);
    int format = (int)luaL_checkinteger(L, 6);
    rlUpdateTexture(id, offsetX, offsetY, width, height, format,
                    get_data_buffer_checked(L, 7, pixel_size(width, height, format)));
    return 0;
}

// rlGetGlTextureFormats(format) -> glInternalFormat, glFormat, glType
static int rlw_rlGetGlTextureFormats(lua_State *L) {
    int format = (int)luaL_checkinteger(L, 1);
    unsigned int internal = 0, glFormat = 0, glType = 0;
    rlGetGlTextureFormats(format, &internal, &glFormat, &glType);
    lua_pushinteger(L, internal);
    lua_pushinteger(L, glFormat);
    lua_pushinteger(L, glType);
    return 3;
}

// rlGenTextureMipmaps(id, width, height, format) -> mipmap count
static int rlw_rlGenTextureMipmaps(lua_State *L) {
    unsigned int id = check_uint(L, 1);
    int width = check_positive_int(L, 2);
    int height = check_positive_int(L, 3);
    int format = (int)luaL_checkinteger(L, 4);
    int mipmaps = 0;
    rlGenTextureMipmaps(id, width, height, format, &mipmaps);
    lua_pushinteger(L, mipmaps);
    return 1;
}

// rlReadTexturePixels(id, width, height, format) -> string of pixel data (nil on failure)
static int rlw_rlReadTexturePixels(lua_State *L) {
    unsigned int id = check_uint(L, 1);
    int width = check_positive_int(L, 2);
    int height = check_positive_int(L, 3);
    int format = (int)luaL_checkinteger(L, 4);
    size_t size = pixel_size(width, height, format);
    void *pixels = rlReadTexturePixels(id, width, height, format);
    if (pixels == NULL) { lua_pushnil(L); return 1; }
    lua_pushlstring(L, (const char *)pixels, size);
    MemFree(pixels);
    return 1;
}

// rlReadScreenPixels(width, height) -> RGBA string (width*height*4 bytes)
static int rlw_rlReadScreenPixels(lua_State *L) {
    int width = check_positive_int(L, 1);
    int height = check_positive_int(L, 2);
    unsigned char *pixels = rlReadScreenPixels(width, height);
    if (pixels == NULL) { lua_pushnil(L); return 1; }
    lua_pushlstring(L, (const char *)pixels, (size_t)width * (size_t)height * 4);
    MemFree(pixels);
    return 1;
}

// rlCopyFramebuffer(x, y, width, height, format) -> string of pixel data
static int rlw_rlCopyFramebuffer(lua_State *L) {
    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    int width = check_positive_int(L, 3);
    int height = check_positive_int(L, 4);
    int format = (int)luaL_checkinteger(L, 5);
    size_t size = pixel_size(width, height, format);
    luaL_argcheck(L, size > 0, 5, "unknown pixel format");
    void *pixels = lua_newuserdatauv(L, size, 0);
    memset(pixels, 0, size);
    rlCopyFramebuffer(x, y, width, height, format, pixels);
    lua_pushlstring(L, (const char *)pixels, size);
    return 1;
}

// ---------------------------------------------------------------------------
// Shaders and shader storage buffers
// ---------------------------------------------------------------------------

static int uniform_components(int type) {
    switch (type) {
        case RL_SHADER_UNIFORM_FLOAT: case RL_SHADER_UNIFORM_INT:
        case RL_SHADER_UNIFORM_UINT:  case RL_SHADER_UNIFORM_SAMPLER2D: return 1;
        case RL_SHADER_UNIFORM_VEC2:  case RL_SHADER_UNIFORM_IVEC2:
        case RL_SHADER_UNIFORM_UIVEC2: return 2;
        case RL_SHADER_UNIFORM_VEC3:  case RL_SHADER_UNIFORM_IVEC3:
        case RL_SHADER_UNIFORM_UIVEC3: return 3;
        case RL_SHADER_UNIFORM_VEC4:  case RL_SHADER_UNIFORM_IVEC4:
        case RL_SHADER_UNIFORM_UIVEC4: return 4;
        default: return 0;
    }
}

// rlSetUniform(locIndex, value, uniformType, count): value is a number or a flat table of
// count * components(uniformType) numbers
static int rlw_rlSetUniform(lua_State *L) {
    int locIndex = (int)luaL_checkinteger(L, 1);
    int type = (int)luaL_checkinteger(L, 3);
    int count = check_positive_int(L, 4);
    int comps = uniform_components(type);
    luaL_argcheck(L, comps > 0, 3, "unknown uniform type");
    luaL_argcheck(L, count <= 4096, 4, "count too large");
    int n = comps * count;
    int is_float = type == RL_SHADER_UNIFORM_FLOAT || type == RL_SHADER_UNIFORM_VEC2 ||
                   type == RL_SHADER_UNIFORM_VEC3 || type == RL_SHADER_UNIFORM_VEC4;
    double *v = lua_newuserdatauv(L, sizeof(double) * (size_t)n, 0);
    if (lua_isnumber(L, 2) && n == 1) v[0] = lua_tonumber(L, 2);
    else read_numbers(L, 2, n, v);
    void *buf = lua_newuserdatauv(L, sizeof(float) * (size_t)n, 0);
    if (is_float) {
        float *f = buf;
        for (int i = 0; i < n; i++) f[i] = (float)v[i];
    } else if (type == RL_SHADER_UNIFORM_INT || type == RL_SHADER_UNIFORM_IVEC2 ||
               type == RL_SHADER_UNIFORM_IVEC3 || type == RL_SHADER_UNIFORM_IVEC4 ||
               type == RL_SHADER_UNIFORM_SAMPLER2D) {
        int *iv = buf;
        for (int i = 0; i < n; i++) iv[i] = (int)v[i];
    } else {
        unsigned int *uv = buf;
        for (int i = 0; i < n; i++) uv[i] = (unsigned int)v[i];
    }
    rlSetUniform(locIndex, buf, type, count);
    return 0;
}

// rlSetUniformMatrices(locIndex, {matrix, matrix, ...})
static int rlw_rlSetUniformMatrices(lua_State *L) {
    int locIndex = (int)luaL_checkinteger(L, 1);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_Integer count = luaL_len(L, 2);
    luaL_argcheck(L, count > 0 && count <= 4096, 2, "expected 1..4096 matrices");
    Matrix *mats = lua_newuserdatauv(L, sizeof(Matrix) * (size_t)count, 0);
    for (lua_Integer i = 0; i < count; i++) {
        lua_rawgeti(L, 2, i + 1);
        mats[i] = get_matrix_from_table(L, -1);
        lua_pop(L, 1);
    }
    rlSetUniformMatrices(locIndex, mats, (int)count);
    return 0;
}

// rlLoadShaderBuffer(size, data|nil, usageHint)
static int rlw_rlLoadShaderBuffer(lua_State *L) {
    unsigned int size = check_uint(L, 1);
    int usageHint = (int)luaL_checkinteger(L, 3);
    const void *data = opt_data(L, 2, size);
    lua_pushinteger(L, rlLoadShaderBuffer(size, data, usageHint));
    return 1;
}

// rlUpdateShaderBuffer(id, data, dataSize, offset)
static int rlw_rlUpdateShaderBuffer(lua_State *L) {
    unsigned int id = check_uint(L, 1);
    unsigned int dataSize = check_uint(L, 3);
    unsigned int offset = check_uint(L, 4);
    rlUpdateShaderBuffer(id, get_data_buffer_checked(L, 2, dataSize), dataSize, offset);
    return 0;
}

// rlReadShaderBuffer(id, count, offset) -> string of `count` bytes
static int rlw_rlReadShaderBuffer(lua_State *L) {
    unsigned int id = check_uint(L, 1);
    unsigned int count = check_uint(L, 2);
    unsigned int offset = check_uint(L, 3);
    void *dest = lua_newuserdatauv(L, count > 0 ? count : 1, 0);
    memset(dest, 0, count > 0 ? count : 1);
    rlReadShaderBuffer(id, dest, count, offset);
    lua_pushlstring(L, (const char *)dest, count);
    return 1;
}

// ---------------------------------------------------------------------------

static const luaL_Reg rlgl_buffer_functions[] = {
    {"rlMultMatrixf", rlw_rlMultMatrixf},
    {"rlLoadRenderBatch", rlw_rlLoadRenderBatch},
    {"rlUnloadRenderBatch", rlw_rlUnloadRenderBatch},
    {"rlDrawRenderBatch", rlw_rlDrawRenderBatch},
    {"rlSetRenderBatchActive", rlw_rlSetRenderBatchActive},
    {"rlLoadVertexBuffer", rlw_rlLoadVertexBuffer},
    {"rlLoadVertexBufferElement", rlw_rlLoadVertexBufferElement},
    {"rlUpdateVertexBuffer", rlw_rlUpdateVertexBuffer},
    {"rlUpdateVertexBufferElements", rlw_rlUpdateVertexBufferElements},
    {"rlSetVertexAttributeDefault", rlw_rlSetVertexAttributeDefault},
    {"rlDrawVertexArrayElements", rlw_rlDrawVertexArrayElements},
    {"rlDrawVertexArrayElementsInstanced", rlw_rlDrawVertexArrayElementsInstanced},
    {"rlLoadTexture", rlw_rlLoadTexture},
    {"rlLoadTextureCubemap", rlw_rlLoadTextureCubemap},
    {"rlUpdateTexture", rlw_rlUpdateTexture},
    {"rlGetGlTextureFormats", rlw_rlGetGlTextureFormats},
    {"rlGenTextureMipmaps", rlw_rlGenTextureMipmaps},
    {"rlReadTexturePixels", rlw_rlReadTexturePixels},
    {"rlReadScreenPixels", rlw_rlReadScreenPixels},
    {"rlCopyFramebuffer", rlw_rlCopyFramebuffer},
    {"rlSetUniform", rlw_rlSetUniform},
    {"rlSetUniformMatrices", rlw_rlSetUniformMatrices},
    {"rlLoadShaderBuffer", rlw_rlLoadShaderBuffer},
    {"rlUpdateShaderBuffer", rlw_rlUpdateShaderBuffer},
    {"rlReadShaderBuffer", rlw_rlReadShaderBuffer},
    {NULL, NULL}
};

void register_raylib_rlgl_buffers(lua_State *L) {
    luaL_newmetatable(L, "rlRenderBatch");
    lua_pushcfunction(L, rlw_rlUnloadRenderBatch);
    lua_setfield(L, -2, "__close");              // local b <close> = rlLoadRenderBatch(...)
    lua_pop(L, 1);
    luaL_setfuncs(L, rlgl_buffer_functions, 0);
}
