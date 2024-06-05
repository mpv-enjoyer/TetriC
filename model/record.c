#include "record.h"

void tMakeRecord(Record* record, Config* config)
{
    D_ASSERT(config != nullptr);
    record->config = config;
    record->level = 0;
    record->lines_cleared = 0;
    record->score = 0;
    record->time = 0;
}

double tCalculateFrameTime(const Record *record, bool player_requests_faster)
{
    const Config* config = record->config;
    double output = config->begin_keyframe_seconds - config->acceleration * record->level;
    if (output < config->min_keyframe_seconds) output = config->min_keyframe_seconds;
    if (player_requests_faster) output /= 2.0f;
    return output;
}

int tCalculatePointsIncrement(const Record* record, int current_lines_cleared)
{
    int output = 0;
    switch (current_lines_cleared)
    {
        case 0: output = 0; break;
        case 1: output = 40; break;
        case 2: output = 100; break;
        case 3: output = 300; break;
        case 4: output = 1200; break;
        default: D_ASSERT(false);
    }
    output *= (record->level + 1);
    return output;
}