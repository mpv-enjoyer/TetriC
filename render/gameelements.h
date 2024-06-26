#ifndef GAMEELEMENTS_H
#define GAMEELEMENTS_H

#include <raylib.h>
#include "field.h"
#include "shape.h"
#include "record.h"

#define FIELD_COLOR (Color){50, 50, 50, 255}
#define FIELD_OUTSIDE_COLOR (Color) {0, 0, 0, 255}
#define SHAPE_O_COLOR (Color){191,169,64,255}
#define SHAPE_I_COLOR (Color){91,218,170,255}
#define SHAPE_T_COLOR (Color){174,81,163,255}
#define SHAPE_J_COLOR (Color){88,73,169,255}
#define SHAPE_L_COLOR (Color){198,119,68,255}
#define SHAPE_Z_COLOR (Color){202,72,79,255}
#define SHAPE_S_COLOR (Color){142,191,61,255}

void tDrawFieldBlockRotated(float rectangle_size, int x, int y, int color_type, bool current_shape, bool shadow, float rotation, Vector2 origin);
void tDrawFieldBlock(float rectangle_size, int x, int y, int color_type);
void tDrawShapeBlock(float rectangle_size, int x, int y, int color_type);
void tDrawShadowBlock(float rectangle_size, int x, int y, int color_type);
void tDrawShapeRotated(const Shape *shape, float rectangle_size, float rotation, int x, int y);
void tDrawField(const Field *field, int begin_x, int rectangle_size);
void tDrawShape(const Shape* shape, int begin_x, int rectangle_size);
void tDrawStatistics(const Record *current_record, int begin_x);
void tDrawNextShapes(const Bag *bag, int begin_x);
void tDrawHoldShape(Shape *shape, int begin_x, int rectangle_size);

#endif
