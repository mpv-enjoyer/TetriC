#include "playing.h"

bool _tKeyFrame(Field* field, Shape* shape, Record* record);
double _tCalculateFrameTime(int level, double begin, double acceleration, double min);

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
        shared.current_record.config = nullptr;
        shared.current_record.lines_cleared = 0;
        shared.current_record.score = 0;
        shared.current_record.time = 0;
        shared.current_record.config = shared.config;
        shared.current_record.level = 0;
    }

    int current_key = KEY_NULL;
    double current_key_timing = 0.0f;
    double previous_keyframe = GetTime();
    while (shared.state == STATE_PLAYING)
    {
        int level = shared.current_record.level;
        double begin_sec = shared.config->begin_keyframe_seconds;
        double acceleration = shared.config->acceleration;
        double min_sec = shared.config->min_keyframe_seconds;
        
        wait_keyframe = _tCalculateFrameTime(level, begin_sec, acceleration, min_sec);
        double faster_keyframe = wait_keyframe / 2;

        double current_wait_time = wait_keyframe;
        bool current_hard_dropped = false;

        bool current_key_exists = false;
        current_key_exists |= IsKeyDown(KEY_DOWN);
        current_key_exists |= IsKeyDown(KEY_LEFT);
        current_key_exists |= IsKeyDown(KEY_RIGHT);
        if (!current_key_exists)
        {
            current_key = KEY_NULL;
            current_key_timing = -HOLD_TIMEOUT;
        }
        else
        {
            if (current_key != )
            if (current_key_timing < 0)
            {
                
            }
        }

        bool should_keyframe = false;
        should_keyframe |= current_hard_dropped;
        should_keyframe |= GetTime() - previous_keyframe >= current_wait_time;
        if (should_keyframe)
        {
            double deltatime = GetTime() - previous_keyframe;
            shared.current_record.time += deltatime;
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
            tDrawGameFrame(field, shape, &(shared.current_record));
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
    static double __previous = 0.0;
    printf("%f\n", GetTime() - __previous);
    __previous = GetTime();

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

        record->level = (record->lines_cleared / record->config->lines_for_acceleration);
    }
    tDrawGameFrame(field, shape, record);
    return true;
}

double _tCalculateFrameTime(int level, double begin, double acceleration, double min)
{
    D_ASSERT(level >= 0);
    D_ASSERT(min >= 0);
    double output = begin - acceleration * level;
    if (output < min) output = min;
    return output;
}