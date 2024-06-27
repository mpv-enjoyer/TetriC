#ifndef BUTTON_H
#define BUTTON_H

#include "uiitem.h"

typedef struct UIDataButton
{
    bool clicked;
    bool released;
    bool resize_on_hover;
    int resized_text_size;
    Color text_color;
    Color outline_color;
    Color hovered_text_color;
} UIDataButton;

void tMakeButton(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor);

#endif