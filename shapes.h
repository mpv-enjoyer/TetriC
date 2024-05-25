#ifndef SHAPES_H
#define SHAPES_H

#include "misc.h"

#define SHAPE_ROTATE_SIZE 4
#define SHAPE_SIZE 4
#define SHAPE_TYPE_COUNT 7
#define SHAPE_COLOR_COUNT SHAPE_TYPE_COUNT
#define SHAPE_DEFAULT_X 3
#define SHAPE_DEFAULT_Y -2
#define SHAPE_DEFAULT_ROTATION 0

typedef struct
{
    const char* hitboxes[SHAPE_ROTATE_SIZE];
    int rotate_state;
    int x;
    int y;
    int color;
} Shape;

const static Shape ShapeO = {{
"0110"
"0110"
"0000"
"0000",

"0110"
"0110"
"0000"
"0000",

"0110"
"0110"
"0000"
"0000",

"0110"
"0110"
"0000"
"0000"
}};

const static Shape ShapeI = {{
"0000"
"1111"
"0000"
"0000",

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
"0100"
}};

const static Shape ShapeT = {{
"0100"
"1110"
"0000"
"0000",

"0100"
"0110"
"0100"
"0000",

"0000"
"1110"
"0100"
"0000",

"0100"
"1100"
"0100"
"0000"
}};

const static Shape ShapeJ = {{
"1000"
"1110"
"0000"
"0000",

"0110"
"0100"
"0100"
"0000",

"0000"
"1110"
"0010"
"0000",

"0100"
"0100"
"1100"
"0000"
}};

const static Shape ShapeL = {{
"0010"
"1110"
"0000"
"0000",

"0100"
"0100"
"0110"
"0000",

"0000"
"1110"
"1000"
"0000",

"1100"
"0100"
"0100"
"0000"
}};

const static Shape ShapeZ = {{
"1100"
"0110"
"0000"
"0000",

"0010"
"0110"
"0100"
"0000",

"0000"
"1100"
"0110"
"0000",

"0100"
"1100"
"1000"
"0000"
}};

const static Shape ShapeS = {{

"0110"
"1100"
"0000"
"0000",

"0100"
"0110"
"0010"
"0000",

"0000"
"0110"
"1100"
"0000",

"1000"
"1100"
"0100"
"0000"
}};

#endif