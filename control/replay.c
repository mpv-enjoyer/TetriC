#include "replay.h"
#include "render.h"
#include "action.h"

bool _tKeyFrame(Field* field, Record* record, int next_shape_type);

Shared tReplay(Shared shared)
{
    if (!FileExists(REPLAY_FILE_NAME))
    {
        shared.state = STATE_IN_MENU;
        return shared;
    }
    shared.current_replay = LoadFileText(REPLAY_FILE_NAME);
    shared.field = tAllocField(shared.config->replay);
    tMakeField(shared.field, shared.config);
    tMakeShapeKnown(shared.field, shared.current_replay[0] - '0');
    tMakeRecord(shared.current_record, shared.config);

    size_t index = 0;

    double previous_keyframe = GetTime();
    while (shared.state == STATE_REPLAY)
    {
        double current_time = GetTime();

        double wait_keyframe = tCalculateFrameTime(shared.current_record, false);
        double delta_keyframe_time = current_time - previous_keyframe;
        bool should_keyframe = delta_keyframe_time >= wait_keyframe;
        tUpdateShapeShadow(shared.field);

        bool game_ended = false;

        if (should_keyframe)
        {
            shared.current_record->time += delta_keyframe_time;
            index++;
            int next_figure_type = -1;
            
            while (shared.current_replay[index] != '\n')
            {
                switch (shared.current_replay[index])
                {
                    case (ACTION_HARD_DROP): tHardDropShape(shared.field); break;
                    case (ACTION_LEFT): tMoveShapeLeft(shared.field); break;
                    case (ACTION_RIGHT): tMoveShapeRight(shared.field); break;
                    case (ACTION_ROTATE_LEFT): tRotateShapeLeft(shared.field); break;
                    case (ACTION_ROTATE_RIGHT): tRotateShapeRight(shared.field); break;
                }
                if (shared.current_replay[index] >= '0' && shared.current_replay[index] <= '9') next_figure_type = shared.current_replay[index] - '0';
                if (shared.current_replay[index] == '\0') game_ended = true;
                index++;
            }
            next_figure_type = shared.current_replay[index + 1] - '0';
            game_ended |= !_tKeyFrame(shared.field, shared.current_record, next_figure_type);
            previous_keyframe = current_time;
        }
        else
        {
            tDrawReplayFrame(shared.field, shared.current_record);
        }
        if (IsKeyPressed(KEY_ESCAPE) || game_ended)
        {
            shared.state = STATE_IN_MENU;
            tFreeField(shared.field);
            shared.field = nullptr;
            UnloadFileText(shared.current_replay);
            shared.current_replay = nullptr;
            break;
        }
        if (WindowShouldClose())
        {
            shared.state = STATE_EXITING;
            break;
        }
    }
    return shared;
}

bool _tKeyFrame(Field* field, Record* record, int next_shape_type)
{
    bool falling = tGravityShape(field);
    if (!falling)
    {
        bool good_placement = tPlaceShape(field);
        if (!good_placement) return false;
        int lines_cleared = tRemoveFullLines(field);
        record->lines_cleared += lines_cleared;
        record->score += tCalculatePointsIncrement(record, lines_cleared);
        bool good_spawn = tMakeShapeKnown(field, next_shape_type);
        if (!good_spawn) return false;
        record->level = (record->lines_cleared / record->config->lines_for_acceleration);
    }
    tDrawReplayFrame(field, record);
    return true;
}