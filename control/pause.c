#include "pause.h"
#include "render.h"

Shared tPause(Shared shared)
{
    while (shared.state == STATE_PAUSED)
    {
        int selected = tDrawPauseFrame(shared.field, shared.shape, &(shared.current_record));
        switch (selected)
        {
            case 0: shared.state = STATE_PLAYING; break;
            case 1: shared.field = nullptr;
                    shared.shape = nullptr;
                    shared.state = STATE_IN_MENU; break;
        }
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