#pragma once
#include "ship.h"
#include <vector>
/*

The class attributes are:
size: unsigned short, defines the grid length/width, we planned on using 10 giving a 10*10 grid
grid: vector, a vector of length size*size with each entry storing a number representing a part of a ship. The index (-1) of a ship in the ‘ships’ vector (1 maps to index 0 of the vector). 0 in the grid represents water (no ship) in the grid cell, 1 is the first ship, (2) the second and so on. A non-zero and out-of-bounds index, represents a ship part (the cell belongs to a ship, but it is not yet clear to which ship).
shots: vector, a vector of length size*size with each entry defining if a cell already has been shot at (TRUE) or not (FALSE).
ships: vector, the agreed upon list of ships in the game somewhere on this board.
*/


class Board {
public:

Board();
Board(unsigned short size_);

// Implement later for customization of the game
// Board(unsigned short size_, unsigned short n_ships);

private:
    unsigned short size = 10;
    int grid[size][size];
    bool shots[size][size];
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
bool is_valid_placement(const std::pair<unsigned short, unsigned short> &coords[], ShipCategory shiptype);
bool place_ship(const std::pair<unsigned short, unsigned short> &coords[], ShipCategory shiptype);
bool rotate_ship(std::pair<unsigned short, unsigned short> &coords[], ShipCategory shiptype);

private:

}


/*
The class operations are:
is_valid_shot: bool, checks if a given shot is valid. Returns !is_shot.
*/

class EnemyBoard : public Board {
public:
bool is_valid_shot(const std::pair<unsigned short, unsigned short> &coords[][]);

private:


}