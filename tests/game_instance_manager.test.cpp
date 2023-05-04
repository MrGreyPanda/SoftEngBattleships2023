#include "game_instance_manager.h"
#include "player_manager.h"

#include "gtest/gtest.h"

TEST(GameInstanceManagerTest, TryAddPlayer) {
    PlayerManager *player_manager = new PlayerManager();
    Player* player1 = player_manager->add_or_get_player("Johan");
    GameInstanceManager *game_manager = new GameInstanceManager();
    GameInstance *game = game_manager->create_new_game_();
    EXPECT_TRUE(game_manager->try_add_player(player1, game));
    Player* player2 = player_manager->add_or_get_player("Lukas");
    game_manager->try_add_player(player2, game);
    Player* player3 = player_manager->add_or_get_player("Simon");
    EXPECT_FALSE(game_manager->try_add_player(player3, game));
    // delete game_manager;
    delete player_manager;
}

// TEST(GameInstanceManagerTest, AddPlayerToAnyGame) {

// }

// TEST(GameInstanceManagerTest, TryRemovePlayer) {

// }

// TEST(GameInstanceManagerTest, FindGameByPlayerId) {

// }

// TEST(GameInstanceManagerTest, FindJoinableGameInstance) {

// }