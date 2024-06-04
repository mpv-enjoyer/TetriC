#include <raylib.h>
#include "input.h"
#include "action.h"

int last_key = KEY_NULL;
double last_key_begin_time = 0;
double last_action_time = 0;

int tInput(_Field* field, double time)
{
    int callback = CALLBACK_NOTHING;
    int key = GetKeyPressed();
    while (key != KEY_NULL)
    {
        switch (key)
        {
        case KEY_Z: if (!tRotateShapeLeft(field)) callback |= CALLBACK_COLLISION; break;
        case KEY_X: if (!tRotateShapeRight(field)) callback |= CALLBACK_COLLISION; break;
        case KEY_UP: if (!tRotateShapeRight(field)) callback |= CALLBACK_COLLISION; break;
        case KEY_LEFT: 
            if (!tMoveShapeLeft(field)) callback |= CALLBACK_COLLISION;
            if (last_key != KEY_LEFT)
            {
                last_key = KEY_LEFT;
                last_key_begin_time = time;
                last_action_time = 0;
            }
            break;
        case KEY_RIGHT: 
            if (!tMoveShapeRight(field)) callback |= CALLBACK_COLLISION; 
            if (last_key != KEY_RIGHT)
            {
                last_key = KEY_RIGHT;
                last_key_begin_time = time;
                last_action_time = 0;
            }
            break;
        case KEY_SPACE: 
            if (tHardDropShape(field)) callback |= CALLBACK_HARDDROP;
            callback |= CALLBACK_KEYFRAME;
            break;
        case KEY_ESCAPE: callback |= CALLBACK_PAUSE; break;
        }
        key = GetKeyPressed();
    }

    if (IsKeyDown(KEY_DOWN)) callback |= CALLBACK_FASTER_KEYFRAME;

    if (last_key == KEY_NULL) return callback;
    if (!IsKeyDown(last_key))
    {
        last_key = KEY_NULL;
        return callback;
    }

    if (time - last_key_begin_time > HOLD_TIMEOUT && time - last_action_time > HOLD_INTERVAL)
    {
        last_action_time = time;
        if (last_key == KEY_LEFT && !tMoveShapeLeft(field)) callback |= CALLBACK_COLLISION;
        if (last_key == KEY_RIGHT && !tMoveShapeRight(field)) callback |= CALLBACK_COLLISION;
    }
    return callback;
}