#include "gameover.h"
#include "render.h"

Shared tGameOver(Shared shared)
{
    const int item_count = 9;
    UIItem items[item_count];
    UIItem *level_value, *lines_cleared_value, *score_value, *time_value, *group, *game_over, *group2, *button, *sec;
    tBindUIItems(items, item_count, &level_value, &lines_cleared_value, &score_value, &time_value, &group, &game_over, &button, &group2, &sec);

    bool is_40_lines_passed = shared.is_40_lines && shared.current_record->lines_cleared >= 40;
    tMakeText(game_over, is_40_lines_passed ? "40 LINES!" : "GAME OVER", group, AnchorTop);
    game_over->font_size = 100;
    game_over->padding = 20;
    game_over->color_text = is_40_lines_passed ? DARKGREEN : RED;

    if (shared.is_40_lines)
    {
        tMakeDoubleBox(level_value, "Figures/sec: ", nullptr, AnchorPassive, shared.current_record->shapes_placed / shared.current_record->time, 0, __FLT_MAX__);
    }
    else
    {
        tMakeIntBox(level_value, "Level: ", nullptr, AnchorPassive, shared.current_record->level, 0, __INT_MAX__);
    }
    level_value->data_textbox->color_input_background = (Color){0, 0, 0, 0};
    level_value->data_textbox->allow_edit = false;
    level_value->data_textbox->label_item->position_anchor = AnchorLeft;
    level_value->stretch_x = false;

    if (shared.is_40_lines)
    {
        tMakeDoubleBox(lines_cleared_value, "Lines/sec: ", level_value, AnchorBottom, shared.current_record->lines_cleared / shared.current_record->time, 0, __FLT_MAX__);
    }
    else
    {
        tMakeIntBox(lines_cleared_value, "Lines: ", level_value, AnchorBottom, shared.current_record->lines_cleared, 0, __INT_MAX__);
    }
    lines_cleared_value->data_textbox->color_input_background = (Color){0, 0, 0, 0};
    lines_cleared_value->data_textbox->allow_edit = false;
    lines_cleared_value->data_textbox->label_item->position_anchor = AnchorLeft;
    lines_cleared_value->stretch_x = false;

    tMakeIntBox(score_value, "Score: ", lines_cleared_value, AnchorBottom, shared.current_record->score, 0, __INT_MAX__);
    score_value->data_textbox->color_input_background = (Color){0, 0, 0, 0};
    score_value->data_textbox->allow_edit = false;
    score_value->data_textbox->label_item->position_anchor = AnchorLeft;
    score_value->stretch_x = false;

    tMakeDoubleBox(time_value, "Time: ", score_value, AnchorBottom, shared.current_record->time, 0, __DBL_MAX__);
    time_value->data_textbox->color_input_background = (Color){0, 0, 0, 0};
    time_value->data_textbox->allow_edit = false;
    time_value->data_textbox->label_item->position_anchor = AnchorLeft;
    time_value->stretch_x = false;
    tMakeText(sec, "s.", time_value, AnchorRight);
    sec->secondary_anchor = AnchorCenter;

    tMakeGroup(group, "Group", nullptr, 8, level_value, level_value->data_textbox->label_item,
                                           lines_cleared_value, lines_cleared_value->data_textbox->label_item,
                                           score_value, score_value->data_textbox->label_item,
                                           time_value, time_value->data_textbox->label_item);
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