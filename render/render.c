#include "render.h"

void tDrawGameFrame(const Field* field, const Shape* shape)
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
        case 0: D_ASSERT(false); break;
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

void tDrawMenuFrame(int state)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("You lost.\nClick Enter to play again.", 0, 0, 20, BLACK);
    EndDrawing();
}