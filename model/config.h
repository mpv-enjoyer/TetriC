#ifndef CONFIG_H
#define CONFIG_H

typedef struct Config
{
    double begin_keyframe_seconds;
    double acceleration;
    int lines_for_acceleration;
    double min_keyframe_seconds;
    bool srs;
    bool replay;
} Config;

void tMakeConfigDefault(Config* config);
bool tLoadConfig(Config* config, const char* file_name);
bool tSaveConfig(const Config* config, const char* file_name);

#endif