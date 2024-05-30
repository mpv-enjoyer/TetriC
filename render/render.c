#include "render.h"

void tDrawGameFrame(const Field* field, const Shape* shape, const Record *record)
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
        case 1: color = SHAPE_O_COLOR; break;
        case 2: color = SHAPE_I_COLOR; break;
        case 3: color = SHAPE_T_COLOR; break;
        case 4: color = SHAPE_J_COLOR; break;
        case 5: color = SHAPE_L_COLOR; break;
        case 6: color = SHAPE_Z_COLOR; break;
        case 7: color = SHAPE_S_COLOR; break;
        default: D_ASSERT(false);
    }
    Color shadow_color = color;
    shadow_color.a = 80;
    for (int yi = 0; yi < SHAPE_SIZE; yi++)
    {
        for (int xi = 0; xi < SHAPE_SIZE; xi++)
        {
            int x = begin_x + (xi + shape->x) * rectangle_size;
            int y = (yi + shape->y + FIELD_OUTSIDE_HEIGHT) * rectangle_size;
            int shape_offset = yi * SHAPE_SIZE + xi;
            if (shape->hitboxes[shape->rotate_state][shape_offset] == '0') continue;
            DrawRectangle(x, y, rectangle_size, rectangle_size, color);
            int y_shadow = (yi + shape->y_shadow + FIELD_OUTSIDE_HEIGHT) * rectangle_size;
            DrawRectangle(x, y_shadow, rectangle_size, rectangle_size, shadow_color);
        }
    }

    DrawText(TextFormat("Shape type: %d\nRotate state: %d\nX: %d\nY: %d", shape->type, shape->rotate_state, shape->x, shape->y), 0, 0, DEFAULT_FONT_SIZE, RED);
    DrawText(TextFormat("Lines cleared: %i\nScore: %i\nTime: %f", record->lines_cleared, record->score, record->time), 0, 80, DEFAULT_FONT_SIZE, GREEN);
    DrawText(TextFormat("Level %i", record->lines_cleared / record->config->lines_for_acceleration + 1), 0, 140, DEFAULT_FONT_SIZE, YELLOW);
    EndDrawing();
}

void tDrawMenuFrame(int selected, const Rectangle* items)
{
    const static char* strings[MENU_ITEM_COUNT] = {"Play", "Settings", "Exit"};
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i = 0; i < MENU_ITEM_COUNT; i++)
    {
        Color color = BLACK;
        if (selected == i) color = RED;
        DrawText(strings[i], items[i].x + 2, items[i].y + 2, DEFAULT_FONT_SIZE * 2, GRAY);
        DrawText(strings[i], items[i].x, items[i].y, DEFAULT_FONT_SIZE * 2, color);
    }
    EndDrawing();
}

void tDrawGameOverFrame(int lines_cleared)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Game over frame.\nDon't mind me.", 0, 0, DEFAULT_FONT_SIZE, BLACK);
    EndDrawing();
}

void tDrawPauseFrame(int* selected)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Paused frame.\nDon't mind me.\n(click Enter to proceed)", 0, 0, DEFAULT_FONT_SIZE, BLACK);
    EndDrawing();
}