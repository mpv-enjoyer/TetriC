#include "collision.h"

#define SRS_KICK_COUNT 4
#define SRS_ROTATE_COUNT 4

typedef struct _WallKickData
{
    const int Right[SRS_ROTATE_COUNT][SRS_KICK_COUNT * 2];
    const int Left[SRS_ROTATE_COUNT][SRS_KICK_COUNT * 2];
} _WallKickData;

const _WallKickData _wallkickJLTSZ
{
    {
        {-1, 0,-1,-1, 0, 2,-1, 2},
        { 1, 0, 1, 1, 0,-2, 1,-2},
        { 1, 0, 1,-1, 0, 2, 1, 2},
        {-1, 0,-1, 1, 0,-2,-1,-2}
    },
    {
        { 1, 0, 1,-1, 0, 2, 1, 2},
        { 1, 0, 1, 1, 0,-2, 1,-2},
        {-1, 0,-1,-1, 0, 2,-1, 2},
        {-1, 0,-1, 1, 0,-2,-1,-2}
    }
};

const _WallKickData _wallkickI
{
    {
        {-2, 0,  1, 0, -2, 1,  1,-2},
        { 2, 0, -1, 0,  2,-1, -1, 2},
        {-1, 0,  2, 0, -1,-2,  2, 1},
        { 1, 0, -2, 0,  1, 2, -2,-1}
    },
    {
        {-1, 0,  2, 0, -1,-2,  2, 1},
        { 2, 0, -1, 0,  2,-1, -1, 2},
        {-2, 0,  1, 0, -2, 1,  1,-2},
        { 1, 0, -2, 0,  1, 2, -2,-1}
    }
};

bool tCollisionSRS(const Field *field, Shape *shape, SRSRotateType type)
{
    const _WallKickData* current_wall_kicks = nullptr;
    switch (shape->type)
    {
        case SHAPE_TYPE_J: current_wall_kicks = &_wallkickJLTSZ; break;
        case SHAPE_TYPE_L: current_wall_kicks = &_wallkickJLTSZ; break;
        case SHAPE_TYPE_T: current_wall_kicks = &_wallkickJLTSZ; break;
        case SHAPE_TYPE_S: current_wall_kicks = &_wallkickJLTSZ; break;
        case SHAPE_TYPE_Z: current_wall_kicks = &_wallkickJLTSZ; break;
        case SHAPE_TYPE_I: current_wall_kicks = &_wallkickI; break;
        default: return false;
    }
    for (int i = 0; i < SRS_KICK_COUNT; i++)
    {
        int dx;
        int dy;
        if (type == Left)
        {
            int initial_rotation = LOOP_PLUS(shape->rotate_state, SHAPE_ROTATE_SIZE);
            dx = current_wall_kicks->Left[initial_rotation][i * 2];
            dy = current_wall_kicks->Left[initial_rotation][i * 2 + 1];
        }
        else if (type == Right)
        {
            int initial_rotation = LOOP_MINUS(shape->rotate_state, SHAPE_ROTATE_SIZE);
            dx = current_wall_kicks->Right[initial_rotation][i * 2];
            dy = current_wall_kicks->Right[initial_rotation][i * 2 + 1];
        }
        shape->x += dx;
        shape->y += dy;
        if (!tCollision(field, shape)) return true;
        shape->x -= dx;
        shape->y -= dy;
    }
    return false;
}

bool tCollision(const Field* field, const Shape* shape)
{
    return tCollisionY(field, shape, nullptr);
}

bool tCollisionY(const Field* field, const Shape* shape, int* y_top)
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
    return false;
}
