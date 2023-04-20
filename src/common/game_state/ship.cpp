#include "ship.h"
/*
The class attributes are:
length: short, defines the length of the ship, for example 5, 4, 3, 2 
is_sunk: bool, defines if the ship has sunk (TRUE) or not (FALSE), this is the case when ship_coord is empty
remaining_length: short, holds remaining length of the ship, gets updated by shot_at

The class operations are:
shot_at, void, updates remaining_length and checks is_sunk, then sets the value accordingly.
*/

// // Constructor
// Ship::Ship(unsigned int length_, ShipCategory name_) : length(length_), name(name_), is_sunk(false) {
//     remaining_length = length;
// }

// Constructor
Ship::Ship(ShipCategory name_) : name(name_), is_sunk(false){
    length = category_to_size(name_);
    if(length == 0) throw std::exception("Not a valid ShipCategory");
    remaining_length = length;
}


void Ship::shot_at(){
    if(this.remaining_length <= 0 || this.is_sunk){
        throw std::exception("This ship is already sunk and therefore can't be shot at. Invalid shot.");
    }
    --this.remaining_length;
    if(remaining_length == 0){
        this.is_sunk = true;
        std::cout << "Your " << name << " has been sunk!\n";
    }
}

