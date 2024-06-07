#include "settings.h"
#include "render.h"

void _tMakeSettingsFrameData(SettingsFrameData* frame_data, const Config* config);
bool _tProcessFinalFrame(const SettingsFrameData* frame_data, Config* config);

Shared tSettings(Shared shared)
{
    SettingsFrameData frame_data;
    _tMakeSettingsFrameData(&frame_data, shared.config);
    while (shared.state == STATE_IN_SETTINGS)
    {
        tDrawSettingsFrame(shared.config, &frame_data);
        if (_tProcessFinalFrame(&frame_data, shared.config))
        {
            shared.state = STATE_IN_MENU;
            break;
        }
        if (WindowShouldClose())
        {
            shared.state = STATE_EXITING;
            break;
        }
        if (IsKeyPressed(KEY_ESCAPE))
        {
            shared.state = STATE_IN_MENU;
        }
    }
    return shared;
}

void _tMakeSettingsFrameData(SettingsFrameData *frame_data, const Config* config)
{
    const static int buffer_size = 13;
    tMakeUIButton(&(frame_data->back), 10, 10, "Exit", false);
    tMakeUIButton(&(frame_data->save_and_back), 10, -1, "Save and exit", false);
    char* buffer = (char*)malloc(buffer_size * sizeof(char));
    tMakeUIIntBox(&(frame_data->lines_for_next_level), 10, -1, "Lines for next level", buffer, buffer_size, config->lines_for_acceleration, 1, 1000);
    buffer = (char*)malloc(buffer_size * sizeof(char));
    tMakeUIDoubleBox(&(frame_data->min_speed), 10, -1, "Begin speed (blocks per second)", buffer, buffer_size, 1 / config->begin_keyframe_seconds, 0.1f, 1000);
    buffer = (char*)malloc(buffer_size * sizeof(char));
    tMakeUIDoubleBox(&(frame_data->max_speed), 10, -1, "Max speed (blocks per second)", buffer, buffer_size, 1 / config->min_keyframe_seconds, 0.1f, 1000);
    buffer = (char*)malloc(buffer_size * sizeof(char));
    tMakeUIDoubleBox(&(frame_data->acceleration), 10, -1, "Acceleration (Weird value)", buffer, buffer_size, config->acceleration, 0.00001f, 100);
    tMakeUICheckBox(&(frame_data->srs), 10, -1, "Super Rotation System", config->srs);
}

bool _tProcessFinalFrame(const SettingsFrameData *frame_data, Config *config)
{
    bool is_last_frame = frame_data->back.data || frame_data->save_and_back.data;
    if (!is_last_frame) return false;
    free(frame_data->min_speed.data);
    free(frame_data->max_speed.data);
    free(frame_data->lines_for_next_level.data);
    free(frame_data->acceleration.data);
    if (frame_data->back.data) return true;
    config->begin_keyframe_seconds = 1 / frame_data->min_speed.value;
    config->lines_for_acceleration = frame_data->lines_for_next_level.value;
    config->min_keyframe_seconds = 1 / frame_data->max_speed.value;
    config->acceleration = frame_data->acceleration.value;
    config->srs = frame_data->srs.data;
    return true;
}
