#ifndef FIELD_H
#define FIELD_H

#include "shape.h"


#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define FIELD_OUTSIDE_HEIGHT 2

typedef char Field;

struct _Field
{
    const char* data;
    Shape* shape;
    Shape* shape_hold;
    bool can_hold;

};

#endif