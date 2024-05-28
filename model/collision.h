#ifndef COLLISION_H
#define COLLISION_H

#include "field.h"
#include "shape.h"

typedef enum
{
    Left,
    Right
} SRSRotateType;

bool tCollisionSRS(const Field *field, Shape *shape, SRSRotateType type);
bool tCollision(const Field *field, const Shape *shape);
bool tCollisionY(const Field *field, const Shape *shape, int *y_top);

#endif