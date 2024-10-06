#ifndef UIITEM_H
#define UIITEM_H

#include <raylib.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "misc.h"
#include "helpers.h"

struct UIItem;
typedef void (*UIItemFunction)(struct UIItem*);

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
    struct UIItem* parent;
    bool stretch_x;
    Vector2 max_xy;
    Vector2 current_hitbox;
    const char* label;
    bool mouse_active;
    bool mouse_hovered;
    bool mouse_clicked;
    bool mouse_released;
    bool position_changed;
    bool active;
    UIItemFunction UpdateHitbox;
    UIItemFunction Update;
    UIItemFunction Draw;
    UIItemFunction Free;
    int font_size;
    int outline_size;
    Color color_background;
    Color color_hitbox;
    Color color_text;
    bool visible;
    int padding;
    struct UIDataButton* data_button;
    struct UIDataCheckBox* data_checkbox;
    struct UIDataTextBox* data_textbox;
    struct UIDataIntBox* data_intbox;
    struct UIDataDoubleBox* data_doublebox;
    struct UIDataGroup* data_group;
    struct UIDataButton* data_text;
    struct UIDataPictureBox* data_picturebox;
    struct UIDataDummy* data_dummy;
} UIItem;

void tBindUIItems(UIItem items[], int item_count, UIItem** item_slot, ...);
void tMakeUIItem(UIItem *item, const char *label, UIItemAnchor anchor, UIItem *parent, UIItemFunction UpdateHitbox, UIItemFunction Update, UIItemFunction Draw, UIItemFunction Free);
Rectangle tGetUIItemHitbox(UIItem* item);

void tUpdateUIItemXY(UIItem* item);
bool tUpdateUIVisibility(UIItem* item);
void tUpdateUIItemMouse(UIItem* item);

void tUpdateDrawUIItems(UIItem* items, int items_count);
void tFreeUIItems(UIItem* items, int items_count);

#ifdef __cplusplus
}
#endif

#include "button.h"
#include "group.h"
#include "text.h"
#include "textbox.h"
#include "doublebox.h"
#include "intbox.h"
#include "checkbox.h"
#include "picturebox.h"
#include "dummy.h"

#endif //UIITEM_H