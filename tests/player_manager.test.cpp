#include "player_manager.h"

#include "gtest/gtest.h"
#include "player.h"

TEST(PlayerManagerTest, TryGetPlayer) {
    PlayerManager *manager = new PlayerManager();
    std::string player_id  = "Johan";
    Player *player_ptr     = manager->try_get_player(player_id);
    EXPECT_TRUE(player_ptr == nullptr);
    player_ptr = manager->add_or_get_player(player_id);
    EXPECT_TRUE(player_ptr != nullptr);
    delete manager;
}

TEST(PlayerManagerTest, TryAddPlayer) {
    PlayerManager *manager = new PlayerManager();
    std::string player_id  = "Johan";
    Player *player_ptr     = manager->add_or_get_player(player_id);
    EXPECT_TRUE(player_ptr != nullptr);
    delete manager;
}

TEST(PlayerManagerTest, TryRemovePlayer) {
    PlayerManager *manager = new PlayerManager();
    std::string player_id  = "Johan";
    Player *player_ptr = manager->add_or_get_player(player_id);
    EXPECT_TRUE(manager->remove_player(player_id));
    EXPECT_FALSE(manager->remove_player(player_id));
    delete manager;
}
