#include "button.h"

void _UpdateDraw(UIItem* item);
void _Free(UIItem* item);

void tMakeButton(UIItem* item, const char* label, UIItem* parent, UIItemAnchor anchor)
{
    tMakeUIItem(item, label, anchor, parent, _UpdateDraw, _Free);
    item->data_button = (UIDataButton*)malloc(sizeof(UIDataButton));
    item->data_button->clicked = false;
    item->data_button->released = false;
    item->data_button->resize_on_hover = false;
}

void _UpdateDraw(UIItem* item)
{
    bool clicked_before = item->active;

    
    bool clicked = tButton(button->x, button->y, button->label, &(button->height));
    button->data = clicked;
    button->data_changed = clicked != data_before;
    if (next_element_y) *next_element_y = button->y + button->height;


    const int outline_value = 5;
    int font_size = 35;
    Color text_color = BLACK;
    Color outline_color = BLACK;
    Rectangle hitbox = tCalculateCenteredText(text, GetRenderWidth() / 2, y_center, font_size);
    Rectangle outline_hitbox = tResizeCentered(hitbox, outline_value * 2, outline_value * 2);
    if (height) *height = outline_hitbox.height;
    bool hovered = CheckCollisionPointRec(GetMousePosition(), outline_hitbox);
    if (hovered)
    {
        font_size = 40;
        text_color = RED;
        hitbox = tCalculateCenteredText(text, GetRenderWidth() / 2, y_center, font_size);
        outline_hitbox = tResizeCentered(hitbox, outline_value * 2, outline_value * 2);
    }
    DrawRectangle(outline_hitbox.x, outline_hitbox.y, outline_hitbox.width, outline_hitbox.height, RAYWHITE);
    DrawRectangleLinesEx(outline_hitbox, 2, outline_color);
    DrawText(text, hitbox.x, hitbox.y, font_size, text_color);
    return (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}