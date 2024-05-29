#include "playing.h"

bool _tKeyFrame(Field* field, Shape* shape, Record* record);

Shared tPlaying(Shared shared)
{
    Shape* shape;
    Field* field;
    Shape new_shape;
    double wait_keyframe;
    if (shared.field != nullptr)
    {
        D_ASSERT(shared.shape != nullptr);
        Config* config;
        tLoadFromShared(&shared, &field, &shape, &config, nullptr);
        int acceleration_times = (shared.current_record.lines_cleared / config->lines_for_acceleration);
        wait_keyframe = config->begin_keyframe_seconds - acceleration_times * config->acceleration;
        if (wait_keyframe < config->min_keyframe_seconds) wait_keyframe = config->min_keyframe_seconds;
    }
    else
    {
        D_ASSERT(shared.shape == nullptr);
        tResetRNG();
        field = (Field*)calloc(FIELD_HEIGHT * FIELD_WIDTH, sizeof(char));
        shape = &new_shape;
        tMakeShape(field, shape);
        shared.field = field;
        shared.shape = shape;
        wait_keyframe = shared.config->begin_keyframe_seconds;
        shared.current_record.lines_cleared = 0;
        shared.current_record.score = 0;
        shared.current_record.time = 0;
    }

    double faster_keyframe = wait_keyframe / 2;
    double previous_keyframe = GetTime();

    while (shared.state == STATE_PLAYING)
    {
        shared.current_record.time += GetFrameTime();
        double current_wait_time = wait_keyframe;
        bool current_hard_dropped = false;

        int key = GetKeyPressed();
        while (key != KEY_NULL)
        {
            switch (key)
            {
            case KEY_Z: tRotateShapeLeft(field, shape); break;
            case KEY_X: tRotateShapeRight(field, shape); break;
            case KEY_UP: tRotateShapeRight(field, shape); break;
            case KEY_LEFT: tMoveShapeLeft(field, shape); break;
            case KEY_RIGHT: tMoveShapeRight(field, shape); break;
            case KEY_DOWN: current_wait_time = faster_keyframe; break;
            case KEY_SPACE: tHardDropShape(field, shape); current_hard_dropped = true; break;
            case KEY_ESCAPE: shared.state = STATE_PAUSED; break;
            }
            key = GetKeyPressed();
        }

        bool should_keyframe = false;
        should_keyframe |= current_hard_dropped;
        should_keyframe |= GetTime() - previous_keyframe >= current_wait_time;
        if (should_keyframe)
        {
            if (!_tKeyFrame(field, shape, &shared.current_record))
            {
                shared.state = STATE_GAME_OVER;
                free(field);
                shared.field = nullptr;
                shared.shape = nullptr;
                break;
            }
            previous_keyframe = GetTime();
        }
        else
        {
            tDrawGameFrame(field, shape);
        }
        if (WindowShouldClose())
        {
            shared.state = STATE_EXITING;
            break;
        }
    }
    return shared;
}

bool _tKeyFrame(Field* field, Shape* shape, Record* record)
{
    bool falling = tGravity(field, shape);
    if (!falling)
    {
        bool good_placement = tPlaceShape(field, shape);
        if (!good_placement) return false;
        while (true)
        {
            int found = tFindLine(field);
            if (found == -1) break;
            record->lines_cleared++;
            tRemoveLine(field, found);
        }
        bool good_spawn = tMakeShape(field, shape);
        if (!good_spawn) return false;
    }
    tDrawGameFrame(field, shape);
    return true;
}