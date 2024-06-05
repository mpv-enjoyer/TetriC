#include "shape.h"

bool tGetShapeHitbox(const Shape *shape, int x, int y)
{
    D_ASSERT(x >= 0 && x < SHAPE_SIZE);
    D_ASSERT(y >= 0 && y < SHAPE_SIZE);
    int offset = y * SHAPE_SIZE + x;
    return shape->hitboxes[shape->rotate_state][offset] == '1';
}