#include "bag.h"

Bag tCreateBag(int previous)
{
    Bag bag;
    bag.index = 0;
    for (int i = 0; i < SHAPE_TYPE_COUNT; i++) 
    {
        bag.data[i] = i;
    }
    do { shuffle(bag.data, SHAPE_TYPE_COUNT); }
    while (bag.data[0] == previous);
    return bag;
}

int tGetNextInBag(Bag* bag)
{
    D_ASSERT(bag->index <= SHAPE_TYPE_COUNT);
    D_ASSERT(bag->index >= 0);
    if (bag->index == SHAPE_TYPE_COUNT)
    {
        return -1;
    }

    int value = bag->data[bag->index];
    bag->index += 1;
    return value;
}

int tGetLastInBag(Bag* bag)
{
    return bag->data[SHAPE_TYPE_COUNT - 1];
}