#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "uiitem.h"
#include "ui.h"

typedef struct UIDataTextBox
{
    char* text;
    char* text_backup;
    size_t max_size;
    bool is_number;
    bool is_integer;
    UIItem* label_item;
    Color color_input_background;
    double begin_active;
    bool is_backspace_pressed;
    double backspace_press_begin;
    double backspace_press_last_emitted;
    double backspace_emit_period;
    double backspace_before_emit_period;
    bool data_changed;
    UIItemFunction UpdateValue;
    UIItemFunction RestoreValue;
} UIDataTextBox;

void tMakeTextBox(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor, const char *text, size_t max_size);

#endif //TEXTBOX_H