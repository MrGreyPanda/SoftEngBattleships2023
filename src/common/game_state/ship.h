#pragma once
/*
The class attributes are:
length: short, defines the length of the ship, for example 5, 4, 3, 2 or 1
is_sunk: bool, defines if the ship has sunk (TRUE) or not (FALSE), this is the case when ship_coord is empty
remaining_length: short, holds remaining length of the ship, gets updated by shot_at
name: ShipCategory, holds the unique name of a ship

The class operations are:
shot_at, void, updates remaining_length and checks is_sunk, then sets the value accordingly.
*/
// Enumerators to categorize the different ship types
enum ShipCategory{
    Carrier = 4,        // size = 5
    Battleship = 3,     // size = 4
    Cruiser = 2,        // size = 3
    Submarine = 1,      // size = 3
    Destroyer = 0       // size = 2
}; 

// Given a Category returns the corresponding ship size
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

class Ship {
public:
    Ship(unsigned int length_, ShipCategory name_);
    Ship(ShipCategory name_);
    ~Ship();
    void shot_at();

private:

    unsigned short length;
    bool is_sunk;
    unsigned short remaining_length;
    ShipCategory name;
};
