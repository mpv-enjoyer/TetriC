#include "text.h"

void tMakeText(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor)
{
    tMakeButton(item, label, parent, anchor);
    item->color_hitbox = (Color){0, 0, 0, 0};
    item->color_background = (Color){0, 0, 0, 0};
    item->data_text = item->data_button;
    item->data_button->resize_on_hover = false;
    item->data_button->recolor_on_active = false;
    item->data_button->color_active = (Color){0, 0, 0, 0};
}