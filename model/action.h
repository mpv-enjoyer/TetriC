#ifndef ACTION_H
#define ACTION_H

#include "field.h"
#include "shape.h"

#define ACTION_LEFT 'L'
#define ACTION_RIGHT 'R'
#define ACTION_HARD_DROP 'H'
#define ACTION_ROTATE_LEFT 'l'
#define ACTION_ROTATE_RIGHT 'r'
#define ACTION_GRAVITY '\n'
#define ACTION_MAKE_FIGURE(type) ('0' + type)

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
int tRemoveFullLines(Field* field);
void tUpdateShapeShadow(Field* field);
bool tHoldShape(Field* field);

#endif