#pragma once
/*
The class attributes are:
size: unsigned short, defines the grid length/width, we planned on using 10 giving a 1010 grid
grid: vector, a vector of length sizesize with each entry storing a number representing a part of a ship. The index (-1) of a ship in the ‘ships’ vector (1 maps to index 0 of the vector). 0 in the grid represents water (no ship) in the grid cell, 1 is the first ship, (2) the second and so on. A non-zero and out-of-bounds index, represents a ship part (the cell belongs to a ship, but it is not yet clear to which ship).
shots: vector, a vector of length size*size with each entry defining if a cell already has been shot at (TRUE) or not (FALSE).
ships: vector, the agreed upon list of ships in the game somewhere on this board.
*/





class Board {
public:

private:

};
