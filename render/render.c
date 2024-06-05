#include "render.h"
#include "ui.h"
#include "gameelements.h"
#include "bg.h"

void tDrawGameFrame(const _Field* field, const Record *record)
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
        tDrawShape(field->shape, begin_x, rectangle_size);
        tDrawStatistics(record, begin_x);
        tDrawHoldShape(field->shape_hold, begin_x, rectangle_size);
        tDrawNextShapes(begin_x);
    EndDrawing();
}

int tDrawMenuFrame()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    tDrawMenuBackground();
    const float sector_height = 20;
    int sector_count = MENU_ITEM_COUNT * 2 - 1;
    int y_center = GetRenderHeight() / 2;
    int y_center_begin = y_center - sector_height * ((sector_count - 1) / 2.0f);
    int selected = -1;
    for (int i = 0; i < MENU_ITEM_COUNT; i++)
    {
        int y_center_current = y_center_begin + i * 2 * sector_height;
        if (tCenteredButton(y_center_current, menu_item_strings[i])) selected = i;
    }
    EndDrawing();
    return selected;
}

void tDrawGameOverFrame(int lines_cleared)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Game over frame.\nDon't mind me.\n(click Enter to proceed)", 0, 0, DEFAULT_FONT_SIZE, BLACK);
    EndDrawing();
}

int tDrawPauseFrame(const _Field* field, const Record *record)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    float rectangle_size = GetRenderHeight() / (FIELD_HEIGHT + FIELD_OUTSIDE_HEIGHT);
    float begin_x = GetRenderWidth() / 2 - rectangle_size * FIELD_WIDTH / 2;
    tDrawField(field, begin_x, rectangle_size);
    tDrawShape(field->shape, begin_x, rectangle_size);
    tDrawStatistics(record, begin_x);
    tDrawHoldShape(field->shape_hold, begin_x, rectangle_size);
    tDrawNextShapes(begin_x);

    Color darker = BLACK;
    darker.a = 200;
    DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), darker);

    const float sector_height = 20;
    int sector_count = PAUSE_ITEM_COUNT * 2 - 1;
    int y_center = GetRenderHeight() / 2;
    int y_center_begin = y_center - sector_height * ((sector_count - 1) / 2.0f);
    int selected = -1;
    for (int i = 0; i < PAUSE_ITEM_COUNT; i++)
    {
        int y_center_current = y_center_begin + i * 2 * sector_height;
        if (tCenteredButton(y_center_current, pause_item_strings[i])) selected = i;
    }
    EndDrawing();
    return selected;
}

void tDrawSettingsFrame(const Config* config)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Settings frame.\nDon't mind me.\n(click ESC to return to menu)", 0, 0, DEFAULT_FONT_SIZE, BLACK);
    EndDrawing();
}