#ifndef FIELD_H
#define FIELD_H

#include "shape.h"
#include "config.h"

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define FIELD_OUTSIDE_HEIGHT 2

typedef char Field;

typedef struct _Field
{
    char* data;
    Shape* shape;
    Shape* shape_hold;
    bool can_hold;
    Config* config
} _Field;

int tGetFieldXY(const _Field* field, int x, int y);
void tSetFieldXY(_Field* field, int x, int y, int value);
_Field* tAllocField();
void tMakeField(_Field *field, Config *config);
void tFreeField(_Field* field);

#endif