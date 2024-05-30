#ifndef RENDER_H
#define RENDER_H

#include <raylib.h>
#include "field.h"
#include "shape.h"
#include "record.h"

#define WIDTH 800
#define HEIGHT 450

#define DEFAULT_FONT_SIZE 20

#define MENU_ITEM_COUNT 3
#define PAUSE_ITEM_COUNT 2
#define GAME_OVER_ITEM_COUNT 1

const static char* menu_item_strings[MENU_ITEM_COUNT] = {"Play", "Settings", "Exit"};
const static char* pause_item_strings[PAUSE_ITEM_COUNT] = {"Continue", "To menu"};
const static char* game_over_strings[GAME_OVER_ITEM_COUNT] = {"To menu"};

void tDrawGameFrame(const Field* field, const Shape* shape, const Record* record);
int tDrawMenuFrame();
void tDrawGameOverFrame(int lines_cleared);
void tDrawPauseFrame(int* selected);

#endif