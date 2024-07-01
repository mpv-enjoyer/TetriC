#include "pause.h"
#include "render.h"
#include "uiitem.h"

Shared tPause(Shared shared)
{
    const int item_count = 3;
    UIItem items[item_count];
    tMakeButton(&(items[0]), "Continue", nullptr, AnchorPassive);
    tMakeButton(&(items[1]), "To menu", &(items[0]), AnchorBottom);
    tMakeGroup(&(items[2]), "Group", nullptr, 2, &(items[0]), &(items[1]));

    while (shared.state == STATE_PAUSED)
    {
        tDrawPauseFrame(&(items[0]), item_count, shared.field, shared.current_record);
        if (items[0].mouse_released || IsKeyPressed(KEY_ENTER)) shared.state = STATE_PLAYING;
        if (items[1].mouse_released || IsKeyPressed(KEY_ESCAPE))
        {
            tFreeField(shared.field);
            shared.field = nullptr;
            shared.state = STATE_IN_MENU;
        }
        if (WindowShouldClose()) shared.state = STATE_EXITING;
    }
    return shared;
}