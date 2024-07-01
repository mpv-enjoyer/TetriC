#include "picturebox.h"

#define DATA item->data_picturebox

void _tUpdateDrawPictureBox(UIItem* item);
void _tFreePictureBox(UIItem* item);

void tMakePictureBox(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor)
{
    tMakeUIItem(item, label, anchor, parent, _tUpdateDrawPictureBox, _tFreePictureBox);
    DATA = (UIDataPictureBox*)malloc(sizeof(UIDataPictureBox));
    DATA->image = LoadImage(label);
    DATA->texture = LoadTextureFromImage(DATA->image);
    DATA->tint = WHITE;
}

void _tUpdateDrawPictureBox(UIItem *item)
{
    D_ASSERT(DATA);
    tUpdateUIItemXY(item);
    item->visible = IsTextureReady(DATA->texture);
    if (!tUpdateUIVisibility(item)) return;

    item->current_hitbox.x = DATA->texture.width;
    item->current_hitbox.y = DATA->texture.height;
    DrawTexture(DATA->texture, item->position.x, item->position.y, DATA->tint);
    DrawRectangleLinesEx(tGetUIItemHitbox(item), 2, item->color_hitbox);
    
    tUpdateUIItemMouse(item);
}

void _tFreePictureBox(UIItem *item)
{
    UnloadTexture(DATA->texture);
    UnloadImage(DATA->image);
    free(DATA);
}
