#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "uiitem.h"

typedef struct UIDataCheckBox
{
    bool value;
    bool value_changed;
    Color color_active;
    Color color_hovered_background;
    UIItem* label_item;
} UIDataCheckBox;

void tMakeCheckBox(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor, bool value);

#endif //CHECKBOX_H