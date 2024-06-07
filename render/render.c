#include "render.h"
#include "gameelements.h"
#include "bg.h"

void tDrawGameFrame(const Field* field, const Record *record)
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
        DrawFPS(0, 0);
        tDrawField(field, begin_x, rectangle_size);
        tDrawShape(field->shape, begin_x, rectangle_size);
        tDrawStatistics(record, begin_x);
        tDrawHoldShape(field->shape_hold, begin_x, rectangle_size);
        tDrawNextShapes(field->bag, begin_x);
    EndDrawing();
}

int tDrawMenuFrame()
{
    const static int item_count = 3;
    const static char* item_strings[item_count] = {"Play", "Settings", "Exit"};
    BeginDrawing();
    ClearBackground(RAYWHITE);
    tDrawMenuBackground();
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
    float rectangle_size = GetRenderHeight() / (FIELD_HEIGHT + FIELD_OUTSIDE_HEIGHT);
    float begin_x = GetRenderWidth() / 2 - rectangle_size * FIELD_WIDTH / 2;
    tDrawField(field, begin_x, rectangle_size);
    tDrawShape(field->shape, begin_x, rectangle_size);
    tDrawStatistics(record, begin_x);
    tDrawHoldShape(field->shape_hold, begin_x, rectangle_size);
    tDrawNextShapes(field->bag, begin_x);

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