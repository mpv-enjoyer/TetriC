#ifndef RENDER_H
#define RENDER_H

#include <raylib.h>
#include "field.h"
#include "shape.h"
#include "record.h"

#define WIDTH 800
#define HEIGHT 450

#define FIELD_COLOR (Color){50, 50, 50, 255}
#define FIELD_OUTSIDE_COLOR (Color) {0, 0, 0, 255}

#define SHAPE_O_COLOR (Color){191,169,64,255}
#define SHAPE_I_COLOR (Color){91,218,170,255}
#define SHAPE_T_COLOR (Color){174,81,163,255}
#define SHAPE_J_COLOR (Color){88,73,169,255}
#define SHAPE_L_COLOR (Color){198,119,68,255}
#define SHAPE_Z_COLOR (Color){202,72,79,255}
#define SHAPE_S_COLOR (Color){142,191,61,255}

#define DEFAULT_FONT_SIZE 20

#define MENU_ITEM_COUNT 3
#define PAUSE_ITEM_COUNT 2
#define GAME_OVER_ITEM_COUNT 1

const static char* menu_item_strings[MENU_ITEM_COUNT] = {"Play", "Settings", "Exit"};
const static char* pause_item_strings[PAUSE_ITEM_COUNT] = {"Continue", "To menu"};
const static char* game_over_strings[GAME_OVER_ITEM_COUNT] = {"To menu"};

void tDrawGameFrame(const Field* field, const Shape* shape, const Record* record);
void tDrawMenuFrame(int selected, const Rectangle* items);
void tDrawGameOverFrame(int lines_cleared);
void tDrawPauseFrame(int* selected);

#endif