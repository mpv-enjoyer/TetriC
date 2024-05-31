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
        if (shapes[i] != nullptr) continue; 
        shapes[i] = _tMakeBGShape();
        shapes[i]->x = random(- BG_MENU_OFFSCREEN, GetRenderWidth() + BG_MENU_OFFSCREEN);
        shapes[i]->y = random(- BG_MENU_OFFSCREEN, GetRenderHeight() + BG_MENU_OFFSCREEN);
    }
}

void tDrawMenuBackground()
{
    int found = 0;
    for (int i = 0; i < BG_MENU_SHAPE_COUNT; i++)
    {
        if (shapes[i] != nullptr) found++;
    }
    if (found == 0) tInitMenuBackground();
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
    _BGShape* bgshape = (_BGShape*)malloc(sizeof(_BGShape));
    bgshape->shape = Shapes[type];
    int outside_coordinate = rand() % BG_MENU_OFFSCREEN + BG_MENU_OFFSCREEN;
    int inside_coordinate_x = random(- BG_MENU_OFFSCREEN, GetRenderWidth() + BG_MENU_OFFSCREEN);
    int inside_coordinate_y = random(- BG_MENU_OFFSCREEN, GetRenderHeight() + BG_MENU_OFFSCREEN);
    int velocity_directed = random(BG_MENU_MIN_VELOCITY, BG_MENU_MAX_VELOCITY);
    int velocity_undirected = random(-BG_MENU_MAX_VELOCITY, BG_MENU_MAX_VELOCITY);

    bgshape->x = GetRenderWidth() + outside_coordinate;
    bgshape->y = inside_coordinate_y;
    bgshape->velocity.x = - velocity_directed;
    bgshape->velocity.y = velocity_undirected;
    /*int border = rand() % 4;
    switch (border)
    {
    case 0:
        bgshape->x = - outside_coordinate;
        bgshape->y = inside_coordinate_y;
        bgshape->velocity.x = velocity_directed;
        bgshape->velocity.y = velocity_undirected;
        break;
    case 1:
        bgshape->y = - outside_coordinate;
        bgshape->x = inside_coordinate_x;
        bgshape->velocity.y = velocity_directed;
        bgshape->velocity.x = velocity_undirected;
        break;
    case 2:
        bgshape->x = GetRenderWidth() + outside_coordinate;
        bgshape->y = inside_coordinate_y;
        bgshape->velocity.x = - velocity_directed;
        bgshape->velocity.y = velocity_undirected;
        break;
    case 3:
        bgshape->y = GetRenderHeight() + outside_coordinate;
        bgshape->x = inside_coordinate_x;
        bgshape->velocity.y = - velocity_directed;
        bgshape->velocity.x = velocity_undirected;
        break;
    }*/
    bgshape->angular_velocity = 0;
    bgshape->rotation = 0;
    bgshape->time = GetTime();
    bgshape->rectangle_size = random(BG_MENU_BLOCK_SIZE_MAX, BG_MENU_BLOCK_SIZE_MIN);
    return bgshape;
}