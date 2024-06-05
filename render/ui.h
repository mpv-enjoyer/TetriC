#ifndef UI_H
#define UI_H

#include <raylib.h>
#include "helpers.h"
#include "misc.h"

bool tCenteredButton(int y_center, const char *text, int *height);
bool tButton(int x, int y, const char *text, int *height);
bool tCheckbox(bool *value, int x, int y, const char *text, int *height);

#endif
