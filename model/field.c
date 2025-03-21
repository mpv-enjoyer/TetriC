#include "field.h"

int tGetFieldXY(const Field* field, int x, int y)
{
    if (y < 0) return -1;
    D_ASSERT(y < FIELD_HEIGHT);
    D_ASSERT(x >= 0 && x < FIELD_WIDTH);
    int offset = y * FIELD_WIDTH + x;
    return field->data[offset];
}

void tSetFieldXY(Field* field, int x, int y, int value)
{
    D_ASSERT(y >= 0 && y < FIELD_HEIGHT);
    D_ASSERT(x >= 0 && x < FIELD_WIDTH);
    D_ASSERT(value >= 0 && value < SHAPE_COLOR_COUNT + 1);
    int offset = y * FIELD_WIDTH + x;
    field->data[offset] = value;
}

Field* tAllocField()
{
    Field* output = TMALLOC(Field);
    output->data = (char*)tMalloc(FIELD_WIDTH * FIELD_HEIGHT * sizeof(char));
    output->shape = TMALLOC(Shape);
    output->bag = TMALLOC(Bag);
    output->replay = tAllocString();
    return output;
}

void tMakeField(Field* field, Config* config)
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
    field->shape_on_ground_begin = 0.0f;
    field->is_shape_on_ground = false;
    tMakeBag(field->bag);
}

void tFreeField(Field* field)
{
    free(field->data);
    free(field->shape);
    if (field->shape_hold) free(field->shape_hold);
    free(field->bag);
    if (field->replay) tFreeString(field->replay);
    free(field);
}