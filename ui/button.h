#ifndef BUTTON_H
#define BUTTON_H

#include "uiitem.h"

typedef struct UIDataButton
{
    bool resize_on_hover;
    int resized_text_size;
    bool recolor_on_active;
    Color color_active;
} UIDataButton;

void tMakeButton(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor);

#endif