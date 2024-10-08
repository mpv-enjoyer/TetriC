#ifndef RENDER_H
#define RENDER_H

#include <raylib.h>
#include "field.h"
#include "shape.h"
#include "record.h"
#include "uiitem.h"

#define WIDTH 800
#define HEIGHT 500

#define DEFAULT_FONT_SIZE 20

void tDrawGameFrame(const Field *field, const Record *record, bool is_40_lines);
void tDrawMenuFrame(UIItem* items, int items_count);
void tDrawGameOverFrame(UIItem* items, int item_count);
void tDrawPauseFrame(UIItem* items, int item_count, const Field *field, const Record *record, bool is_40_lines);
void tDrawSettingsFrame(UIItem* items, int item_count);
void tDrawReplayFrame(const Field *field, const Record *record, bool is_40_lines);

#endif