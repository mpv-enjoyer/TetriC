#ifndef SHAPES_H
#define SHAPES_H

#include "misc.h"

#define SHAPE_ROTATE_SIZE 4
#define SHAPE_SIZE 4
#define SHAPE_TYPE_COUNT 7
#define SHAPE_COLOR_COUNT 4

typedef struct
{
    const char* hitboxes[SHAPE_ROTATE_SIZE];
    int rotate_state;
    int x;
    int y;
    int color;
} Shape;

const static Shape ShapeO = {{
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
}};

const static Shape ShapeI = {{
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
}};

const static Shape ShapeT = {{
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
}};

const static Shape ShapeJ = {{
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
}};

const static Shape ShapeL = {{
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
}};

const static Shape ShapeZ = {{
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
}};

const static Shape ShapeS = {{

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
}};

#endif