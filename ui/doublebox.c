#include "doublebox.h"

#define DATA item->data_doublebox

void _tFreeDoubleBox(UIItem *item);
void _tUpdateValueDoubleBox(UIItem* item);
void _tRestoreValueDoubleBox(UIItem* item);

void tMakeDoubleBox(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor, double value, double min, double max)
{
    const int buffer_size = 10;
    char buffer[buffer_size];
    snprintf(&(buffer[0]), buffer_size, "%f", value);
    tMakeTextBox(item, label, parent, anchor, &(buffer[0]), buffer_size);
    item->data_textbox->UpdateValue = _tUpdateValueDoubleBox;
    item->data_textbox->RestoreValue = _tRestoreValueDoubleBox;
    item->data_textbox->is_integer = false;
    item->data_textbox->is_number = true;
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
