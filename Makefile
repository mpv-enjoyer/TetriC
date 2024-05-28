SOURCES = $(wildcard model/*.c) $(wildcard *.c)
LIBS = -lraylib

RAYPATH = raylib_mingw64/

all:
	g++ $(SOURCES) -Imodel -I. $(LIBS) -g -o exec

windows:
	x86_64-w64-mingw32-g++ -Imodel -I. $(SOURCES) $(LIBS) -L$(RAYPATH)/lib -I$(RAYPATH)/include -g -o exec
