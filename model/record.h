#ifndef RECORD_H
#define RECORD_H

#include "config.h"
#include "misc.h"

typedef struct Record
{
    Config* config;
    int lines_cleared;
    long score;
    int level;
    double time;
    int shapes_placed;
} Record;

void tMakeRecord(Record* record, Config* config);
double tCalculateFrameTime(const Record* record, bool player_requests_faster);
int tCalculatePointsIncrement(const Record *record, int current_lines_cleared);

#endif