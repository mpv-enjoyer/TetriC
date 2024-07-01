#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include "uiitem.h"

typedef struct UIDataPictureBox
{
    Image image;
    Texture2D texture;
    Color tint;
} UIDataPictureBox;

void tMakePictureBox(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor);

#endif //PICTUREBOX_H