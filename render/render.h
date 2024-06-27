#ifndef RENDER_H
#define RENDER_H

#include <raylib.h>
#include "field.h"
#include "shape.h"
#include "record.h"
#include "ui.h"
#include "uiitem.h"

#define WIDTH 800
#define HEIGHT 450

#define DEFAULT_FONT_SIZE 20

typedef struct SettingsFrameData
{
    UIButton back;
    UIButton save_and_back;
    UIIntBox lines_for_next_level;
    UIDoubleBox min_speed;
    UIDoubleBox acceleration;
    UIDoubleBox max_speed;
    UICheckBox srs;
} SettingsFrameData;

void tDrawGameFrame(const Field *field, const Record *record);
void tDrawMenuFrame(UIItem* items, int items_count);
void tDrawGameOverFrame(int lines_cleared);
int tDrawPauseFrame(const Field *field, const Record *record);
void tDrawSettingsFrame(const Config *config, SettingsFrameData* frame_data);
void tDrawReplayFrame(const Field *field, const Record *record);

#endif