#include "menu.h"
#include "render.h"
#include "shared.h"
#include "helpers.h"
#include "bg.h"

#include "uiitem.h"

Shared tMenu(Shared shared)
{
    tInitMenuBackground();

    const int item_count = 6;
    UIItem items[item_count];
    UIItem *play, *replay, *settings, *exit, *group, *hint;
    tBindUIItems(items, item_count, &play, &replay, &settings, &exit, &group, &hint);

    tMakeButton(play, "Play", nullptr, AnchorPassive);
    tMakeButton(replay, "Replay", play, AnchorRight);
    replay->visible = FileExists("replay.ggg");
    replay->font_size = 20;
    replay->data_button->resize_on_hover = false;
    tMakeButton(settings, "Settings", play, AnchorBottom);
    tMakeButton(exit, "Exit", settings, AnchorBottom);
    tMakeGroup(group, "Group", nullptr, 3, play, settings, exit);
    tMakeText(hint, "Replay unavailable", play, AnchorRight);
    hint->outline_size = 1;
    hint->font_size = 20;
    hint->color_text = GRAY;
    hint->visible = !replay->visible;

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