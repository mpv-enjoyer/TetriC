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
    config->srs = true;
    config->replay = true;
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

    return true;
}

bool tSaveConfig(const Config *config, const char *file_name)
{
    char* buffer = (char*)malloc(sizeof(char) * 1000);
    int index = 0;

    sprintf(buffer, "%i\n\0", config->lines_for_acceleration);
    index = TextLength(buffer);

    int srs = config->srs ? 1 : 0;
    sprintf(buffer + index, "%i\n\0", srs);
    index = TextLength(buffer);

    sprintf(buffer + index, "%f\n\0", config->acceleration);
    index = TextLength(buffer);

    sprintf(buffer + index, "%f\n\0", config->begin_keyframe_seconds);
    index = TextLength(buffer);

    sprintf(buffer + index, "%f\n\0", config->min_keyframe_seconds);
    index = TextLength(buffer);

    if (!SaveFileText(file_name, buffer)) return false;
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