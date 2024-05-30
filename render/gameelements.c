#include "gameelements.h"
#include "helpers.h"

void tDrawFieldBlock(float rectangle_size, int x, int y, int color_type, bool current_shape, bool shadow)
{
    Color color;
    switch (color_type)
    {
        case 0: color = FIELD_COLOR; break;
        case 1: color = SHAPE_O_COLOR; break;
        case 2: color = SHAPE_I_COLOR; break;
        case 3: color = SHAPE_T_COLOR; break;
        case 4: color = SHAPE_J_COLOR; break;
        case 5: color = SHAPE_L_COLOR; break;
        case 6: color = SHAPE_Z_COLOR; break;
        case 7: color = SHAPE_S_COLOR; break;
        default: D_ASSERT(false);
    }
    if (shadow) color.a = 80;
    Rectangle rect = { x, y, rectangle_size, rectangle_size };
    DrawRectangle(x, y, rectangle_size, rectangle_size, color);
    if (!current_shape) DrawRectangleLinesEx(rect, 1, BLACK);
}

void tDrawField(const Field *field, int begin_x, int rectangle_size)
{
    for (int yi = 0; yi < FIELD_HEIGHT; yi++)
    {
        for (int xi = 0; xi < FIELD_WIDTH; xi++)
        {
            Color color;
            int offset = yi * FIELD_WIDTH + xi;
            int x = begin_x + xi * rectangle_size;
            int y = (yi + FIELD_OUTSIDE_HEIGHT) * rectangle_size;
            tDrawFieldBlock(rectangle_size, x, y, field[offset], false, false);
        }
    }
}

void tDrawShape(const Shape *shape, int begin_x, int rectangle_size)
{
    for (int yi = 0; yi < SHAPE_SIZE; yi++)
    {
        for (int xi = 0; xi < SHAPE_SIZE; xi++)
        {
            int x = begin_x + (xi + shape->x) * rectangle_size;
            int y = (yi + shape->y + FIELD_OUTSIDE_HEIGHT) * rectangle_size;
            int shape_offset = yi * SHAPE_SIZE + xi;
            if (shape->hitboxes[shape->rotate_state][shape_offset] == '0') continue;
            tDrawFieldBlock(rectangle_size, x, y, shape->type + 1, true, false);
            int y_shadow = (yi + shape->y_shadow + FIELD_OUTSIDE_HEIGHT) * rectangle_size;
            tDrawFieldBlock(rectangle_size, x, y_shadow, shape->type + 1, true, true);
        }
    }
}

Vector2 _tStatisticsElement(const char* label, long value, Rectangle bounds)
{
    int font_size = 40;
    const char* text = TextFormat("%s: %i", label, value);
    Vector2 measured = tMeasureTextFix(text, font_size);
    if (measured.x < bounds.width)
    {
        DrawText(text, bounds.x + 2, bounds.y - 2, font_size, GRAY);
        DrawText(text, bounds.x, bounds.y, font_size, RAYWHITE);
        return measured;
    }
    value /= 1000;
    text = TextFormat("%s: %iK", label, value);
    measured = tMeasureTextFix(text, font_size);
    if (measured.x < bounds.width)
    {
        DrawText(text, bounds.x + 2, bounds.y - 2, font_size, GRAY);
        DrawText(text, bounds.x, bounds.y, font_size, RAYWHITE);
        return measured;
    }
    value /= 1000;
    text = TextFormat("%s: %iM", label, value);
    measured = tMeasureTextFix(text, font_size);
    if (measured.x < bounds.width)
    {
        DrawText(text, bounds.x + 2, bounds.y - 2, font_size, GRAY);
        DrawText(text, bounds.x, bounds.y, font_size, RAYWHITE);
        return measured;
    }
    value /= 1000;
    text = TextFormat("%s: %iB", label, value);
    measured = tMeasureTextFix(text, font_size);
    if (measured.x < bounds.width)
    {
        DrawText(text, bounds.x + 2, bounds.y - 2, font_size, GRAY);
        DrawText(text, bounds.x, bounds.y, font_size, RAYWHITE);
        return measured;
    }
    text = TextFormat("%s ?", label, value);
    measured = tMeasureTextFix(text, font_size);
    if (measured.x < bounds.width)
    {
        DrawText(text, bounds.x + 2, bounds.y - 2, font_size, GRAY);
        DrawText(text, bounds.x, bounds.y, font_size, RAYWHITE);
        return measured;
    }
    return (Vector2){0, 0};
}

void tDrawStatistics(const Record* current_record, Rectangle bounds)
{
    Vector2 measured;
    measured = _tStatisticsElement("Score", current_record->score, bounds);
    bounds.y += measured.y;
    bounds.height -= measured.y;
    if (bounds.height < 0) return;
    measured = _tStatisticsElement("Level", current_record->level, bounds);
    bounds.y += measured.y;
    bounds.height -= measured.y;
    if (bounds.height < 0) return;
    measured = _tStatisticsElement("Lines", current_record->lines_cleared, bounds);
    bounds.y += measured.y;
    bounds.height -= measured.y;
    if (bounds.height < 0) return;
    measured = _tStatisticsElement("Time", current_record->time, bounds);
    bounds.y += measured.y;
    bounds.height -= measured.y;
}