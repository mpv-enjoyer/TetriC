#include "button.h"

#define DATA item->data_button

void _tUpdateHitboxButton(UIItem* item);
void _tUpdateButton(UIItem* item);
void _tDrawButton(UIItem* item);
void _tFreeButton(UIItem* item);

void tMakeButton(UIItem* item, const char* label, UIItem* parent, UIItemAnchor anchor)
{
    tMakeUIItem(item, label, anchor, parent, _tUpdateHitboxButton, _tUpdateButton, _tDrawButton, _tFreeButton);
    item->color_hitbox = BLACK;
    DATA = (UIDataButton*)malloc(sizeof(UIDataButton));
    DATA->resize_on_hover = true;
    DATA->resized_text_size = 46;
    DATA->recolor_on_active = true;
    DATA->color_active = RED;
}

void _tUpdateHitboxButton(UIItem *item)
{
    D_ASSERT(DATA);
    tUpdateUIItemXY(item);
    if (!tUpdateUIVisibility(item)) return;

    int font_size = item->font_size;
    int outline = item->outline_size;
    Vector2 text_hitbox = tMeasureTextFix(item->label, font_size);

    if (item->mouse_hovered)
    {
        if (DATA->resize_on_hover)
        {
            font_size = DATA->resized_text_size;
            outline *= 2;
            text_hitbox = tMeasureTextFix(item->label, font_size);
        }
    }

    Vector2 old_hitbox = item->current_hitbox;

    item->current_hitbox.x = text_hitbox.x + outline * 2;
    item->current_hitbox.y = text_hitbox.y + outline * 2;

    if (item->stretch_x)
    {
        item->current_hitbox.x = item->max_xy.x - item->position.x;
    }

    if (item->current_hitbox.x != old_hitbox.x || item->current_hitbox.y != old_hitbox.y)
    {
        item->position_changed = true;
    }
}

void _tUpdateButton(UIItem *item)
{
    D_ASSERT(DATA);
    tUpdateUIItemMouse(item);
}

void _tDrawButton(UIItem *item)
{
    D_ASSERT(DATA);
    if (!item->visible) return;

    Color text_color = item->color_text;
    Color outline_color = item->color_hitbox;
    int font_size = item->font_size;
    int outline = item->outline_size;
    Vector2 text_hitbox = tMeasureTextFix(item->label, font_size);

    if (item->mouse_hovered)
    {
        if (DATA->recolor_on_active)
        {
            text_color = DATA->color_active;
        }
        if (DATA->resize_on_hover)
        {
            font_size = DATA->resized_text_size;
            outline *= 2;
            text_hitbox = tMeasureTextFix(item->label, font_size);
        }
    }

    int text_x = item->position.x + outline;
    if (item->stretch_x)
    {
        text_x = text_x + (item->max_xy.x - item->position.x - text_hitbox.x) / 2;
    }

    if (item->mouse_active && item->mouse_hovered && DATA->recolor_on_active)
    {
        outline_color = DATA->color_active;
    }

    DrawRectanglePro(tGetUIItemHitbox(item), (Vector2){0, 0}, 0.0f, item->color_background);
    DrawRectangleLinesEx(tGetUIItemHitbox(item), 2, outline_color);
    DrawText(item->label, text_x, item->position.y + outline, font_size, text_color);
}

void _tFreeButton(UIItem* item)
{
    free(DATA);
}