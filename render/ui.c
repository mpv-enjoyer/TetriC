#include "ui.h"
#include <errno.h>

#define SETUP_UI_ELEMENT(name) \
    name->data = data; \
    name->data_changed = false; \
    name->x = x; \
    name->y = y; \
    name->label = label

void tMakeUIButton(UIButton *button, int x, int y, const char* label, bool data)
{
    SETUP_UI_ELEMENT(button);
}

void tDrawUpdateUIButton(UIButton *button, int* next_element_y)
{
    bool data_before = button->data;
    bool clicked = tButton(button->x, button->y, button->label, &(button->height));
    button->data = clicked;
    button->data_changed = clicked != data_before;
    if (next_element_y) *next_element_y = button->y + button->height;
}

void tMakeUICheckBox(UICheckBox *checkbox, int x, int y, const char *label, bool data)
{
    SETUP_UI_ELEMENT(checkbox);
}

void tDrawUpdateUICheckBox(UICheckBox *checkbox, int* next_element_y)
{
    checkbox->data_changed = tCheckbox(&(checkbox->data), checkbox->x, checkbox->y, checkbox->label, &(checkbox->height));
    if (next_element_y) *next_element_y = checkbox->y + checkbox->height;
}

void tMakeUITextBox(UITextBox *textbox, int x, int y, const char *label, char *data, char* data_backup, int data_size, const char *value)
{
    SETUP_UI_ELEMENT(textbox);
    textbox->data_size = data_size;
    textbox->active = false;
    if (!value || value == data) 
    {
        data[0] = '\0';
        data_backup[0] = '\0';
        return;
    }
    strncpy(data, value, MIN(TextLength(value), data_size));
    strncpy(data_backup, data, data_size);
}

void tDrawUpdateUITextBox(UITextBox *textbox, int* next_element_y)
{
    bool was_active = textbox->active;
    textbox->data_changed = tTextBox(textbox->data, textbox->data_size, textbox->x, textbox->y, TEXTBOX_MODE_STRING, textbox->label, &(textbox->height), &(textbox->active));
    bool is_active = textbox->active;
    if (was_active && !is_active)
    {
        if (textbox->data_changed) strncpy(textbox->data_backup, textbox->data, textbox->data_size);
        else strncpy(textbox->data, textbox->data_backup, textbox->data_size);
    }
    if (next_element_y) *next_element_y = textbox->y + textbox->height;
}

void tMakeUIDoubleBox(UIDoubleBox *doublebox, int x, int y, const char *label, char *data, int data_size, double value, double min, double max)
{
    SETUP_UI_ELEMENT(doublebox);
    doublebox->value = value;
    doublebox->data_size = data_size;
    doublebox->active = false;
    doublebox->min = min;
    doublebox->max = max;
    D_ASSERT(min <= value && value <= max);
    snprintf(data, data_size, "%f", value);
}

void tDrawUpdateUIDoubleBox(UIDoubleBox *doublebox, int* next_element_y)
{
    bool was_active = doublebox->active;
    doublebox->data_changed = tTextBox(doublebox->data, doublebox->data_size, doublebox->x, doublebox->y, TEXTBOX_MODE_DOUBLE, doublebox->label, &(doublebox->height), &(doublebox->active));
    bool is_active = doublebox->active;
    if (was_active && !is_active)
    {
        double parsed = atof(doublebox->data);
        if (parsed < doublebox->min) parsed = doublebox->min;
        if (parsed > doublebox->max) parsed = doublebox->max;
        if (doublebox->data_changed) doublebox->value = parsed;
        snprintf(doublebox->data, doublebox->data_size, "%f", doublebox->value);
    }
    if (next_element_y) *next_element_y = doublebox->y + doublebox->height;
}

void tMakeUIIntBox(UIIntBox *intbox, int x, int y, const char *label, char *data, int data_size, int value, int min, int max)
{
    SETUP_UI_ELEMENT(intbox);
    intbox->value = value;
    intbox->data_size = data_size;
    intbox->active = false;
    intbox->min = min;
    intbox->max = max;
    D_ASSERT(min <= value && value <= max);
    snprintf(data, data_size, "%i", value);
}

void tDrawUpdateUIIntBox(UIIntBox *intbox, int* next_element_y)
{
    bool was_active = intbox->active;
    intbox->data_changed = tTextBox(intbox->data, intbox->data_size, intbox->x, intbox->y, TEXTBOX_MODE_INT, intbox->label, &(intbox->height), &(intbox->active));
    bool is_active = intbox->active;
    if (was_active && !is_active)
    {
        int parsed = atoi(intbox->data);
        if (parsed < intbox->min) parsed = intbox->min;
        if (parsed > intbox->max) parsed = intbox->max;
        if (intbox->data_changed) intbox->value = parsed;
        snprintf(intbox->data, intbox->data_size, "%i", intbox->value);
    }
    if (next_element_y) *next_element_y = intbox->y + intbox->height;
}
