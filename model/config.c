#include "config.h"
#include "misc.h"
#include <raylib.h>

#define ARENA_IMPLEMENTATION
#include "arena.h"

//bool _tStringToInt(const char* input, int* output);
//bool _tStringToBool(const char* input, bool* output);
//bool _tStringToDouble(const char* input, double* output);
//#define DESERIALIZE(INPUT, OUTPUT) _Generic((OUTPUT), \
//    int: _tStringToInt, \
//    bool: _tStringToBool, \
//    double: _tStringToDouble \
//    )(INPUT, &(OUTPUT))

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

#define FILE_LAYOUT(prefix) \
        "%i\n"\
         "%i\n"\
          "%f\n"\
           "%f\n"\
            "%f\n"\
             "%i\n"\
              "%f\n"\
               "%f\n"\
                "%f\n",\
prefix## lines_for_acceleration,\
prefix##  srs ? 1 : 0,\
prefix##   acceleration,\
prefix##    begin_keyframe_seconds,\
prefix##     min_keyframe_seconds,\
prefix##      fps,\
prefix##       wait_on_hold_seconds,\
prefix##        wait_on_ground_seconds,\
prefix##         hold_interval_seconds\

int _tCall_vsscanf(char *tokenstring, char *format, ...)
{
    int result;
    va_list arglist;
    va_start(arglist, format);
    result = vsscanf(tokenstring, format, arglist);
    va_end(arglist);
    return result;
}

bool tLoadConfig(Config *config, const char *file_name)
{
    const char* file_text = LoadFileText(file_name);
    if (!file_text) return false;
    int split_text_size;
    const char** split_text = TextSplit(file_text, '\n', &split_text_size);
    _tCall_vsscanf(file_text, FILE_LAYOUT(&config->));
    return true;
}

bool tSaveConfig(const Config *config, const char *file_name)
{
    Arena arena = { 0 };
    char* buffer = arena_sprintf(&arena, FILE_LAYOUT(config->));
#ifndef NO_FILESAVE
    if (!SaveFileText(file_name, buffer)) return false;
#endif
    arena_free(&arena);
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