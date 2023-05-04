#include "player_manager.h"

#include "gtest/gtest.h"
#include "player.h"

TEST(PlayerManagerTest, TryGetPlayer) {
    PlayerManager *manager = new PlayerManager();
    Player *player1 = new Player("Johan");
    // std::string player_id  = "Johan";
    // Player *player_ptr     = nullptr;
    EXPECT_FALSE(manager->try_get_player(player1->get_id(), player1));
    manager->add_or_get_player(player1->get_id(), player1);
    EXPECT_TRUE(manager->try_get_player(player1->get_id(), player1));
    delete manager;
    delete player1;
}

TEST(PlayerManagerTest, TryAddPlayer) {
    PlayerManager *manager = new PlayerManager();
    Player *player1 = new Player("Johan");
    // std::string player_id  = "Johan";
    // Player *player_ptr     = nullptr;
    EXPECT_FALSE(manager->add_or_get_player(player1->get_id(), player1));
    EXPECT_TRUE(manager->add_or_get_player(player1->get_id(), player1));
    delete manager;
    delete player1;
}

TEST(PlayerManagerTest, TryRemovePlayer) {
    PlayerManager *manager = new PlayerManager();
    // std::string player_id  = "Johan";
    // Player *player_ptr     = nullptr;
    Player* player_ptr = new Player("Johan");
    manager->add_or_get_player(player_ptr->get_id(), player_ptr);
    EXPECT_TRUE(manager->remove_player(player_ptr->get_id(), player_ptr));
    EXPECT_FALSE(manager->remove_player(player_ptr->get_id(), player_ptr));
    delete manager;
    delete player_ptr;
}
