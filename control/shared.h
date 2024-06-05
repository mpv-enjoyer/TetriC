#ifndef SHARED_H
#define SHARED_H

#include "record.h"
#include "field.h"
#include "shape.h"
#include "config.h"

#define STATE_PLAYING     0
#define STATE_GAME_OVER   1
#define STATE_IN_MENU     2
#define STATE_PAUSED      3
#define STATE_IN_SETTINGS 4
#define STATE_EXITING     5

typedef struct Shared
{
    int state;
    _Field* field;
    Config* config;
    Record* current_record;
    Record* all_records;
} Shared;

#endif