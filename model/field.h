#ifndef FIELD_H
#define FIELD_H

#include "shape.h"
#include "config.h"
#include "bag.h"

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define FIELD_OUTSIDE_HEIGHT 2

typedef struct Field
{
    char* data;
    Bag* bag;
    Shape* shape;
    Shape* shape_hold;
    bool can_hold;
    bool is_shape_on_ground;
    double shape_on_ground_begin;
    Config* config;
    tString* replay;
} Field;

int tGetFieldXY(const Field* field, int x, int y);
void tSetFieldXY(Field* field, int x, int y, int value);
Field* tAllocField();
void tMakeField(Field *field, Config *config);
void tFreeField(Field* field);

#endif