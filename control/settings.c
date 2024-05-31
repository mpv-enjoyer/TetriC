#include "settings.h"
#include "render.h"

Shared tSettings(Shared shared)
{
    while (shared.state == STATE_IN_SETTINGS)
    {
        tDrawSettingsFrame(shared.config);
        if (IsKeyPressed(KEY_ESCAPE)) shared.state = STATE_IN_MENU;
    }
    return shared;
}