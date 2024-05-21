#include "render.h"

Shape _shape;

Field* field;
Shape* shape;

bool _tKeyFrame();
void _tFrame();

void tInit()
{
    shape = &_shape;

    InitWindow(WIDTH, HEIGHT, "TetriC");
    SetTargetFPS(60);
    srand(time(NULL));
}

void tMainLoop()
{
    field = (Field*)calloc(FIELD_HEIGHT * FIELD_WIDTH + 1, sizeof(char));
    tMakeShape(field, shape);

    bool playing = true;
    double previous_keyframe = 0;
    double wait_keyframe = 0.1f;
    double faster_keyframe = 0.04f;
    while (!WindowShouldClose() && playing)
    {
        double current_wait_time = wait_keyframe;
        if (IsKeyPressed(KEY_UP)) tRotateShapeLeft(field, shape);
        if (IsKeyPressed(KEY_DOWN)) tRotateShapeRight(field, shape);
        if (IsKeyPressed(KEY_LEFT)) tMoveShapeLeft(field, shape);
        if (IsKeyPressed(KEY_RIGHT)) tMoveShapeRight(field, shape);
        if (IsKeyDown(KEY_SPACE)) current_wait_time = faster_keyframe;
        if (GetTime() - previous_keyframe < current_wait_time)
        {
            _tFrame();
        }
        else
        {
            playing = _tKeyFrame();
            previous_keyframe = GetTime();
        }
    }
}

bool tMenu()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawText("You lost.\nClick Enter to play again.", 0, 0, 20, BLACK);
        ClearBackground(RAYWHITE);
        EndDrawing();
        if (IsKeyPressed(KEY_ENTER)) return true;
    }
    return false;
}

bool _tKeyFrame()
{
    bool falling = tGravity(field, shape);
    if (!falling)
    {
        bool good_placement = tPlaceShape(field, shape);
        if (!good_placement) return false;
        while (true)
        {
            int found = tFindLine(field);
            if (found == -1) break;
            tRemoveLine(field, found);
        }
        bool good_spawn = tMakeShape(field, shape);
        if (!good_spawn) return false;
    }
    _tFrame();
    return true;
}

void _tFrame()
{
    float rectangle_size = GetRenderHeight() / FIELD_HEIGHT;
    float begin_x = GetRenderWidth() / 2 - rectangle_size * FIELD_WIDTH / 2;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int yi = 0; yi < FIELD_HEIGHT; yi++)
    {
        for (int xi = 0; xi < FIELD_WIDTH; xi++)
        {
            Color color;
            int offset = yi * FIELD_WIDTH + xi;
            switch (field[offset])
            {
                case 0: color =  (Color){ 0, 0, 0, 255}; break;
                case 1: color =  (Color){ 200, 50, 0, 255 }; break;
                case 2: color =  (Color){ 0, 200, 80, 255 }; break;
                case 3: color =  (Color){ 100, 0, 200, 255 } ; break;
                case 4: color =  (Color){ 200, 0, 200, 255 }; break;
                default: color = (Color){ 255, 0, 0, 255 };
            }
            int x = begin_x + xi * rectangle_size;
            int y = yi * rectangle_size;
            Rectangle rect = { x, y, rectangle_size, rectangle_size };
            DrawRectangle(x, y, rectangle_size, rectangle_size, color);
            DrawRectangleLinesEx(rect, 1, BLACK);
        }
    }

    Color color;
    switch (shape->color)
    {
        case 0:  color = (Color){ 0, 0, 0, 255}; break;
        case 1:  color = (Color){ 100, 0, 0, 255 }; break;
        case 2:  color = (Color){ 0, 100, 0, 255 }; break;
        case 3:  color = (Color){ 0, 0, 100, 255 } ; break;
        case 4:  color = (Color){ 100, 0, 100, 255 }; break;
        default: color = (Color){ 255, 0, 0, 255 };
    }
    for (int yi = 0; yi < SHAPE_SIZE; yi++)
    {
        for (int xi = 0; xi < SHAPE_SIZE; xi++)
        {
            int x = begin_x + (xi + shape->x) * rectangle_size;
            int y = (yi + shape->y) * rectangle_size;
            int shape_offset = yi * SHAPE_SIZE + xi;
            if (shape->hitboxes[shape->rotate_state][shape_offset] == '0') continue;
            DrawRectangle(x, y, rectangle_size, rectangle_size, color);
        }
    }

    const char* output = to_string(shape->color);
    DrawText(TextFormat("Color: %d\nRotate state: %d\nX: %d\nY: %d", shape->color, shape->rotate_state, shape->x, shape->y), 0, 0, 20, RED);
    EndDrawing();
}