#include "playing.h"

bool _already_playing = false;
double _wait_keyframe;
double _faster_keyframe;
Shape _shape_data;
Shape* _shape;
Field* _field;

bool _tKeyFrame();

int tPlaying(const Config* config)
{
    if (!_already_playing)
    {
        tResetRNG();
        _field = (Field*)calloc(FIELD_HEIGHT * FIELD_WIDTH, sizeof(char));
        _shape = &_shape_data;
        tMakeShape(_field, _shape);
        _already_playing = true;
        _wait_keyframe = config->keyframe_seconds;
        _faster_keyframe = config->faster_keyframe_seconds;
    }
    
    double previous_keyframe = GetTime();

    while (_already_playing)
    {
        double current_wait_time = _wait_keyframe;
        bool current_hard_dropped = false;

        int key = GetKeyPressed();
        while (key != -1)
        {
            switch (key)
            {
            case KEY_Z: tRotateShapeLeft(_field, _shape); break;
            case KEY_X: tRotateShapeRight(_field, _shape); break;
            case KEY_UP: tRotateShapeRight(_field, _shape); break;
            case KEY_LEFT: tMoveShapeLeft(_field, _shape); break;
            case KEY_RIGHT: tMoveShapeRight(_field, _shape); break;
            case KEY_DOWN: current_wait_time = _faster_keyframe; break;
            case KEY_SPACE: tHardDropShape(_field, _shape); current_hard_dropped = true; break;
            }
            key = GetKeyPressed();
        }

        bool should_keyframe = false;
        should_keyframe |= current_hard_dropped;
        should_keyframe |= GetTime() - previous_keyframe >= current_wait_time;
        if (should_keyframe)
        {
            _already_playing = _tKeyFrame(_field, _shape);
            previous_keyframe = GetTime();
        }
        else
        {
            tDrawGameFrame(_field, _shape);
        }
        if (WindowShouldClose()) return STATE_EXITING;
    }
    free(_field);
    return STATE_GAME_OVER;
}

bool _tKeyFrame()
{
    bool falling = tGravity(_field, _shape);
    if (!falling)
    {
        bool good_placement = tPlaceShape(_field, _shape);
        if (!good_placement) return false;
        while (true)
        {
            int found = tFindLine(_field);
            if (found == -1) break;
            tRemoveLine(_field, found);
        }
        bool good_spawn = tMakeShape(_field, _shape);
        if (!good_spawn) return false;
    }
    tDrawGameFrame(_field, _shape);
    return true;
}