#include <raylib.h>
#include "playing.h"
#include "input.h"
#include "replay.h"

bool _tKeyFrame(Field* field, Record* record);

Shared tPlaying(Shared shared)
{
    if (shared.field == nullptr)
    {
        shared.field = tAllocField(shared.config->replay);
        tMakeField(shared.field, shared.config);
        tMakeShape(shared.field);
        tMakeRecord(shared.current_record, shared.config);
    }
    double previous_keyframe = GetTime();
    while (shared.state == STATE_PLAYING)
    {
        double current_time = GetTime();

        int input_callback = tInput(shared.field, current_time);
        if (input_callback == CALLBACK_RESTART)
        {
            tFreeField(shared.field);
            shared.field = nullptr;
            return shared;
        }
        if (input_callback & CALLBACK_SOFTDROP) previous_keyframe = current_time;
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
#ifndef NO_FILESAVE
                SaveFileText(REPLAY_FILE_NAME, shared.field->replay->data);
#endif
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

bool _tKeyFrame(Field* field, Record* record)
{
    bool falling = tGravityShape(field);
    if (!falling)
    {
        bool good_placement = tPlaceShape(field);
        if (!good_placement) return false;
        int lines_cleared = tRemoveFullLines(field);
        record->lines_cleared += lines_cleared;
        record->score += tCalculatePointsIncrement(record, lines_cleared);
        bool good_spawn = tMakeShape(field);
        if (!good_spawn) return false;
        record->level = (record->lines_cleared / record->config->lines_for_acceleration);
    }
    tDrawGameFrame(field, record);
    return true;
}