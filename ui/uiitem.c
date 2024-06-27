#include "uiitem.h"

void tMakeUIItem(UIItem *item, const char* label, UIItemAnchor anchor, UIItem* parent, UIItemFunction UpdateDraw, UIItemFunction Free)
{
    item->data_button = nullptr;
    item->data_checkbox = nullptr;
    item->data_doublebox = nullptr;
    item->data_intbox = nullptr;
    item->data_textbox = nullptr;

    item->stretch_x = true;

    item->parent = parent;
    item->label = label;
    item->max_xy = (Vector2){ .x = GetRenderWidth(), .y = GetRenderHeight() };
    item->position = (Vector2){0, 0};
    item->current_hitbox = (Vector2){0, 0};
    item->active = false;
    item->mouse_active = false;
    item->mouse_hovered = false;
    item->mouse_clicked = false;
    item->mouse_released = false;
    item->position_anchor = anchor;
    item->secondary_anchor = AnchorCenter;
    item->UpdateDraw = UpdateDraw;
    item->Free = Free;

    item->font_size = 20;
    item->outline_size = 3;
}

void tUpdateUIItemXY(UIItem *item)
{
    if (!item->parent) return;
    if (item->position_anchor == AnchorPassive) return;
    D_ASSERT(item->position_anchor != AnchorCenter);
    D_ASSERT(item->secondary_anchor != AnchorPassive);
    Vector2 parent_position = item->parent->position;
    Vector2 parent_size = item->parent->current_hitbox;
    switch (item->position_anchor)
    {
        case AnchorBottom: item->position.y = parent_position.y + parent_size.y; break;
        case AnchorTop: item->position.y = parent_position.y - item->current_hitbox.y; break;
        case AnchorLeft: item->position.x = parent_position.x - item->current_hitbox.x; break;
        case AnchorRight: item->position.x = parent_position.x + parent_size.x; break;
        default: break;
    }

    if (item->position_anchor == AnchorBottom || item->position_anchor == AnchorTop)
    {
        int difference_x = parent_size.x - item->current_hitbox.x;
        switch (item->secondary_anchor)
        {
            case AnchorCenter: item->position.x = parent_position.x + difference_x / 2; break;
            case AnchorLeft: item->position.x = parent_position.x; break;
            case AnchorRight: item->position.x = parent_position.x + difference_x; break;
            default: D_ASSERT(false);
        }
    }
    else
    {
        int difference_y = parent_size.y - item->current_hitbox.y;
        switch (item->secondary_anchor)
        {
            case AnchorCenter: item->position.y = parent_position.y + difference_y / 2; break;
            case AnchorTop: item->position.y = parent_position.y; break;
            case AnchorBottom: item->position.y = parent_position.y + difference_y; break;
            default: D_ASSERT(false);
        }
    }
}

Rectangle tGetUIItemHitbox(UIItem *item)
{
    Rectangle hover_hitbox = {.x = item->position.x, .y = item->position.y, .width = item->current_hitbox.x, .height = item->current_hitbox.y};
    return hover_hitbox;
}

void tUpdateUIItemMouse(UIItem *item)
{
    bool pressed_before = item->mouse_active;
    bool hovered_before = item->mouse_hovered;
    item->mouse_clicked = !pressed_before && hovered_before && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    item->mouse_released = pressed_before && hovered_before && !IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    if (item->mouse_clicked) item->mouse_active = true;
    if (!hovered_before || item->mouse_released) item->mouse_active = false;
    item->mouse_hovered = CheckCollisionPointRec(GetMousePosition(), tGetUIItemHitbox(item));
}
