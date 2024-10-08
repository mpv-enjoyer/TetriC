SOURCES = $(wildcard *.c)
SOURCES += $(wildcard model/*.c)
SOURCES += $(wildcard render/*.c)
SOURCES += $(wildcard control/*.c)
SOURCES += $(wildcard ui/*.c)

INCLUDES = -I.
INCLUDES += -Imodel
INCLUDES += -Irender
INCLUDES += -Icontrol
INCLUDES += -Iui

LIBS = -lraylib

RAYPATH = raylib_mingw64/

#-fanalyzer

all:
	gcc $(SOURCES) $(LIBS) $(INCLUDES) -O0 -g -o exec

windows:
	x86_64-w64-mingw32-gcc $(SOURCES) -static -l:libraylib.dll.a -l:libraylib.a $(INCLUDES) -L$(RAYPATH)/lib -I$(RAYPATH)/include -O3 -g -o tetriC
