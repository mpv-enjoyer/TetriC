#include "action.h"
#include "bag.h"
#include "collision.h"

bool tMakeShape(Field* field)
{
    int type = tGetNextInBag(field->bag);
    return tMakeShapeKnown(field, type);
}

bool tMakeShapeKnown(Field* field, int type)
{
    *(field->shape) = Shapes[type];
    D_ASSERT(type < SHAPE_TYPE_COUNT);
    field->shape->rotate_state = SHAPE_DEFAULT_ROTATION;
    field->shape->x = SHAPE_DEFAULT_X;
    field->shape->y = SHAPE_DEFAULT_Y;
    field->shape->type = type;
    tUpdateShapeShadow(field);
    field->can_hold = true;
    return !tCollision(field);
}

bool tHardDropShape(const Field* field)
{
    int y_before = field->shape->y;
    while (!tCollision(field)) field->shape->y += 1;
    D_ASSERT(y_before != field->shape->y);
    field->shape->y -= 1;
    return field->shape->y != y_before;
}

bool tRotateShapeLeft(const Field* field)
{
    field->shape->rotate_state = LOOP_MINUS(field->shape->rotate_state, SHAPE_ROTATE_SIZE);
    if (!tCollision(field)) return true;
    if (field->config->srs && !tCollisionSRS(field, Left)) return true;
    field->shape->rotate_state = LOOP_PLUS(field->shape->rotate_state, SHAPE_ROTATE_SIZE);
    return false;
}

bool tRotateShapeRight(Field* field)
{
    field->shape->rotate_state = LOOP_PLUS(field->shape->rotate_state, SHAPE_ROTATE_SIZE);
    if (!tCollision(field)) return true;
    if (field->config->srs && !tCollisionSRS(field, Right)) return true;
    field->shape->rotate_state = LOOP_MINUS(field->shape->rotate_state, SHAPE_ROTATE_SIZE);
    return false;
}

bool tMoveShapeLeft(const Field *field)
{
    field->shape->x -= 1;
    if (!tCollision(field)) return true;
    field->shape->x += 1;
    return false;
}

bool tMoveShapeRight(Field *field)
{
    field->shape->x += 1;
    if (!tCollision(field)) return true;
    field->shape->x -= 1;
    return false;
}

bool tGravityShape(Field* field)
{
    field->shape->y += 1;
    if (!tCollision(field)) return true;
    field->shape->y -= 1;
    return false;
}

bool tPlaceShape(Field *field)
{
    D_ASSERT(!tCollision(field));
    int color = field->shape->type + 1;
    D_ASSERT(color <= SHAPE_COLOR_COUNT && color > 0);
    for (int xi = 0; xi < SHAPE_SIZE; xi++)
    {
        for (int yi = 0; yi < SHAPE_SIZE; yi++)
        {
            if (!tGetShapeHitbox(field->shape, xi, yi)) continue;
            int shape_y = field->shape->y + yi;
            int shape_x = field->shape->x + xi;
            if (shape_y <= 0) return false;
            tSetFieldXY(field, shape_x, shape_y, color);
        }
    }
    return true;
}

int tFindLine(const Field* field)
{
    for (int yi = 0; yi < FIELD_HEIGHT; yi++)
    {
        bool air_found = false;
        for (int xi = 0; xi < FIELD_WIDTH; xi++)
        {
            if (!tGetFieldXY(field, xi, yi))
            {
                air_found = true;
                break;
            }
        }
        if (!air_found) return yi;
    }
    return -1;
}

void tRemoveLine(Field* field, int y)
{
    D_ASSERT(y > 0 && y < FIELD_HEIGHT);
    for (int yi = y; yi > 0; yi--)
    {
        for (int xi = 0; xi < FIELD_WIDTH; xi++)
        {
            int upper = tGetFieldXY(field, xi, yi - 1);
            tSetFieldXY(field, xi, yi, upper);
            tSetFieldXY(field, xi, yi - 1, 0);
        }
    }
    for (int xi = 0; xi < FIELD_WIDTH; xi++)
    {
        tSetFieldXY(field, xi, 0, 0);
    }
}

void tUpdateShapeShadow(Field *field)
{
    int shape_y_backup = field->shape->y;
    while (!tCollision(field)) field->shape->y += 1;
    field->shape->y_shadow = field->shape->y - 1;
    field->shape->y = shape_y_backup;
}

bool tHoldShape(Field* field)
{
    if (!field->can_hold) return false;
    D_ASSERT(field->shape != nullptr);
    Shape to_hold = *(field->shape);
    bool result;
    if (field->shape_hold == nullptr)
    {
        field->shape_hold = (Shape*)malloc(sizeof(Shape));
        result = tMakeShape(field);
    }
    else result = tMakeShapeKnown(field, field->shape_hold->type);
    *(field->shape_hold) = to_hold;
    field->can_hold = false;
    return result;
}