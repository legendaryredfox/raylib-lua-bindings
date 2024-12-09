# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Ilua/src -Iraylib/src -I/lua/src -fPIC

# Platform-specific settings
ifeq ($(OS),Windows_NT)
    LDFLAGS = -Lraylib -lraylib -Llua -llua -lgdi32 -lwinmm
    OUTPUT = raylib.dll
    RM = del /f /q
    EXT = .dll
else
    LDFLAGS = -Lraylib -lraylib -L/usr/lib/x86_64-linux-gnu -llua5.4 -lX11 -lm -lpthread -fPIC -I/usr/include/lua5.4
    OUTPUT = raylib.so
    RM = rm -f
    EXT = .so
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
            $(SRC_DIR)/raylib_wrappers.c

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Build target
all: $(OUTPUT)

# Link object files into a shared library
$(OUTPUT): $(OBJ_FILES)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	$(RM) $(OBJ_FILES) $(OUTPUT)
