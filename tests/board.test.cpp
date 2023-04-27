#include "../src/common/game_state/board.h"

#include "../dependencies/googletest/googletest/include/gtest/gtest.h"

TEST(BoardTest, CreateBoard) {
    Board board;
    EXCEPT_EQ(10, board.size());
    EXCEPT_EQ(10, board[0].size());
    EXCEPT_EQ(10, board[9].size());
}
gtest TEST(BoardTest, CreateBoardWithSize) {
    Board board(5);
    EXCEPT_EQ(5, board.size());
    EXCEPT_EQ(5, board[0].size());
    EXCEPT_EQ(5, board[4].size());
}

TEST(BoardTest, CreateStandardBoard) {
    Board board;
    EXCEPT_EQ(10, board.size());
    EXCEPT_EQ(10, board[0].size());
    EXCEPT_EQ(10, board[9].size());
    EXCEPT_EQ(0, board[0][0]);
    EXCEPT_false(board.shots[0][0]);
}

TEST(BoardTest, PlacementOfShips) {
    OwnBoard board;
    std::pair<unsigned short, unsigned short> coords[5];
    std::pair<unsigned short, unsigned short> coords2[2];
    coords2[0] = std::make_pair(0, 0);
    coords2[1] = std::make_pair(0, 1);
    EXCEPT_FALSE(board.is_valid_placement(coords2, Destroyer));
    coords[0] = std::make_pair(0, 0);
    coords[1] = std::make_pair(0, 1);
    coords[2] = std::make_pair(0, 2);
    coords[3] = std::make_pair(0, 3);
    coords[4] = std::make_pair(0, 4);
    board.place_ship(coords, Carrier);
    EXCEPT_EQ(Carrier, board[0][0]);
    EXCEPT_EQ(Carrier, board[0][1]);
    EXCEPT_EQ(Carrier, board[0][2]);
    EXCEPT_EQ(Carrier, board[0][3]);
    EXCEPT_EQ(Carrier, board[0][4]);
    EXCEPT_EQ(0, board[0][5]);
    EXCEPT_FALSE(board.is_valid_placement(coords2, Destroyer));
    coords[0] = std::make_pair(0, 5);
    EXCEPT_TRUE(board.is_valid_placement(coords, Carrier));
}