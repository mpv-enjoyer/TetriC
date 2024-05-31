#ifndef BG_H
#define BG_H

#include <raylib.h>
#include "gameelements.h"

#define BG_MENU_SHAPE_COUNT 40
#define BG_MENU_BLOCK_SIZE_MAX 30
#define BG_MENU_BLOCK_SIZE_MIN 10
#define BG_MENU_OFFSCREEN BG_MENU_BLOCK_SIZE_MAX * 4
#define BG_MENU_MAX_VELOCITY 40
#define BG_MENU_MIN_VELOCITY 15
#define BG_MENU_MAX_ANG_VELOCITY 30

void tInitMenuBackground();
void tDrawMenuBackground();

#endif