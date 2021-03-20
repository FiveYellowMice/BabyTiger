.DEFAULT: babytiger_emu

COMPILER_FLAGS = -Wall -Wextra
LINKER_FLAGS = -lSDL2

babytiger_emu: babytiger_emu.h babytiger_emu.c
	gcc babytiger_emu.c $(COMPILER_FLAGS) $(LINKER_FLAGS) -o babytiger_emu
