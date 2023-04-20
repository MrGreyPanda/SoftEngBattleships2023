#include "ship.h"
/*
The class attributes are:
length: short, defines the length of the ship, for example 5, 4, 3, 2 or 1
is_sunk: bool, defines if the ship has sunk (TRUE) or not (FALSE), this is the case when ship_coord is empty
remaining_length: short, holds remaining length of the ship, gets updated by shot_at

The class operations are:
shot_at, void, updates remaining_length and checks is_sunk, then sets the value accordingly.
*/


Ship(unsigned int length_) : length(length_) {
}

void Ship::shot_at(){
    if(this.remaining_length <= 0 || this.is_sunk){
        throw std::error("This ship is already sunk and therefore can't be shot at. Invalid shot.");
    }
    --this.remaining_length;
    if(remaining_length == 0){
        this.is_sunk = true;
    }
}

