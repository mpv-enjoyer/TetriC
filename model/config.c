#include "config.h"
#include "misc.h"
#include <raylib.h>

#define ARENA_IMPLEMENTATION
#include "arena.h"

void tMakeConfigDefault(Config *config)
{
    *config = (Config)
    {
    .begin_keyframe_seconds = 0.2,
    .acceleration = 0.02,
    .lines_for_acceleration = 5,
    .min_keyframe_seconds = 1.0 / 60.0,
    .wait_on_ground_seconds = 0.4,
    .wait_on_hold_seconds = 0.133,
    .hold_interval_seconds = 0.03,
    .srs = true,
    .replay = true,
    .fps = __INT_MAX__
    };
}

#define CFG_INT "%i "
#define CFG_FLT "%f "
#define CFG_LAYOUT(conf) \
        CFG_INT\
         CFG_INT\
          CFG_FLT\
           CFG_FLT\
            CFG_FLT\
             CFG_INT\
              CFG_FLT\
               CFG_FLT\
                CFG_FLT,\
conf->  lines_for_acceleration,\
conf->   srs,\
conf->    acceleration,\
conf->     begin_keyframe_seconds,\
conf->      min_keyframe_seconds,\
conf->       fps,\
conf->        wait_on_hold_seconds,\
conf->         wait_on_ground_seconds,\
conf->          hold_interval_seconds\

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
    char* file_text = LoadFileText(file_name);
    if (!file_text) return false;
    _tCall_vsscanf(file_text, CFG_LAYOUT(&config));
    return true;
}

bool tSaveConfig(const Config *config, const char *file_name)
{
    Arena arena = { 0 };
    char* buffer = arena_sprintf(&arena, CFG_LAYOUT(config));
#ifndef NO_FILESAVE
    if (!SaveFileText(file_name, buffer)) return false;
#endif
    arena_free(&arena);
    return true;
}