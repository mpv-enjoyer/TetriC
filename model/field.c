#include "field.h"

bool tMakeShape(_Field* field)
{
    int type = tGetNextInBag();
    *(field->shape) = Shapes[type];
    D_ASSERT(type < SHAPE_TYPE_COUNT);
    field->shape->rotate_state = SHAPE_DEFAULT_ROTATION;
    field->shape->x = SHAPE_DEFAULT_X;
    field->shape->y = SHAPE_DEFAULT_Y;
    field->shape->type = type;
    tUpdateShapeShadow(field);
    return !tCollision(field);
}

bool tHardDropShape(_Field* field)
{
    int y_before = field->shape->y;
    int y_collision_top;
    while (!tCollisionY(field, shape, &y_collision_top)) shape->y += 1;
    D_ASSERT(y_before != shape->y);
    shape->y -= 1;
    return shape->y != y_before;
}

bool tRotateShapeLeft(const Field* field, Shape* shape)
{
    shape->rotate_state = LOOP_MINUS(shape->rotate_state, SHAPE_ROTATE_SIZE);
    if (!tCollision(field, shape)) return true;
    if (!tCollisionSRS(field, shape, Left)) return true;
    shape->rotate_state = LOOP_PLUS(shape->rotate_state, SHAPE_ROTATE_SIZE);
    return false;
}

bool tRotateShapeRight(const Field* field, Shape* shape)
{
    shape->rotate_state = LOOP_PLUS(shape->rotate_state, SHAPE_ROTATE_SIZE);
    if (!tCollision(field, shape)) return true;
    if (!tCollisionSRS(field, shape, Right)) return true;
    shape->rotate_state = LOOP_MINUS(shape->rotate_state, SHAPE_ROTATE_SIZE);
    return false;
}

bool tMoveShapeLeft(const Field *field, Shape *shape)
{
    shape->x -= 1;
    if (!tCollision(field, shape)) return true;
    shape->x += 1;
    return false;
}

bool tMoveShapeRight(const Field *field, Shape *shape)
{
    shape->x += 1;
    if (!tCollision(field, shape)) return true;
    shape->x -= 1;
    return false;
}

bool tGravity(const Field* field, Shape* shape)
{
    shape->y += 1;
    if (!tCollision(field, shape)) return true;
    shape->y -= 1;
    return false;
}

bool tPlaceShape(Field *field, const Shape *shape)
{
    D_ASSERT(!tCollision(field, shape));
    int color = shape->type + 1;
    D_ASSERT(color <= SHAPE_COLOR_COUNT && color > 0);
    for (int xi = 0; xi < SHAPE_SIZE; xi++)
    {
        for (int yi = 0; yi < SHAPE_SIZE; yi++)
        {
            int shape_offset = yi * SHAPE_SIZE + xi;
            if (shape->hitboxes[shape->rotate_state][shape_offset] == '0') continue;
            int shape_y = shape->y + yi;
            int shape_x = shape->x + xi;
            if (shape_y <= 0) return false;
            int field_offset = shape_y * FIELD_WIDTH + shape_x;
            field[field_offset] = color;
        }
    }
    return true;
}

int tFindLine(const Field *field)
{
    for (int yi = 0; yi < FIELD_HEIGHT; yi++)
    {
        bool air_found = false;
        for (int xi = 0; xi < FIELD_WIDTH; xi++)
        {
            int field_offset = yi * FIELD_WIDTH + xi;
            if (field[field_offset] == 0)
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
            int field_offset_upper = (yi - 1) * FIELD_WIDTH + xi;
            int field_offset = yi * FIELD_WIDTH + xi;
            field[field_offset] = field[field_offset_upper];
            field[field_offset_upper] = 0;
        }
    }
    for (int xi = 0; xi < FIELD_WIDTH; xi++)
    {
        int field_offset = xi;
        field[field_offset] = 0;
    }
}

void tUpdateShapeShadow(const Field *field, Shape* shape)
{
    Shape shadow = *shape;
    while (!tCollision(field, &shadow)) shadow.y += 1;
    shape->y_shadow = shadow.y - 1;
}

void tHoldShape(Shape* shape, Shape* shape_hold)
{
    if (shape_hold)
}

int tGetFieldXY(const _Field* field, int x, int y)
{
    if (y < 0) return -1;
    D_ASSERT(y < FIELD_HEIGHT);
    D_ASSERT(x >= 0 && x < FIELD_WIDTH);
    int offset = y * FIELD_WIDTH + x;
    return field->data[offset];
}

void tSetFieldXY(_Field* field, int x, int y, int value)
{
    D_ASSERT(y >= 0 && y < FIELD_HEIGHT);
    D_ASSERT(x >= 0 && x < FIELD_WIDTH);
    D_ASSERT(value >= 0 && value < SHAPE_COLOR_COUNT + 1);
    int offset = y * FIELD_WIDTH + x;
    field->data[offset] = value;
}