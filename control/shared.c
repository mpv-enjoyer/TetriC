#include "shared.h"

bool LoadFromShared(const Shared *shared, Field **field, Shape **shape, Config **config, Record* current_record)
{
    if (shared == nullptr) return false;
    if (field != nullptr) *field = shared->field;
    if (shape != nullptr) *shape = shared->shape;
    if (config != nullptr) *config = shared->config;
    if (current_record != nullptr) *current_record = shared->current_record;
    return true;
}