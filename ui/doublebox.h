#ifndef DOUBLEBOX_H
#define DOUBLEBOX_H

#include "uiitem.h"
#include "textbox.h"

typedef struct UIDataDoubleBox
{
    double value;
    double min;
    double max;
} UIDataDoubleBox;

void tMakeDoubleBox(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor, double value, double min, double max);

#endif //DOUBLEBOX_H