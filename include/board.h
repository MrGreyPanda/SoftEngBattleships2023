#pragma once
#include "ship.h"
#include <utility>
#include <vector>
#include <memory>


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

// /**
//  * @brief Get the ships_ that are not sunk on the board
//  * @return The ships_ on the board
// */
// unsigned short get_num_active_ships();

/**
 * @brief Get the grid value at a given coordinate
 * @param x, y The coordinates
 * @return The grid value at the given coordinate
*/
unsigned short get_grid_value(const short &x, const short &y);

/**
 * @brief Set the grid value at a given coordinate
 * @param x, y The coordinates
 * @param value The value to set the grid value to
*/
void set_grid_value(const short &x, const short &y, int value);


/**
 * @brief Get number of ships_ on the board
*/
unsigned short get_num_ships();

/**
 * @brief Get the ships_ on the board
 * @return The ships_ on the board
*/
std::shared_ptr<std::vector<std::shared_ptr<Ship>>> get_ship_vec();

/**
 * @brief Get the is_shot_ value at a given coordinate
 * @param x, y The coordinates
 * @return The is_shot_ value at the given coordinate
*/
bool get_is_shot(const short &x, const short &y);

/**
 * @brief Set the is_shot_ value at a given coordinate
 * @param x, y The coordinates
 * @param value The value to set the is_shot_ value to
*/
void set_is_shot(const short &x, const short &y, bool value);


private:
    /**
     * @brief The grid_size_ of the board, default is 10 -> grid_size_ * grid_size_ board
    */
    unsigned short grid_size_ = 10;
    std::vector<std::vector<unsigned short>> grid_ = std::vector<std::vector<unsigned short>>(grid_size_, std::vector<unsigned short>(grid_size_, 0));
    std::vector<std::vector<bool>> is_shot_ = std::vector<std::vector<bool>>(grid_size_, std::vector<bool>(grid_size_, false));
    std::vector<std::shared_ptr<Ship>> ships_;
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
 * @param x, y The coordinates of the ship to be placed
 * @param ship The ship to be checked
 * TODO: throw an error if coords.grid_size_() != shiptype grid_size_
*/
bool is_valid_placement(const short &x, const short &y, const Ship &ship);

/**
 * @brief Places a ship on the board
 * @param x, y  The coordinates of the ship to be placed
 * @param ship The ship to be placed
*/
bool place_ship(const short &x, const short &y, Ship &ship);


/**
 * @brief If ship is on the board, it checks if it can be rotated. 
 * @brief If not, it returns false. If it can, it rotates the ship and returns true. If not on board, it returns rotates it and returns true.  
 * @param ship The ship to be rotated
 * TODO: throw an error if coords.grid_size_() != shiptype grid_size_
*/
bool rotate_ship(Ship &ship);


/**
 * @brief Get the ship at a given coordinate
 * @param x, y The coordinates
 * @return The ship at the given coordinate
 * TODO: throw an error if no ship at given coordinate
*/
std::shared_ptr<Ship> get_ship(const short &x, const short &y);

/**
 * @brief Check if all the ships on this board have been destroyed
*/
bool all_ships_sunk();

/**
 * @brief update the ship at a given coordinate
*/
void update_ship(const short &x, const short &y);

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
 * @param x, y The coordinates of the shot to be placed
*/
bool is_valid_shot(const short &x, const short &y);

void update_ship_vec(ShipCategory ship);

private:


};