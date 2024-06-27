#include "button.h"

void _UpdateDraw(UIItem *item);
void _Free(UIItem* item);

void tMakeButton(UIItem* item, const char* label, UIItem* parent, UIItemAnchor anchor)
{
    tMakeUIItem(item, label, anchor, parent, _UpdateDraw, _Free);
    item->stretch_x = false;
    item->data_button = (UIDataButton*)malloc(sizeof(UIDataButton));
    item->data_button->clicked = false;
    item->data_button->released = false;
    item->data_button->resize_on_hover = true;
    item->data_button->resized_text_size = 26;
    item->data_button->text_color = BLACK;
    item->data_button->outline_color = BLACK;
    item->data_button->hovered_text_color = RED;
}

void _UpdateDraw(UIItem* item)
{
    D_ASSERT(item->data_button);
    bool pressed_before = item->active;
    tUpdateUIItemXY(item);

    bool hovered = tIsUIItemHovered(item);

    Color text_color = item->data_button->text_color;
    int font_size = item->font_size;
    int outline = item->outline_size;

    Vector2 text_hitbox = tMeasureTextFix(item->label, font_size);

    if (hovered)
    {
        text_color = item->data_button->hovered_text_color;
        if (item->data_button->resize_on_hover)
        {
            font_size = item->data_button->resized_text_size;
            outline *= 2;
            text_hitbox = tMeasureTextFix(item->label, font_size);
        }
    }

    item->current_hitbox.x = text_hitbox.x + outline * 2;
    item->current_hitbox.y = text_hitbox.y + outline * 2;

    if (item->stretch_x)
    {
        item->current_hitbox.x = item->max_xy.x - item->position.x;
    }

    DrawRectanglePro(tGetUIItemHitbox(item), (Vector2){0, 0}, 0.0f, WHITE);
    DrawRectangleLinesEx(tGetUIItemHitbox(item), 2, item->data_button->outline_color);
    DrawText(item->label, item->position.x + outline, item->position.y + outline, font_size, text_color);
    
    bool pressed = (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
    item->data_button->clicked = !pressed_before && pressed;
    item->data_button->released = pressed_before && !pressed;
    item->active = pressed;
}

void _Free(UIItem* item)
{
    free(item->data_button);
}