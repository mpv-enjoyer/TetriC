#include "action.h"
#include "state.h"
#include "record.h"
#include "config.h"
#include "render.h"

int _state = STATE_PLAYING;

bool _tKeyFrame(Field* field, Shape* shape);
bool _tMenu();

void tInit()
{
    InitWindow(WIDTH, HEIGHT, "TetriC");
    SetTargetFPS(60);
    srand(time(NULL));
    SetExitKey(KEY_NULL);
}

void tMainLoop()
{
    while (true)
    {
        switch (_state)
        {
            case (STATE_PLAYING): _state = tPlaying(); break;
            case (STATE_GAME_OVER): break;
            case (STATE_IN_MENU): _state = _tMenu(); break;
            case (STATE_PAUSED): break;
            case (STATE_IN_SETTINGS): break;
            case (STATE_EXITING): return;
        }
    }
}

void tEnd()
{
    CloseWindow();
}

bool _tMenu()
{
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ENTER)) return true;
    }
    return false;
}