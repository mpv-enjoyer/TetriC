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

    const int item_count = 8;
    UIItem items[item_count];
    UIItem *play, *replay, *settings, *exit, *group1, *hint, *picture, *group2;
    tBindUIItems(items, item_count, &play, &replay, &settings, &exit, &hint, &group1, &picture, &group2);

    tMakeButton(play, "Play", nullptr, AnchorPassive);
    tMakeButton(replay, "Replay", play, AnchorRight);
    replay->visible = FileExists(REPLAY_FILE_NAME);
    replay->font_size = 20;
    replay->data_button->resize_on_hover = false;
    tMakeButton(settings, "Settings", play, AnchorBottom);
    tMakeButton(exit, "Exit", settings, AnchorBottom);
    tMakeText(hint, "Replay unavailable", play, AnchorRight);
    hint->font_size = 20;
    hint->color_background = WHITE;
    hint->color_text = GRAY;
    hint->color_hitbox = LIGHTGRAY;
    hint->visible = !replay->visible;
    tMakePictureBox(picture, "assets/linus.png", group1, AnchorRight);
    picture->padding = 50;
    tMakeGroup(group1, "Group1", nullptr, 4, play, settings, exit, hint);
    group1->position_anchor = AnchorPassive;
    tMakeGroup(group2, "Group2", nullptr, 2, group1, picture);

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