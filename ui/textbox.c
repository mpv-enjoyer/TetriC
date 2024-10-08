#include "textbox.h"

#define DATA item->data_textbox

void _tUpdateHitboxTextBox(UIItem* item);
void _tUpdateTextBox(UIItem* item);
void _tDrawTextBox(UIItem* item);
void _tFreeTextBox(UIItem* item);

void _tProcessTextBox(UIItem* item);
void _tUpdateValueTextBox(UIItem* item);
void _tRestoreValueTextBox(UIItem* item);
int _tCheckInputTextBox(UIItem* item, int c);

void tMakeTextBox(UIItem *item, const char *label, UIItem* parent, UIItemAnchor anchor, const char *text, size_t max_size)
{
    tMakeUIItem(item, label, anchor, parent, _tUpdateHitboxTextBox, _tUpdateTextBox, _tDrawTextBox, _tFreeTextBox);
    if (anchor != AnchorLeft && anchor != AnchorRight) item->secondary_anchor = AnchorLeft;
    item->stretch_x = true;
    item->padding = item->outline_size;
    DATA = (UIDataTextBox*)malloc(sizeof(UIDataTextBox));
    D_ASSERT(max_size > 0);
    DATA->text = (char*)malloc(sizeof(char) * max_size);
    DATA->text_backup = (char*)malloc(sizeof(char) * max_size);
    DATA->max_size = max_size;
    if (!text)
    {
        DATA->text[0] = '\0';
        DATA->text_backup[0] = '\0';
    }
    else
    {
        int len = TextLength(text);
        int null_pos = MIN(len, max_size - 1);
        strncpy(DATA->text, text, MIN(len, max_size));
        DATA->text[null_pos] = '\0';
        strncpy(DATA->text_backup, DATA->text, max_size);
    }
    DATA->backspace_press_begin = 0.0f;
    DATA->backspace_press_last_emitted = 0.0f;
    DATA->backspace_emit_period = 0.1f;
    DATA->backspace_before_emit_period = 0.4f;
    DATA->label_item = (UIItem*)malloc(sizeof(UIItem));
    DATA->color_input_background = LIGHTGRAY;
    DATA->is_backspace_pressed = false;
    DATA->allow_edit = true;
    DATA->UpdateValue = _tUpdateValueTextBox;
    DATA->RestoreValue = _tRestoreValueTextBox;
    DATA->CheckInput = _tCheckInputTextBox;
    tMakeText(DATA->label_item, label, item, AnchorRight);
}

void _tUpdateHitboxTextBox(UIItem* item)
{
    D_ASSERT(DATA);
    tUpdateUIItemXY(item);
    DATA->label_item->UpdateHitbox(DATA->label_item);
    DATA->label_item->visible = item->visible;
    if (!tUpdateUIVisibility(item)) return;
    Vector2 measured_data = tMeasureTextFix(DATA->text, item->font_size);

    Vector2 old_hitbox = item->current_hitbox;

    item->current_hitbox.x = item->outline_size * 2 + measured_data.x;
    item->current_hitbox.y = item->outline_size * 2 + measured_data.y;

    int label_x_difference = GetRenderWidth() - DATA->label_item->current_hitbox.x - item->position.x - item->outline_size * 2 - measured_data.x;
    if (item->stretch_x && label_x_difference > 0) item->current_hitbox.x += label_x_difference;

    if (item->current_hitbox.x != old_hitbox.x || item->current_hitbox.y != old_hitbox.y)
    {
        item->position_changed = true;
    }
}

