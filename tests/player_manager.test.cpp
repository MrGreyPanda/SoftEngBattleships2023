#include "player_manager.h"

#include "gtest/gtest.h"
#include "player.h"

TEST(PlayerManagerTest, TryGetPlayer) {
    PlayerManager *manager = new PlayerManager();
    std::string player_id  = "Johan";
    Player *player_ptr     = nullptr;
    EXPECT_FALSE(manager->try_get_player(player_id, player_ptr));
    manager->add_or_get_player(player_id, player_ptr);
    EXPECT_TRUE(manager->try_get_player(player_id, player_ptr));
    delete manager;
}

TEST(PlayerManagerTest, TryAddPlayer) {
    PlayerManager *manager = new PlayerManager();
    std::string player_id  = "Johan";
    Player *player_ptr     = nullptr;
    EXPECT_FALSE(manager->add_or_get_player(player_id, player_ptr));
    EXPECT_TRUE(manager->add_or_get_player(player_id, player_ptr));
    delete manager;
}

TEST(PlayerManagerTest, TryRemovePlayer) {
    PlayerManager *manager = new PlayerManager();
    std::string player_id  = "Johan";
    Player *player_ptr     = nullptr;
    manager->add_or_get_player(player_id, player_ptr);
    EXPECT_TRUE(manager->remove_player(player_id, player_ptr));
    EXPECT_FALSE(manager->remove_player(player_id, player_ptr));
    delete manager;
}
