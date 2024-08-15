#include "picturebox.h"

#define DATA item->data_picturebox

void _tUpdateHitboxPictureBox(UIItem* item);
void _tUpdatePictureBox(UIItem* item);
void _tDrawPictureBox(UIItem* item);
void _tFreePictureBox(UIItem* item);

void tMakePictureBox(UIItem *item, const char *label, UIItem *parent, UIItemAnchor anchor)
{
    tMakeUIItem(item, label, anchor, parent, _tUpdateHitboxPictureBox, _tUpdatePictureBox, _tDrawPictureBox, _tFreePictureBox);
    DATA = (UIDataPictureBox*)malloc(sizeof(UIDataPictureBox));
    DATA->image = LoadImage(label);
    DATA->texture = LoadTextureFromImage(DATA->image);
    DATA->tint = WHITE;
}

void _tUpdateHitboxPictureBox(UIItem *item)
{
    D_ASSERT(DATA);
    tUpdateUIItemXY(item);
    if (IsTextureReady(DATA->texture)) item->visible = false;
    if (!tUpdateUIVisibility(item)) return;

    item->current_hitbox.x = DATA->texture.width;
    item->current_hitbox.y = DATA->texture.height;
}

void _tUpdatePictureBox(UIItem *item)
{
    D_ASSERT(DATA);
    tUpdateUIItemMouse(item);
}

void _tDrawPictureBox(UIItem *item)
{
    D_ASSERT(DATA);
    if (!item->visible) return;
    DrawTexture(DATA->texture, item->position.x, item->position.y, DATA->tint);
    DrawRectangleLinesEx(tGetUIItemHitbox(item), 2, item->color_hitbox);
}

void _tFreePictureBox(UIItem *item)
{
    UnloadTexture(DATA->texture);
    UnloadImage(DATA->image);
    free(DATA);
}
