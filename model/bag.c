#include "bag.h"

void _tFillBagData(int *data, int previous);

void tPeekBag(const Bag* bag, int *values, int count)
{
    D_ASSERT(count <= BAG_SIZE);
    D_ASSERT(values != nullptr);
    int output_index = 0;
    for (int i = bag->index; i < BAG_SIZE; i++)
    {
        values[output_index] = bag->data[i];
        output_index++;
        if (output_index >= count) return;
    }
    for (int i = 0; i < BAG_SIZE; i++)
    {
        values[output_index] = bag->data_next[i];
        output_index++;
        if (output_index >= count) return;
    }
    D_ASSERT(false);
}

void tMakeBag(Bag *bag)
{
    bag->index = 0;
    _tFillBagData(bag->data, -1);
    int last = bag->data[BAG_SIZE - 1];
    _tFillBagData(bag->data_next, last);
}

void _tFillBagData(int* data, int previous)
{
    for (int i = 0; i < BAG_SIZE; i++) 
    {
        data[i] = i;
    }
    do { shuffle(data, BAG_SIZE); }
    while (data[0] == previous);
}

int tGetNextInBag(Bag* bag)
{
    D_ASSERT(bag->index <= BAG_SIZE);
    D_ASSERT(bag->index >= 0);
    if (bag->index == BAG_SIZE)
    {
        for (int i = 0; i < BAG_SIZE; i++)
        {
            bag->data[i] = bag->data_next[i];
        }
        bag->index = 0;
        int last = bag->data[BAG_SIZE - 1];
        _tFillBagData(bag->data_next, last);
    }
    int value = bag->data[bag->index];
    bag->index += 1;
    return value;
}