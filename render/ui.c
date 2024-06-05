#include "ui.h"

bool tCenteredButton(int y_center, const char* text, int* height)
{
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

bool tButton(int x, int y, const char* text, int* height)
{
    const int outline_value = 5;
    int font_size = 35;
    Color text_color = BLACK;
    Color outline_color = BLACK;
    Rectangle hitbox;
    x += outline_value * 2;
    y += outline_value;
    hitbox.x = x;
    hitbox.y = y;
    Vector2 measured = tMeasureTextFix(text, font_size);
    hitbox.height = measured.y;
    hitbox.width = measured.x;
    Rectangle outline_hitbox = tResizeCentered(hitbox, outline_value * 2, outline_value * 2);
    if (height) *height = outline_hitbox.height;
    bool hovered = CheckCollisionPointRec(GetMousePosition(), outline_hitbox);
    if (hovered) text_color = RED;
    DrawRectangle(outline_hitbox.x, outline_hitbox.y, outline_hitbox.width, outline_hitbox.height, RAYWHITE);
    DrawRectangleLinesEx(outline_hitbox, 2, outline_color);
    DrawText(text, hitbox.x, hitbox.y, font_size, text_color);
    return (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

bool tCheckbox(bool* value, int x, int y, const char* text, int* height)
{
    const int outline_value = 5;
    int font_size = 35;
    Color background_color = WHITE;
    Vector2 measured = tMeasureTextFix(text, font_size);
    Rectangle hitbox;
    x += outline_value;
    y += outline_value;
    hitbox.x = x;
    hitbox.y = y;
    hitbox.width = measured.y + outline_value + measured.x;
    hitbox.height = measured.y;
    Rectangle outline_hitbox = tResizeCentered(hitbox, outline_value * 2, outline_value * 2);
    bool hovered = CheckCollisionPointRec(GetMousePosition(), outline_hitbox);
    if (hovered) background_color = GRAY;
    DrawText(text, x + measured.y + outline_value, hitbox.y, font_size, BLACK);
    Rectangle checkbox_hitbox;
    checkbox_hitbox.x = x;
    checkbox_hitbox.y = y;
    checkbox_hitbox.height = measured.y;
    checkbox_hitbox.width = measured.y;
    DrawRectanglePro(checkbox_hitbox, (Vector2){0, 0}, 0, background_color);
    DrawRectangleLinesEx(checkbox_hitbox, 2, BLACK);
    if (*value)
    {
        Vector2 check_point_1 = {x + 0.25f * measured.y, y + 0.5f  * measured.y};
        Vector2 check_point_2 = {x + 0.5f  * measured.y, y + 0.75f * measured.y};
        Vector2 check_point_3 = {x + 0.75f * measured.y, y + 0.25f * measured.y};
        DrawLineEx(check_point_1, check_point_2, 4, BLACK);
        check_point_2.x -= 2;
        DrawLineEx(check_point_3, check_point_2, 4, BLACK);
    }
    bool changed = false;
    if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
    {
        *value = !(*value);
        changed = true;
    }
    if (height) *height = outline_hitbox.height;
    return changed;
}