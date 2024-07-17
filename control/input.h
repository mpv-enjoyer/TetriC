#ifndef INPUT_H
#define INPUT_H

#include "field.h"
#include "shape.h"

#define CALLBACK_NOTHING         0
#define CALLBACK_KEYFRAME        1
#define CALLBACK_FASTER_KEYFRAME 2
#define CALLBACK_COLLISION       4
#define CALLBACK_HARDDROP        8
#define CALLBACK_PAUSE           16
#define CALLBACK_SOFTDROP        32
#define CALLBACK_RESTART         64

#define HOLD_TIMEOUT 0.133
#define HOLD_INTERVAL 0.04

int tInput(Field* field, double time);

#endif