# Compiler and flags
CC = gcc
# -Wall -Wextra surface real bugs (uninitialized use, sign mismatches, etc.).
# -Wno-unused-parameter keeps the noise down: every Lua C function takes
# (lua_State *L) whether or not it uses it. Override with `make CFLAGS=...`.
CFLAGS = -Iinclude -Ilua/src -Iraylib/src -fPIC -O2 -Wall -Wextra -Wno-unused-parameter

# Vendored static libraries, built from raylib/ and lua/ on first `make`
RAYLIB_LIB = raylib/src/libraylib.a
LUA_LIB = lua/src/liblua.a

# Platform-specific settings
ifeq ($(OS),Windows_NT)
    LDFLAGS = -Lraylib/src -lraylib -Llua/src -llua -lgdi32 -lwinmm
    OUTPUT = raylib.dll
    RM = del /f /q
    EXT = .dll
    LUA_SYSCFLAGS =
else
    LDFLAGS = -Lraylib/src -lraylib -Llua/src -llua -lX11 -lm -lpthread -fPIC
    OUTPUT = raylib.so
    RM = rm -f
    EXT = .so
    LUA_SYSCFLAGS = -DLUA_USE_LINUX
endif

# Directories
SRC_DIR = src
INCLUDE_DIR = include

# Source files
SRC_FILES = $(SRC_DIR)/lua_raylib.c \
            $(SRC_DIR)/lua_raylib_core.c \
            $(SRC_DIR)/lua_raylib_draw.c \
            $(SRC_DIR)/lua_raylib_audio.c \
            $(SRC_DIR)/lua_raylib_textures.c \
            $(SRC_DIR)/lua_raylib_models.c \
            $(SRC_DIR)/lua_raylib_text.c \
            $(SRC_DIR)/lua_raylib_shapes.c \
            $(SRC_DIR)/lua_raylib_extra.c \
            $(SRC_DIR)/raylib_wrappers.c

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Build target
all: $(OUTPUT)

# Link object files into a shared library
$(OUTPUT): $(OBJ_FILES) $(RAYLIB_LIB) $(LUA_LIB)
	$(CC) -shared -o $@ $(OBJ_FILES) $(LDFLAGS)

# -fPIC: both archives are linked into a shared library
$(RAYLIB_LIB):
	$(MAKE) -C raylib/src PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=STATIC CUSTOM_CFLAGS=-fPIC

$(LUA_LIB):
	$(MAKE) -C lua/src a SYSCFLAGS="$(LUA_SYSCFLAGS)" MYCFLAGS=-fPIC

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run unit tests (requires lua 5.5 on PATH)
test: $(OUTPUT)
	LUA_CPATH="./?.so" lua tests/runner.lua

# Clean build files
clean:
	$(RM) $(OBJ_FILES) $(OUTPUT)

# Also clean the vendored raylib and Lua builds
distclean: clean
	$(MAKE) -C raylib/src clean
	$(MAKE) -C lua/src clean

.PHONY: all test clean distclean
