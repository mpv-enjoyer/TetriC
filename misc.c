#include "misc.h"
#include <stdlib.h>

void *tMalloc(size_t size)
{
    void* output = malloc(size);
    D_ASSERT(output != nullptr);
    return output;
}

tString *tAllocString()
{
    tString* string = TMALLOC(tString);
    string->size = 32;
    string->data = (char*)tMalloc(string->size * sizeof(char));
    memset(string->data, '\0', string->size * sizeof(char));
    return string;
}

size_t tActualStringSize(tString* string)
{
    for (size_t i = 0; i < string->size; i++)
    {
        if (string->data[i] == '\0')
        {
            return i;
        }
    }
    D_ASSERT(false);
    return 0;
}

void tAppendString(tString* string, char c)
{
    size_t index = tActualStringSize(string);
    if (index == string->size - 1)
    {
        size_t previous_size = string->size;
        string->size = previous_size * 2;
        string->data = (char*)realloc(string->data, string->size * sizeof(char));
        memset(string->data + previous_size, '\0', previous_size * sizeof(char));
    }
    string->data[index] = c;
}

size_t tSizeUntilCharString(const tString* string, size_t begin, char c)
{
    for (size_t i = begin; i < string->size; i++)
    {
        if (string->data[i] == '\0') return i - begin; 
        if (string->data[i] == c) return i - begin;
    }
    D_ASSERT(false);
    return 0;
}

void tFreeString(tString* string)
{
    free(string->data);
    free(string);
}

/* Arrange the N elements of ARRAY in random order.
    Only effective if N is much smaller than RAND_MAX;
    if this may not be the case, use a better random
    number generator. */

void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int random_int(int left_bound, int right_bound)
{
    return (rand() % (right_bound - left_bound)) + left_bound;
}