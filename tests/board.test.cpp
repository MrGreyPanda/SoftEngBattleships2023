#include "board.h"

#include "gtest/gtest.h"

TEST(BoardTest, CreateBoard) {
    Board board;
    EXPECT_EQ(10, board.get_grid_size());
    EXPECT_EQ(5, board.get_num_active_ships());
    EXPECT_EQ(0, board.get_grid_value(std::make_pair(0, 0)));
    EXPECT_EQ(0, board.get_grid_value(std::make_pair(9, 9)));
    EXPECT_FALSE(board.get_is_shot(std::make_pair(0, 0)));
    EXPECT_FALSE(board.get_is_shot(std::make_pair(4, 5)));
}

// TEST(BoardTest, CreateBoardWithSize) {
//     Board board(5);
//     EXPECT_EQ(5, board.get_grid_size());
//     EXPECT_EQ(5, board.get_num_active_ships());
//     EXPECT_EQ(0, board.get_grid_value(std::make_pair(0, 0)));
//     EXPECT_EQ(0, board.get_grid_value(std::make_pair(4, 4)));
//     EXPECT_FALSE(board.get_is_shot(std::make_pair(0, 0)));
//     EXPECT_FALSE(board.get_is_shot(std::make_pair(4, 4)));
// }

TEST(OwnBoardTest, CreateOwnBoard) {
    OwnBoard own_board;
    EXPECT_EQ(10, own_board.get_grid_size());
    EXPECT_EQ(5, own_board.get_num_active_ships());
    EXPECT_EQ(0, own_board.get_grid_value(std::make_pair(0, 0)));
    EXPECT_EQ(0, own_board.get_grid_value(std::make_pair(9, 9)));
    EXPECT_FALSE(own_board.get_is_shot(std::make_pair(0, 0)));
    EXPECT_FALSE(own_board.get_is_shot(std::make_pair(4, 5)));
}

// TEST(OwnBoardTest, CreateOwnBoardWithSize) {
//     OwnBoard own_board(5);
//     EXPECT_EQ(5, own_board.get_grid_size());
//     EXPECT_EQ(5, own_board.get_num_active_ships());
//     EXPECT_EQ(0, own_board.get_grid_value(std::make_pair(0, 0)));
//     EXPECT_EQ(0, own_board.get_grid_value(std::make_pair(4, 4)));
//     EXPECT_FALSE(own_board.get_is_shot(std::make_pair(0, 0)));
//     EXPECT_FALSE(own_board.get_is_shot(std::make_pair(4, 4)));
// }

TEST(OwnBoardTest, PlaceShip){
    OwnBoard own_board;
    std::vector<std::pair<unsigned short, unsigned short>> coords;
    coords.push_back(std::make_pair(0, 0));
    coords.push_back(std::make_pair(0, 1));
    coords.push_back(std::make_pair(0, 2));
    coords.push_back(std::make_pair(0, 3));
    coords.push_back(std::make_pair(0, 4));
    EXPECT_TRUE(own_board.place_ship(coords, Carrier));
    EXPECT_EQ(5, own_board.get_grid_value(std::make_pair(0, 0)));
    EXPECT_EQ(5, own_board.get_grid_value(std::make_pair(0, 1)));
    EXPECT_EQ(5, own_board.get_grid_value(std::make_pair(0, 2)));
    EXPECT_EQ(5, own_board.get_grid_value(std::make_pair(0, 3)));
    EXPECT_EQ(5, own_board.get_grid_value(std::make_pair(0, 4)));
    // EXPECT_FALSE(own_board.place_ship(coords, Carrier));
    EXPECT_FALSE(own_board.place_ship(coords, Battleship));
    EXPECT_FALSE(own_board.place_ship(coords, Cruiser));
    EXPECT_FALSE(own_board.place_ship(coords, Submarine));
    EXPECT_FALSE(own_board.place_ship(coords, Destroyer));
    coords.clear();
    coords.push_back(std::make_pair(2, 2));
    coords.push_back(std::make_pair(3, 2));
    coords.push_back(std::make_pair(4, 2));
    EXPECT_TRUE(own_board.place_ship(coords, Submarine));
    EXPECT_EQ(2, own_board.get_grid_value(std::make_pair(2, 2)));
    EXPECT_EQ(2, own_board.get_grid_value(std::make_pair(3, 2)));
}

