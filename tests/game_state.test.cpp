#include "game_state.h"
#include "player_manager.h"

#include "gtest/gtest.h"

TEST(GameTest, CreateGameState) {
    PlayerManager* player_manager = new PlayerManager();
    Player *player1_ptr = player_manager->add_or_get_player("Johan");
    Player *player2_ptr = player_manager->add_or_get_player("Simon");
    std::vector<Player*> player_ptrs = {player1_ptr, player1_ptr};
    GameState game("1234", player_ptrs);
    EXPECT_EQ("1234", game.get_id());
    EXPECT_EQ(0, game.get_phase());
    EXPECT_EQ(5, game.get_ships().size());
    EXPECT_EQ(0, game.get_turn_player_index());
    EXPECT_EQ(2, game.get_players().size());
    delete player_manager;
    player_manager = nullptr;
}