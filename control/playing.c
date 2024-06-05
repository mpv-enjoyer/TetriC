#include "playing.h"
#include "input.h"
#include "bag.h"
#include "field.h"

bool _tKeyFrame(_Field* field, Record* record);

Shared tPlaying(Shared shared)
{
    if (shared.field == nullptr)
    {
        tResetBag();
        shared.field = tAllocField();
        tMakeField(shared.field, shared.config);
        tMakeShape(shared.field);
        tMakeRecord(shared.current_record, shared.config);
    }

    double previous_keyframe = GetTime();
    while (shared.state == STATE_PLAYING)
    {
        double current_time = GetTime();

        int input_callback = tInput(shared.field, current_time);
        bool want_faster_keyframe = input_callback & CALLBACK_FASTER_KEYFRAME;
        if (input_callback & CALLBACK_PAUSE) shared.state = STATE_PAUSED;
        bool should_keyframe = ( input_callback & CALLBACK_KEYFRAME );

        double wait_keyframe = tCalculateFrameTime(shared.current_record, want_faster_keyframe);
        double delta_keyframe_time = current_time - previous_keyframe;
        should_keyframe |= delta_keyframe_time >= wait_keyframe;
        tUpdateShapeShadow(shared.field);
        if (should_keyframe)
        {
            shared.current_record->time += delta_keyframe_time;
            if (!_tKeyFrame(shared.field, shared.current_record))
            {
                shared.state = STATE_GAME_OVER;
                tFreeField(shared.field);
                shared.field = nullptr;
                break;
            }
            previous_keyframe = current_time;
        }
        else
        {
            tDrawGameFrame(shared.field, shared.current_record);
        }
        if (WindowShouldClose())
        {
            shared.state = STATE_EXITING;
            break;
        }
    }
    return shared;
}

bool _tKeyFrame(_Field* field, Record* record)
{
    bool falling = tGravityShape(field);
    if (!falling)
    {
        bool good_placement = tPlaceShape(field);
        if (!good_placement) return false;
        int lines_cleared = 0;
        while (true)
        {
            int found = tFindLine(field);
            if (found == -1) break;
            lines_cleared++;
            tRemoveLine(field, found);
        }
        record->lines_cleared += lines_cleared;
        int points_increment = 0;
        switch (lines_cleared)
        {
            case 0: points_increment = 0; break;
            case 1: points_increment = 40; break;
            case 2: points_increment = 100; break;
            case 3: points_increment = 300; break;
            case 4: points_increment = 1200; break;
            default: D_ASSERT(false);
        }
        record->score += points_increment;
        bool good_spawn = tMakeShape(field);
        if (!good_spawn) return false;
        record->level = (record->lines_cleared / record->config->lines_for_acceleration);
    }
    tDrawGameFrame(field, record);
    return true;
}