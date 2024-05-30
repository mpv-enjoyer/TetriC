#include "ui.h"

bool tCenteredButton(int y_center, const char* text)
{
    int font_size = 30;
    Color text_color = BLACK;
    Color outline_color = BLACK;
    Rectangle hitbox = tCalculateCenteredText(text, GetRenderWidth() / 2, y_center, font_size);
    Rectangle outline_hitbox = tResizeCentered(hitbox, 10, 10);
    bool hovered = CheckCollisionPointRec(GetMousePosition(), outline_hitbox);
    if (hovered)
    {
        font_size = 35;
        text_color = RED;
        hitbox = tCalculateCenteredText(text, GetRenderWidth() / 2, y_center, font_size);
        outline_hitbox = tResizeCentered(hitbox, 10, 10);
    }
    DrawRectangle(outline_hitbox.x, outline_hitbox.y, outline_hitbox.width, outline_hitbox.height, RAYWHITE);
    DrawRectangleLinesEx(outline_hitbox, 2, outline_color);
    DrawText(text, hitbox.x, hitbox.y, font_size, text_color);
    return (hovered && IsMouseButtonDown(MOUSE_LEFT_BUTTON));
}