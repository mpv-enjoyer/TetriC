#include "menu.h"
#include "render.h"
#include "shared.h"

Shared tMenu(Shared shared)
{
    while (shared.state == STATE_IN_MENU)
    {
        tDrawMenuFrame(0);
        if (IsKeyPressed(KEY_ENTER)) shared.state = STATE_PLAYING;
        if (WindowShouldClose()) shared.state = STATE_EXITING;
    }
    return shared;
}