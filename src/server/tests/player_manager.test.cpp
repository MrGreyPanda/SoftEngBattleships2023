#include "../player_manager.h"
#include "../../common/game_state/include/player.h"

#include "gtest/gtest.h"

TEST(PlayerManagerTest, TryGetPlayerFalse) {
    PlayerManager *manager = new PlayerManager();
    std::string player_id = "Johan";
    Player *player_ptr = nullptr;
    EXPECT_FALSE(manager->try_get_player(player_id, player_ptr));
    delete manager;
}

TEST(PlayerManagerTest, TryGetPlayerTrue) {
    PlayerManager *manager = new PlayerManager();
    std::string player_id = "Johan";
    Player *player_ptr = nullptr;
    manager->add_or_get_player(player_id, player_ptr);
    EXPECT_TRUE(manager->try_get_player(player_id, player_ptr));
    delete manager;
}

TEST(PlayerManagerTest, TryRemovePlayerTrue) {
    PlayerManager *manager = new PlayerManager();
    std::string player_id = "Johan";
    Player *player_ptr = nullptr;
    manager->add_or_get_player(player_id, player_ptr);
    EXPECT_TRUE(manager->remove_player(player_id, player_ptr));
    delete manager;
}