TEST(OwnBoardTest, RotateShip){
    OwnBoard own_board;
    std::vector<std::pair<unsigned short, unsigned short>> coords;
    coords.push_back(std::make_pair(0, 0));
    coords.push_back(std::make_pair(0, 1));
    coords.push_back(std::make_pair(0, 2));
    coords.push_back(std::make_pair(0, 3));
    coords.push_back(std::make_pair(0, 4));
    ShipCategory ship = Carrier;
    EXPECT_TRUE(own_board.place_ship(coords, ship));
    EXPECT_EQ(5, own_board.get_grid_value(std::make_pair(0, 0)));
    EXPECT_EQ(5, own_board.get_grid_value(std::make_pair(0, 1)));


    EXPECT_EQ(5, own_board.get_grid_value(std::make_pair(0, 4)));
    EXPECT_TRUE(own_board.rotate_ship(coords, ship));
    EXPECT_TRUE(own_board.place_ship(coords, ship));
    EXPECT_EQ(1, coords[1].first);
    EXPECT_EQ(5, own_board.get_grid_value(std::make_pair(0, 0)));
    EXPECT_EQ(0, own_board.get_grid_value(std::make_pair(0, 1)));
    EXPECT_EQ(0, own_board.get_grid_value(std::make_pair(0, 3)));
    EXPECT_EQ(5, own_board.get_grid_value(std::make_pair(3, 0)));
    EXPECT_EQ(5, own_board.get_grid_value(std::make_pair(4, 0)));
    coords.clear();
    coords.push_back(std::make_pair(2, 2));
    coords.push_back(std::make_pair(3, 2));
    coords.push_back(std::make_pair(4, 2));
    EXPECT_TRUE(own_board.place_ship(coords, Submarine));
    EXPECT_EQ(2, own_board.get_grid_value(std::make_pair(2, 2)));
    EXPECT_EQ(2, own_board.get_grid_value(std::make_pair(3, 2)));
    EXPECT_EQ(2, own_board.get_grid_value(std::make_pair(4, 2)));
    EXPECT_EQ(3, coords.size());
    EXPECT_EQ(2, coords[0].first);
    EXPECT_TRUE(own_board.rotate_ship(coords, Submarine));
    EXPECT_TRUE(own_board.place_ship(coords, Submarine));
    EXPECT_EQ(0, own_board.get_grid_value(std::make_pair(3, 2)));
    EXPECT_EQ(2, own_board.get_grid_value(std::make_pair(2, 3)));

    coords.clear();
    coords.push_back(std::make_pair(0,0));
    coords.push_back(std::make_pair(1,0));
    EXPECT_FALSE(own_board.place_ship(coords, Destroyer));
}

TEST(EnemyBoardTest, CreateEnemyBoard){
    EnemyBoard enemy_board;
    std::cout << "enemy_board created" << std::endl;
    EXPECT_EQ(10, enemy_board.get_grid_size());
    EXPECT_EQ(5, enemy_board.get_num_active_ships());
    EXPECT_EQ(0, enemy_board.get_grid_value(std::make_pair(0, 0)));
    EXPECT_EQ(0, enemy_board.get_grid_value(std::make_pair(9, 9)));
    EXPECT_FALSE(enemy_board.get_is_shot(std::make_pair(0, 0)));
    EXPECT_FALSE(enemy_board.get_is_shot(std::make_pair(4, 5)));
}

// TEST(EnemyBoardTest, CreateEnemyBoardWithSize){
//     EnemyBoard board(5);
//     EXPECT_EQ(5, board.get_grid_size());
//     EXPECT_EQ(5, board.get_num_active_ships());
//     EXPECT_EQ(0, board.get_grid_value(std::make_pair(0, 0)));
//     EXPECT_EQ(0, board.get_grid_value(std::make_pair(4, 4)));
//     EXPECT_FALSE(board.get_is_shot(std::make_pair(0, 0)));
//     EXPECT_FALSE(board.get_is_shot(std::make_pair(4, 4)));
// }