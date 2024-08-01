#include "config.h"
#include "misc.h"
#include <raylib.h>

bool _tStringToInt(const char* input, int* output);
bool _tStringToBool(const char *input, bool *output);
bool _tStringToDouble(const char *input, double *output);

void tMakeConfigDefault(Config *config)
{
    config->begin_keyframe_seconds = 0.2f;
    config->acceleration = 0.02f;
    config->lines_for_acceleration = 5;
    config->min_keyframe_seconds = 1.0f / 60.0f;
    config->wait_on_ground_seconds = 0.4f;
    config->wait_on_hold_seconds = 0.133f;
    config->hold_interval_seconds = 0.03f;
    config->srs = true;
    config->replay = true;
    config->fps = __INT_MAX__;
}

bool tLoadConfig(Config *config, const char *file_name)
{
    const char* file_text = LoadFileText(file_name);
    if (!file_text) return false;
    int split_text_size;
    const char** split_text = TextSplit(file_text, '\n', &split_text_size);

    _tStringToInt(split_text[0], &(config->lines_for_acceleration));
    _tStringToBool(split_text[1], &(config->srs));
    _tStringToDouble(split_text[2], &(config->acceleration));
    _tStringToDouble(split_text[3], &(config->begin_keyframe_seconds));
    _tStringToDouble(split_text[4], &(config->min_keyframe_seconds));
    _tStringToInt(split_text[5], &(config->fps));
    _tStringToDouble(split_text[6], &(config->wait_on_hold_seconds));
    _tStringToDouble(split_text[7], &(config->wait_on_ground_seconds));
    _tStringToDouble(split_text[8], &(config->hold_interval_seconds));

    return true;
}

bool tSaveConfig(const Config *config, const char *file_name)
{
    char* buffer = (char*)malloc(sizeof(char) * 1000);
    int size = sprintf(buffer, "%i\n%i\n%f\n%f\n%f\n%i\n%f\n%f\n%f\n\0", config->lines_for_acceleration,
                                                      config->srs ? 1 : 0,
                                                      config->acceleration,
                                                      config->begin_keyframe_seconds,
                                                      config->min_keyframe_seconds,
                                                      config->fps,
                                                      config->wait_on_hold_seconds,
                                                      config->wait_on_ground_seconds,
                                                      config->hold_interval_seconds);
    D_ASSERT(size < 1000);

#ifndef NO_FILESAVE
    if (!SaveFileText(file_name, buffer)) return false;
#endif
    free(buffer);
    return true;
}

bool _tStringToInt(const char* input, int* output)
{
    int length = TextLength(input);
    for (int i = 0; i < length; i++)
    {
        if (input[i] < '0' || input[i] > '9') return false;
    }
    *output = atoi(input);
    return true;
}

bool _tStringToBool(const char* input, bool* output)
{
    int length = TextLength(input);
    for (int i = 0; i < length; i++)
    {
        if (input[i] < '0' || input[i] > '1') return false;
    }
    *output = atoi(input);
    return true;
}

bool _tStringToDouble(const char *input, double *output)
{
    int length = TextLength(input);
    for (int i = 0; i < length; i++)
    {
        if (input[i] == '.') continue;
        if (input[i] < '0' || input[i] > '9') return false;
    }
    *output = atof(input);
    return true;
}