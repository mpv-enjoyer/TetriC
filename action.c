#include "action.h"

bool _tCollision(const Field* field, const Shape* shape);
#define COPYHITBOX(t, dest) \
    strncpy(dest[0], t[0], SHAPE_SIZE * SHAPE_SIZE); \
    strncpy(dest[1], t[1], SHAPE_SIZE * SHAPE_SIZE); \
    strncpy(dest[2], t[2], SHAPE_SIZE * SHAPE_SIZE);\
    strncpy(dest[3], t[3], SHAPE_SIZE * SHAPE_SIZE);

bool tMakeShape(const Field* field, Shape* shape)
{
    int type = rand() % SHAPE_TYPE_COUNT;
    switch (type)
    {
        case 0: COPYHITBOX(ShapeI, shape->hitboxes); break;
        case 1: COPYHITBOX(ShapeJ, shape->hitboxes); break;
        case 2: COPYHITBOX(ShapeL, shape->hitboxes); break;
        case 3: COPYHITBOX(ShapeO, shape->hitboxes); break;
        case 4: COPYHITBOX(ShapeS, shape->hitboxes); break;
        case 5: COPYHITBOX(ShapeT, shape->hitboxes); break;
        case 6: COPYHITBOX(ShapeZ, shape->hitboxes); break;
        default: D_ASSERT(false);
    }
    shape->rotate_state = rand() % SHAPE_ROTATE_SIZE;
    int x_min = -1;
    int x_max = -1;
    int y_min = -1;
    int y_max = -1;
    for (int xi = 0; xi < SHAPE_SIZE; xi++)
    {
        for (int yi = 0; yi < SHAPE_SIZE; yi++)
        {
            int offset = yi * SHAPE_SIZE + xi;
            if (!shape->hitboxes[shape->rotate_state][offset]) continue;
            if (x_min == -1 || x_min > xi) x_min = xi;
            if (y_min == -1 || y_min > yi) y_min = yi;
            if (x_max == -1 || x_max < xi) x_max = xi;
            if (y_max == -1 || y_max < yi) y_max = yi;
        }
    }
    int available_width = FIELD_WIDTH - (x_max - x_min);
    shape->x = rand() % available_width - x_min;
    shape->y = - y_max;
    shape->color = rand() % SHAPE_COLOR_COUNT + 1;
    return !_tCollision(field, shape);
}

bool tRotateShapeLeft(const Field* field, Shape* shape)
{
    shape->rotate_state = (shape->rotate_state + 1) % SHAPE_ROTATE_SIZE;
    if (!_tCollision(field, shape)) return true;
    shape->rotate_state = (shape->rotate_state + SHAPE_ROTATE_SIZE - 1) % SHAPE_ROTATE_SIZE;
    return false;
}

bool tRotateShapeRight(const Field* field, Shape* shape)
{
    shape->rotate_state = (shape->rotate_state + SHAPE_ROTATE_SIZE - 1) % SHAPE_ROTATE_SIZE;
    if (!_tCollision(field, shape)) return true;
    shape->rotate_state = (shape->rotate_state + 1) % SHAPE_ROTATE_SIZE;
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
            int field_offset = shape_y * FIELD_WIDTH + shape_x;
            field[field_offset] = color;
            if (shape_y <= 0) return false;
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
    for (int xi = 0; xi < SHAPE_SIZE; xi++)
    {
        for (int yi = 0; yi < SHAPE_SIZE; yi++)
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
    return false;
}