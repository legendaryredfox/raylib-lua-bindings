# AGENTS.md — raylib-lua-bindings

## Project overview

This project is a C shared library that exposes [Raylib](https://www.raylib.com/) (a simple, C-based game development framework) as a Lua 5.5 module. It is loaded with `require("raylib")` from any Lua script, giving the script access to Raylib's drawing, audio, texture, model, text, and input APIs without writing any C.

The output artifact is a single shared library (`raylib.so` on Linux, `raylib.dll` on Windows) that Lua's dynamic loader picks up at runtime.

## Repository layout

```
raylib-lua-bindings/
├── src/                    # C source for every binding module
│   ├── lua_raylib.c        # Entry point: luaopen_raylib, color constants, function table
│   ├── lua_raylib_core.c   # Window, input, cursor, monitor, clipboard, time, FPS
│   ├── lua_raylib_draw.c   # 2D primitives: rectangles, circles, lines, polygons, grids
│   ├── lua_raylib_shapes.c # Shape helpers, splines, 2D collision checks
│   ├── lua_raylib_textures.c # Image load/save/transform, texture management, color utils
│   ├── lua_raylib_models.c # 3D mesh/model/material/animation, 3D collision, ray casts
│   ├── lua_raylib_text.c   # Font loading, text drawing, text measurement, UTF-8 helpers
│   ├── lua_raylib_audio.c  # Sound, music streams, audio streams, audio processors
│   ├── lua_raylib_extra.c  # Added bindings: render modes, camera, shaders, input, filesystem, data utils
│   └── raylib_wrappers.c   # Shared C helpers: struct ↔ Lua table conversion
├── include/                # Header for every src/ file + vendored raylib.h / lua headers
├── lua/                    # Vendored Lua 5.5.0 source tree
├── raylib/                 # Vendored Raylib source tree
├── examples/
│   └── basic_window.lua    # Minimal "Hello World" Lua script
├── main.lua                # Audio streaming demo: 440 Hz tone via UpdateAudioStream
└── makefile                # Cross-platform build (Linux + Windows/MinGW)
```

## Build system

The project uses a plain GNU `makefile`.

| Target | Effect |
|--------|--------|
| `make` | Build vendored raylib/Lua if missing, compile all `src/*.c` to `.o`, link into `raylib.so` / `raylib.dll` |
| `make test` | Run Lua unit test suite (`tests/runner.lua`) |
| `make clean` | Remove object files and the shared library |
| `make distclean` | `clean`, plus `make -C raylib/src clean` and `make -C lua/src clean` |

Compiler: **GCC** (Linux native, MinGW on Windows).

Key flags:
- `-fPIC` — required for shared libraries on Linux.
- `-Iinclude -Ilua/src -Iraylib/src` — include paths for vendored headers.
- Linux link: `-Lraylib/src -lraylib -Llua/src -llua -lX11 -lm -lpthread` — uses vendored static libs.
- Windows link: `-Lraylib/src -lraylib -Llua/src -llua -lgdi32 -lwinmm`

Both static libraries (`raylib/src/libraylib.a`, `lua/src/liblua.a`) are **built from the vendored sources** by the makefile on first `make` (with `-fPIC`), so no system installation is required. No `.a`/`.lib` files are committed (`*.a` is gitignored).

## Architecture

### Module entry point (`src/lua_raylib.c`)

`luaopen_raylib` is the single Lua C module entry point. It:
1. Sets `globalLuaState = L` so the main-thread file I/O and trace-log callbacks
   in `lua_raylib_extra.c` can reach the Lua state. (Audio handlers never use it;
   see Audio handlers below.)
2. Calls `register_raylib_metatables` to create one named metatable per userdata
   type (`Image`, `Texture2D`, `Sound`, `Model`, …). These must exist before any
   binding runs — `luaL_setmetatable` / `luaL_checkudata` rely on them to tag and
   type-check objects. (Without them, `setmetatable` attaches a nil metatable and
   every `checkudata` rejects its argument.)
3. Registers all wrapped functions via a `luaL_Reg` table.
4. Calls `register_raylib_colors` to push Raylib's named colour constants (e.g. `RAYWHITE`, `RED`) onto the module table (`raylib.RAYWHITE`) and as Lua globals.

### Binding pattern

Each source module follows the same pattern:

```c
int lua_SomeName(lua_State *L) {
    // 1. Pull arguments off the Lua stack with luaL_check* helpers
    // 2. Call the underlying Raylib C function
    // 3. Push return value(s) onto the stack
    return <number of return values>;
}
```

### Struct ↔ Lua table conversion (`src/raylib_wrappers.c`)

Raylib structs are passed between C and Lua as plain tables with named fields. All
helpers use `lua_setfield` / `lua_getfield` exclusively (never the older
`lua_pushstring + lua_settable/gettable` pattern).

| Convention | Direction | Examples |
|---|---|---|
| `get_<type>_from_table(L, index)` | Lua → C | `get_color_from_table`, `get_vector3_from_table`, `get_ray_from_table` |
| `push_<type>_to_table(L, value)` | C → Lua | `push_vector2_to_table`, `push_rectangle_to_table`, `push_ray_collision_to_table` |

Available push helpers: `push_vector2/3/4_to_table`, `push_rectangle_to_table`,
`push_color_to_table`, `push_bounding_box_to_table`, `push_ray_collision_to_table`.
Images are pushed with `push_image_to_userdata` — an Image is **userdata**, not a
table, so every `Image`-returning binding (`LoadImage`, the `GenImage*` family,
`ImageCopy`, …) yields the same type that `ImageDraw*`/`UnloadImage` expect.

Complex opaque types (Image, Texture2D, Model, Sound, Music, AudioStream, etc.)
are stored as **Lua userdata** with a named metatable (e.g. `"Image"`, `"Sound"`).
The canonical texture metatable name is `"Texture2D"` everywhere (load → draw →
unload). Every type in this set gets its metatable from `register_raylib_metatables`
(which also registers `"Shader"`).

### Extra bindings module (`src/lua_raylib_extra.c`)

A large batch of bindings (render-state mode pairs, 3D/2D camera + coordinate
transforms, the shader subsystem, gamepad/gesture/touch input, filesystem & path
helpers, data compression / base64, random sequences, logging, directory listing,
audio playback control, and 3D/2D draw extras) lives in `lua_raylib_extra.c`. Its
functions are `static` and registered as a group by `register_extra(L)`, which
`luaL_setfuncs` them onto the module table created by `luaopen_raylib` (called
right after `luaL_newlib`). To add more there, append to its `extra_functions[]`
table — no change to `lua_raylib.c` is needed.

`Camera` (3D) is **userdata** (`"Camera"`); build one with `CreateCamera3D(position,
target, up, fovy, projection)` so it can be passed to `BeginMode3D` / `UpdateCamera`
(which mutates it in place) / `DrawBillboard`. `Camera2D` is a plain table
`{offset, target, rotation, zoom}`. `Matrix` ↔ table uses fields `m0`..`m15`.

### Colour representation

Colours can be passed to API functions in two ways:

- As a Lua table `{r=255, g=0, b=0, a=255}` — read by `get_color_from_table`.
- As a packed 32-bit integer `0xRRGGBBAA` — unpacked by `convert_color(int)`.

The `check_color` helper in `lua_raylib_draw.c` transparently accepts both forms,
so callers of `ClearBackground` and `DrawRectangle` can use either.

Named colours (`RAYWHITE`, `RED`, …) are `{r,g,b,a}` tables pushed by
`register_raylib_colors` in `lua_raylib.c` from its `raylib_colors[]` table, both as
module fields (`raylib.RED`) and as globals (`RED`).

### Audio handlers (`src/lua_raylib_audio.c`)

`AttachAudioStreamProcessor`, `AttachAudioMixedProcessor` and `SetAudioStreamCallback`
take a Lua function that raylib calls on its **audio thread**. The script's
`lua_State` must never run there, so each handler is copied (`lua_dump` + load) into
its own private `lua_State` in one of 16 slots (`audioSlots[]`). raylib callbacks get
no user data, so each slot has its own C trampoline (`audioTrampolines[]`).

- Handlers are called as `handler(samples, frames, channels)`. `samples` is an
  `AudioSampleBuffer` userdata, indexable `1..#samples` and valid only during the call.
  Processors get stereo floats; stream callbacks get the stream's own format (8/16/32-bit).
- Handlers may not capture upvalues other than `_ENV` (rejected at attach time) and do
  not see the script's globals; they keep state in their own globals.
- Detach by passing the same function value; slots are matched by function and stream.
- raylib holds `AUDIO.System.lock` while calling handlers, and Attach/Detach/
  `SetAudioStreamCallback` take the same lock, so a slot's state is closed only after
  raylib has stopped calling it. `UnloadAudioStream` releases the stream's slots.
- A handler error disables that slot and prints to stderr (not `TraceLog`, which could
  re-enter the script state through a Lua trace-log callback).

## Memory ownership rules

These rules are critical when adding new bindings:

- **Raylib userdata** (Sound, Music, Texture, Model, …): stored in Lua userdata;
  lifetime managed by the Lua GC. Always call the corresponding `Unload*` function
  before the userdata is collected.
- **Raylib static-buffer strings** (`TextToUpper`, `TextToLower`, `TextToPascal`,
  `TextToSnake`, `TextToCamel`, `TextJoin`, `TextSplit`): return pointers into
  internal static buffers. **Do not call `free()` or `MemFree()` on them.**
- **Raylib heap strings** (`TextReplace`, `TextInsert`): return newly allocated
  memory. **Use `MemFree()` after pushing to Lua.**
- **`ExportImageToMemory`**: returns a heap buffer. **Use `MemFree()`, not
  `UnloadImageColors`.**
- **`get_vector2_array_from_table`**: allocates with `malloc`; the caller must
  `free()` the returned pointer after use.
- **`LoadMaterials` / `LoadModelAnimations`**: each element is shallow-copied into
  its own userdata, which then owns that element's internal allocations. The
  binding `MemFree`s only the array container raylib returned — it must NOT call
  `UnloadMaterial` / `UnloadModelAnimations` on the source (that would free data
  the userdata copies still point at). The Lua caller releases each element with
  `UnloadMaterial` / `UnloadModelAnimation`.
- **`UnloadModelAnimation`**: use the singular `UnloadModelAnimation(anim)` on a
  userdata. raylib 6.0 has **no** singular `UnloadModelAnimation`, so the binding
  uses a static helper (`unload_one_model_animation`) that frees only the
  `keyframePoses` rows and array (`ModelAnimation` has `keyframeCount` /
  `keyframePoses`, no `bones` field). The plural `UnloadModelAnimations` must NOT
  be used on a single userdata — it also `RL_FREE`s the pointer, which is
  Lua-owned userdata memory (heap corruption).
- **Raw data buffers** (`UpdateSound`, `UpdateAudioStream`, `UpdateTexture`,
  `UpdateTextureRec`, `UpdateMeshBuffer`): resolve the data argument with
  `get_data_buffer`, which accepts a Lua binary string (the usual case) or a raw
  pointer. Do not use `lua_touserdata` directly — a Lua string yields NULL there
  and raylib then dereferences it.

## Adding a new binding

1. Declare the C function in the appropriate `include/lua_raylib_*.h` header.
2. Implement it in the matching `src/lua_raylib_*.c` file:
   - Use `lua_getfield` / `lua_setfield` for struct field access (never `lua_pushstring + lua_gettable`).
   - Use `push_ray_collision_to_table` for `RayCollision` returns; `push_bounding_box_to_table` for `BoundingBox` returns.
   - Respect the memory ownership rules above.
3. Register it in the `raylib_functions` table inside `src/lua_raylib.c`.
4. Run `make` — no other changes needed.

## Lua usage

```lua
local raylib = require("raylib")

raylib.InitWindow(800, 450, "My Game")
raylib.SetTargetFPS(60)

while not raylib.WindowShouldClose() do
    raylib.BeginDrawing()
    raylib.ClearBackground(RAYWHITE)          -- named colour constant (table)
    raylib.ClearBackground(0xF5F5F5FF)        -- packed integer also accepted
    raylib.DrawText("Hello!", 100, 150, 20, {r=0, g=0, b=0, a=255})
    raylib.EndDrawing()
end

raylib.CloseWindow()
```

Run any script with the standard Lua interpreter, ensuring `raylib.so` / `raylib.dll`
is on Lua's `package.cpath`.

## VSCode autocomplete

A companion extension provides autocomplete for all bound functions:
https://marketplace.visualstudio.com/items?itemName=LegendaryRedfox.raylib-lua-bindings-autocomplete

## Testing

Tests live in `tests/` and are plain Lua scripts. Run with:

```bash
make test
# or directly:
LUA_CPATH="./?.so" lua tests/runner.lua
```

| File | What it covers |
|------|----------------|
| `tests/runner.lua` | Minimal harness; loads and runs all suites; exits non-zero on failure |
| `tests/test_text.lua` | `TextLength`, `TextIsEqual`, `TextToUpper/Lower`, `TextSubtext`, `TextReplace*`, `TextInsert*`, `TextJoin`, `TextSplit`, `TextFindIndex`, case converters, `GetCodepoint*` (incl. bounded `GetCodepointPrevious`), `CodepointToUTF8`, `TextCopy`, `TextAppend`, and more |
| `tests/test_hashing.lua` | `ComputeCRC32`, `ComputeMD5`, `ComputeSHA1`, `ComputeSHA256` — fixed expected values |
| `tests/test_color.lua` | `ColorToInt`, `ColorNormalize`, `ColorFromNormalized`, `ColorToHSV`, `ColorFromHSV`, `ColorTint`, `ColorAlpha`, `ColorBrightness`, `GetRandomValue`, named colours (`raylib.RAYWHITE` and globals) |
| `tests/test_image.lua` | Image userdata round-trips: `GenImageColor`/`GenImageChecked` return userdata, `IsImageValid`, `GetImageColor`, `ImageCopy`, `ImageColorInvert`, `ImageCrop` (table and four-number forms), distinct-metatable type rejection, `UnloadImage` |
| `tests/test_filesystem.lua` | `MakeDirectory`, `IsFileNameValid`, `FileCopy`, `FileRemove`, `FileRename`, `FileMove`, `GetDirectoryFileCount` |
| `tests/test_extra.lua` | `TextToInteger/Float`, path utilities, `Load/SaveFileData/Text`, `Compress/DecompressData`, `Encode/DecodeDataBase64`, `LoadRandomSequence`, `LoadDirectoryFiles`, `ExportDataAsCode` |
| `tests/test_safety.lua` | Hardened array readers, zero-on-unload, Base64 round-trip, error paths that previously leaked or crashed |
| `tests/test_audio.lua` | Audio handler validation: C-function and upvalue rejection, no-op detach (no audio device needed) |

All 271 checks run without a window. CPU-side image operations are covered; bindings that need a GL context or audio device (rendering, hardware textures, audio playback, input) are not — those are verified by running example scripts.

### Known test quirks

- `FileCopy` returns **1** on success (stores `SaveFileData`'s `bool` return directly).
- `FileMove` always returns **-1** in Raylib 6.0 due to a bug: it checks `FileCopy == 0` to detect success, but `FileCopy` returns 1 on success. The destination file is still created correctly.
- `ColorAlpha(color, factor)` sets alpha to `(int)(255 * factor)` — the original alpha is replaced, not scaled.

## Known limitations / open issues

- Audio handlers run in isolated Lua states: no upvalues, no access to the script's
  globals or the raylib module, at most 16 attached at once.
- GPU/audio-dependent bindings (rendering, hardware textures, audio playback, input) require a window or audio device and are verified by running example scripts; everything window-free is covered by the `tests/` suite (see Testing).
- The library ships with vendored **Raylib 6.0** and **Lua 5.5.0** sources; updating them means replacing `raylib/` / `lua/` and running `make distclean && make`.
- `GetTargetFPS` is exposed in the Lua API but Raylib does not have that function; it currently delegates to `GetFPS()` instead.
- `DrawCircleGradient` Lua API changed in this update: now takes `(center: Vector2, radius, inner, outer)` instead of `(centerX, centerY, radius, inner, outer)`.
- `TextReplace`/`TextInsert` are now static-buffer returns (no allocation); use `TextReplaceAlloc`/`TextInsertAlloc` for heap-allocated results.
- Dual-form signatures: `DrawRectangleLines`, `DrawRectangleGradientEx`, `ImageCrop` and
  `UpdateTextureRec` take raylib's form (Rectangle table; no `lineThick`), but still accept
  the older binding forms (four numbers for the rectangle; `DrawRectangleLines(x, y, w, h,
  lineThick, color)`). New rectangle arguments should use `get_rectangle_arg`.
- `GetCodepointPrevious(text [, pos])` takes an optional 1-based byte position and is
  bounded by the start of the string (raylib's own function is not).
