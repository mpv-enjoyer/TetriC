#include "misc.h"

const char *to_string(int number)
{
    int power10 = 0;
    int copy = number;
    while (copy > 0)
    {
        copy /= 10;
        power10++;
    }
    char* output = (char*)calloc(power10 + 1, sizeof(char));
    for (int i = 0; i < power10; i++)
    {
        output[i] = '0' + copy % 10;
        copy /= 10;
    }
    return output;
}
