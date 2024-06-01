#include "shared.h"

bool tLoadFromShared(const Shared *shared, Field **field, Shape **shape, Shape** shape_hold, Config **config, Record *current_record)
{
    if (shared == nullptr) return false;
    if (field != nullptr) *field = shared->field;
    if (shape != nullptr) *shape = shared->shape;
    if (config != nullptr) *config = shared->config;
    if (current_record != nullptr) *current_record = shared->current_record;
    if (shape_hold != nullptr) *shape_hold = shared->shape_hold;
    return true;
}