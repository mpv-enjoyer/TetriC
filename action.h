#ifndef ACTION_H
#define ACTION_H

#include "field.h"
#include "shapes.h"

bool tMakeShape(const Field *field, Shape *shape);
bool tRotateShapeLeft(const Field *field, Shape *shape);
bool tRotateShapeRight(const Field* field, Shape* shape);
bool tMoveShapeLeft(const Field* field, Shape* shape);
bool tMoveShapeRight(const Field* field, Shape* shape);
bool tGravity(const Field* field, Shape* shape);
bool tPlaceShape(Field* field, const Shape* shape);
int tFindLine(const Field* field);
void tRemoveLine(Field *field, int y);

#endif