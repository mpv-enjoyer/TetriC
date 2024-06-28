#ifndef GROUP_H
#define GROUP_H

#include "uiitem.h"

typedef struct UIDataGroup
{
    UIItem* passive_item;
    UIItem** items;
    int item_count;
} UIDataGroup;

void tMakeGroup(UIItem* item, const char* label, UIItem* parent, int group_item_count, UIItem* passive_item, ...);

#endif