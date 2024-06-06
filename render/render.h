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

void tDrawGameFrame(const _Field *field, const Record *record);
int tDrawMenuFrame();
void tDrawGameOverFrame(int lines_cleared);
int tDrawPauseFrame(const _Field *field, const Record *record);
int tDrawSettingsFrame(const Config *config, int active_element, char* data, int data_size);

#endif