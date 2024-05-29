#include <raylib.h>
#include "input.h"
#include "action.h"

int last_key = KEY_NULL;
double last_key_begin = 0;

int tInput(Field* field, Shape* shape, double time)
{
    int callback = CALLBACK_NOTHING;
    int key = GetKeyPressed();
    while (key != KEY_NULL)
    {
        switch (key)
        {
        case KEY_Z: if (!tRotateShapeLeft(field, shape)) callback |= CALLBACK_COLLISION; break;
        case KEY_X: if (!tRotateShapeRight(field, shape)) callback |= CALLBACK_COLLISION; break;
        case KEY_UP: if (!tRotateShapeRight(field, shape)) callback |= CALLBACK_COLLISION; break;
        case KEY_LEFT: if (!tMoveShapeLeft(field, shape)) callback |= CALLBACK_COLLISION; break;
        case KEY_RIGHT: if (!tMoveShapeRight(field, shape)) callback |= CALLBACK_COLLISION; break;
        case KEY_DOWN: callback |= CALLBACK_FASTER_KEYFRAME; break;
        case KEY_SPACE: 
            if (tHardDropShape(field, shape)) callback |= CALLBACK_HARDDROP;
            callback |= CALLBACK_KEYFRAME;
            break;
        case KEY_ESCAPE: callback |= CALLBACK_PAUSE; break;
        }
        key = GetKeyPressed();
    }
}