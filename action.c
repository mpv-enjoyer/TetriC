#include "action.h"
#include "bag.h"

bool _tCollisionY(const Field* field, const Shape* shape, int* y_top);
bool _tCollision(const Field* field, const Shape* shape);
Bag _bag;
bool _bag_empty = true;

void tResetRNG()
{
    if (_bag_empty)
    {
        _bag = tCreateBag(-1);
        _bag_empty = false;
    }
    else
    {
        int previous = tGetLastInBag(&_bag);
        _bag = tCreateBag(previous);
    }
};

bool tMakeShape(const Field* field, Shape* shape)
{
    int type = tGetNextInBag(&_bag);
    if (type == -1)
    {
        tResetRNG();
        type = tGetNextInBag(&_bag);
    }
    switch (type)
    {
        case 0: *shape = ShapeO; break;
        case 1: *shape = ShapeI; break;
        case 2: *shape = ShapeT; break;
        case 3: *shape = ShapeJ; break;
        case 4: *shape = ShapeL; break;
        case 5: *shape = ShapeZ; break;
        case 6: *shape = ShapeS; break;
        default: D_ASSERT(false);
    }
    shape->rotate_state = SHAPE_DEFAULT_ROTATION;
    shape->x = SHAPE_DEFAULT_X;
    shape->y = SHAPE_DEFAULT_Y;
    shape->color = type + 1;
    return !_tCollision(field, shape);
}

bool tHardDropShape(const Field* field, Shape* shape)
{
    int y_before = shape->y;
    int y_collision_top;
    while (!_tCollisionY(field, shape, &y_collision_top)) shape->y += 1;
    D_ASSERT(y_before != shape->y);
    shape->y -= 1;
    return shape->y != y_before;
}

bool tRotateShapeLeft(const Field* field, Shape* shape)
{
    shape->rotate_state = (shape->rotate_state + SHAPE_ROTATE_SIZE - 1) % SHAPE_ROTATE_SIZE;
    if (!_tCollision(field, shape)) return true;
    shape->rotate_state = (shape->rotate_state + 1) % SHAPE_ROTATE_SIZE;
    return false;
}

bool tRotateShapeRight(const Field* field, Shape* shape)
{
    shape->rotate_state = (shape->rotate_state + 1) % SHAPE_ROTATE_SIZE;
    if (!_tCollision(field, shape)) return true;
    shape->rotate_state = (shape->rotate_state + SHAPE_ROTATE_SIZE - 1) % SHAPE_ROTATE_SIZE;
    return false;
}

bool tMoveShapeLeft(const Field *field, Shape *shape)
{
    shape->x -= 1;
    if (!_tCollision(field, shape)) return true;
    shape->x += 1;
    return false;
}

bool tMoveShapeRight(const Field *field, Shape *shape)
{
    shape->x += 1;
    if (!_tCollision(field, shape)) return true;
    shape->x -= 1;
    return false;
}

bool tGravity(const Field* field, Shape* shape)
{
    shape->y += 1;
    if (!_tCollision(field, shape)) return true;
    shape->y -= 1;
    return false;
}

bool tPlaceShape(Field *field, const Shape *shape)
{
    D_ASSERT(!_tCollision(field, shape));
    int color = shape->color;
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

bool _tCollision(const Field* field, const Shape* shape)
{
    return _tCollisionY(field, shape, nullptr);
}

bool _tCollisionY(const Field* field, const Shape* shape, int* y_top)
{
    for (int yi = 0; yi < SHAPE_SIZE; yi++)
    {
        if (y_top) *y_top = yi;
        for (int xi = 0; xi < SHAPE_SIZE; xi++)
        {
            int shape_offset = yi * SHAPE_SIZE + xi;
            if (shape->hitboxes[shape->rotate_state][shape_offset] == '0') continue;
            int shape_x = shape->x + xi;
            if (shape_x >= FIELD_WIDTH || shape_x < 0) return true;
            int shape_y = shape->y + yi;
            if (shape_y < 0) continue;
            if (shape_y >= FIELD_HEIGHT) return true;
            int field_offset = shape_y * FIELD_WIDTH + shape_x;
            if (field[field_offset]) return true;
        }
    }
    if (y_top) *y_top = 0xBACCA;
    return false;
}