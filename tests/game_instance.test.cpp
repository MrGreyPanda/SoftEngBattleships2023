#include "game_instance.h"

#include "gtest/gtest.h"
#include "player_manager.h"

TEST(GameInstanceTest, TryAddPlayer) {
    GameInstance *game = new GameInstance();
    PlayerManager *player_manager = new PlayerManager();
    Player *player1 = new Player("Johan");
    player_manager->add_or_get_player(player1->get_id(), player1);
    EXPECT_TRUE(game->try_add_player(player1));
    Player *player2 = new Player("Lukas");
    player_manager->add_or_get_player(player1->get_id(), player2);
    Player *player3 = new Player("Simon");
    player_manager->add_or_get_player(player1->get_id(), player3);
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
    Player *player1 = new Player("Johan");
    player_manager->add_or_get_player(player1->get_id(), player1);
    game->try_add_player(player1);
    EXPECT_TRUE(game->has_player("Johan"));
    delete game;
    delete player_manager;
}

TEST(GameInstanceTest, TryRemovePlayer) {
    GameInstance *game = new GameInstance();
    PlayerManager *player_manager = new PlayerManager();
    Player *player1 = new Player("Johan");
    player_manager->add_or_get_player(player1->get_id(), player1);
    game->try_add_player(player1);
    EXPECT_TRUE(game->try_remove_player(player1));
    EXPECT_FALSE(game->try_remove_player(player1));
    delete game;
    delete player_manager;
}