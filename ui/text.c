#include "text.h"

#define DATA item->data_text

void tMakeText(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor)
{
    tMakeButton(item, label, parent, anchor);
    item->color_hitbox = (Color){0, 0, 0, 0};
    item->color_background = (Color){0, 0, 0, 0};
    DATA = item->data_button;
    DATA->resize_on_hover = false;
    DATA->recolor_on_active = false;
    DATA->color_active = (Color){0, 0, 0, 0};
}