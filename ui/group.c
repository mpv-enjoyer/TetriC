#include "group.h"

#define DATA item->data_group

void _tUpdateHitboxGroup(UIItem* item);
void _tUpdateGroup(UIItem* item);
void _tDrawGroup(UIItem* item);
void _tFreeGroup(UIItem* item);

void tMakeGroup(UIItem* item, const char* label, UIItem* parent, int group_item_count, UIItem* passive_item, ...)
{
    tMakeUIItem(item, label, AnchorCenter, parent, _tUpdateHitboxGroup, _tUpdateGroup, _tDrawGroup, _tFreeGroup);
    group_item_count -= 1;
    DATA = (UIDataGroup*)malloc(sizeof(UIDataGroup));
    DATA->passive_item = passive_item;
    DATA->item_count = group_item_count;
    DATA->items = (UIItem**)malloc(sizeof(UIItem*) * group_item_count);
    va_list group_items;
    va_start(group_items, group_item_count);
    for (int i = 0; i < group_item_count; i++) 
    {
        DATA->items[i] = va_arg(group_items, UIItem*);
    }
    va_end(group_items);
}

void _tUpdateHitboxGroup(UIItem *item)
{
    D_ASSERT(DATA);
    tUpdateUIItemXY(item);

    D_ASSERT(DATA->passive_item->position_anchor == AnchorPassive);

    Vector2 relative_first_item_position = {0, 0};
    Rectangle inner_hitbox = tGetUIItemHitbox(DATA->passive_item);

    for (int i = 0; i < DATA->item_count; i++)
    {
        UIItem* current_item = *(DATA->items + i);
        if (!current_item->visible) continue;
        int ldx = inner_hitbox.x - current_item->position.x;
        int ldy = inner_hitbox.y - current_item->position.y;
        if (ldx > 0)
        {
            inner_hitbox.x -= ldx;
            inner_hitbox.width += ldx;
            relative_first_item_position.x += ldx;
        }
        if (ldy > 0)
        {
            inner_hitbox.y -= ldy;
            inner_hitbox.height += ldy;
            relative_first_item_position.y += ldy;
        }

        int rdx = current_item->position.x + current_item->current_hitbox.x - inner_hitbox.x - inner_hitbox.width;
        int rdy = current_item->position.y + current_item->current_hitbox.y - inner_hitbox.y - inner_hitbox.height;

        if (rdx > 0) inner_hitbox.width += rdx;
        if (rdy > 0) inner_hitbox.height += rdy;
    }

    Vector2 old_passive_item_position = DATA->passive_item->position;

    DATA->passive_item->position.x = relative_first_item_position.x + item->position.x;
    DATA->passive_item->position.y = relative_first_item_position.y + item->position.y;

    Vector2 new_passive_item_position = DATA->passive_item->position;

    DATA->passive_item->position_changed =  (old_passive_item_position.x != new_passive_item_position.x) ||
                                            (old_passive_item_position.y != new_passive_item_position.y);

    Vector2 old_hitbox = item->current_hitbox;

    item->current_hitbox.x = inner_hitbox.width;
    item->current_hitbox.y = inner_hitbox.height;

    if (item->current_hitbox.x != old_hitbox.x || item->current_hitbox.y != old_hitbox.y)
    {
        item->position_changed = true;
    }
}

void _tUpdateGroup(UIItem *item)
{
    D_ASSERT(DATA);
    tUpdateUIItemMouse(item);
}

void _tDrawGroup(UIItem *item)
{
    D_ASSERT(DATA);
    if (!item->visible) return;
    DrawRectangleLinesEx(tGetUIItemHitbox(item), 2, item->color_hitbox);
}

void _tFreeGroup(UIItem *item)
{
    free(DATA->items);
    free(DATA);
}
