#include "helpers.h"

Rectangle tResizeCentered(Rectangle rectangle, int dw, int dh)
{
    rectangle.x -= dw / 2;
    rectangle.y -= dh / 2;
    rectangle.width += dw;
    rectangle.height += dh;
    return rectangle;
}

Vector2 tMeasureTextFix(const char* text, int font_size)
{
    Vector2 measured = MeasureTextEx(GetFontDefault(), text, font_size, 0);
    measured.x = MeasureText(text, font_size);
    return measured;
}

Rectangle tCalculateCenteredText(const char *text, int x, int y, int font_size)
{
    Vector2 measured = tMeasureTextFix(text, font_size);
    Rectangle output;
    output.x = x - measured.x / 2;
    output.y = y - measured.y / 2;
    output.width = measured.x;
    output.height = measured.y;
    return output;
}

bool tCalculateMultipleCenteredText(const char* text_array[], int count, Rectangle* rectangles, int font_size)
{
    int h = GetRenderHeight();
    int w = GetRenderWidth();
    int sectors = count * 2 - 1;
    Rectangle precalculated = tCalculateCenteredText("Welp", w / 2, h / 2, font_size);
    float text_height = precalculated.height;
    int begin_draw_y = ( h / 2 ) - text_height * (sectors / 2.0f);
    for (int i = 0; i < sectors; i++)
    {
        if (i % 2 == 1) continue;
        int array_index = i / 2;
        int y = begin_draw_y + i * text_height;
        rectangles[array_index] = tCalculateCenteredText(text_array[array_index], w / 2, y, font_size);
    }
    return true;
}
