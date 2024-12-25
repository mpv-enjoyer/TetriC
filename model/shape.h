#ifndef SHAPE_H
#define SHAPE_H

#include "misc.h"

#define SHAPE_ROTATE_SIZE 4
#define SHAPE_SIZE 4
#define SHAPE_TYPE_COUNT 7
#define SHAPE_COLOR_COUNT SHAPE_TYPE_COUNT
#define SHAPE_DEFAULT_X 3
#define SHAPE_DEFAULT_Y -2
#define SHAPE_DEFAULT_ROTATION 0
#define SHAPE_DEFAULT_ARGS SHAPE_DEFAULT_ROTATION, SHAPE_DEFAULT_X, SHAPE_DEFAULT_Y, SHAPE_DEFAULT_Y

#define SHAPE_TYPE_O 0
#define SHAPE_TYPE_I 1
#define SHAPE_TYPE_T 2
#define SHAPE_TYPE_J 3
#define SHAPE_TYPE_L 4
#define SHAPE_TYPE_Z 5
#define SHAPE_TYPE_S 6

typedef struct Shape
{
    const char* hitboxes[SHAPE_ROTATE_SIZE];
    int type;
    int rotate_state;
    int x;
    int y;
    int y_shadow;
} Shape;

bool tGetShapeHitbox(const Shape* shape, int x, int y);

static const Shape Shapes[SHAPE_TYPE_COUNT] = 
{{{
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
}, SHAPE_TYPE_O, SHAPE_DEFAULT_ARGS}, {{
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
}, SHAPE_TYPE_I, SHAPE_DEFAULT_ARGS}, {{
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
}, SHAPE_TYPE_T, SHAPE_DEFAULT_ARGS}, {{
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
}, SHAPE_TYPE_J, SHAPE_DEFAULT_ARGS}, {{
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
}, SHAPE_TYPE_L, SHAPE_DEFAULT_ARGS}, {{
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
}, SHAPE_TYPE_Z, SHAPE_DEFAULT_ARGS}, {{

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
}, SHAPE_TYPE_S, SHAPE_DEFAULT_ARGS}};

#endif