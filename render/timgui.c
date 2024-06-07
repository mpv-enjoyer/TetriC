#include "timgui.h"

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

bool tTextBox(char* data, int max_length, int x, int y, int mode, const char* text, int* height, bool* active)
{
    const int outline_value = 5;
    int font_size = 35;
    x += outline_value * 2;
    y += outline_value;
    Vector2 measured = tMeasureTextFix(text, font_size);
    int text_x = GetRenderWidth() - measured.x - outline_value;
    Vector2 measured_data = tMeasureTextFix(data, font_size);
    bool show_right_text = true;
    if (x + measured_data.x + outline_value + measured.x > GetRenderWidth()) show_right_text = false;
    Rectangle hitbox;
    hitbox.x = x - outline_value;
    hitbox.y = y;
    hitbox.width = text_x - x - outline_value;
    hitbox.height = measured_data.y;
    DrawRectanglePro(hitbox, (Vector2){0, 0}, 0, LIGHTGRAY);
    DrawText(data, x, y, font_size, BLACK);
    DrawText(text, text_x, y, font_size, BLACK);
    if (height) *height = hitbox.height + outline_value;
    bool hovered = CheckCollisionPointRec(GetMousePosition(), hitbox);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        *active = hovered;
    }
    if (!(*active)) return false;
    if (IsKeyPressed(KEY_ENTER)) 
    {
        *active = false;
        return true;
    }
    int length = TextLength(data);
    D_ASSERT(length + 1 <= max_length);
    if (length != 0 && IsKeyPressed(KEY_BACKSPACE))
    {
        data[length - 1] = '\0';
        length -= 1;
    }
    if ((int)GetTime() % 2) DrawLine(x + measured_data.x + outline_value, y, x + measured_data.x + outline_value, y + measured_data.y, BLACK);
    if (length + 1 == max_length) return false;
    int input_char = GetCharPressed();
    int new_input_char = input_char;
    while (new_input_char != 0 && length + 1 < max_length)
    {
        bool is_number = input_char >= '0' && input_char <= '9';
        bool is_number_delimiter = input_char == ',' || input_char == '.';
        new_input_char = GetCharPressed();
        if (mode == TEXTBOX_MODE_INT && !is_number) continue;
        if (mode == TEXTBOX_MODE_DOUBLE && !(is_number || is_number_delimiter)) continue;
        if (input_char == '\n') continue;
        if (input_char == ',') input_char = '.';
        data[length] = input_char;
        data[length + 1] = '\0';
        length++;
        input_char = new_input_char;
    }
    return false;
}