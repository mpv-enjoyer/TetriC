#include <raylib.h>
#include "field.h"
#include "shapes.h"
#include "render.h"

int main(void)
{
    tInit();
    do
    {
        tMainLoop();
    }
    while (tMenu());
    CloseWindow();
    return 0;
}