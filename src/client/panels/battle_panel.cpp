#include "battle_panel.h"

GameState* BattlePanel::game_state_ = nullptr;

void BattlePanel::init()
{
    SDLGui::SDLGuiContext* battle_panel_context = 
        new SDLGui::SDLGuiContext("battlePanelContext");



    SDLGui::SDLGuiEnvironment::pushContext(battle_panel_context);
}

void BattlePanel::render()
{
    SDLGui::begin("battlePanelContext");



    SDLGui::end();
}