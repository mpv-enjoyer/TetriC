#include "menu.h"
#include "render.h"
#include "shared.h"
#include "helpers.h"
#include "bg.h"

#include "button.h"

Shared tMenu(Shared shared)
{
    tInitMenuBackground();

    UIItem items[4];
    tMakeButton(&(items[0]), "Play", nullptr, AnchorPassive);
    tMakeButton(&(items[1]), "Replay last game", &(items[0]), AnchorRight);
    items[1].font_size = 10;
    items[1].data_button->resize_on_hover = false;
    tMakeButton(&(items[2]), "Settings", &(items[0]), AnchorBottom);
    items[2].stretch_x = true;
    items[2].secondary_anchor = AnchorLeft;
    tMakeButton(&(items[3]), "Exit", &(items[2]), AnchorBottom);

    while (shared.state == STATE_IN_MENU)
    {
        tDrawMenuFrame(&(items[0]), 4);
        if (items[0].mouse_released) shared.state = STATE_PLAYING;
        if (items[1].mouse_released) shared.state = STATE_REPLAY;
        if (items[2].mouse_released) shared.state = STATE_IN_SETTINGS;
        if (items[3].mouse_released) shared.state = STATE_EXITING;
        if (IsKeyPressed(KEY_ENTER)) shared.state = STATE_PLAYING;
        if (WindowShouldClose()) shared.state = STATE_EXITING;
    }

    for (int i = 0; i < 4; i++)
    {
        items[i].Free(&(items[i]));
    }

    return shared;
}