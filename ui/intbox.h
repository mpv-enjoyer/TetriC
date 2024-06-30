#ifndef INTBOX_H
#define INTBOX_H

#include "uiitem.h"
#include "textbox.h"

typedef struct UIDataIntBox
{
    int value;
    int min;
    int max;
} UIDataIntBox;

void tMakeIntBox(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor, int value, int min, int max);

#endif //INTBOX_H