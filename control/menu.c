#include "menu.h"
#include "render.h"
#include "shared.h"
#include "helpers.h"
#include "bg.h"

Shared tMenu(Shared shared)
{
    tInitMenuBackground();
    while (shared.state == STATE_IN_MENU)
    {
        int selected = tDrawMenuFrame();
        switch (selected)
        {
            case 0: shared.state = STATE_PLAYING; break;
            case 1: shared.state = STATE_REPLAY; break;
            case 2: shared.state = STATE_IN_SETTINGS; break;
            case 3: shared.state = STATE_EXITING; break;
        }
        if (IsKeyPressed(KEY_ENTER)) shared.state = STATE_PLAYING;
        if (WindowShouldClose()) shared.state = STATE_EXITING;
    }
    return shared;
}