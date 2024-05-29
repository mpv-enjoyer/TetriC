#ifndef CONFIG_H
#define CONFIG_H

typedef struct Config
{
    double begin_keyframe_seconds;
    double acceleration;
    int lines_for_acceleration;
    double min_keyframe_seconds;
} Config;

#endif