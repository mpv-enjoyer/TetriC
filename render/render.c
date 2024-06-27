#include "render.h"
#include "gameelements.h"
#include "bg.h"

void _tDrawGameFrameEx(const Field* field, const Record* record, bool is_replay)
{
    float rectangle_size = GetRenderHeight() / (FIELD_HEIGHT + FIELD_OUTSIDE_HEIGHT);
    float begin_x = GetRenderWidth() / 2 - rectangle_size * FIELD_WIDTH / 2;

    if (begin_x < 0)
    {
        rectangle_size = GetRenderWidth() / FIELD_WIDTH;
        begin_x = 0;
    }

    if (is_replay) DrawText("REPLAY", 0, 0, 50, RED);
    else DrawFPS(0, 0);
    
    tDrawField(field, begin_x, rectangle_size);
    tDrawShape(field->shape, begin_x, rectangle_size);
    tDrawStatistics(record, begin_x);
    tDrawHoldShape(field->shape_hold, begin_x, rectangle_size);
    if (!is_replay) tDrawNextShapes(field->bag, begin_x);
}

void tDrawGameFrame(const Field* field, const Record *record)
{
    BeginDrawing();
        ClearBackground(FIELD_OUTSIDE_COLOR);
        _tDrawGameFrameEx(field, record, false);
    EndDrawing();
}

void tDrawMenuFrame(UIItem* items, int items_count)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    tDrawMenuBackground();

    items[0].position.x = 100;
    for (int i = 0; i < items_count; i++)
    {
        items->UpdateDraw(&(items[i]));
    }

    EndDrawing();
}

void tDrawGameOverFrame(int lines_cleared)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Game over frame.\nDon't mind me.\n(click Enter to proceed)", 0, 0, DEFAULT_FONT_SIZE, BLACK);
    EndDrawing();
}

int tDrawPauseFrame(const Field* field, const Record *record)
{
    const static int item_count = 2;
    const static char* item_strings[item_count] = {"Continue", "To menu"};
    BeginDrawing();
    ClearBackground(RAYWHITE);

    _tDrawGameFrameEx(field, record, false);

    Color darker = BLACK;
    darker.a = 200;
    DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), darker);

    const float sector_height = 23;
    int sector_count = item_count * 2 - 1;
    int y_center = GetRenderHeight() / 2;
    int y_center_begin = y_center - sector_height * ((sector_count - 1) / 2.0f);
    int selected = -1;
    for (int i = 0; i < item_count; i++)
    {
        int y_center_current = y_center_begin + i * 2 * sector_height;
        if (tCenteredButton(y_center_current, item_strings[i], nullptr)) selected = i;
    }
    EndDrawing();
    return selected;
}

void tDrawSettingsFrame(const Config* config, SettingsFrameData* frame_data)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);

        tDrawUpdateUIButton(&(frame_data->back), &(frame_data->save_and_back.y));
        tDrawUpdateUIButton(&(frame_data->save_and_back), &(frame_data->min_speed.y));
        tDrawUpdateUIDoubleBox(&(frame_data->min_speed), &(frame_data->max_speed.y));
        tDrawUpdateUIDoubleBox(&(frame_data->max_speed), &(frame_data->acceleration.y));
        tDrawUpdateUIDoubleBox(&(frame_data->acceleration), &(frame_data->lines_for_next_level.y));
        tDrawUpdateUIIntBox(&(frame_data->lines_for_next_level), &(frame_data->srs.y));
        tDrawUpdateUICheckBox(&(frame_data->srs), nullptr);

    EndDrawing();
}

void tDrawReplayFrame(const Field* field, const Record* record)
{
    BeginDrawing();
    ClearBackground(FIELD_OUTSIDE_COLOR);
    _tDrawGameFrameEx(field, record, true);
    EndDrawing();
}