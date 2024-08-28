#include "dummy.h"

#define DATA item->data_dummy

void _tUpdateHitboxDummy(UIItem* item);
void _tUpdateDummy(UIItem* item);
void _tDrawDummy(UIItem* item);
void _tFreeDummy(UIItem* item);

void tMakeDummy(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor, int width, int height)
{
    tMakeUIItem(item, label, anchor, parent, _tUpdateHitboxDummy, _tUpdateDummy, _tDrawDummy, _tFreeDummy);
    item->position_changed = false;
    item->current_hitbox.x = (float)width;
    item->current_hitbox.y = (float)height;
    DATA = (UIDataDummy*)malloc(sizeof(UIDataDummy));
}

void _tUpdateHitboxDummy(UIItem *item)
{
    tUpdateUIItemXY(item);
}

void _tUpdateDummy(UIItem *item)
{

}

void _tDrawDummy(UIItem *item)
{

}

void _tFreeDummy(UIItem *item)
{
    free(DATA);
}
