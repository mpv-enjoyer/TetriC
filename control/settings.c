#include "settings.h"
#include "render.h"
#include "uiitem.h"

Shared tSettings(Shared shared)
{
    const int item_count = 8;
    UIItem items[item_count];
    UIItem* exit, *save_exit, *begin_speed, *max_speed, *acceleration, *lines_for_next_level, *srs, *fps;
    tBindUIItems(items, item_count, &exit, &save_exit, &begin_speed, &max_speed, &acceleration, &lines_for_next_level, &srs, &fps);

    tMakeButton(save_exit, "Save and Exit", nullptr, AnchorPassive);
    save_exit->position.x = 5;
    save_exit->position.y = 5;
    save_exit->data_button->resize_on_hover = false;
    save_exit->color_text = DARKGREEN;
    tMakeButton(exit, "Exit", save_exit, AnchorRight);
    exit->data_button->resize_on_hover = false;
    tMakeDoubleBox(begin_speed, "Begin speed (blocks per second)", save_exit, AnchorBottom, 1.0f / shared.config->begin_keyframe_seconds, 0.1, 1000);
    tMakeDoubleBox(max_speed, "Max speed (blocks per second)", begin_speed, AnchorBottom, 1.0f / shared.config->min_keyframe_seconds, 0.1, 1000);
    tMakeDoubleBox(acceleration, "Acceleration (weird value)", max_speed, AnchorBottom, shared.config->acceleration, 0.00001, 100);
    tMakeIntBox(lines_for_next_level, "Lines for next level", acceleration, AnchorBottom, shared.config->lines_for_acceleration, 1, 1000);
    tMakeCheckBox(srs, "Super Rotation System", lines_for_next_level, AnchorBottom, shared.config->srs);
    srs->secondary_anchor = AnchorLeft;
    srs->padding = 3;
    tMakeIntBox(fps, "FPS", srs, AnchorBottom, shared.config->fps, 0, __INT_MAX__);
    fps->secondary_anchor = AnchorLeft;

    bool save = false;
    while (shared.state == STATE_IN_SETTINGS)
    {
        bool had_active_textbox = false;
        for (int i = 0; i < item_count; i++)
        {
            had_active_textbox |= (items[i].data_textbox && items[i].active);
        }
        tDrawSettingsFrame(&(items[0]), item_count);
        if (exit->mouse_released) shared.state = STATE_IN_MENU;
        if (save_exit->mouse_released)
        {
            save = true;
            shared.state = STATE_IN_MENU;
        }
        if (IsKeyPressed(KEY_ESCAPE) && !had_active_textbox) shared.state = STATE_IN_MENU;
        if (WindowShouldClose()) shared.state = STATE_EXITING;
    }
    
    if (save)
    {
        shared.config->begin_keyframe_seconds = 1 / begin_speed->data_doublebox->value;
        shared.config->lines_for_acceleration = lines_for_next_level->data_intbox->value;
        shared.config->min_keyframe_seconds = 1 / max_speed->data_doublebox->value;
        shared.config->acceleration = acceleration->data_doublebox->value;
        shared.config->srs = srs->data_checkbox->value;
        shared.config->fps = fps->data_intbox->value;
        if (shared.config->fps == 0)
        {
            SetWindowState(FLAG_VSYNC_HINT);
        }
        else
        {
            SetTargetFPS(shared.config->fps);
            ClearWindowState(FLAG_VSYNC_HINT);
        }
    }

    for (int i = 0; i < item_count; i++)
    {
        items[i].Free(&(items[i]));
    }
    return shared;
}
