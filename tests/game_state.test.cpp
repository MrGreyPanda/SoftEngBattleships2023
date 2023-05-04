#include "game_state.h"

#include "gtest/gtest.h"

TEST(GameTest, CreateGameState) {
    std::vector<std::string> player_ids = {"player1", "player2"};
    GameState game("1234", player_ids);
    EXPECT_EQ("1234", game.get_id());
    EXPECT_EQ(0, game.get_phase());
    EXPECT_EQ(5, game.get_ships().size());
    EXPECT_EQ(0, game.get_turn_player_index());
    EXPECT_EQ(2, game.get_players().size());
}