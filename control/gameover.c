#include "gameover.h"
#include "render.h"

Shared tGameOver(Shared shared)
{
    const int item_count = 12;
    UIItem items[item_count];
    UIItem* level, *level_value, *lines_cleared, *lines_cleared_value, *score, *score_value, *time, *time_value, *group, *game_over, *group2, *button;
    tBindUIItems(items, item_count, &level, &level_value, &lines_cleared, &lines_cleared_value, &score, &score_value, &time, &time_value, &group, &game_over, &button, &group2);

    bool is_40_lines_passed = shared.is_40_lines && shared.current_record->lines_cleared == 40;
    tMakeText(game_over, is_40_lines_passed ? "40 LINES!" : "GAME OVER", group, AnchorTop);
    game_over->font_size = 100;
    game_over->padding = 20;
    game_over->color_text = is_40_lines_passed ? DARKGREEN : RED;

    if (shared.is_40_lines)
    {
        tMakeText(level, "Figures/sec: ", nullptr, AnchorPassive);
        tMakeDoubleBox(level_value, "", level, AnchorRight, shared.current_record->shapes_placed / shared.current_record->time, 0, __FLT_MAX__);
    }
    else
    {
        tMakeText(level, "Level: ", nullptr, AnchorPassive);
        tMakeIntBox(level_value, "", level, AnchorRight, shared.current_record->level, 0, __INT_MAX__);
    }
    level_value->data_textbox->color_input_background = (Color){0, 0, 0, 0};
    level_value->data_textbox->allow_edit = false;
    level_value->stretch_x = false;

    if (shared.is_40_lines)
    {
        tMakeText(lines_cleared, "Lines/sec: ", level, AnchorBottom);
        tMakeDoubleBox(lines_cleared_value, "", lines_cleared, AnchorRight, shared.current_record->lines_cleared / shared.current_record->time, 0, __FLT_MAX__);
    }
    else
    {
        tMakeText(lines_cleared, "Lines: ", level, AnchorBottom);
        tMakeIntBox(lines_cleared_value, "", lines_cleared, AnchorRight, shared.current_record->lines_cleared, 0, __INT_MAX__);
    }
    lines_cleared_value->data_textbox->color_input_background = (Color){0, 0, 0, 0};
    lines_cleared_value->data_textbox->allow_edit = false;
    lines_cleared_value->stretch_x = false;

    tMakeText(score, "Score: ", lines_cleared, AnchorBottom);
    tMakeIntBox(score_value, "", score, AnchorRight, shared.current_record->score, 0, __INT_MAX__);
    score_value->data_textbox->color_input_background = (Color){0, 0, 0, 0};
    score_value->data_textbox->allow_edit = false;
    score_value->stretch_x = false;

    tMakeText(time, "Time: ", score, AnchorBottom);
    tMakeDoubleBox(time_value, "s.", time, AnchorRight, shared.current_record->time, 0, __DBL_MAX__);
    time_value->data_textbox->color_input_background = (Color){0, 0, 0, 0};
    time_value->data_textbox->allow_edit = false;
    time_value->stretch_x = false;

    tMakeGroup(group, "Group", nullptr, 8, level, level_value, lines_cleared, lines_cleared_value, score, score_value, time, time_value);
    group->position_anchor = AnchorPassive;
    tMakeGroup(group2, "Group2", nullptr, 3, group, game_over, button);
    tMakeButton(button, "To menu", group, AnchorBottom);
    button->data_button->resize_on_hover = false;

    while (shared.state == STATE_GAME_OVER)
    {
        tDrawGameOverFrame(items, item_count);
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE) || button->mouse_released) shared.state = STATE_IN_MENU;
        if (WindowShouldClose()) shared.state = STATE_EXITING;
    }

    for (int i = 0; i < item_count; i++)
    {
        items[i].Free(&(items[i]));
    }
    return shared;
}