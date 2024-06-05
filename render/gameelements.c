#include "gameelements.h"
#include "helpers.h"
#include "bag.h"

void tDrawFieldBlockRotated(float rectangle_size, int x, int y, int color_type, bool current_shape, bool shadow, float rotation, Vector2 origin)
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
    if (shadow) color.a = 60;
    Color bound_color = current_shape ? color : BLACK;
    Rectangle rect = { (float)x, (float)y, rectangle_size, rectangle_size };
    DrawRectanglePro(rect, origin, rotation, bound_color);
    Rectangle bound = tResizeCentered(rect, -2, -2);
    DrawRectanglePro(bound, origin, rotation, color);
}

void tDrawFieldBlock(float rectangle_size, int x, int y, int color_type)
{
    tDrawFieldBlockRotated(rectangle_size, x, y, color_type, false, false, 0, (Vector2){0, 0});
}

void tDrawShapeBlock(float rectangle_size, int x, int y, int color_type)
{
    tDrawFieldBlockRotated(rectangle_size, x, y, color_type, true, false, 0, (Vector2){0, 0});
}

void tDrawShadowBlock(float rectangle_size, int x, int y, int color_type)
{
    tDrawFieldBlockRotated(rectangle_size, x, y, color_type, true, true, 0, (Vector2){0, 0});
}

void tDrawShapeRotated(const Shape* shape, float rectangle_size, float rotation, int x, int y)
{
    Vector2 origin;
    for (int yi = 0; yi < SHAPE_SIZE; yi++)
    {
        for (int xi = 0; xi < SHAPE_SIZE; xi++)
        {
            float origin_x_coeff = - xi + SHAPE_SIZE / 2;
            float origin_y_coeff = - yi + SHAPE_SIZE / 2;
            origin.x = origin_x_coeff * rectangle_size;
            origin.y = origin_y_coeff * rectangle_size;
            int xc = xi * rectangle_size + x + origin.x;
            int yc = yi * rectangle_size + y + origin.y;
            int shape_offset = yi * SHAPE_SIZE + xi;
            if (shape->hitboxes[shape->rotate_state][shape_offset] == '0') continue;
            tDrawFieldBlockRotated(rectangle_size, xc, yc, shape->type + 1, false, false, rotation, origin);
        }
    }
}

void tDrawField(const _Field *field, int begin_x, int rectangle_size)
{
    for (int yi = 0; yi < FIELD_HEIGHT; yi++)
    {
        for (int xi = 0; xi < FIELD_WIDTH; xi++)
        {
            int color_type = tGetFieldXY(field, xi, yi);
            int x = begin_x + xi * rectangle_size;
            int y = (yi + FIELD_OUTSIDE_HEIGHT) * rectangle_size;
            tDrawFieldBlock(rectangle_size, x, y, color_type);
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
            if (!tGetShapeHitbox(shape, xi, yi)) continue;
            tDrawShapeBlock(rectangle_size, x, y, shape->type + 1);
            int y_shadow = (yi + shape->y_shadow + FIELD_OUTSIDE_HEIGHT) * rectangle_size;
            tDrawShadowBlock(rectangle_size, x, y_shadow, shape->type + 1);
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

void tDrawStatistics(const Record* current_record, int begin_x)
{
    Rectangle bounds;
    bounds.x = begin_x - 320;
    if (bounds.x < 20) bounds.x = 20;
    bounds.y = GetRenderHeight() / 2;
    bounds.width = begin_x - 20 - bounds.x;
    bounds.height = GetRenderHeight() / 2 - 30;

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

void tDrawNextShapes(const Bag* bag, int begin_x)
{
    Rectangle bounds;
    bounds.x = GetRenderWidth() / 2 + (GetRenderWidth() / 2 - begin_x) + 30;
    bounds.y = 50;
    bounds.width = 200;
    bounds.height = GetRenderHeight() - 60;

    DrawText("Next:", bounds.x, 10, 30, GRAY);
    DrawText("Next:", bounds.x, 10, 30, RAYWHITE);

    int rectangle_size = bounds.width / SHAPE_SIZE;
    int bag_lookup_size = MIN(bounds.height / (rectangle_size * SHAPE_SIZE), BAG_SIZE);
    int* bag_info = (int*)malloc(sizeof(int) * bag_lookup_size);
    tPeekBag(bag, bag_info, bag_lookup_size);
    for (int i = 0; i < bag_lookup_size; i++)
    {
        Shape shape = Shapes[bag_info[i]];
        shape.rotate_state = 0;
        tDrawShapeRotated(&shape, rectangle_size, 0, bounds.x, rectangle_size * 4 * i + bounds.y);
    }
}

void tDrawHoldShape(Shape* shape, int begin_x, int rectangle_size)
{
    if (shape == nullptr) return;
    int x = begin_x - 6 * rectangle_size - 50;
    int y = 50;
    DrawText("Hold:", x, 10, 30, GRAY);
    DrawText("Hold:", x, 10, 30, RAYWHITE);
    tDrawShapeRotated(shape, rectangle_size * 2, 0.0f, x, y);
}