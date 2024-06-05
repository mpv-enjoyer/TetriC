#include "settings.h"
#include "render.h"

Shared tSettings(Shared shared)
{
    int active_input = -1;
    while (shared.state == STATE_IN_SETTINGS)
    {
        tDrawSettingsFrame(shared.config, active_input);
        if (WindowShouldClose())
        {
            shared.state = STATE_EXITING;
            break;
        }
        if (IsKeyPressed(KEY_ESCAPE)) shared.state = STATE_IN_MENU;
    }
    return shared;
}