#include "game_instance_manager.h"
#include "player_manager.h"

#include "gtest/gtest.h"

// TEST(GameInstanceManagerTest, TryAddPlayer) {
//     PlayerManager *player_manager = new PlayerManager();
//     Player* player1 = new Player("Johan");
//     player_manager->add_or_get_player(player1->get_id(), player1);
//     GameInstanceManager *game_manager = new GameInstanceManager();
//     GameInstance *game = game_manager->create_new_game_();
//     EXPECT_TRUE(game_manager->try_add_player(player1, game));
//     Player* player2 = new Player("Lukas");
//     player_manager->add_or_get_player(player2->get_id(), player2);
//     game_manager->try_add_player(player2, game);
//     Player* player3 = new Player("Simon");
//     player_manager->add_or_get_player(player3->get_id(), player3);
//     EXPECT_FALSE(game_manager->try_add_player(player3, game));
//     delete game_manager;
//     delete player_manager;
// }

// TEST(GameInstanceManagerTest, AddPlayerToAnyGame) {

// }

// TEST(GameInstanceManagerTest, TryRemovePlayer) {

// }

// TEST(GameInstanceManagerTest, FindGameByPlayerId) {

// }

// TEST(GameInstanceManagerTest, FindJoinableGameInstance) {

// }