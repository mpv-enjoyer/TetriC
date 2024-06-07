#ifndef ACTION_H
#define ACTION_H

#include "field.h"
#include "shape.h"

bool tMakeShape(Field* field);
bool tMakeShapeKnown(Field *field, int type);
bool tHardDropShape(const Field *field);
bool tRotateShapeLeft(const Field* field);
bool tRotateShapeRight(Field* field);
bool tMoveShapeLeft(const Field* field);
bool tMoveShapeRight(Field* field);
bool tGravityShape(Field* field);
bool tPlaceShape(Field* field);
int tFindLine(const Field* field);
void tRemoveLine(Field* field, int y);
void tUpdateShapeShadow(Field* field);
bool tHoldShape(Field* field);

#endif