![logo](images/logo.png)

# Raylib-Lua Bindings (WIP)

This project provides bindings for **Raylib** (a simple and easy-to-use game development library) to be used with **Lua**, a powerful, efficient, lightweight scripting language. With this binding, you can use Raylib's functionalities directly from Lua scripts, enabling rapid development of games and graphical applications.

## Features

- **Simple Lua bindings** for Raylib
- Includes bindings for **drawing**, **audio**, **textures**, **models**, **shaders**, **3D/2D cameras**, **gamepad/gesture/touch input**, **filesystem & data utilities**, and more
- Colors as `{r,g,b,a}` tables or named constants (`RED`, `RAYWHITE`, …); `ClearBackground` and `DrawRectangle` additionally accept a packed `0xRRGGBBAA` integer
- Autocomplete available for VSCode: https://marketplace.visualstudio.com/items?itemName=LegendaryRedfox.raylib-lua-bindings-autocomplete
- Easily extendable: Add more bindings as you go!

## Prerequisites

Before building this project, ensure you have the following software installed:

### On Linux: (Work still in progress)

1. **GCC**: C compiler used for compiling the bindings.
2. **Make**: A tool to automate the build process.
3. **libX11** development headers (usually `libx11-dev`).

Raylib 6.0 and Lua 5.5.0 are **vendored** as static libraries — no system installation required.

### On Windows:

1. **GCC (MinGW)**: C compiler used for compiling the bindings.
2. **Make**: A tool to automate the build process.

> **Note**: Windows users must supply a Lua 5.5.0 `lua.lib` (the vendored one is for Lua 5.4) and a Raylib 6.0 import library.

### Additional Libraries (for both platforms):

- **Raylib** development files
- **Lua** development files

## Installation

### 1. Clone the repository

```bash
git clone https://github.com/yourusername/raylib-lua-bindings.git
cd raylib-lua-bindings
```

### 2. Install dependencies

#### On Linux:

I'm still working on that

#### On Windows:

Download and install MinGW (GCC for Windows).
Download Raylib and Lua (make sure to install the development headers).

### 3. Build the project

Run the following command to compile and create the shared library:

```bash
make
```

This will generate the appropriate shared library file:

**Linux: libraylib.so**
**Windows: raylib.dll**

### 4. Using the bindings

In your Lua script, you can require the Raylib bindings as follows:

```lua
local raylib = require("raylib")

-- Initialize the window
raylib.InitWindow(800, 600, "Raylib Lua Example")

-- Main game loop
while not raylib.WindowShouldClose() do
    raylib.BeginDrawing()
    raylib.ClearBackground(DARKGRAY)                          -- named color constant
    raylib.DrawText("Hello, Raylib and Lua!", 10, 10, 20, DARKGREEN)
    raylib.EndDrawing()
end

-- Close window
raylib.CloseWindow()
```

Colors are passed as a named constant or a `{r,g,b,a}` table. A packed 32-bit
integer (`0xRRGGBBAA`) is *additionally* accepted by `ClearBackground` and
`DrawRectangle`; every other function expects a table or named constant:

```lua
raylib.ClearBackground(RAYWHITE)                      -- named constant (a table)
raylib.ClearBackground({r=245, g=245, b=245, a=255})  -- explicit table
raylib.ClearBackground(0xF5F5F5FF)                    -- packed int (ClearBackground/DrawRectangle only)
raylib.DrawText("hi", 10, 10, 20, RAYWHITE)           -- other calls need a table/constant
```

### 5. Running tests

The suite (227 checks) covers text utilities and parsing, hashing (CRC32/MD5/SHA1/SHA256), color utilities, CPU-side image operations (generate/inspect/copy/transform), filesystem & path helpers, data (de)compression and base64, and random sequences — everything that runs without an open window.

```bash
make test
```

Tests are plain Lua scripts in `tests/` run against the bundled `raylib.so`. The only requirement is a Lua 5.5 interpreter on `PATH`.

### 6. Cleaning up

To remove the object files and shared library:

```bash
make clean
```

This will delete the compiled object files and the generated shared library (libraylib.so or raylib.dll).

| Make target | Effect |
|-------------|--------|
| `make` | Compile all sources, link `raylib.so` / `raylib.dll` |
| `make test` | Run the Lua unit test suite |
| `make clean` | Remove object files and the shared library |

### Known Issues

- The project works well on Windows; Linux support is in progress and some features may not behave correctly.
- Audio stream processor callbacks dispatch to fixed Lua global function names, so only one processor of each type can be active at a time.
- Raylib objects (textures, images, sounds, fonts, models, …) are returned as userdata and must be released with the matching `Unload*`; they are not garbage-collected automatically.
- Contributions to help resolve these issues are highly welcome.

### Contributing

If you would like to contribute, please feel free to fork the repository, submit issues, and create pull requests.

- Fork the repository
- Create a feature branch
- Commit your changes
- Push to the branch
- Open a pull request
