SOURCES = main.c render.c action.c misc.c
LIBS = -lraylib
all:
	g++ $(SOURCES) $(LIBS) -g -o exec