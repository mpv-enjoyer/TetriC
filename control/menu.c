#include "menu.h"
#include "render.h"
#include "shared.h"
#include "helpers.h"
#include "bg.h"

#include "uiitem.h"

Shared tMenu(Shared shared)
{
    tInitMenuBackground();

    const int item_count = 9;
    UIItem items[item_count];
    UIItem *play, *replay, *settings, *exit, *group, *hint, *input_name, *doublebox, *intbox;
    tBindUIItems(items, item_count, &play, &replay, &settings, &exit, &group, &hint, &input_name, &doublebox, &intbox);

    tMakeButton(play, "Play", nullptr, AnchorPassive);
    tMakeButton(replay, "Replay", play, AnchorRight);
    replay->visible = FileExists("replay.ggg");
    replay->font_size = 20;
    replay->data_button->resize_on_hover = false;
    tMakeButton(settings, "Settings", play, AnchorBottom);
    tMakeButton(exit, "Exit", settings, AnchorBottom);
    tMakeGroup(group, "Group", nullptr, 3, play, settings, exit);
    tMakeText(hint, "Replay unavailable", play, AnchorRight);
    hint->outline_size = 3;
    hint->font_size = 20;
    hint->color_background = WHITE;
    hint->color_text = GRAY;
    hint->color_hitbox = DARKGRAY;
    hint->visible = !replay->visible;
    tMakeTextBox(input_name, "Test input", exit, AnchorBottom, "label", 100);
    input_name->secondary_anchor = AnchorRight;
    input_name->stretch_x = false;
    input_name->data_textbox->label_item->color_background = WHITE;
    input_name->data_textbox->is_number = true;
    input_name->data_textbox->is_integer = true;
    tMakeDoubleBox(doublebox, "BOX", nullptr, AnchorTop, 10, 1, 100);
    tMakeIntBox(intbox, "INTBOX !!!!", doublebox, AnchorTop, 10, 1, 1000);
    

    while (shared.state == STATE_IN_MENU)
    {
        tDrawMenuFrame(&(items[0]), item_count);
        if (play->mouse_released) shared.state = STATE_PLAYING;
        if (replay->mouse_released) shared.state = STATE_REPLAY;
        if (settings->mouse_released) shared.state = STATE_IN_SETTINGS;
        if (exit->mouse_released) shared.state = STATE_EXITING;
        if (IsKeyPressed(KEY_ENTER)) shared.state = STATE_PLAYING;
        if (WindowShouldClose()) shared.state = STATE_EXITING;
    }

    for (int i = 0; i < item_count; i++)
    {
        items[i].Free(&(items[i]));
    }

    return shared;
}