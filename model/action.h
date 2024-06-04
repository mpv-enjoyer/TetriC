#ifndef ACTION_H
#define ACTION_H

#include "field.h"
#include "shape.h"

bool tMakeShape(_Field* field);
bool tMakeShapeKnown(_Field *field, int type);
bool tHardDropShape(const _Field *field);
bool tRotateShapeLeft(const _Field* field);
bool tRotateShapeRight(_Field* field);
bool tMoveShapeLeft(const _Field* field);
bool tMoveShapeRight(_Field* field);
bool tGravityShape(_Field* field);
bool tPlaceShape(_Field* field);
int tFindLine(const _Field* field);
void tRemoveLine(_Field* field, int y);
void tUpdateShapeShadow(const _Field* field);
bool tHoldShape(_Field* field);

#endif