#ifndef RENDER_H
#define RENDER_H

#include <raylib.h>
#include "action.h"

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

void tInit();
void tMainLoop();
bool tMenu();

#endif