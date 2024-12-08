# Raylib-Lua Bindings (WIP)

This project provides bindings for **Raylib** (a simple and easy-to-use game development library) to be used with **Lua**, a powerful, efficient, lightweight scripting language. With this binding, you can use Raylib's functionalities directly from Lua scripts, enabling rapid development of games and graphical applications.

## Features

- **Simple Lua bindings** for Raylib
- Includes bindings for **drawing**, **audio**, **textures**, **models**, and more
- Easily extendable: Add more bindings as you go!

## Prerequisites

Before building this project, ensure you have the following software installed:

### On Linux:

1. **GCC**: C compiler used for compiling Raylib and Lua bindings.
2. **Raylib**: A simple game development library.
3. **Lua 5.4**: The scripting language for which we create bindings.
4. **Make**: A tool to automate the build process.
5. **X11, pthread, and other dependencies** required for linking Raylib on Linux. (support on linux is currently limited)

### On Windows:

1. **GCC (MinGW)**: C compiler used for compiling Raylib and Lua bindings.
2. **Raylib**: A simple game development library.
3. **Lua 5.4**: The scripting language for which we create bindings.
4. **Make**: A tool to automate the build process.

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

Install the necessary libraries:

```bash

sudo apt-get update
sudo apt-get install gcc make liblua5.4-dev libraylib-dev libx11-dev libpthread-stubs0-dev
```

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
raylib.ClearBackground(raylib.DARKGRAY)
raylib.DrawText("Hello, Raylib and Lua!", 10, 10, 20, raylib.DARKGREEN)
raylib.EndDrawing()
end

-- Close window
raylib.CloseWindow()
```

### 5. Cleaning up

To remove the object files and shared library:

```bash
make clean
```

This will delete the compiled object files and the generated shared library (libraylib.so or raylib.dll).

### Known Issues

Currently, the project works well on Windows, but there are issues with it on Linux. Specifically, certain features do not function as expected on Linux, and troubleshooting has been difficult due to a lack of low-level programming experience. Contributions to help resolve these issues are highly welcome.
Contributing

If you would like to contribute, please feel free to fork the repository, submit issues, and create pull requests.

- Fork the repository
- Create a feature branch
- Commit your changes
- Push to the branch
- Open a pull request
