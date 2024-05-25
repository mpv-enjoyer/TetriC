SOURCES = main.c render.c action.c misc.c bag.c
LIBS = -lraylib

RAYPATH = raylib_mingw64/

all:
	g++ $(SOURCES) $(LIBS) -g -o exec

windows:
	x86_64-w64-mingw32-g++ $(SOURCES) $(LIBS) -L$(RAYPATH)/lib -I$(RAYPATH)/include -g -o exec
