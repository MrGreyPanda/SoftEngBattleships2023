#include "board.h"

#include "gtest/gtest.h"

TEST(BoardTest, CreateBoard) {
    Board board;
    EXPECT_EQ(10, board.get_grid_size());
    EXPECT_EQ(5, board.get_num_ships());
    EXPECT_EQ(0, board.get_grid_value(0, 0));
    EXPECT_EQ(0, board.get_grid_value(9, 9));
    EXPECT_FALSE(board.get_is_shot(0, 0));
    EXPECT_FALSE(board.get_is_shot(6,5));
}


TEST(OwnBoardTest, CreateOwnBoard) {
    OwnBoard own_board;
    EXPECT_EQ(10, own_board.get_grid_size());
    EXPECT_EQ(5, own_board.get_num_ships());
    EXPECT_EQ(0, own_board.get_grid_value(0, 0));
    EXPECT_EQ(0, own_board.get_grid_value(9, 9));
    EXPECT_FALSE(own_board.get_is_shot(0, 0));
    EXPECT_FALSE(own_board.get_is_shot(4, 5));
}

TEST(OwnBoardTest, PlaceShip){
    OwnBoard own_board;
    Ship carrier(Carrier);
    EXPECT_TRUE(own_board.place_ship(0, 0, carrier));
    EXPECT_EQ(5, own_board.get_grid_value(0, 0));
    EXPECT_EQ(5, own_board.get_grid_value(0, 1));
    EXPECT_EQ(5, own_board.get_grid_value(0, 2));
    EXPECT_EQ(5, own_board.get_grid_value(0, 3));
    EXPECT_EQ(5, own_board.get_grid_value(0, 4));
    EXPECT_TRUE(carrier.get_is_placed());
    EXPECT_FALSE(carrier.get_is_horizontal());
    Ship battleship(Battleship);
    Ship cruiser(Cruiser);
    Ship submarine(Submarine);
    Ship destroyer(Destroyer);
    EXPECT_FALSE(own_board.place_ship(0, 0, battleship));
    EXPECT_FALSE(own_board.place_ship(0, 1, cruiser));
    EXPECT_FALSE(own_board.place_ship(0, 2, submarine));
    EXPECT_FALSE(own_board.place_ship(0, 3, destroyer));

    EXPECT_TRUE(own_board.place_ship(2, 2, submarine));
    EXPECT_EQ(2, own_board.get_grid_value(2, 2));
    EXPECT_EQ(0, own_board.get_grid_value(3, 2));
    EXPECT_EQ(2, own_board.get_grid_value(2, 3));
}

TEST(OwnBoardTest, RotateShip){
    OwnBoard own_board;
    Ship ship(Carrier);
    EXPECT_TRUE(own_board.place_ship(0, 0, ship));
    EXPECT_EQ(5, own_board.get_grid_value(0, 0));
    EXPECT_EQ(5, own_board.get_grid_value(0, 1));
    EXPECT_EQ(5, own_board.get_grid_value(0, 4));
    EXPECT_FALSE(ship.get_is_horizontal());
    EXPECT_TRUE(own_board.rotate_ship(ship));
    EXPECT_EQ(5, own_board.get_grid_value(0, 0));
    EXPECT_EQ(0, own_board.get_grid_value(0, 1));
    EXPECT_EQ(0, own_board.get_grid_value(0, 3));
    EXPECT_EQ(5, own_board.get_grid_value(3, 0));
    EXPECT_EQ(5, own_board.get_grid_value(4, 0));
    Ship sub(Submarine);
    EXPECT_TRUE(own_board.rotate_ship(sub));
    EXPECT_TRUE(own_board.place_ship(2, 2, sub));
    EXPECT_EQ(Submarine, own_board.get_grid_value(2, 2));
    EXPECT_EQ(Submarine, own_board.get_grid_value(3, 2));
    EXPECT_EQ(Submarine, own_board.get_grid_value(4, 2));
    EXPECT_TRUE(own_board.rotate_ship(sub));
    EXPECT_EQ(0, own_board.get_grid_value(3, 2));
    EXPECT_EQ(2, own_board.get_grid_value(2, 3));
}

TEST(EnemyBoardTest, CreateEnemyBoard){
    EnemyBoard enemy_board;
    EXPECT_EQ(10, enemy_board.get_grid_size());
    EXPECT_EQ(5, enemy_board.get_num_ships());
    EXPECT_EQ(0, enemy_board.get_grid_value(0, 0));
    EXPECT_EQ(0, enemy_board.get_grid_value(9, 9));
    EXPECT_FALSE(enemy_board.get_is_shot(0, 0));
    EXPECT_FALSE(enemy_board.get_is_shot(4, 5));
}
