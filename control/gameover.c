#include "gameover.h"
#include "render.h"

Shared tGameOver(Shared shared)
{
    while (shared.state == STATE_GAME_OVER)
    {
        tDrawGameOverFrame(shared.current_record->lines_cleared);
        if (IsKeyPressed(KEY_ENTER)) shared.state = STATE_IN_MENU;
        if (WindowShouldClose()) shared.state = STATE_EXITING;
    }
    return shared;
}