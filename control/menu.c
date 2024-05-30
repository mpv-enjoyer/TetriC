#include "menu.h"
#include "render.h"
#include "shared.h"
#include "helpers.h"

Shared tMenu(Shared shared)
{
    int selected = -1;
    Rectangle* hitboxes = (Rectangle*)malloc(MENU_ITEM_COUNT * sizeof(Rectangle));
    while (shared.state == STATE_IN_MENU)
    {
        tCalculateMultipleCenteredText(menu_item_strings, MENU_ITEM_COUNT, hitboxes, DEFAULT_FONT_SIZE * 2);
        selected = -1;
        for (int i = 0; i < MENU_ITEM_COUNT; i++)
        {
            if (CheckCollisionPointRec(GetMousePosition(), hitboxes[i])) 
            {
                selected = i;
                hitboxes[i].x -= 5;
                hitboxes[i].y -= 5;
                break;
            }
        }
        tDrawMenuFrame(selected, hitboxes);
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && selected == 0) shared.state = STATE_PLAYING;
        if (IsKeyPressed(KEY_ENTER)) shared.state = STATE_PLAYING;
        if (WindowShouldClose()) shared.state = STATE_EXITING;
    }
    free(hitboxes);
    return shared;
}