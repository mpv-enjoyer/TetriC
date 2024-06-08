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
    //SetTargetFPS(60);
    srand(time(NULL));
    SetExitKey(KEY_NULL);
}

void tMainLoop()
{
    Shared shared_data;
    Config config;
    Record current_record;
    shared_data.config = &config;
    shared_data.state = STATE_IN_MENU;
    shared_data.field = nullptr;
    shared_data.current_record = &current_record;

    tMakeConfigDefault(&config);
    tLoadConfig(&config, "tetriC.data");

    while (shared_data.state != STATE_EXITING)
    {
        switch (shared_data.state)
        {
            case (STATE_PLAYING): shared_data = tPlaying(shared_data); break;
            case (STATE_GAME_OVER): shared_data = tGameOver(shared_data); break;
            case (STATE_IN_MENU): shared_data = tMenu(shared_data); break;
            case (STATE_PAUSED): shared_data = tPause(shared_data); break;
            case (STATE_IN_SETTINGS): shared_data = tSettings(shared_data); break;
        }
    }
    tSaveConfig(&config, "tetriC.data");
}

void tEnd()
{
    CloseWindow();
}