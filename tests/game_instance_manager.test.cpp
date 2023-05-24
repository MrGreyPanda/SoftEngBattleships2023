#include "game_instance_manager.h"

#include "gtest/gtest.h"
#include "player_manager.h"

TEST(GameInstanceManagerTest, TryAddPlayer) {
    PlayerManager *player_manager = new PlayerManager();
    Player *player1               = player_manager->add_or_get_player("Johan");
    GameInstanceManager *game_manager = new GameInstanceManager();
    GameInstance *game                = game_manager->create_new_game_();
    EXPECT_TRUE(game_manager->try_add_player(player1, game));
    Player *player2 = player_manager->add_or_get_player("Lukas");
    game_manager->try_add_player(player2, game);
    Player *player3 = player_manager->add_or_get_player("Simon");
    EXPECT_FALSE(game_manager->try_add_player(player3, game));
    delete game_manager;
    delete player_manager;
}

TEST(GameInstanceManagerTest, AddPlayerToAnyGame) {
    PlayerManager *player_manager = new PlayerManager();
    Player *player1               = player_manager->add_or_get_player("Johan");
    GameInstanceManager *game_manager = new GameInstanceManager();
    GameInstance *added_game = game_manager->add_player_to_any_game(player1);
    EXPECT_TRUE(added_game != nullptr);
    Player *player2 = player_manager->add_or_get_player("Lukas");
    added_game      = game_manager->add_player_to_any_game(player2);
    GameInstance* full_game = added_game;
    EXPECT_TRUE(added_game != nullptr);
    Player *player3 = player_manager->add_or_get_player("Simon");
    added_game      = game_manager->add_player_to_any_game(player3);
    EXPECT_TRUE(added_game != nullptr);
    EXPECT_NE(added_game, full_game);
    delete game_manager;
    delete player_manager;
}

TEST(GameInstanceManagerTest, TryRemovePlayer) {
    PlayerManager *player_manager = new PlayerManager();
    Player *player1               = player_manager->add_or_get_player("Johan");
    GameInstanceManager *game_manager = new GameInstanceManager();
    GameInstance *game                = game_manager->create_new_game_();
    game_manager->try_add_player(player1, game);
    Player *player2 = player_manager->add_or_get_player("Lukas");
    game_manager->try_add_player(player2, game);
    EXPECT_TRUE(game_manager->try_remove_player(player1, game));
    EXPECT_TRUE(game_manager->try_remove_player(player2, game));
    delete game_manager;
    delete player_manager;
}

TEST(GameInstanceManagerTest, FindGameByPlayerId) {
    PlayerManager *player_manager = new PlayerManager();
    Player *player1               = player_manager->add_or_get_player("Johan");
    GameInstanceManager *game_manager = new GameInstanceManager();
    GameInstance *game                = game_manager->create_new_game_();
    EXPECT_TRUE(game_manager->find_game_by_player_id("Johan") == nullptr);
    game_manager->try_add_player(player1, game);
    Player *player2 = player_manager->add_or_get_player("Lukas");
    game_manager->try_add_player(player2, game);
    GameInstance *found_game = game_manager->find_game_by_player_id("Johan");
    EXPECT_TRUE(found_game == game &&
                game_manager->find_game_by_player_id("Lukas") == game);
    delete game_manager;
    delete player_manager;
}

TEST(GameInstanceManagerTest, FindJoinableGameInstance) {
    GameInstanceManager *game_manager = new GameInstanceManager();
    EXPECT_TRUE(game_manager->find_joinable_game_instance_() == nullptr);
    GameInstance *game = game_manager->create_new_game_();
    EXPECT_TRUE(game_manager->find_joinable_game_instance_() != nullptr);
    delete game_manager;
}