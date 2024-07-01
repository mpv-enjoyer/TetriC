#include "checkbox.h"

#define DATA item->data_checkbox

void _tUpdateDrawCheckBox(UIItem* item);
void _tFreeCheckBox(UIItem* item);

void tMakeCheckBox(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor, bool value)
{
    tMakeUIItem(item, label, anchor, parent, _tUpdateDrawCheckBox, _tFreeCheckBox);
    item->color_hitbox = BLACK;
    item->active = value;
    DATA = (UIDataCheckBox*)malloc(sizeof(UIDataCheckBox));
    DATA->color_active = RED;
    DATA->color_hovered_background = LIGHTGRAY;
    DATA->value = value;
    DATA->value_changed = false;
    DATA->label_item = (UIItem*)malloc(sizeof(UIItem));
    tMakeText(DATA->label_item, label, item, AnchorRight);
}

void _tUpdateDrawCheckBox(UIItem *item)
{
    D_ASSERT(DATA);
    tUpdateUIItemXY(item);
    DATA->label_item->visible = item->visible;
    DATA->label_item->UpdateDraw(DATA->label_item);
    if (!tUpdateUIVisibility(item)) return;
    
    D_ASSERT(item->active == DATA->value);
    bool value = DATA->value;
    DATA->value_changed = item->mouse_released || DATA->label_item->mouse_released;
    bool mouse_hovered = item->mouse_hovered || DATA->label_item->mouse_hovered;
    bool mouse_active = item->mouse_active || DATA->label_item->mouse_active;
    int size = DATA->label_item->current_hitbox.y;

    if (DATA->value_changed)
    {
        item->active = !value;
        DATA->value = !value;
    }

    item->current_hitbox.y = size;
    item->current_hitbox.x = size;

    Color main_color = item->color_text;
    Color outline_color = mouse_active ? DATA->color_active : item->color_hitbox;
    Color background_color = mouse_hovered ? DATA->color_hovered_background : item->color_background;

    DrawRectanglePro(tGetUIItemHitbox(item), (Vector2){0, 0}, 0, background_color);
    DrawRectangleLinesEx(tGetUIItemHitbox(item), 2, outline_color);
    if (DATA->value)
    {
        Vector2 check_point_1 = {item->position.x + 0.25f * size, item->position.y + 0.5f  * size};
        Vector2 check_point_2 = {item->position.x + 0.5f  * size, item->position.y + 0.75f * size};
        Vector2 check_point_3 = {item->position.x + 0.75f * size, item->position.y + 0.25f * size};
        DrawLineEx(check_point_1, check_point_2, 4, BLACK);
        check_point_2.x -= 2;
        DrawLineEx(check_point_3, check_point_2, 4, BLACK);
    }

    tUpdateUIItemMouse(item);
}

void _tFreeCheckBox(UIItem *item)
{
    DATA->label_item->Free(DATA->label_item);
    free(DATA->label_item);
    free(DATA);
}
