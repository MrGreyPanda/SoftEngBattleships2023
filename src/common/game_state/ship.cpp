#include "include/ship.h"
/*
The class attributes are:
length: short, defines the length of the ship, for example 5, 4, 3, 2 
is_sunk: bool, defines if the ship has sunk (TRUE) or not (FALSE), this is the case when ship_coord is empty
damage: short, holds remaining length of the ship, gets updated by shot_at

The class operations are:
shot_at, void, updates damage and checks is_sunk, then sets the value accordingly.
*/

// // Constructor
// Ship::Ship(unsigned int length_, ShipCategory name_) : length(length_), name(name_), is_sunk(false) {
//     damage = length;
// }

unsigned short category_to_size(ShipCategory type){
        switch(type){
        case Carrier    : return 5; 
        case Battleship : return 4; 
        case Cruiser    : return 3; 
        case Submarine  : return 3; 
        case Destroyer  : return 2; 
        default         : return 0;
    }
}

// Constructor
Ship::Ship(ShipCategory name_) : name(name_), is_sunk(false){
    length = category_to_size(name_);
    // if(length == 0) throw std::runtime_error(std::string("Not a valid ShipCategory"));
    damage = length;
}

Ship::Ship() : name(Destroyer), is_sunk(false), length(2), damage(0){}

Ship::~Ship(){
    // Nothing to do here
}


void Ship::shot_at(){
    if(damage <= 0 || is_sunk){
        // throw std::exception("This ship is already sunk and therefore can't be shot at. Invalid shot.");
    }
    --damage;
    if(damage == 0){
        is_sunk = true;
        // std::cout << "Your " << name << " has been sunk!\n";
    }
}

