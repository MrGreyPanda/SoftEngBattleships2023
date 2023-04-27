#pragma once
#include "ship.h"
#include <utility>
#include <vector>
/*

The class attributes are:
size: unsigned short, defines the grid length/width, we planned on using 10 giving a 10*10 grid
grid: vector, a vector of length size*size with each entry storing a number representing a part of a ship. The index (-1) of a ship in the ‘ships’ vector (1 maps to index 0 of the vector). 0 in the grid represents water (no ship) in the grid cell, 1 is the first ship, (2) the second and so on. A non-zero and out-of-bounds index, represents a ship part (the cell belongs to a ship, but it is not yet clear to which ship).
is_shot: vector, a vector of length size*size with each entry defining if a cell already has been shot at (TRUE) or not (FALSE).
ships: vector, the agreed upon list of ships in the game somewhere on this board.
*/


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

private:
    unsigned short size = 10;
    ShipCategory grid[10 * 10];
    bool is_shot[10 * 10];
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
 * @brief Checks if a given placement is valid
 * @param coords The coordinates of the ship to be placed
*/
bool is_valid_placement(const std::pair<unsigned short, unsigned short> coords[]);

/**
 * @brief Places a ship on the board
 * @param coords The coordinates of the ship to be placed
*/
bool place_ship(const std::pair<unsigned short, unsigned short> coords[]);

/**
 * @brief Rotates a ship on the board
 * @param coords The coordinates of the ship to be rotated
*/
bool rotate_ship(std::pair<unsigned short, unsigned short> coords[]);

private:

};


/*
The class operations are:
is_valid_shot: bool, checks if a given shot is valid. Returns !is_shot.
*/

class EnemyBoard : public Board {
public:

/**
 * @brief Checks if a given shot is valid
 * @param coords The coordinates of the shot to be placed
*/
bool is_valid_shot(const std::pair<unsigned short, unsigned short> &coord);

private:


};