#ifndef TIMGUI_H
#define TIMGUI_H

#include <raylib.h>
#include "helpers.h"
#include "misc.h"

#define TEXTBOX_MODE_STRING 0
#define TEXTBOX_MODE_INT    1
#define TEXTBOX_MODE_DOUBLE 2

bool tCenteredButton(int y_center, const char *text, int *height);
bool tButton(int x, int y, const char *text, int *height);
bool tCheckbox(bool *value, int x, int y, const char *text, int *height);
bool tTextBox(char *data, int max_length, int x, int y, int mode, const char *text, int *height, bool *active);

#endif
