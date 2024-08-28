#include "doublebox.h"

#define DATA item->data_doublebox

void _tFreeDoubleBox(UIItem *item);
void _tUpdateValueDoubleBox(UIItem* item);
void _tRestoreValueDoubleBox(UIItem* item);
int _tCheckInputDoubleBox(UIItem* item, int c);

void tMakeDoubleBox(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor, double value, double min, double max)
{
    const int buffer_size = 10;
    char buffer[buffer_size];
    snprintf(&(buffer[0]), buffer_size, "%f", value);
    tMakeTextBox(item, label, parent, anchor, &(buffer[0]), buffer_size);
    item->data_textbox->UpdateValue = _tUpdateValueDoubleBox;
    item->data_textbox->RestoreValue = _tRestoreValueDoubleBox;
    item->data_textbox->CheckInput = _tCheckInputDoubleBox;
    DATA = (UIDataDoubleBox*)malloc(sizeof(UIDataDoubleBox));
    DATA->value = value;
    DATA->min = min;
    DATA->max = max;
}

void _tFreeDoubleBox(UIItem *item)
{
    item->data_textbox->label_item->Free(item->data_textbox->label_item);
    free(item->data_textbox->label_item);
    free(item->data_textbox->text);
    free(item->data_textbox->text_backup);
    free(item->data_textbox);
    free(DATA);
}

void _tUpdateValueDoubleBox(UIItem *item)
{
    double parsed = atof(item->data_textbox->text);
    if (parsed < DATA->min) parsed = DATA->min;
    if (parsed > DATA->max) parsed = DATA->max;
    DATA->value = parsed;
    snprintf(item->data_textbox->text_backup, item->data_textbox->max_size, "%f", DATA->value);
    snprintf(item->data_textbox->text, item->data_textbox->max_size, "%f", DATA->value);
}

void _tRestoreValueDoubleBox(UIItem *item)
{
    snprintf(item->data_textbox->text, item->data_textbox->max_size, "%f", DATA->value);
}

int _tCheckInputDoubleBox(UIItem* item, int c)
{
    bool is_number = c >= '0' && c <= '9';
    bool is_number_delimiter = c == ',' || c == '.';
    if (!is_number && !is_number_delimiter) return 0;
    for (int i = 0; i < item->data_textbox->max_size; i++)
    {
        char current_char = item->data_textbox->text[i];
        if (!current_char) break;
        if (current_char == '.')
        {
            if (is_number_delimiter) return 0;
            break;
        }
    }
    if (is_number_delimiter) c = '.';
    return c;
}