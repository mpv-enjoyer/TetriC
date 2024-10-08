#ifndef CONFIG_H
#define CONFIG_H

#include "misc.h"

typedef struct Config
{
    double begin_keyframe_seconds;
    double acceleration;
    int lines_for_acceleration;
    double min_keyframe_seconds;
    double wait_on_ground_seconds;
    double wait_on_hold_seconds;
    double hold_interval_seconds;
    bool srs;
    bool replay;
    int fps;
} Config;

void tMakeConfigDefault(Config* config);
bool tLoadConfig(Config* config, const char* file_name);
bool tSaveConfig(const Config* config, const char* file_name);

#endif