# Makefile para compilar e instalar Lua no Windows

# Diretório de origem
SRC_DIR = src

# Variáveis principais
PLAT = windows
CC = gcc
CFLAGS = -O2 -Wall -Wextra -I$(SRC_DIR)
LDFLAGS =
AR = ar rcu
RANLIB = ranlib
RM = del /Q
INSTALL = copy
INSTALL_TOP = .\install
INSTALL_BIN = $(INSTALL_TOP)\bin
INSTALL_INC = $(INSTALL_TOP)\include
INSTALL_LIB = $(INSTALL_TOP)\lib
INSTALL_SHARE = $(INSTALL_TOP)\share\lua\5.4
INSTALL_CMOD = $(INSTALL_TOP)\lib\lua\5.4

# Arquivos
LIB = lua54.lib
DLL = lua54.dll
EXE = lua.exe luac.exe
CORE_O = src/lapi.o src/lcode.o src/lctype.o src/ldebug.o src/ldo.o src/ldump.o \
         src/lfunc.o src/lgc.o src/llex.o src/lmem.o src/lobject.o src/lopcodes.o \
         src/lparser.o src/lstate.o src/lstring.o src/ltable.o src/ltm.o \
         src/lundump.o src/lvm.o src/lzio.o

LIB_O = $(CORE_O) src/lauxlib.o src/lbaselib.o src/lcorolib.o src/ldblib.o \
        src/liolib.o src/lmathlib.o src/loslib.o src/lstrlib.o src/ltablib.o \
        src/loadlib.o src/linit.o src/lutf8lib.o


# Regras
default: all

all: $(EXE)

lua.exe: $(SRC_DIR)/lua.o $(LIB)
	$(CC) -o $@ $(SRC_DIR)/lua.o $(LDFLAGS) $(LIB)

luac.exe: $(SRC_DIR)/luac.o $(LIB)
	$(CC) -o $@ $(SRC_DIR)/luac.o $(LDFLAGS) $(LIB)

$(LIB): $(LIB_O)
	$(AR) $@ $^
	$(RANLIB) $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(SRC_DIR)\*.o *.exe *.lib *.dll

install: all
	@if not exist "$(INSTALL_BIN)" mkdir "$(INSTALL_BIN)"
	@if not exist "$(INSTALL_INC)" mkdir "$(INSTALL_INC)"
	@if not exist "$(INSTALL_LIB)" mkdir "$(INSTALL_LIB)"
	@if not exist "$(INSTALL_SHARE)" mkdir "$(INSTALL_SHARE)"
	@if not exist "$(INSTALL_CMOD)" mkdir "$(INSTALL_CMOD)"
	$(INSTALL) lua.exe $(INSTALL_BIN)
	$(INSTALL) luac.exe $(INSTALL_BIN)
	$(INSTALL) lua54.dll $(INSTALL_BIN)
	$(INSTALL) lua54.lib $(INSTALL_LIB)
	$(INSTALL) $(SRC_DIR)\*.h $(INSTALL_INC)

uninstall:
	rd /S /Q $(INSTALL_TOP)

.PHONY: all clean install uninstall
