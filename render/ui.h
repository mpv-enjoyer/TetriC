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
void tDrawUpdateUIButton(UIButton* button);

typedef struct UICheckBox
{
    UI_DEFAULT_FIELDS(bool);
} UICheckBox;

void tMakeUICheckBox(UICheckBox* checkbox, int x, int y, const char* label, bool data);
void tDrawUpdateUICheckBox(UICheckBox* checkbox);

typedef struct UITextBox
{
    UI_DEFAULT_FIELDS(char*);
    char* data_backup;
    int data_size;
    bool active;
} UITextBox;

void tMakeUITextBox(UITextBox *textbox, int x, int y, const char *label, char *data, char *data_backup, int data_size, const char *value);
void tDrawUpdateUITextBox(UITextBox* textbox);

typedef struct UIDoubleBox
{
    UI_DEFAULT_FIELDS(char*);
    int data_size;
    bool active;
    double value;
} UIDoubleBox;

void tMakeUIDoubleBox(UIDoubleBox* doublebox, int x, int y, const char* label, char* data, int data_size, double value);
void tDrawUpdateUIDoubleBox(UIDoubleBox* doublebox);

typedef struct UIIntBox
{
    UI_DEFAULT_FIELDS(char*);
    int data_size;
    bool active;
    int value;
} UIIntBox;

void tMakeUIIntBox(UIIntBox* intbox, int x, int y, const char* label, char* data, int data_size, int value);
void tDrawUpdateUIIntBox(UIIntBox* intbox);

#endif