#include "render.h"
#include "gameelements.h"
#include "bg.h"

void _tDrawGameFrameEx(const Field* field, const Record* record, bool is_replay, bool is_40_lines)
{
    float rectangle_size = GetRenderHeight() / (FIELD_HEIGHT + FIELD_OUTSIDE_HEIGHT);
    float begin_x = GetRenderWidth() / 2 - rectangle_size * FIELD_WIDTH / 2;

    if (begin_x < 0)
    {
        rectangle_size = GetRenderWidth() / FIELD_WIDTH;
        begin_x = 0;
    }

    if (is_40_lines) DrawText("40 LINES", 0, GetRenderHeight() - 50, 50, RED);

    if (is_replay) DrawText("REPLAY", 0, 0, 50, RED);
    else DrawFPS(0, 0);
    
    tDrawField(field, begin_x, rectangle_size);
    tDrawShape(field->shape, begin_x, rectangle_size);
    tDrawStatistics(record, begin_x);
    tDrawHoldShape(field->shape_hold, begin_x, rectangle_size);
    if (!is_replay) tDrawNextShapes(field->bag, begin_x);
}

void tDrawGameFrame(const Field* field, const Record *record, bool is_40_lines)
{
    BeginDrawing();
        ClearBackground(FIELD_OUTSIDE_COLOR);
        _tDrawGameFrameEx(field, record, false, is_40_lines);
    EndDrawing();
}

void tDrawMenuFrame(UIItem* items, int items_count)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    tDrawMenuBackground();
    tUpdateDrawUIItems(items, items_count);
    EndDrawing();
}

void tDrawGameOverFrame(UIItem* items, int item_count)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        tUpdateDrawUIItems(items, item_count);
    EndDrawing();
}

void tDrawPauseFrame(UIItem* items, int item_count, const Field* field, const Record *record, bool is_40_lines)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    _tDrawGameFrameEx(field, record, false, is_40_lines);
    Color darker = BLACK;
    darker.a = 200;
    DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), darker);
    tUpdateDrawUIItems(items, item_count);
    EndDrawing();
}

void tDrawSettingsFrame(UIItem* items, int item_count)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        tUpdateDrawUIItems(items, item_count);
    EndDrawing();
}

void tDrawReplayFrame(const Field* field, const Record* record, bool is_40_lines)
{
    BeginDrawing();
    ClearBackground(FIELD_OUTSIDE_COLOR);
    _tDrawGameFrameEx(field, record, true, is_40_lines);
    EndDrawing();
}