#ifndef RENDER_H
#define RENDER_H

#include <raylib.h>
#include "field.h"
#include "shape.h"
#include "record.h"
#include "ui.h"

#define WIDTH 800
#define HEIGHT 450

#define DEFAULT_FONT_SIZE 20

typedef struct SettingsFrameData
{
    UIButton back;
    UIButton save_and_back;
    UIIntBox lines_for_acceleration_box;
    UIDoubleBox min_keyframe_seconds_box;
} SettingsFrameData;

void tDrawGameFrame(const Field *field, const Record *record);
int tDrawMenuFrame();
void tDrawGameOverFrame(int lines_cleared);
int tDrawPauseFrame(const Field *field, const Record *record);
void tDrawSettingsFrame(const Config *config, SettingsFrameData* frame_data);

#endif