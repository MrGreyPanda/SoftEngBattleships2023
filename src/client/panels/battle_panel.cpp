#include "battle_panel.h"

GameState* BattlePanel::game_state_ = nullptr;

void BattlePanel::init()
{
    SDLGui::SDLGuiContext* battle_panel_context = 
        new SDLGui::SDLGuiContext("battlePanelContext");

    SDLGui::GridWidget* own_board = 
        new SDLGui::GridWidget("own_board", .05f, .05f, .4f, .8f,
        0., 10, 10, SDLGui::GridFlagsExt_CenterVertical | SDLGui::GridFlagsExt_Square);
    battle_panel_context->addWidget(own_board);

    SDLGui::GridWidget* enemy_board = 
        new SDLGui::GridWidget("enemy_board", .55f, .05f, .4f, .8f,
        0., 10, 10, SDLGui::GridFlagsExt_CenterVertical | SDLGui::GridFlagsExt_Square);
    battle_panel_context->addWidget(enemy_board);

    SDLGui::TextWidget* battle_phase_title = 
        new SDLGui::TextWidget("battle_title", "Battle Phase",
        .0f, .05f, .6f, .1f, 0., SDLGui::TextFlagsExt_CenterText | 
        SDLGui::TextFlagsExt_CenterHorizontal);
        battle_panel_context->addWidget(battle_phase_title);

    SDLGui::SDLGuiEnvironment::pushContext(battle_panel_context);
}

void BattlePanel::render()
{
    SDLGui::begin("battlePanelContext");



    SDLGui::end();
}