# AGENTS.md: raylib-lua-bindings

C shared library exposing [Raylib](https://www.raylib.com/) 6.2 as a Lua 5.5 module (`require("raylib")`). Output: `raylib.so` (Linux) / `raylib.dll` (Windows, MinGW). Vendored sources: `raylib/` (Raylib 6.2), `lua/` (Lua 5.5.1). Updating them: replace the dir, refresh the `include/` copies of `raylib.h`/`raymath.h`/`rlgl.h`/`lua*.h`/`lauxlib.h`/`luaconf.h` (`-Iinclude` wins over the vendored `src/` dirs), then `make distclean && make`.

## Layout

- `src/lua_raylib.c`: entry `luaopen_raylib`, color constants, `raylib_functions` table.
- `src/lua_raylib_core.c` (window, input, cursor, monitor, clipboard, time, FPS), `_draw.c` (2D primitives), `_shapes.c` (splines, 2D collision), `_textures.c` (image/texture, color utils), `_models.c` (3D, ray casts), `_text.c` (fonts, text, UTF-8), `_audio.c` (sound, music, streams, processors), `_extra.c` (render modes, cameras, shaders, gamepad/gesture/touch, filesystem/paths, compression/base64, random, logging, dirs, draw extras).
- `src/raylib_wrappers.c`: struct <-> Lua table helpers. `include/`: one header per `src/` file plus vendored headers.
- `examples/basic_window.lua`, `main.lua` (440 Hz audio stream demo), `makefile`.

## Build and test

```bash
make              # builds vendored libraylib.a/liblua.a with -fPIC if missing, then the module
make test         # LUA_CPATH="./?.so" lua tests/runner.lua
make clean | make distclean   # distclean also cleans raylib/src and lua/src
```

GCC (MinGW on Windows). Linux links `-lraylib -llua -lX11 -lm -lpthread`; Windows `-lgdi32 -lwinmm`. `*.a` is gitignored.

Tests (`tests/test_*.lua`, ~430 checks, no window needed) cover text, hashing, color, image userdata, filesystem, extra utils, safety (hardened readers, zero-on-unload, error paths), and audio handler validation. Rendering, GPU textures, audio playback, and input are verified by running example scripts.

## Architecture

- `luaopen_raylib`: sets `globalLuaState` (used by main-thread file I/O and trace-log callbacks in `_extra.c`, never by audio), calls `register_raylib_metatables` (one named metatable per userdata type; must run before any binding or `luaL_checkudata` rejects everything), registers `raylib_functions`, then `register_raylib_colors` (named colors as `{r,g,b,a}` tables on the module and as globals).
- Binding pattern: `luaL_check*` args, call Raylib, push results, return count.
- Structs <-> tables via `lua_getfield`/`lua_setfield` only (never `pushstring + gettable`). Helpers: `get_<type>_from_table(L, i)`, `push_<type>_to_table(L, v)` (vector2/3/4, rectangle, color, bounding_box, ray_collision). New rectangle args use `get_rectangle_arg`.
- Opaque types are **userdata with named metatables**: Image (`push_image_to_userdata`; every Image-returning binding yields userdata), Texture2D (canonical name everywhere), Model, Sound, Music, AudioStream, Shader, Camera.
- `_extra.c` functions are `static`, registered by `register_extra(L)`; add new ones to `extra_functions[]` (no change to `lua_raylib.c`).
- `Camera` (3D) is userdata from `CreateCamera3D(position, target, up, fovy, projection)`; `UpdateCamera` mutates it. `Camera2D` is a table `{offset, target, rotation, zoom}`. `Matrix` tables use `m0`..`m15`.
- Colors: table `{r,g,b,a}` or packed `0xRRGGBBAA` (`convert_color`); `check_color` in `_draw.c` accepts both.
- **Audio handlers** (`AttachAudioStreamProcessor`, `AttachAudioMixedProcessor`, `SetAudioStreamCallback`) run on raylib's audio thread, so each handler is `lua_dump`ed into a private `lua_State` in one of 16 `audioSlots[]` with its own C trampoline. Called as `handler(samples, frames, channels)`; `samples` is an `AudioSampleBuffer` valid only during the call. No upvalues except `_ENV`, no script globals or raylib module. Detach with the same function. Attach/Detach take `AUDIO.System.lock`. Errors disable the slot and print to stderr (not `TraceLog`, to avoid re-entering the script state).

## Memory ownership (critical for new bindings)

- Userdata (Sound, Music, Texture, Model, ...) is GC-managed; scripts must call the matching `Unload*`.
- Static-buffer strings, never free: `TextToUpper/Lower/Pascal/Snake/Camel`, `TextJoin`, `TextSplit`, `TextReplace`, `TextInsert`, `TextReplaceBetween`.
- Heap strings, `MemFree()` after pushing: `TextReplaceAlloc`, `TextInsertAlloc`, `TextReplaceBetweenAlloc`.
- `ExportImageToMemory`: `MemFree()`, not `UnloadImageColors`.
- `get_vector2_array_from_table` returns a Lua-managed userdata buffer (pinned on the stack); never `free()` it.
- `LoadMaterials` / `LoadModelAnimations`: each element is shallow-copied into its own userdata; the binding `MemFree`s only the container. Never call `UnloadMaterial`/`UnloadModelAnimations` on the source. Scripts release elements with `UnloadMaterial` / `UnloadModelAnimation`.
- `UnloadModelAnimation(anim)` (singular, ours) uses `unload_one_model_animation` to free `keyframePoses`. Never use raylib's plural `UnloadModelAnimations` on one userdata (it frees Lua-owned memory).
- Raw data buffers (`UpdateSound`, `UpdateAudioStream`, `UpdateTexture`, `UpdateTextureRec`, `UpdateMeshBuffer`): use `get_data_buffer` (Lua string or raw pointer), never `lua_touserdata` (NULL for strings).

## Adding a binding

1. Declare it in `include/lua_raylib_*.h`.
2. Implement it in the matching `src/lua_raylib_*.c`, following the rules above.
3. Register it in `raylib_functions` (`src/lua_raylib.c`) or `extra_functions[]` (`_extra.c`).
4. `make && make test`. Add a test when the binding works without a window.

## Quirks and API notes

- `FileCopy` / `FileMove` return 0 on success (Raylib 6.2; 6.0 returned 1 / -1). `ChangeDirectory` returns int in 6.2; the binding still pushes a boolean.
- `DrawCapsule` / `DrawCapsuleWires` args are `(rings, slices)` (6.2 order). `ImageColorContrast` takes an int.
- 6.2 renames keep the old Lua name as an alias: `GetSplinePointBezierQuad` -> `...Quadratic`, `ImageDrawTriangleEx` -> `ImageDrawTriangleGradient`. `ImageDraw` (rectangle form) maps to `ImageDrawImagePro`; `ImageDrawRectangleLines` takes either the rec table form (-> `...LinesEx`) or `(x, y, w, h, color)`.
- Constants (`src/lua_raylib_constants.c`, includes the `RL_*` rlgl constants) and raymath (`src/lua_raylib_math.c`) are **generated** by `tools/gen_constants.py` / `tools/gen_raymath.py`; never hand-edit, rerun after a raylib bump (CI checks they are in sync). Resource metatables get `__close` -> matching `Unload*` in `register_close_metamethods`.
- rlgl: `src/lua_raylib_rlgl.c` is GENERATED by `tools/gen_rlgl.py` (scalar/string/Matrix functions); buffer/array/batch functions are handwritten in `src/lua_raylib_rlgl_buffers.c` and must be listed in the generator's `MANUAL` set (the generator fails if an rlgl function is in neither `MANUAL`, `UNSUPPORTED` nor wrappable, so a raylib bump cannot drop one silently). Buffers validate sizes via `get_data_buffer_checked`; outputs come back as Lua strings and C buffers are freed. The active render batch is anchored in the registry; unloading it deactivates it first. Never expose functions that keep a C pointer past the call (`rlSetShader`, `rlEnableStatePointer`).
- `make test-gl` / `make examples` need a GL context: they run under `xvfb-run`. Examples exit after `EXAMPLE_FRAMES` frames.
- `GetRenderTextureTexture(rt)` is ours (not raylib): returns a Texture2D sharing the render texture's GL id; never `UnloadTexture` it.
- 6.2 additions (`IsFileHidden`, `IsPathAbsolute`, `IsPathDirectory`, `Draw*LinesEx`, `DrawTriangleGradient`, `LoadRenderTextureEx`, `ImageDraw*` family) live in `_extra.c`; tests in `tests/test_raylib62.lua`.
- `ColorAlpha(color, f)` replaces alpha with `255*f`.
- `GetTargetFPS` doesn't exist in Raylib; it delegates to `GetFPS()`.
- `DrawCircleGradient(center: Vector2, radius, inner, outer)`.
- Dual-form signatures: `DrawRectangleLines`, `DrawRectangleGradientEx`, `ImageCrop`, `UpdateTextureRec` take raylib's Rectangle form and still accept the older four-number forms.
- `GetCodepointPrevious(text [, pos])`: optional 1-based byte position, bounded by string start.
- VSCode autocomplete extension: `LegendaryRedfox.raylib-lua-bindings-autocomplete`.
