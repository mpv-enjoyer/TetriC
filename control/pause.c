#include "pause.h"
#include "render.h"
#include "uiitem.h"

Shared tPause(Shared shared)
{
    const int item_count = 4;
    UIItem items[item_count];
    UIItem *button_continue, *to_menu, *restart, *group;
    tBindUIItems(items, item_count, &button_continue, &to_menu, &restart, &group);

    tMakeButton(button_continue, "Continue", restart, AnchorTop);
    tMakeButton(restart, "Restart", button_continue, AnchorPassive);
    tMakeButton(to_menu, "To menu", restart, AnchorBottom);
    tMakeGroup(group, "Group", nullptr, 1, restart);

    while (shared.state == STATE_PAUSED)
    {
        tDrawPauseFrame(&(items[0]), item_count, shared.field, shared.current_record, shared.is_40_lines);
        if (button_continue->mouse_released || IsKeyPressed(KEY_ENTER)) shared.state = STATE_PLAYING;
        if (restart->mouse_released || IsKeyPressed(KEY_R))
        {
            tFreeField(shared.field);
            shared.field = nullptr;
            shared.state = STATE_PLAYING;
        }
        if (to_menu->mouse_released || IsKeyPressed(KEY_ESCAPE))
        {
            tFreeField(shared.field);
            shared.field = nullptr;
            shared.state = STATE_IN_MENU;
        }
        if (WindowShouldClose()) shared.state = STATE_EXITING;
    }

    for (int i = 0; i < item_count; i++)
    {
        items[i].Free(&(items[i]));
    }
    return shared;
}