#include "menu.h"
#include "render.h"
#include "shared.h"

bool _tMenu()
{
    while (true)
    {
        if (WindowShouldClose()) return STATE_EXITING;
        if (IsKeyPressed(KEY_ENTER)) return STATE_PLAYING;
    }
    return false;
}