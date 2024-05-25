#ifndef BAG_H
#define BAG_H

#include "shapes.h"

typedef struct {
    int data[SHAPE_TYPE_COUNT];
    int index;
} Bag;

Bag tCreateBag(int previous);
int tGetNextInBag(Bag* bag);
int tGetLastInBag(Bag* bag);

#endif