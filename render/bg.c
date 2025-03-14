#include "bg.h"

typedef struct _BGShape
{
    Shape shape;
    float rotation;
    float angular_velocity;
    Vector2 velocity;
    double time;
    int rectangle_size;
    float x;
    float y;
} _BGShape;

_BGShape* _tMakeBGShape();

_BGShape* shapes[BG_MENU_SHAPE_COUNT] = { nullptr };

void tInitMenuBackground()
{
    for (int i = 0; i < BG_MENU_SHAPE_COUNT; i++)
    {
        if (shapes[i] != nullptr) free(shapes[i]); 
        shapes[i] = _tMakeBGShape();
        shapes[i]->x = random_int(- BG_MENU_OFFSCREEN, GetRenderWidth() + BG_MENU_OFFSCREEN);
        shapes[i]->y = random_int(- BG_MENU_OFFSCREEN, GetRenderHeight() + BG_MENU_OFFSCREEN);
    }
}

void tDrawMenuBackground()
{
    for (int i = 0; i < BG_MENU_SHAPE_COUNT; i++)
    {
        if (shapes[i] == nullptr)
        {
            if (rand() % 60 == 0) 
            {
                shapes[i] = _tMakeBGShape();
            }
            continue;
        }
        if (shapes[i]->x > GetRenderWidth() + BG_MENU_OFFSCREEN * 3  ||
            shapes[i]->x < - BG_MENU_OFFSCREEN * 3                   ||
            shapes[i]->y > GetRenderHeight() + BG_MENU_OFFSCREEN * 3 ||
            shapes[i]->y < - BG_MENU_OFFSCREEN * 3)
        {
            free(shapes[i]);
            shapes[i] = nullptr;
            continue;
        }
        double delta_time = GetTime() - shapes[i]->time;
        shapes[i]->time = GetTime();
        shapes[i]->x = shapes[i]->x + delta_time * shapes[i]->velocity.x;
        shapes[i]->y = shapes[i]->y + delta_time * shapes[i]->velocity.y;
        shapes[i]->rotation = shapes[i]->rotation + delta_time * shapes[i]->angular_velocity;
        tDrawShapeRotated(&(shapes[i]->shape), shapes[i]->rectangle_size, shapes[i]->rotation, shapes[i]->x, shapes[i]->y);
    }
}

_BGShape* _tMakeBGShape()
{
    int type = rand() % SHAPE_TYPE_COUNT;
    _BGShape* bgshape = TMALLOC(_BGShape);
    bgshape->shape = Shapes[type];
    int outside_coordinate = rand() % BG_MENU_OFFSCREEN + BG_MENU_OFFSCREEN;
    int inside_coordinate_y = random_int(- BG_MENU_OFFSCREEN, GetRenderHeight() + BG_MENU_OFFSCREEN);
    int velocity_directed = random_int(BG_MENU_MIN_VELOCITY, BG_MENU_MAX_VELOCITY);
    int velocity_undirected = random_int(-BG_MENU_MAX_VELOCITY, BG_MENU_MAX_VELOCITY);

    bgshape->x = GetRenderWidth() + outside_coordinate;
    bgshape->y = inside_coordinate_y;
    bgshape->velocity.x = - velocity_directed;
    bgshape->velocity.y = velocity_undirected;
    bgshape->angular_velocity = random_int(-30, 30);
    bgshape->rotation = rand() % 360;
    bgshape->time = GetTime();
    bgshape->rectangle_size = random_int(BG_MENU_BLOCK_SIZE_MAX, BG_MENU_BLOCK_SIZE_MIN);
    return bgshape;
}