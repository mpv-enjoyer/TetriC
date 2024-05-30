#include "render.h"
#include "ui.h"
#include "gameelements.h"

void tDrawGameFrame(const Field* field, const Shape* shape, const Record *record)
{
    float rectangle_size = GetRenderHeight() / (FIELD_HEIGHT + FIELD_OUTSIDE_HEIGHT);
    float begin_x = GetRenderWidth() / 2 - rectangle_size * FIELD_WIDTH / 2;

    if (begin_x < 0)
    {
        rectangle_size = GetRenderWidth() / FIELD_WIDTH;
        begin_x = 0;
    }

    BeginDrawing();
    ClearBackground(FIELD_OUTSIDE_COLOR);
        tDrawField(field, begin_x, rectangle_size);
        tDrawShape(shape, begin_x, rectangle_size);
        Rectangle statistics_bounds;
        statistics_bounds.x = begin_x - 320;
        if (statistics_bounds.x < 20) statistics_bounds.x = 20;
        statistics_bounds.y = 30;
        statistics_bounds.width = begin_x - 20 - statistics_bounds.x;
        statistics_bounds.height = GetRenderHeight() - 30;
        tDrawStatistics(record, statistics_bounds);
    EndDrawing();
}

int tDrawMenuFrame()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    const float sector_height = 20;
    int sector_count = MENU_ITEM_COUNT * 2 - 1;
    int y_center = GetRenderHeight() / 2;
    int y_center_begin = y_center - sector_height * ((sector_count - 1) / 2.0f);
    for (int i = 0; i < MENU_ITEM_COUNT; i++)
    {
        int y_center_current = y_center_begin + i * 2 * sector_height;
        if (tCenteredButton(y_center_current, menu_item_strings[i])) return i;
    }
    EndDrawing();
    return -1;
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