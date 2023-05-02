#pragma once
#include "ship.h"
#include <utility>
#include <vector>


class Board {
public:

// Implement later for customization of the game
// Board(unsigned short size_, unsigned short n_ships);

/**
 * @brief Construct a new Board object
*/
Board();

/**
 * @brief Construct a new Board object
 * @param size_ The size of the board
*/
Board(unsigned short size_);

/**
 * @brief Destroy the Board object
*/
~Board();

/**
 * @brief Get the size of the board
 * @return The size of the board
*/
unsigned short get_size();

/**
 * @brief Get the ships that are not sunk on the board
 * @return The ships on the board
*/
unsigned short get_num_active_ships();

    int grid[10][10];
    bool is_shot[10][10];
private:
    unsigned short size = 10;
    std::vector<Ship> ships;
};

/*
The class operations are:
is_valid_placement: bool, checks if ship placement is valid
place_ship: bool, calls is_valid_placement, updates corresponding entries in grid and returns TRUE if successful
rotate_ship: bool, updates entries to represent a ship rotated by 90 degrees, returns TRUE if succesful
*/

class OwnBoard : public Board {
public:

/**
 * @brief Construct a new Own Board object
*/
OwnBoard();

/**
 * @brief Construct a new Own Board object
 * @param size_ The size of the board
*/
OwnBoard(unsigned int size_);

/**
 * @brief Checks if a given placement is valid
 * @param coords The coordinates of the ship to be placed
 * TODO: throw an error if coords.size() != shiptype size
*/
bool is_valid_placement(const std::vector<std::pair<unsigned short, unsigned short>> coords, ShipCategory shiptype);

/**
 * @brief Places a ship on the board
 * @param coords The coordinates of the ship to be placed
*/
bool place_ship(const std::vector<std::pair<unsigned short, unsigned short>> coords, ShipCategory shiptype);

/**
 * @brief Rotates a ship on the board
 * @param coords The coordinates of the ship to be rotated
 * TODO: throw an error if coords.size() != shiptype size
*/
bool rotate_ship(std::vector<std::pair<unsigned short, unsigned short>> &coords, ShipCategory shiptype);

private:

};


/*
The class operations are:
is_valid_shot: bool, checks if a given shot is valid. Returns !is_shot.
*/

class EnemyBoard : public Board {
public:

/**
 * @brief Construct a new Enemy Board object
*/
EnemyBoard();

/**
 * @brief Construct a new Enemy Board object
 * @param size_ The size of the board
*/
EnemyBoard(unsigned int size_);

/**
 * @brief Checks if a given shot is valid
 * @param coords The coordinates of the shot to be placed
*/
bool is_valid_shot(const std::pair<unsigned short, unsigned short> &coord);

private:


};