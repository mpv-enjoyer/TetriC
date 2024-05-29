#ifndef RECORD_H
#define RECORD_H

#include "config.h"

typedef struct Record
{
    Config* config;
    int lines_cleared;
    int score;
    int level;
    double time;
} Record;

#endif