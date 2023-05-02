#include "player.h"

#include "gtest/gtest.h"

TEST(PlayerTest, CreatePlayer) {
    Player player("player1");
    EXPECT_EQ(10, player.get_own_board().get_size());
    EXPECT_EQ(10, player.get_enemy_board().get_size());
    EXPECT_EQ(false, player.get_is_ready());
    EXPECT_EQ(false, player.get_is_prepared());
}

TEST(PlayerTest, SetterAndGetterFunctionsPlayer){
    Player player("player1");
    EXPECT_EQ("player1", player.get_id());
    player.set_id("player2");
    EXPECT_EQ("player2", player.get_id());
    EXPECT_FALSE(player.get_is_ready());
    player.set_ready();
    EXPECT_TRUE(player.get_is_ready());
    EXPECT_FALSE(player.get_is_prepared());
    player.unset_ready();
    EXPECT_FALSE(player.get_is_ready());
    player.set_prepared();
    EXPECT_TRUE(player.get_is_prepared());
    player.unset_prepared();
    EXPECT_FALSE(player.get_is_prepared());
}