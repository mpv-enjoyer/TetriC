#ifndef GROUP_H
#define GROUP_H

#include "uiitem.h"

typedef struct UIDataGroup
{
    UIItem* items;
    int item_count;
} UIDataGroup;

void tMakeGroup(UIItem *item, const char *label, UIItem *parent, UIItem *group_items, int group_item_count);

#endif