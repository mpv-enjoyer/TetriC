#include "pause.h"
#include "render.h"

Shared tPause(Shared shared)
{
    while (shared.state == STATE_PAUSED)
    {
        tDrawPauseFrame(0);
        if (IsKeyPressed(KEY_ENTER)) shared.state = STATE_PLAYING;
        if (IsKeyPressed(KEY_ESCAPE))
        {
            shared.field = nullptr;
            shared.shape = nullptr;
            shared.state = STATE_IN_MENU;
        }
        if (WindowShouldClose()) shared.state = STATE_EXITING;
    }
    return shared;
}