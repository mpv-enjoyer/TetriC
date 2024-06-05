#ifndef BAG_H
#define BAG_H

#include "shape.h"

#define BAG_SIZE SHAPE_TYPE_COUNT

typedef struct Bag {
    int data[BAG_SIZE];
    int data_next[BAG_SIZE];
    int index;
} Bag;

void tPeekBag(const Bag *bag, int *values, int count);
void tMakeBag(Bag *bag);
int tGetNextInBag(Bag *bag);

#endif