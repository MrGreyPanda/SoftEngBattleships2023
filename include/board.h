#pragma once
#include "ship.h"
#include <utility>
#include <vector>


class Board {
public:

// Implement later for customization of the game
// Board(unsigned short grid_size_, unsigned short n_ships);

/**
 * @brief Construct a new Board object
*/
Board();

// /**
//  * @brief Construct a new Board object
//  * @param grid_size_ The grid_size_ of the board
// */
// Board(unsigned short grid_size_);

/**
 * @brief Destroy the Board object
*/
~Board();

/**
 * @brief Get the grid_size_ of the board
 * @return The grid_size_ of the board
*/
unsigned short get_grid_size();

/**
 * @brief Get the ships_ that are not sunk on the board
 * @return The ships_ on the board
*/
unsigned short get_num_active_ships();

/**
 * @brief Get the grid value at a given coordinate
 * @param x The x coordinate
 * @param y The y coordinate
 * @return The grid value at the given coordinate
*/
unsigned short get_grid_value(const std::pair<unsigned short, unsigned short> &coord);

/**
 * @brief Set the grid value at a given coordinate
 * @param x The x coordinate
 * @param y The y coordinate
 * @param value The value to set the grid value to
*/
void set_grid_value(const std::pair<unsigned short, unsigned short> &coord, int value);

/**
 * @brief Get the is_shot_ value at a given coordinate
 * @param x The x coordinate
 * @param y The y coordinate
 * @return The is_shot_ value at the given coordinate
*/
bool get_is_shot(const std::pair<unsigned short, unsigned short> &coord);


private:
    /**
     * @brief The grid_size_ of the board, default is 10 -> grid_size_ * grid_size_ board
    */
    unsigned short grid_size_ = 10;
    std::vector<std::vector<unsigned short>> grid_ = std::vector<std::vector<unsigned short>>(grid_size_, std::vector<unsigned short>(grid_size_, 0));
    std::vector<std::vector<bool>> is_shot_ = std::vector<std::vector<bool>>(grid_size_, std::vector<bool>(grid_size_, false));
    std::vector<Ship> ships_;
};

/*
The class operations are:
is_valid_placement: bool, checks if ship placement is valid
place_ship: bool, calls is_valid_placement, updates corresponding entries in grid_ and returns TRUE if successful
rotate_ship: bool, updates entries to represent a ship rotated by 90 degrees, returns TRUE if succesful
*/

class OwnBoard : public Board {
public:

// /**
//  * @brief Construct a new Own Board object
// */
// OwnBoard();
using Board::Board;

~OwnBoard();

// /**
//  * @brief Construct a new Own Board object
//  * @param grid_size_ The grid_size_ of the board
// */
// OwnBoard(unsigned short grid_size_);

/**
 * @brief Checks if a given placement is valid
 * @param coords The coordinates of the ship to be placed
 * TODO: throw an error if coords.grid_size_() != shiptype grid_size_
*/
bool is_valid_placement(const std::vector<std::pair<unsigned short, unsigned short>> &coords, const ShipCategory &shiptype);

/**
 * @brief Places a ship on the board
 * @param coords The coordinates of the ship to be placed
*/
bool place_ship(const std::vector<std::pair<unsigned short, unsigned short>> &coords, const ShipCategory &shiptype);

/**
 * @brief Rotates a ship on the board
 * @param coords The coordinates of the ship to be rotated
 * TODO: throw an error if coords.grid_size_() != shiptype grid_size_
*/
bool rotate_ship(std::vector<std::pair<unsigned short, unsigned short>> &coords, const ShipCategory &shiptype);

private:

};


/*
The class operations are:
is_valid_shot: bool, checks if a given shot is valid. Returns !is_shot_.
*/

class EnemyBoard : public Board {
public:

// /**
//  * @brief Construct a new Enemy Board object
// */
// EnemyBoard();
using Board::Board;

~EnemyBoard();

// /**
//  * @brief Construct a new Enemy Board object
//  * @param grid_size_ The grid_size_ of the board
// */
// EnemyBoard(unsigned short grid_size_);

/**
 * @brief Checks if a given shot is valid
 * @param coords The coordinates of the shot to be placed
*/
bool is_valid_shot(const std::pair<unsigned short, unsigned short> &coord);

private:


};