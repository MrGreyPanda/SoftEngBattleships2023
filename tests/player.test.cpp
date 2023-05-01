#include "game_state/include/player.h"

#include "gtest/gtest.h"

TEST(PlayerTest, CreatePlayer) {
    Player player;
    EXCEPT_EQ(10, player.own_board.size);
    EXCEPT_EQ(10, player.enemy_board.size);
    EXCEPT_EQ(5, player.own_board.ships.size());
    EXCEPT_EQ(5, player.enemy_board.ships.size());
    EXCEPT_EQ(false, player.is_ready);
    EXCEPT_EQ(false, player.is_prepared);
}

TEST(PlayerTest, CreatePlayerWithSize) {
    Player player(5);
    EXCEPT_EQ(5, player.own_board.size);
    EXCEPT_EQ(5, player.enemy_board.size);
    EXCEPT_EQ(5, player.own_board.ships.size());
    EXCEPT_EQ(5, player.enemy_board.ships.size());
    EXCEPT_EQ(false, player.is_ready);
    EXCEPT_EQ(false, player.is_prepared);
}

TEST(PlayerTest, CreatePlayerWithSizeAndShips) {
    Player player(5, 3);
    EXCEPT_EQ(5, player.own_board.size);
    EXCEPT_EQ(5, player.enemy_board.size);
    EXCEPT_EQ(3, player.own_board.ships.size());
    EXCEPT_EQ(3, player.enemy_board.ships.size());
    EXCEPT_EQ(false, player.is_ready);
    EXCEPT_EQ(false, player.is_prepared);
}