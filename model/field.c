#include "field.h"

int tGetFieldXY(const _Field* field, int x, int y)
{
    if (y < 0) return -1;
    D_ASSERT(y < FIELD_HEIGHT);
    D_ASSERT(x >= 0 && x < FIELD_WIDTH);
    int offset = y * FIELD_WIDTH + x;
    return field->data[offset];
}

void tSetFieldXY(_Field* field, int x, int y, int value)
{
    D_ASSERT(y >= 0 && y < FIELD_HEIGHT);
    D_ASSERT(x >= 0 && x < FIELD_WIDTH);
    D_ASSERT(value >= 0 && value < SHAPE_COLOR_COUNT + 1);
    int offset = y * FIELD_WIDTH + x;
    field->data[offset] = value;
}

_Field* tAllocField()
{
    _Field* output = (_Field*)malloc(sizeof(_Field));
    output->data = (char*)malloc(FIELD_WIDTH * FIELD_HEIGHT * sizeof(char));
    output->shape = (Shape*)malloc(sizeof(Shape));
    return output;
}

void tMakeField(_Field* field, Config* config)
{
    field->can_hold = true;
    D_ASSERT(config != nullptr);
    field->config = config;
    for (int x = 0; x < FIELD_WIDTH; x++)
    {
        for (int y = 0; y < FIELD_HEIGHT; y++)
        {
            tSetFieldXY(field, x, y, 0);
        }
    }
    field->shape_hold = nullptr;
}

void tFreeField(_Field* field)
{
    free(field->data);
    free(field->shape);
    if (field->shape_hold) free(field->shape_hold);
    free(field);
}