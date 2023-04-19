#pragma once
/*
The class attributes are:
length: short, defines the length of the ship, for example 5, 4, 3, 2 or 1
is_sunk: bool, defines if the ship has sunk (TRUE) or not (FALSE), this is the case when ship_coord is empty
remaining_length: short, holds remaining length of the ship, gets updated by shot_at
The class operations are:
shot_at, void, updates remaining_length and checks is_sunk, then sets the value accordingly.
*/

class Ship {
public:
    Ship(unsigned int length_);
    ~Ship();

private:

unsigned short length;
bool is_sunk;
unsigned short remaining_length;

};
