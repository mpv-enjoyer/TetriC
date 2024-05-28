#include <raylib.h>
#include "field.h"
#include "shape.h"
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