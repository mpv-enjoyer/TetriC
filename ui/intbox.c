#include "intbox.h"

#define DATA item->data_intbox

void _tFreeIntBox(UIItem* item);
void _tUpdateValueIntBox(UIItem* item);
void _tRestoreValueIntBox(UIItem* item);
int _tCheckInputIntBox(UIItem* item, int c);

void tMakeIntBox(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor, int value, int min, int max)
{
    char buffer_for_max[20];
    int buffer_size = snprintf(&(buffer_for_max[0]), 20, "%i", max) + 1;
    char buffer[buffer_size];
    snprintf(&(buffer[0]), buffer_size, "%i", value);
    tMakeTextBox(item, label, parent, anchor, &(buffer[0]), buffer_size);
    item->data_textbox->UpdateValue = _tUpdateValueIntBox;
    item->data_textbox->RestoreValue = _tRestoreValueIntBox;
    item->data_textbox->CheckInput = _tCheckInputIntBox;
    DATA = (UIDataIntBox*)malloc(sizeof(UIDataIntBox));
    DATA->value = value;
    DATA->min = min;
    DATA->max = max;
}

void _tFreeIntBox(UIItem *item)
{
    item->data_textbox->label_item->Free(item->data_textbox->label_item);
    free(item->data_textbox->label_item);
    free(item->data_textbox->text);
    free(item->data_textbox->text_backup);
    free(item->data_textbox);
    free(DATA);
}

void _tUpdateValueIntBox(UIItem *item)
{
    double parsed = atoi(item->data_textbox->text);
    if (parsed < DATA->min) parsed = DATA->min;
    if (parsed > DATA->max) parsed = DATA->max;
    DATA->value = parsed;
    snprintf(item->data_textbox->text_backup, item->data_textbox->max_size, "%i", DATA->value);
    snprintf(item->data_textbox->text, item->data_textbox->max_size, "%i", DATA->value);
}

void _tRestoreValueIntBox(UIItem *item)
{
    snprintf(item->data_textbox->text, item->data_textbox->max_size, "%i", DATA->value);
}

int _tCheckInputIntBox(UIItem* item, int c)
{
    bool is_number = c >= '0' && c <= '9';
    if (!is_number) return 0;
    return c;
}