#ifndef SHAPES_H
#define SHAPES_H

#include "misc.h"

#define SHAPE_ROTATE_SIZE 4
#define SHAPE_SIZE 4
#define SHAPE_TYPE_COUNT 7
#define SHAPE_COLOR_COUNT 4

typedef struct
{
    char* hitboxes[SHAPE_ROTATE_SIZE];
    int rotate_state;
    int x;
    int y;
    int color;
} Shape;

const static char* ShapeO[4] = {
"0000"
"0110"
"0110"
"0000",

"0000"
"0110"
"0110"
"0000",

"0000"
"0110"
"0110"
"0000",

"0000"
"0110"
"0110"
"0000"
};

const static char* ShapeI[4] = {
"0010"
"0010"
"0010"
"0010",

"0000"
"0000"
"1111"
"0000",

"0100"
"0100"
"0100"
"0100",

"0000"
"1111"
"0000"
"0000"
};

const static char* ShapeT[4] = {
"0010"
"0111"
"0000"
"0000",

"0010"
"0011"
"0010"
"0000",

"0000"
"0111"
"0010"
"0000",

"0010"
"0110"
"0010"
"0000"
};

const static char* ShapeJ[4] = {
"0011"
"0010"
"0010"
"0000",

"0000"
"0111"
"0001"
"0000",

"0010"
"0010"
"0110"
"0000",

"0100"
"0111"
"0000"
"0000"
};

const static char* ShapeL[4] = {
"0110"
"0010"
"0010"
"0000",

"0001"
"0111"
"0000"
"0000",

"0010"
"0010"
"0011"
"0000",

"0000"
"0111"
"0100"
"0000"
};

const static char* ShapeZ[4] = {
"0110"
"0011"
"0000"
"0000",

"0001"
"0011"
"0010"
"0000",

"0000"
"0110"
"0011"
"0000",

"0010"
"0110"
"0100"
"0000"
};

const static char* ShapeS[4] = {

"0011"
"0110"
"0000"
"0000",

"0010"
"0011"
"0001"
"0000",

"0000"
"0011"
"0110"
"0000",

"0100"
"0110"
"0010"
"0000"
};

#endif