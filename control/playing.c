#include <raylib.h>
#include "playing.h"
#include "input.h"
#include "replay.h"

bool _tKeyFrame(Field* field, Record* record, bool is_40_lines);

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
        tUpdateShapeShadow(shared.field);
        if (input_callback == CALLBACK_RESTART)
        {
            tFreeField(shared.field);
            shared.field = nullptr;
            return shared;
        }
        if (input_callback & CALLBACK_SOFTDROP) previous_keyframe = current_time;
        bool want_faster_keyframe = input_callback & CALLBACK_FASTER_KEYFRAME;
        if (input_callback & CALLBACK_PAUSE) shared.state = STATE_PAUSED;
        bool want_keyframe = input_callback & CALLBACK_KEYFRAME;

        bool is_lying_on_ground = shared.field->shape->y == shared.field->shape->y_shadow;
        bool was_lying_on_ground = shared.field->is_shape_on_ground;
        if (is_lying_on_ground && !was_lying_on_ground)
        {
            shared.field->is_shape_on_ground = true;
            shared.field->shape_on_ground_begin = current_time;
        }
        else if (!is_lying_on_ground) shared.field->is_shape_on_ground = false;

        double wait_keyframe = tCalculateFrameTime(shared.current_record, want_faster_keyframe);
        double delta_keyframe_time = current_time - previous_keyframe;
        int keyframe_count = want_keyframe ? 1 : 0;
        if (!shared.field->is_shape_on_ground)
        {
            if (was_lying_on_ground) previous_keyframe = current_time;
            else
            {
                if (!want_faster_keyframe && delta_keyframe_time >= wait_keyframe) keyframe_count = delta_keyframe_time / wait_keyframe;
                if (!want_keyframe) previous_keyframe += keyframe_count * wait_keyframe;
                else previous_keyframe = current_time;
            }
        }
        else
        {
            double waiting = current_time - shared.field->shape_on_ground_begin;
            double wait_on_ground = shared.config->wait_on_ground_seconds;
            if (waiting >= wait_on_ground) keyframe_count = (waiting - wait_on_ground) / wait_keyframe + 1;
            if (keyframe_count > 0 && !want_keyframe) previous_keyframe += wait_on_ground + (keyframe_count - 1) * wait_keyframe;
            else if (want_keyframe) previous_keyframe = current_time;
        }
        if (delta_keyframe_time < 0) D_ASSERT(false);

        if (was_lying_on_ground && !is_lying_on_ground) printf("was_lying_on_ground and not on ground");
        shared.current_record->time += GetFrameTime();
        if (keyframe_count != 0)
        {
            for (int i = 0; i < keyframe_count; i++)
            {
                if (!_tKeyFrame(shared.field, shared.current_record, shared.is_40_lines))
                {
#ifndef NO_FILESAVE
                    SaveFileText(REPLAY_FILE_NAME, shared.field->replay->data);
#endif
                    shared.state = STATE_GAME_OVER;
                    tFreeField(shared.field);
                    shared.field = nullptr;
                    break;
                }
            }
            printf("delta_keyframe_time %f, wait_keyframe %f, keyframe_count %i, current_time %f\n", delta_keyframe_time, wait_keyframe, keyframe_count, current_time);
            printf("was_lying_on_ground %i, is lying on ground %i, want keyframe %i", was_lying_on_ground ? 1 : 0, is_lying_on_ground ? 1 : 0, want_keyframe ? 1 : 0)
        }
        else
        {
            tDrawGameFrame(shared.field, shared.current_record, shared.is_40_lines);
        }
        if (WindowShouldClose())
        {
            shared.state = STATE_EXITING;
            break;
        }
    }
    return shared;
}

bool _tKeyFrame(Field* field, Record* record, bool is_40_lines)
{
    if (is_40_lines && record->lines_cleared == 40) return false;
    bool falling = tGravityShape(field);
    if (!falling)
    {
        bool good_placement = tPlaceShape(field);
        if (!good_placement) return false;
        record->shapes_placed++;
        int lines_cleared = tRemoveFullLines(field);
        record->lines_cleared += lines_cleared;
        record->score += tCalculatePointsIncrement(record, lines_cleared);
        bool good_spawn = tMakeShape(field);
        if (!good_spawn) return false;
        if (!is_40_lines) record->level = (record->lines_cleared / record->config->lines_for_acceleration);
    }
    tDrawGameFrame(field, record, is_40_lines);
    return true;
}