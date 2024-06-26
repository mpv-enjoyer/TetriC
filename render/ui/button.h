#ifndef BUTTON_H
#define BUTTON_H

#include "uiitem.h"

typedef struct UIDataButton
{
    bool clicked;
    bool released;
    bool resize_on_hover;
} UIDataButton;

#endif