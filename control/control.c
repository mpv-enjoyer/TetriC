#include "action.h"
#include "shared.h"
#include "record.h"
#include "config.h"
#include "render.h"
#include "menu.h"
#include "playing.h"
#include "gameover.h"
#include "pause.h"
#include "settings.h"

void tInit()
{
    InitWindow(WIDTH, HEIGHT, "TetriC");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
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
    shared_data.field = nullptr;
    shared_data.shape = nullptr;

    config.begin_keyframe_seconds = 0.2f;
    config.acceleration = 0.02f;
    config.lines_for_acceleration = 5;
    config.min_keyframe_seconds = 1.0f / 60.0f;

    while (true)
    {
        switch (shared_data.state)
        {
            case (STATE_PLAYING): shared_data = tPlaying(shared_data); break;
            case (STATE_GAME_OVER): shared_data = tGameOver(shared_data); break;
            case (STATE_IN_MENU): shared_data = tMenu(shared_data); break;
            case (STATE_PAUSED): shared_data = tPause(shared_data); break;
            case (STATE_IN_SETTINGS): shared_data = tSettings(shared_data); break;
            case (STATE_EXITING): return;
        }
    }
}

void tEnd()
{
    CloseWindow();
}