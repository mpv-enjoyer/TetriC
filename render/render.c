#include "render.h"
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
    const float sector_height = 22;
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

int tDrawPauseFrame(const _Field* field, const Record *record)
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

    const float sector_height = 22;
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

int tDrawSettingsFrame(const Config* config, int active_element, char* data, int data_size)
{
    const static int item_count = 6;
    const static char* item_strings[item_count] = {"To menu",
                                                   "Acceleration per level (sec)",
                                                   "Gravitation at level 0 (sec)",
                                                   "Lines to level up",
                                                   "Maximum gravitation (sec)",
                                                   "Super Rotation System"};
    
    const static int input_buffer_size = 15;
    static char input_buffer[input_buffer_size];
    BeginDrawing();
        ClearBackground(RAYWHITE);
        int x = 10;
        int y = 10;

        int height;
        if (tButton(x, y, item_strings[0], &height)) return 0;
        y += height;

        bool was_active = active_element == 1;
        bool is_active;
        bool ready = tTextBox(input_buffer, input_buffer_size, x, y, TEXTBOX_MODE_FLOAT, item_strings[1], &height, &is_active);
        if (!was_active && is_active)
        {
            snprintf(input_buffer, input_buffer_size, "%s");
        }
        if (ready) strncpy(data, input_buffer, MIN(data_size, input_buffer_size));
        if (ready) return 1;

        
        static bool some_value = false;
        static char string1[100];
        static char string2[100];
        int h1;
        tCheckbox(&some_value, 0, 10, "Some value", &h1);
        int h2;
        tButton(0, 10 + h1, "Button", &h2);
        static bool active1 = true;
        int h3;
        tTextBox(string1, 10, 0, 10 + h1 + h2, TEXTBOX_MODE_STRING, "Any text", &h3, &active1);
        static bool active2 = false;
        tTextBox(string2, 10, 0, 10 + h1 + h2 + h3, TEXTBOX_MODE_FLOAT, "Input float here :D", nullptr, &active2);
    EndDrawing();
}