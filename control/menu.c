#include "menu.h"
#include "render.h"
#include "shared.h"
#include "helpers.h"
#include "bg.h"
#include "replay.h"

#include "uiitem.h"

Shared tMenu(Shared shared)
{
    tInitMenuBackground();

    const int item_count = 9;
    UIItem items[item_count];
    UIItem *play, *play_40_lines, *replay, *settings, *exit, *group1, *hint, *picture, *group2;
    tBindUIItems(items, item_count, &play, &play_40_lines, &replay, &settings, &exit, &hint, &group1, &picture, &group2);

    tMakeButton(play, "Play", nullptr, UIItemAnchorPassive);
    tMakeButton(play_40_lines, "Play 40 lines", play, UIItemAnchorBottom);
    tMakeButton(replay, "Replay", play, UIItemAnchorRight);
    replay->visible = false;
    replay->font_size = 20;
    replay->data_button->resize_on_hover = false;
    tMakeButton(settings, "Settings", play_40_lines, UIItemAnchorBottom);
    tMakeButton(exit, "Exit", settings, UIItemAnchorBottom);
    tMakeText(hint, "Press Enter", play, UIItemAnchorRight);
    hint->font_size = 20;
    hint->color_background = WHITE;
    hint->color_text = GRAY;
    hint->color_hitbox = LIGHTGRAY;
    tMakeGroup(group1, "Group1", nullptr, 4, play, play_40_lines, settings, exit, hint);
    group1->position_anchor = UIItemAnchorPassive;
    tMakePictureBox(picture, "assets/linus.png", group1, UIItemAnchorRight);
    picture->padding = 50;
    tMakeGroup(group2, "Group2", nullptr, 2, group1, picture);

    while (shared.state == STATE_IN_MENU)
    {
        tDrawMenuFrame(&(items[0]), item_count);
        if (play->mouse_released || IsKeyPressed(KEY_ENTER))
        {
            shared.state = STATE_PLAYING;
            shared.is_40_lines = false;
        }
        if (play_40_lines->mouse_released)
        {
            shared.state = STATE_PLAYING;
            shared.is_40_lines = true;
        }
        if (replay->mouse_released) shared.state = STATE_REPLAY;
        if (settings->mouse_released) shared.state = STATE_IN_SETTINGS;
        if (exit->mouse_released) shared.state = STATE_EXITING;
        if (WindowShouldClose()) shared.state = STATE_EXITING;
    }

    for (int i = 0; i < item_count; i++)
    {
        items[i].Free(&(items[i]));
    }

    return shared;
}