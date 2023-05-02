#include "board.h"

#include "gtest/gtest.h"

TEST(BoardTest, CreateBoard) {
    Board board;
    EXPECT_EQ(10, board.get_size());
    EXPECT_EQ(5, board.get_num_active_ships());
    EXPECT_EQ(0, board.grid_[0][0]);
    EXPECT_EQ(0, board.grid_[9][9]);
    EXPECT_FALSE(board.is_shot_[0][0]);
    EXPECT_FALSE(board.is_shot_[4][5]);
}

TEST(BoardTest, CreateBoardWithSize) {
    Board board(5);
    EXPECT_EQ(5, board.get_size());
    EXPECT_EQ(5, board.get_num_active_ships());
    EXPECT_EQ(0, board.grid_[0][0]);
    EXPECT_EQ(0, board.grid_[4][4]);
    EXPECT_FALSE(board.is_shot_[0][0]);
    EXPECT_FALSE(board.is_shot_[4][4]);
}

TEST(OwnBoardTest, CreateOwnBoard) {
    OwnBoard board;
    EXPECT_EQ(10, board.get_size());
    EXPECT_EQ(5, board.get_num_active_ships());
    EXPECT_EQ(0, board.grid_[0][0]);
    EXPECT_EQ(0, board.grid_[9][9]);
    EXPECT_FALSE(board.is_shot_[0][0]);
    EXPECT_FALSE(board.is_shot_[4][5]);
}

TEST(OwnBoardTest, CreateOwnBoardWithSize) {
    OwnBoard board(5);
    EXPECT_EQ(5, board.get_size());
    EXPECT_EQ(5, board.get_num_active_ships());
    EXPECT_EQ(0, board.grid_[0][0]);
    EXPECT_EQ(0, board.grid_[4][4]);
    EXPECT_FALSE(board.is_shot_[0][0]);
    EXPECT_FALSE(board.is_shot_[4][4]);
}

TEST(OwnBoardTest, PlaceShip){
    OwnBoard board;
    std::vector<std::pair<unsigned short, unsigned short>> coords;
    coords.push_back(std::make_pair(0, 0));
    coords.push_back(std::make_pair(0, 1));
    coords.push_back(std::make_pair(0, 2));
    coords.push_back(std::make_pair(0, 3));
    coords.push_back(std::make_pair(0, 4));
    EXPECT_TRUE(board.place_ship(coords, Carrier));
    EXPECT_EQ(5, board.grid_[0][0]);
    EXPECT_EQ(5, board.grid_[0][1]);
    EXPECT_EQ(5, board.grid_[0][2]);
    EXPECT_EQ(5, board.grid_[0][3]);
    EXPECT_EQ(5, board.grid_[0][4]);
    EXPECT_FALSE(board.place_ship(coords, Carrier));
    EXPECT_FALSE(board.place_ship(coords, Battleship));
    EXPECT_FALSE(board.place_ship(coords, Cruiser));
    EXPECT_FALSE(board.place_ship(coords, Submarine));
    EXPECT_FALSE(board.place_ship(coords, Destroyer));
    coords.clear();
    coords.push_back(std::make_pair(2, 2));
    coords.push_back(std::make_pair(3, 2));
    coords.push_back(std::make_pair(4, 2));
    EXPECT_TRUE(board.place_ship(coords, Submarine));
    EXPECT_EQ(2, board.grid_[2][2]);
    EXPECT_EQ(2, board.grid_[3][2]);
}

TEST(OwnBoardTest, RotateShip){
    OwnBoard board;
    std::vector<std::pair<unsigned short, unsigned short>> coords;
    coords.push_back(std::make_pair(0, 0));
    coords.push_back(std::make_pair(0, 1));
    coords.push_back(std::make_pair(0, 2));
    coords.push_back(std::make_pair(0, 3));
    coords.push_back(std::make_pair(0, 4));
    ShipCategory ship = Carrier;
    EXPECT_TRUE(board.place_ship(coords, ship));
    EXPECT_EQ(5, board.grid_[0][0]);
    EXPECT_EQ(5, board.grid_[0][1]);
    

    EXPECT_EQ(5, board.grid_[0][4]);
    board.rotate_ship(coords, ship);
    EXPECT_EQ(5, board.grid_[0][0]);
    EXPECT_EQ(0, board.grid_[0][1]);
    EXPECT_EQ(0, board.grid_[0][3]);
    EXPECT_EQ(5, board.grid_[3][0]);
    EXPECT_EQ(5, board.grid_[4][0]);
    coords.clear();
    coords.push_back(std::make_pair(2, 2));
    coords.push_back(std::make_pair(3, 2));
    coords.push_back(std::make_pair(4, 2));
    EXPECT_TRUE(board.place_ship(coords, Submarine));
    EXPECT_EQ(2, board.grid_[2][2]);
    EXPECT_EQ(2, board.grid_[3][2]);
    board.rotate_ship(coords, Submarine);
    EXPECT_EQ(0, board.grid_[3][2]);
    EXPECT_EQ(2, board.grid_[2][3]);

    coords.clear();
    coords.push_back(std::make_pair(0,0));
    coords.push_back(std::make_pair(1,0));
    EXPECT_FALSE(board.place_ship(coords, Destroyer));
    EXPECT_FALSE(board.rotate_ship(coords, Destroyer));
}

TEST(EnemyBoardTest, CreateEnemyBoard){
    EnemyBoard board;
    EXPECT_EQ(10, board.get_size());
    EXPECT_EQ(5, board.get_num_active_ships());
    EXPECT_EQ(0, board.grid_[0][0]);
    EXPECT_EQ(0, board.grid_[9][9]);
    EXPECT_FALSE(board.is_shot_[0][0]);
    EXPECT_FALSE(board.is_shot_[4][5]);
}

TEST(EnemyBoardTest, CreateEnemyBoardWithSize){
    EnemyBoard board(5);
    EXPECT_EQ(5, board.get_size());
    EXPECT_EQ(5, board.get_num_active_ships());
    EXPECT_EQ(0, board.grid_[0][0]);
    EXPECT_EQ(0, board.grid_[4][4]);
    EXPECT_FALSE(board.is_shot_[0][0]);
    EXPECT_FALSE(board.is_shot_[4][4]);
}