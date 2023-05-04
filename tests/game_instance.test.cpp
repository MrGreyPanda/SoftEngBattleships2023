#include "game_instance.h"

#include "gtest/gtest.h"
#include "player_manager.h"

TEST(GameInstanceTest, TryAddPlayer) {
    GameInstance *game = new GameInstance();
    PlayerManager *player_manager = new PlayerManager();
    Player *player1 = player_manager->add_or_get_player("Johan");
    EXPECT_TRUE(game->try_add_player(player1));
    Player *player2 = player_manager->add_or_get_player("Lukas");
    Player *player3 = player_manager->add_or_get_player("Simon");
    game->try_add_player(player1);
    game->try_add_player(player2);
    EXPECT_FALSE(game->try_add_player(player3));
    delete game;
    delete player_manager;
}

TEST(GameInstanceTest, HasPlayer) {
    GameInstance *game = new GameInstance();
    PlayerManager *player_manager = new PlayerManager();
    EXPECT_FALSE(game->has_player("Johan"));
    Player *player1 = player_manager->add_or_get_player("Johan");
    game->try_add_player(player1);
    EXPECT_TRUE(game->has_player("Johan"));
    delete game;
    delete player_manager;
}

TEST(GameInstanceTest, TryRemovePlayer) {
    GameInstance *game = new GameInstance();
    PlayerManager *player_manager = new PlayerManager();
    Player *player1 = player_manager->add_or_get_player("Johan");
    game->try_add_player(player1);
    EXPECT_TRUE(game->try_remove_player(player1));
    EXPECT_FALSE(game->try_remove_player(player1));
    delete game;
    delete player_manager;
}