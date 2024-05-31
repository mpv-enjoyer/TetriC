#include "bag.h"

bool _bag_empty = true;
Bag _bag;
Bag _next_bag;

Bag _tCreateBag(int previous);
int _tGetNextInBag(Bag* bag);
int _tGetLastInBag(Bag* bag);

void tResetBag()
{
    _bag_empty = true;
}

int tGetNextInBag()
{
    if (_bag_empty)
    {
        _bag = _tCreateBag(-1);
        _next_bag = _tCreateBag(_tGetLastInBag(&_bag));
        _bag_empty = false;
        return _tGetNextInBag(&_bag);
    }
    if (_bag.index == SHAPE_TYPE_COUNT)
    {
        _bag = _next_bag;
        _next_bag = _tCreateBag(_tGetLastInBag(&_bag));
        return _tGetNextInBag(&_bag);
    }
    return _tGetNextInBag(&_bag);
}

void tPeekBag(int *values, int count)
{
    D_ASSERT(count <= BAG_SIZE);
    D_ASSERT(!_bag_empty);
    int index = 0;
    for (int i = _bag.index; i < BAG_SIZE; i++)
    {
        values[index] = _bag.data[i];
        index++;
        if (index >= count) return;
    }
    for (int i = 0; i < BAG_SIZE; i++)
    {
        values[index] = _next_bag.data[i];
        index++;
        if (index >= count) return;
    }
    D_ASSERT(false);
}

Bag _tCreateBag(int previous)
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

int _tGetNextInBag(Bag* bag)
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

int _tGetLastInBag(Bag* bag)
{
    return bag->data[SHAPE_TYPE_COUNT - 1];
}