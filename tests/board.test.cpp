#include "board.h"
#include "helper_functions.h"

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
    EXPECT_TRUE(own_board.place_ship(0, 0, true, Carrier));
    Ship* carrier = own_board.get_ship_by_name(Carrier);
    EXPECT_EQ(5, own_board.get_grid_value(0, 0));
    EXPECT_EQ(5, own_board.get_grid_value(1, 0));
    EXPECT_EQ(5, own_board.get_grid_value(2, 0));
    EXPECT_EQ(5, own_board.get_grid_value(3, 0));
    EXPECT_EQ(5, own_board.get_grid_value(4, 0));
    EXPECT_TRUE(carrier->get_is_placed());
    EXPECT_TRUE(carrier->get_is_horizontal());
    EXPECT_FALSE(own_board.place_ship(0, 0, false, Battleship));
    EXPECT_FALSE(own_board.place_ship(1, 0, false, Cruiser));
    EXPECT_FALSE(own_board.place_ship(2, 0, false, Submarine));
    EXPECT_FALSE(own_board.place_ship(3, 0, false, Destroyer));

    EXPECT_TRUE(own_board.place_ship(2, 2, true, Submarine));
    EXPECT_EQ(2, own_board.get_grid_value(2, 2));
    EXPECT_EQ(0, own_board.get_grid_value(2, 3));
    EXPECT_EQ(2, own_board.get_grid_value(3, 2));
}

TEST(OwnBoardTest, ValidConfiguration){
    OwnBoard own_board;
    EXPECT_TRUE(own_board.place_ship(0, 0, true, Carrier));
    EXPECT_TRUE(own_board.place_ship(0, 1, true, Battleship));
    EXPECT_TRUE(own_board.place_ship(0, 2, true, Cruiser));
    EXPECT_TRUE(own_board.place_ship(0, 3, true, Submarine));
    EXPECT_TRUE(own_board.place_ship(0, 4, true, Destroyer));
    EXPECT_TRUE(own_board.is_valid_configuration());
}

TEST(OwnBoardTest, UltimateConfiguration){
    OwnBoard own_board;
    EXPECT_TRUE(own_board.place_ship(6, 7, true, Destroyer));
    EXPECT_TRUE(own_board.place_ship(2, 7, true, Submarine));
    EXPECT_TRUE(own_board.place_ship(4, 5, true, Cruiser));
    EXPECT_TRUE(own_board.place_ship(7, 2, false, Battleship));
    EXPECT_TRUE(own_board.place_ship(3, 6, true, Carrier));
    EXPECT_TRUE(own_board.is_valid_configuration());
    EXPECT_TRUE(own_board.is_ultimate_configuration());
}

TEST(OwnBoard, UltimateConfigurationWithHelper){
    OwnBoard own_board;
    std::array<ShipData, 5> ship_data = HelperFunctions::get_funny_ship_configuration();
    for (auto ship : ship_data){
        EXPECT_TRUE(own_board.place_ship(ship.x, ship.y, ship.is_horizontal, ship.name));
    }
    EXPECT_TRUE(own_board.is_valid_configuration());
    EXPECT_TRUE(own_board.is_ultimate_configuration());
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
