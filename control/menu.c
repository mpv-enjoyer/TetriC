#include "menu.h"
#include "render.h"
#include "shared.h"
#include "helpers.h"
#include "bg.h"

#include "uiitem.h"

Shared tMenu(Shared shared)
{
    tInitMenuBackground();

    const int item_count = 12;
    UIItem items[item_count];
    tMakeButton(&(items[0]), "Play", nullptr, AnchorPassive);
    tMakeButton(&(items[1]), "Replay last game", &(items[0]), AnchorRight);
    items[1].font_size = 20;
    items[1].data_button->resize_on_hover = false;
    tMakeButton(&(items[2]), "Settings", &(items[0]), AnchorBottom);
    tMakeButton(&(items[3]), "Exit", &(items[2]), AnchorBottom);
    tMakeButton(&(items[4]), "Some button with big outline", &(items[2]), AnchorLeft);
    items[4].outline_size = 10;
    tMakeGroup(&(items[5]), "Group", nullptr, &(items[0]), 5);
    items[5].position_anchor = AnchorPassive;
    tMakeButton(&(items[6]), "Button outside group", &(items[5]), AnchorRight);
    items[6].secondary_anchor = AnchorBottom;
    tMakeButton(&(items[7]), "Some more", &(items[6]), AnchorPassive);
    items[7].secondary_anchor = AnchorLeft;
    tMakeButton(&(items[8]), "Buttons :)", &(items[7]), AnchorBottom);
    items[8].secondary_anchor = AnchorLeft;
    tMakeGroup(&(items[9]), "Group2", &(items[6]), &(items[7]), 2);
    items[9].position_anchor = AnchorBottom;
    items[9].secondary_anchor = AnchorLeft;
    tMakeButton(&(items[10]), "I am huge holy moly hahaha", &(items[5]), AnchorTop);
    items[10].font_size = 60;
    items[10].data_button->resized_text_size = 70;
    tMakeGroup(&(items[11]), "Group3", nullptr, &(items[5]), 6);

    while (shared.state == STATE_IN_MENU)
    {
        tDrawMenuFrame(&(items[0]), item_count);
        if (items[0].mouse_released) shared.state = STATE_PLAYING;
        if (items[1].mouse_released) shared.state = STATE_REPLAY;
        if (items[2].mouse_released) shared.state = STATE_IN_SETTINGS;
        if (items[3].mouse_released) shared.state = STATE_EXITING;
        if (IsKeyPressed(KEY_ENTER)) shared.state = STATE_PLAYING;
        if (WindowShouldClose()) shared.state = STATE_EXITING;
    }

    for (int i = 0; i < item_count; i++)
    {
        items[i].Free(&(items[i]));
    }

    return shared;
}