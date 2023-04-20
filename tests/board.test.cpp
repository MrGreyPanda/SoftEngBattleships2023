#include "gtest/gtest.h"
#include "../src/common/board.h"

TEST(BoardTest, CreateBoard){
    Board board;
    EXCEPT_EQ(10, board.size());
    EXCEPT_EQ(10, board[0].size());
    EXCEPT_EQ(10, board[9].size());
}

TEST(BoardTest, CreateBoardWithSize){
    Board board(5);
    EXCEPT_EQ(5, board.size());
    EXCEPT_EQ(5, board[0].size());
    EXCEPT_EQ(5, board[4].size());
}

TEST(BoardTest, PlacementOfShips){
    Board board;
    std::pair<unsigned short, unsigned short> coords[5];
    coords[0] = std::make_pair(0,0);
    coords[1] = std::make_pair(0,1);
    coords[2] = std::make_pair(0,2);
    coords[3] = std::make_pair(0,3);
    coords[4] = std::make_pair(0,4);
    // EXCEPT_EQ(true, board.place_ship(coords, Carrier));
    // EXCEPT_EQ(true, board.place_ship(coords, Battleship));
    // EXCEPT_EQ(true, board.place_ship(coords, Cruiser));
    // EXCEPT_EQ(true, board.place_ship(coords, Submarine));
    // EXCEPT_EQ(true, board.place_ship(coords, Destroyer));
}