#ifndef UIITEM_H
#define UIITEM_H

#include <raylib.h>
#include "misc.h"
#include "stdarg.h"
#include "helpers.h"

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
    Vector2 max_xy;
    Vector2 current_hitbox;
    const char* label;
    bool mouse_active;
    bool mouse_hovered;
    bool mouse_clicked;
    bool mouse_released;
    bool active;
    UIItemFunction UpdateDraw;
    UIItemFunction Free;
    int font_size;
    int outline_size;
    struct UIDataButton* data_button;
    struct UIDataCheckBox* data_checkbox;
    struct UIDataTextBox* data_textbox;
    struct UIDataIntBox* data_intbox;
    struct UIDataDoubleBox* data_doublebox;
    struct UIDataGroup* data_group;
} UIItem;

void tMakeUIItem(UIItem* item, const char* label, UIItemAnchor anchor, UIItem* parent, UIItemFunction UpdateDraw, UIItemFunction Free);
void tUpdateUIItemXY(UIItem* item);
Rectangle tGetUIItemHitbox(UIItem* item);
void tUpdateUIItemMouse(UIItem* item);

#include "button.h"
#include "group.h"

#endif
