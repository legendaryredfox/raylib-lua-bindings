![logo](images/logo.png)

# Raylib-Lua Bindings (WIP)

This project provides bindings for **Raylib** (a simple and easy-to-use game development library) to be used with **Lua**, a powerful, efficient, lightweight scripting language. With this binding, you can use Raylib's functionalities directly from Lua scripts, enabling rapid development of games and graphical applications.

## Features

- **Simple Lua bindings** for Raylib
- Includes bindings for **drawing**, **audio**, **textures**, **models**, and more
- Colors accepted as `{r,g,b,a}` tables **or** packed `0xRRGGBBAA` integers
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

Color values can be passed as a named constant, a `{r,g,b,a}` table, or a packed
32-bit integer (`0xRRGGBBAA`):

```lua
raylib.ClearBackground(RAYWHITE)               -- named global (table)
raylib.ClearBackground({r=245, g=245, b=245, a=255})  -- explicit table
raylib.ClearBackground(0xF5F5F5FF)             -- packed integer
```

### 5. Running tests

The test suite covers text utilities, hashing functions (CRC32/MD5/SHA1/SHA256), color utilities, and filesystem operations — all functions that don't require an open window.

```bash
make test
```

Tests are pure Lua scripts in `tests/` and use the bundled `raylib.so`. No extra dependencies are needed.

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
- Contributions to help resolve these issues are highly welcome.

### Contributing

If you would like to contribute, please feel free to fork the repository, submit issues, and create pull requests.

- Fork the repository
- Create a feature branch
- Commit your changes
- Push to the branch
- Open a pull request
