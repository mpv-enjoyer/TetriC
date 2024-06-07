#ifndef COLLISION_H
#define COLLISION_H

#include "field.h"
#include "shape.h"

typedef enum
{
    Left,
    Right
} SRSRotateType;

bool tCollisionSRS(const Field* field, SRSRotateType type);
bool tCollision(const Field* field);
bool tCollisionEx(const char* field_data, const Shape *shape, int *y_top);

#endif