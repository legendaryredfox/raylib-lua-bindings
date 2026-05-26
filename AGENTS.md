# AGENTS.md — raylib-lua-bindings

## Project overview

This project is a C shared library that exposes [Raylib](https://www.raylib.com/) (a simple, C-based game development framework) as a Lua 5.4 module. It is loaded with `require("raylib")` from any Lua script, giving the script access to Raylib's drawing, audio, texture, model, text, and input APIs without writing any C.

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
│   └── raylib_wrappers.c   # Shared C helpers: struct ↔ Lua table conversion
├── include/                # Header for every src/ file + vendored raylib.h / lua headers
├── lua/                    # Vendored Lua 5.4 source tree and pre-built .lib files (Windows)
├── raylib/                 # Vendored Raylib source tree
├── examples/
│   └── basic_window.lua    # Minimal "Hello World" Lua script
├── main.lua                # Audio stream processor demo (development scratch file)
├── makefile                # Cross-platform build (Linux + Windows/MinGW)
└── windows_working_mkf     # Snapshot of a known-working Windows makefile
```

## Build system

The project uses a plain GNU `makefile`.

| Target | Effect |
|--------|--------|
| `make` | Compile all `src/*.c` to `.o`, link into `raylib.so` / `raylib.dll` |
| `make test` | Run Lua unit test suite (`tests/runner.lua`) |
| `make clean` | Remove object files and the shared library |

Compiler: **GCC** (Linux native, MinGW on Windows).

Key flags:
- `-fPIC` — required for shared libraries on Linux.
- `-Iinclude -Ilua/src -Iraylib/src` — include paths for vendored headers.
- Linux link: `-Lraylib -lraylib -Llua -llua -lX11 -lm -lpthread` — uses vendored static libs.
- Windows link: `-Lraylib -lraylib -Llua -llua -lgdi32 -lwinmm`

Both Raylib and Lua are linked from **vendored static libraries** (`raylib/libraylib.a`, `lua/liblua.a`), so no system installation is required.

> **Status**: works reliably on Windows. Linux support is in progress; some features may not work correctly.

## Architecture

### Module entry point (`src/lua_raylib.c`)

`luaopen_raylib` is the single Lua C module entry point. It:
1. Sets `globalLuaState = L` so that audio callbacks can reach the Lua state.
2. Registers all wrapped functions via a `luaL_Reg` table.
3. Calls `register_raylib_colors` to push Raylib's named colour constants (e.g. `RAYWHITE`, `RED`) as Lua globals.

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
`push_color_to_table`, `push_image_to_table`, `push_bounding_box_to_table`,
`push_ray_collision_to_table`.

Complex opaque types (Image, Texture, Model, Sound, Music, AudioStream, etc.) are
stored as **Lua userdata** with a named metatable (e.g. `"Image"`, `"Sound"`).

### Colour representation

Colours can be passed to API functions in two ways:

- As a Lua table `{r=255, g=0, b=0, a=255}` — read by `get_color_from_table`.
- As a packed 32-bit integer `0xRRGGBBAA` — unpacked by `convert_color(int)`.

The `check_color` helper in `lua_raylib_draw.c` transparently accepts both forms,
so callers of `ClearBackground` and `DrawRectangle` can use either.

Named colour globals (`RAYWHITE`, `RED`, …) are `{r,g,b,a}` tables pushed by
`register_raylib_colors` in `lua_raylib.c`.

### Audio callbacks (`src/lua_raylib_audio.c`)

Audio stream processors and mixed processors bridge Raylib's C callback system to
Lua. The module stores a `globalLuaState` pointer (set once in `luaopen_raylib`)
and uses fixed Lua global function names (`audioStreamProcessorWrapper`,
`audioMixedProcessorWrapper`, `audioStreamCallbackWrapper`) as the callback targets.

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
| `tests/test_text.lua` | `TextLength`, `TextIsEqual`, `TextToUpper/Lower`, `TextSubtext`, `TextReplace*`, `TextInsert*`, `TextJoin`, `TextSplit`, `TextFindIndex`, case converters, `GetCodepoint*`, `CodepointToUTF8`, `TextCopy`, `TextAppend`, and more |
| `tests/test_hashing.lua` | `ComputeCRC32`, `ComputeMD5`, `ComputeSHA1`, `ComputeSHA256` — fixed expected values |
| `tests/test_color.lua` | `ColorToInt`, `ColorNormalize`, `ColorFromNormalized`, `ColorToHSV`, `ColorFromHSV`, `ColorTint`, `ColorAlpha`, `ColorBrightness`, `GetRandomValue` |
| `tests/test_filesystem.lua` | `MakeDirectory`, `IsFileNameValid`, `FileCopy`, `FileRemove`, `FileRename`, `FileMove`, `GetDirectoryFileCount` |

All 165 tests run without a window. Functions that require `InitWindow` (drawing, audio, textures, input) are not tested — correctness is verified by running example scripts.

### Known test quirks

- `FileCopy` returns **1** on success (stores `SaveFileData`'s `bool` return directly).
- `FileMove` always returns **-1** in Raylib 6.0 due to a bug: it checks `FileCopy == 0` to detect success, but `FileCopy` returns 1 on success. The destination file is still created correctly.
- `ColorAlpha(color, factor)` sets alpha to `(int)(255 * factor)` — the original alpha is replaced, not scaled.

## Known limitations / open issues

- Linux support is incomplete; some bindings may behave incorrectly or crash.
- Audio stream processor callbacks store a single global `lua_State*` and dispatch
  to fixed-name Lua globals — only one processor of each type can be active at a time.
- No automated test suite exists; correctness is verified by running example scripts.
- The library ships with vendored **Raylib 6.0** and **Lua 5.5.0** static libraries; keeping these up to date requires re-downloading and rebuilding the vendored sources.
- `GetTargetFPS` is exposed in the Lua API but Raylib does not have that function; it currently delegates to `GetFPS()` instead.
- Windows pre-built Lua libs (`lua/lua.lib`, `lua/lua54.lib`) are still for Lua 5.4; Windows users must rebuild against Lua 5.5.0.
- `DrawCircleGradient` Lua API changed in this update: now takes `(center: Vector2, radius, inner, outer)` instead of `(centerX, centerY, radius, inner, outer)`.
- `TextReplace`/`TextInsert` are now static-buffer returns (no allocation); use `TextReplaceAlloc`/`TextInsertAlloc` for heap-allocated results.
