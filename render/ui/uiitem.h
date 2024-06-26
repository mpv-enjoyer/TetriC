#ifndef UIITEM_H
#define UIITEM_H

#include <raylib.h>
#include "misc.h"
#include "stdarg.h"
#include "helpers.h"

typedef struct UIDataButton;
typedef struct UIDataCheckBox;
typedef struct UIDataTextBox;
typedef struct UIDataIntBox;
typedef struct UIDataDoubleBox;

typedef struct UIItem;
typedef void (*UIItemFunction)(UIItem*);

typedef enum UIItemAnchor
{
    AnchorLeft,
    AnchorTop,
    AnchorRight,
    AnchorBottom,
    AnchorPassive,
    AnchorCenter
} UIItemAnchor;

typedef struct UIItem
{
    Vector2 position;
    UIItemAnchor position_anchor;
    UIItemAnchor secondary_anchor;
    UIItem* parent;
    bool stretch_x;
    bool stretch_y;
    Vector2 max_xy;
    Vector2 current_hitbox;
    const char* label;
    bool active;
    bool hovered;
    UIItemFunction UpdateDraw;
    UIItemFunction Free;
    struct UIDataButton* data_button;
    struct UIDataCheckBox* data_checkbox;
    struct UIDataTextBox* data_textbox;
    struct UIDataIntBox* data_intbox;
    struct UIDataDoubleBox* data_doublebox;
} UIItem;

void tMakeUIItem(UIItem* item, const char* label, UIItemAnchor anchor, UIItem* parent, UIItemFunction UpdateDraw, UIItemFunction Free);
void tUpdateUIItemXY(UIItem* item);

#include "button.h"

#endif
