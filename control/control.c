#include "action.h"
#include "shared.h"
#include "record.h"
#include "config.h"
#include "render.h"
#include "menu.h"

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
    Shared shared_data;
    Config config;
    shared_data.config = &config;
    shared_data.state = STATE_IN_MENU;
    
    config.begin_keyframe_seconds = 0.2f;
    config.acceleration = 0.005f;
    config.lines_for_acceleration = 5;
    config.min_keyframe_seconds = 0.05f;

    while (true)
    {
        switch (shared_data.state)
        {
            case (STATE_PLAYING): shared_data = tPlaying(); break;
            case (STATE_GAME_OVER): break;
            case (STATE_IN_MENU): shared_data = tInMenu(); break;
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