void _tUpdateTextBox(UIItem *item)
{
    D_ASSERT(DATA);
    DATA->label_item->Update(DATA->label_item);

    DATA->data_changed = false;
    if (item->mouse_clicked && DATA->allow_edit)
    {
        item->active = true;
        DATA->begin_active = GetTime();
    }
    else if (item->active)
    {
        _tProcessTextBox(item);
        bool should_change_data = false;
        bool should_keep_data = false;
        if (!item->mouse_clicked && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) should_change_data = true;
        if (IsKeyDown(KEY_ENTER)) should_change_data = true;
        if (IsKeyDown(KEY_ESCAPE)) should_keep_data = true;
        if (should_change_data)
        {
            item->active = false;
            DATA->UpdateValue(item);
            DATA->data_changed = true;
        }
        else if (should_keep_data)
        {
            item->active = false;
            DATA->RestoreValue(item);
        }
    }

    tUpdateUIItemMouse(item);
}

void _tDrawTextBox(UIItem *item)
{
    D_ASSERT(DATA);
    if (!item->visible) return;

    DATA->label_item->Draw(DATA->label_item);

    Vector2 measured_label = tMeasureTextFix(item->label, item->font_size);
    Vector2 measured_data = tMeasureTextFix(DATA->text, item->font_size);

    bool draw_cursor_line = (int)(GetTime() - DATA->begin_active) % 2 == 0 || DATA->is_backspace_pressed;

    DrawRectanglePro(tGetUIItemHitbox(item), (Vector2){0, 0}, 0, DATA->color_input_background);
    DrawRectangleLinesEx(tGetUIItemHitbox(item), 2, item->color_hitbox);
    DrawText(DATA->text, item->position.x + item->outline_size, item->position.y + item->outline_size, item->font_size, item->color_text);

    if (item->active && draw_cursor_line)
    {
        int cursor_x = item->position.x + measured_data.x + item->outline_size * 2;
        int cursor_y_upper_point = item->position.y + item->outline_size;
        int cursor_y_lower_point = cursor_y_upper_point + measured_data.y;
        DrawLine(cursor_x, cursor_y_upper_point, cursor_x, cursor_y_lower_point, item->color_text);
    }
}

void _tFreeTextBox(UIItem *item)
{
    DATA->label_item->Free(DATA->label_item);
    free(DATA->label_item);
    free(DATA->text);
    free(DATA->text_backup);
    free(DATA);
}

void _tProcessTextBox(UIItem *item)
{
    int length = TextLength(DATA->text);
    D_ASSERT(length + 1 <= DATA->max_size);
    bool emit_backspace = IsKeyDown(KEY_BACKSPACE);
    emit_backspace = emit_backspace && DATA->is_backspace_pressed;
    emit_backspace = emit_backspace && (GetTime() - DATA->backspace_press_begin) > DATA->backspace_before_emit_period;
    emit_backspace = emit_backspace && (GetTime() - DATA->backspace_press_last_emitted) > DATA->backspace_emit_period;

    if (length != 0 && (IsKeyPressed(KEY_BACKSPACE) || emit_backspace))
    {
        DATA->text[length - 1] = '\0';
        length -= 1;
        if (!DATA->is_backspace_pressed) DATA->backspace_press_begin = GetTime();
        DATA->is_backspace_pressed = true;
        DATA->backspace_press_last_emitted = GetTime();
    }
    else if (!IsKeyDown(KEY_BACKSPACE))
    {
        DATA->is_backspace_pressed = false;
    }

    if (length + 1 == DATA->max_size) return;
    int input_char = item->data_textbox->CheckInput(item, GetCharPressed());
    int new_input_char = input_char;
    while (new_input_char != KEY_NULL && length + 1 < DATA->max_size)
    {
        new_input_char = item->data_textbox->CheckInput(item, GetCharPressed());
        if (!input_char) continue;
        if (input_char == '\n') continue;
        DATA->text[length] = input_char;
        DATA->text[length + 1] = '\0';
        DATA->begin_active = GetTime();
        length++;
        input_char = new_input_char;
    }
}

void _tUpdateValueTextBox(UIItem *item)
{
    strncpy(DATA->text_backup, DATA->text, DATA->max_size);
}

void _tRestoreValueTextBox(UIItem *item)
{
    strncpy(DATA->text, DATA->text_backup, DATA->max_size);
}

int _tCheckInputTextBox(UIItem* item, int c)
{
    return c;
}
