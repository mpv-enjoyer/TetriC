#include "uiitem.h"

typedef enum MouseState
{
    MouseStateUp,
    MouseStatePressed,
    MouseStateDown,
    MouseStateReleased
} MouseState;

void _tUpdateUIItemXYNoParent(UIItem* item);

MouseState _mouse_state;

void tBindUIItems(UIItem items[], int item_count, UIItem **item_slot, ...)
{
    *item_slot = &(items[0]);
    va_list slots;
    va_start(slots, item_count - 1);
    for (int i = 1; i < item_count; i++)
    {
        UIItem** current_slot;
        current_slot = va_arg(slots, UIItem**);
        *current_slot = &(items[i]);
    }
    va_end(slots);
}

void tMakeUIItem(UIItem *item, const char *label, UIItemAnchor anchor, UIItem *parent, UIItemFunction UpdateHitbox, UIItemFunction Update, UIItemFunction Draw, UIItemFunction Free)
{
    item->data_button = nullptr;
    item->data_checkbox = nullptr;
    item->data_doublebox = nullptr;
    item->data_intbox = nullptr;
    item->data_textbox = nullptr;
    item->data_group = nullptr;
    item->data_text = nullptr;
    item->data_picturebox = nullptr;

    item->stretch_x = false;
    item->padding = 0;
    item->visible = true;
    item->color_background = WHITE;
    item->color_hitbox = (Color){0, 0, 0, 0};
    item->color_text = BLACK;
    item->parent = parent;
    item->label = label;
    item->max_xy = (Vector2){ .x = (float)GetRenderWidth(), .y = (float)GetRenderHeight() };
    item->position = (Vector2){0, 0};
    item->current_hitbox = (Vector2){0, 0};
    item->mouse_active = false;
    item->mouse_hovered = false;
    item->mouse_clicked = false;
    item->mouse_released = false;
    item->position_changed = true;
    item->active = false;
    item->position_anchor = anchor;
    item->secondary_anchor = AnchorCenter;
    item->UpdateHitbox = UpdateHitbox;
    item->Update = Update;
    item->Draw = Draw;
    item->Free = Free;

    item->font_size = 40;
    item->outline_size = 3;
}

void tUpdateUIItemXY(UIItem *item)
{
    D_ASSERT(item->parent != item);
    item->max_xy.x = GetRenderWidth();
    item->max_xy.y = GetRenderHeight();
    if (item->position_anchor == AnchorPassive) return;
    UIItem* parent = item->parent;
    while (parent && parent->parent && !parent->visible) parent = parent->parent;
    if (!parent) return _tUpdateUIItemXYNoParent(item);
    D_ASSERT(item->position_anchor != AnchorCenter);
    D_ASSERT(item->secondary_anchor != AnchorPassive);
    Vector2 old_position = item->position;
    Vector2 parent_position = parent->position;
    Vector2 parent_size = parent->current_hitbox;
    switch (item->position_anchor)
    {
        case AnchorBottom: item->position.y = parent_position.y + parent_size.y + item->padding; break;
        case AnchorTop: item->position.y = parent_position.y - item->current_hitbox.y - item->padding; break;
        case AnchorLeft: item->position.x = parent_position.x - item->current_hitbox.x - item->padding; break;
        case AnchorRight: item->position.x = parent_position.x + parent_size.x + item->padding; break;
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
    item->position_changed = !(item->position.x == old_position.x && item->position.y == old_position.y);
}

bool tUpdateUIVisibility(UIItem *item)
{
    if (!item->visible)
    {
        item->current_hitbox.x = 0;
        item->current_hitbox.y = 0;
    }
    return item->visible;
}

void _tUpdateUIItemXYNoParent(UIItem *item)
{
    Vector2 old_position = item->position;
    switch (item->position_anchor)
    {
        case AnchorBottom: item->position.y = item->padding; break;
        case AnchorTop: item->position.y = item->max_xy.y - item->current_hitbox.y - item->padding; break;
        case AnchorLeft: item->position.x = item->max_xy.x - item->current_hitbox.x - item->padding; break;
        case AnchorRight: item->position.x = item->padding; break;
        case AnchorCenter: item->position.x = (item->max_xy.x - item->current_hitbox.x) / 2;
                           item->position.y = (item->max_xy.y - item->current_hitbox.y) / 2;
                           break;
        default: break;
    }

    if (item->position_anchor == AnchorBottom || item->position_anchor == AnchorTop)
    {
        switch (item->secondary_anchor)
        {
            case AnchorCenter: item->position.x = (item->max_xy.x - item->current_hitbox.x) / 2; break;
            case AnchorLeft: item->position.x = 0; break;
            case AnchorRight: item->position.x = item->max_xy.x - item->current_hitbox.x; break;
            default: D_ASSERT(false);
        }
    }
    else if (item->position_anchor == AnchorLeft || item->position_anchor == AnchorRight)
    {
        switch (item->secondary_anchor)
        {
            case AnchorCenter: item->position.y = (item->max_xy.y - item->current_hitbox.y) / 2; break;
            case AnchorTop: item->position.y = 0; break;
            case AnchorBottom: item->position.y = item->max_xy.y - item->current_hitbox.y; break;
            default: D_ASSERT(false);
        }
    }
    item->position_changed = !(item->position.x == old_position.x && item->position.y == old_position.y);
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
    item->mouse_hovered = CheckCollisionPointRec(GetMousePosition(), tGetUIItemHitbox(item));
    item->mouse_clicked = hovered_before && _mouse_state == MouseStatePressed;
    item->mouse_released = item->mouse_active && hovered_before && _mouse_state == MouseStateReleased;
    if (item->mouse_clicked) item->mouse_active = true;
    if (_mouse_state == MouseStateReleased) item->mouse_active = false;
}

void tUpdateDrawUIItems(UIItem *items, int items_count)
{
    bool is_mouse_down = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    switch (_mouse_state)
    {
        case MouseStateDown: if (!is_mouse_down) _mouse_state = MouseStateReleased; break;
        case MouseStateReleased: _mouse_state = MouseStateUp; break;
        case MouseStateUp: if (is_mouse_down) _mouse_state = MouseStatePressed; break;
        case MouseStatePressed: _mouse_state = _mouse_state = MouseStateDown; break;
    }

    for (int i = 0; i < items_count; i++)
    {
        if (items[i].Update == nullptr) continue;
        items[i].Update(&(items[i]));
    }

    bool position_changed = false;
    for (int i = 0; i < items_count; i++)
    {
        if (items[i].UpdateHitbox == nullptr) continue;
        items[i].UpdateHitbox(&(items[i]));
        position_changed |= (items[i].position_changed && items[i].position_anchor != AnchorPassive);
    }

    const int placement_attempts = 6;
    for (int attempt = 0; position_changed && (attempt < placement_attempts); attempt++)
    {
        position_changed = false;
        for (int i = 0; i < items_count; i++)
        {
            if (items[i].UpdateHitbox == nullptr) continue;
            items[i].UpdateHitbox(&(items[i]));
            position_changed |= items[i].position_changed && items[i].position_anchor != AnchorPassive;
        }
    }

    if (position_changed)
    {
        printf("Failed to pin UI Items after %i attempts\n", placement_attempts);
    }

    for (int i = 0; i < items_count; i++)
    {
        if (items[i].Draw == nullptr) continue;
        items[i].Draw(&(items[i]));
    }
}

void tFreeUIItems(UIItem *items, int items_count)
{
    for (int i = 0; i < items_count; i++)
    {
        items[i].Free(&(items[i]));
    }
}
