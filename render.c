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
    tResetRNG();
    field = (Field*)calloc(FIELD_HEIGHT * FIELD_WIDTH + 1, sizeof(char));
    tMakeShape(field, shape);

    bool playing = true;
    double previous_keyframe = 0;
    double wait_keyframe = 0.7f;
    double faster_keyframe = 0.04f;
    while (!WindowShouldClose() && playing)
    {
        double current_wait_time = wait_keyframe;
        bool current_hard_dropped = false;

        if (IsKeyPressed(KEY_Z)) tRotateShapeLeft(field, shape);
        if (IsKeyPressed(KEY_X)) tRotateShapeRight(field, shape);
        if (IsKeyPressed(KEY_LEFT)) tMoveShapeLeft(field, shape);
        if (IsKeyPressed(KEY_RIGHT)) tMoveShapeRight(field, shape);
        if (IsKeyDown(KEY_DOWN)) current_wait_time = faster_keyframe;
        if (IsKeyPressed(KEY_SPACE)) 
        {
            tHardDropShape(field, shape);
            current_hard_dropped = true;
        }

        bool should_keyframe = false;
        should_keyframe |= current_hard_dropped;
        should_keyframe |= GetTime() - previous_keyframe >= current_wait_time;
        if (should_keyframe)
        {
            playing = _tKeyFrame();
            previous_keyframe = GetTime();
        }
        else
        {
            _tFrame();
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
    float rectangle_size = GetRenderHeight() / (FIELD_HEIGHT + FIELD_OUTSIDE_HEIGHT);
    float begin_x = GetRenderWidth() / 2 - rectangle_size * FIELD_WIDTH / 2;

    BeginDrawing();
    ClearBackground(FIELD_OUTSIDE_COLOR);
    for (int yi = 0; yi < FIELD_HEIGHT; yi++)
    {
        for (int xi = 0; xi < FIELD_WIDTH; xi++)
        {
            Color color;
            int offset = yi * FIELD_WIDTH + xi;
            switch (field[offset])
            {
                case 0: color = FIELD_COLOR; break;
                case 1: color = SHAPE_O_COLOR; break;
                case 2: color = SHAPE_I_COLOR; break;
                case 3: color = SHAPE_T_COLOR; break;
                case 4: color = SHAPE_J_COLOR; break;
                case 5: color = SHAPE_L_COLOR; break;
                case 6: color = SHAPE_Z_COLOR; break;
                case 7: color = SHAPE_S_COLOR; break;
                default: D_ASSERT(false);
            }
            int x = begin_x + xi * rectangle_size;
            int y = (yi + FIELD_OUTSIDE_HEIGHT) * rectangle_size;
            Rectangle rect = { x, y, rectangle_size, rectangle_size };
            DrawRectangle(x, y, rectangle_size, rectangle_size, color);
            DrawRectangleLinesEx(rect, 1, BLACK);
        }
    }

    Color color;
    switch (shape->type + 1)
    {
        case 0: color = FIELD_COLOR; break;
        case 1: color = SHAPE_O_COLOR; break;
        case 2: color = SHAPE_I_COLOR; break;
        case 3: color = SHAPE_T_COLOR; break;
        case 4: color = SHAPE_J_COLOR; break;
        case 5: color = SHAPE_L_COLOR; break;
        case 6: color = SHAPE_Z_COLOR; break;
        case 7: color = SHAPE_S_COLOR; break;
        default: D_ASSERT(false);
    }
    for (int yi = 0; yi < SHAPE_SIZE; yi++)
    {
        for (int xi = 0; xi < SHAPE_SIZE; xi++)
        {
            int x = begin_x + (xi + shape->x) * rectangle_size;
            int y = (yi + shape->y + FIELD_OUTSIDE_HEIGHT) * rectangle_size;
            int shape_offset = yi * SHAPE_SIZE + xi;
            if (shape->hitboxes[shape->rotate_state][shape_offset] == '0') continue;
            DrawRectangle(x, y, rectangle_size, rectangle_size, color);
        }
    }

    DrawText(TextFormat("Shape type: %d\nRotate state: %d\nX: %d\nY: %d", shape->type, shape->rotate_state, shape->x, shape->y), 0, 0, 20, RED);
    EndDrawing();
}