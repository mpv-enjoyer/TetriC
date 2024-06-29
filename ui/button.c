#include "button.h"

void _UpdateDrawButton(UIItem *item);
void _FreeButton(UIItem* item);

void tMakeButton(UIItem* item, const char* label, UIItem* parent, UIItemAnchor anchor)
{
    tMakeUIItem(item, label, anchor, parent, _UpdateDrawButton, _FreeButton);
    item->color_hitbox = BLACK;
    item->data_button = (UIDataButton*)malloc(sizeof(UIDataButton));
    item->data_button->resize_on_hover = true;
    item->data_button->resized_text_size = 46;
    item->data_button->recolor_on_active = true;
    item->data_button->color_active = RED;
}

void _UpdateDrawButton(UIItem* item)
{
    D_ASSERT(item->data_button);
    tUpdateUIItemXY(item);
    if (!tUpdateUIVisibility(item)) return;

    Color text_color = item->color_text;
    Color outline_color = item->color_hitbox;
    int font_size = item->font_size;
    int outline = item->outline_size;
    Vector2 text_hitbox = tMeasureTextFix(item->label, font_size);

    if (item->mouse_hovered)
    {
        if (item->data_button->recolor_on_active) text_color = item->data_button->color_active;
        if (item->data_button->resize_on_hover)
        {
            font_size = item->data_button->resized_text_size;
            outline *= 2;
            text_hitbox = tMeasureTextFix(item->label, font_size);
        }
    }

    item->current_hitbox.x = text_hitbox.x + outline * 2;
    item->current_hitbox.y = text_hitbox.y + outline * 2;

    int text_x = item->position.x + outline;
    if (item->stretch_x)
    {
        text_x = text_x + (item->max_xy.x - item->position.x - text_hitbox.x) / 2;
        item->current_hitbox.x = item->max_xy.x - item->position.x;
    }

    if (item->mouse_active && item->mouse_hovered) outline_color = item->data_button->color_active;

    DrawRectanglePro(tGetUIItemHitbox(item), (Vector2){0, 0}, 0.0f, item->color_background);
    DrawRectangleLinesEx(tGetUIItemHitbox(item), 2, outline_color);
    DrawText(item->label, text_x, item->position.y + outline, font_size, text_color);

    tUpdateUIItemMouse(item);
}

void _FreeButton(UIItem* item)
{
    free(item->data_button);
}