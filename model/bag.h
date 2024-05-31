#ifndef BAG_H
#define BAG_H

#include "shape.h"

#define BAG_SIZE SHAPE_TYPE_COUNT

typedef struct {
    int data[BAG_SIZE];
    int index;
} Bag;

void tResetBag();
int tGetNextInBag();
void tPeekBag(int* values, int count);

#endif