#ifndef UI_H
#define UI_H

#include "timgui.h"

#define UI_DEFAULT_FIELDS(data_t) \
    data_t data; \
    const char* label; \
    bool data_changed; \
    int x; \
    int y; \
    int height

typedef struct UIButton
{
    UI_DEFAULT_FIELDS(bool);
} UIButton;

void tMakeUIButton(UIButton* button, int x, int y, const char* label, bool data);
void tDrawUpdateUIButton(UIButton* button, int* next_element_y);

typedef struct UICheckBox
{
    UI_DEFAULT_FIELDS(bool);
} UICheckBox;

void tMakeUICheckBox(UICheckBox* checkbox, int x, int y, const char* label, bool data);
void tDrawUpdateUICheckBox(UICheckBox* checkbox, int* next_element_y);

typedef struct UITextBox
{
    UI_DEFAULT_FIELDS(char*);
    char* data_backup;
    int data_size;
    bool active;
} UITextBox;

void tMakeUITextBox(UITextBox *textbox, int x, int y, const char *label, char *data, char *data_backup, int data_size, const char *value);
void tDrawUpdateUITextBox(UITextBox* textbox, int* next_element_y);

typedef struct UIDoubleBox
{
    UI_DEFAULT_FIELDS(char*);
    int data_size;
    bool active;
    double value;
    double min;
    double max;
} UIDoubleBox;

void tMakeUIDoubleBox(UIDoubleBox* doublebox, int x, int y, const char* label, char* data, int data_size, double value, double min, double max);
void tDrawUpdateUIDoubleBox(UIDoubleBox* doublebox, int* next_element_y);

typedef struct UIIntBox
{
    UI_DEFAULT_FIELDS(char*);
    int data_size;
    bool active;
    int value;
    int min;
    int max;
} UIIntBox;

void tMakeUIIntBox(UIIntBox* intbox, int x, int y, const char* label, char* data, int data_size, int value, int min, int max);
void tDrawUpdateUIIntBox(UIIntBox* intbox, int* next_element_y);

#endif