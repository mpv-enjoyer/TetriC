#ifndef HELPERS_H
#define HELPERS_H

#include <raylib.h>

Rectangle tResizeCentered(Rectangle rectangle, int dw, int dh);
Rectangle tCalculateCenteredText(const char *text, int x, int y, int font_size);
bool tCalculateMultipleCenteredText(const char* text_array[], int count, Rectangle* rectangles, int font_size);

#define BUTTON_HITBOX_WIDTH 150

#endif