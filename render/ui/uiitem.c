#include "uiitem.h"

void tMakeUIItem(UIItem *item, const char* label, UIItemAnchor anchor, UIItem* parent, UIItemFunction UpdateDraw, UIItemFunction Free)
{
    item->data_button = nullptr;
    item->data_checkbox = nullptr;
    item->data_doublebox = nullptr;
    item->data_intbox = nullptr;
    item->data_textbox = nullptr;

    item->stretch_x = true;
    item->stretch_y = false;

    item->parent = parent;
    item->label = label;
    Vector2 max_xy = { .x = GetRenderWidth(), .y = GetRenderHeight() };
    item->position = (Vector2){0, 0};
    item->current_hitbox = (Vector2){0, 0};
    item->active = false;
    item->hovered = false;
    item->position_anchor = anchor;
    item->UpdateDraw = UpdateDraw;
    item->Free = Free;
}

void tUpdateUIItemXY(UIItem *item)
{
    if (!item->parent) return;
    if (item->position_anchor == AnchorPassive) return;
    D_ASSERT(item->position_anchor != AnchorCenter);
    D_ASSERT(item->secondary_anchor != AnchorPassive);
    
}
