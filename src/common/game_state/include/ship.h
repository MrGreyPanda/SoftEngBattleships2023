#pragma once
#include <stdexcept>
#include <utility>
/*
The class attributes are:
length: short, defines the length of the ship, for example 5, 4, 3, 2 or 1
is_sunk: bool, defines if the ship has sunk (TRUE) or not (FALSE), this is the case when ship_coord is empty
damage: short, holds remaining length of the ship, gets updated by shot_at
name: ShipCategory, holds the unique name of a ship

The class operations are:
shot_at, void, updates damage and checks is_sunk, then sets the value accordingly.
*/
// Enumerators to categorize the different ship types

enum ShipCategory{
    Carrier = 5,        // size = 5
    Battleship = 4,     // size = 4
    Cruiser = 3,        // size = 3
    Submarine = 2,      // size = 3
    Destroyer = 1       // size = 2
}; 

/**
 * @brief Converts a ShipCategory to the size of the ship
 * @param type The ShipCategory to be converted
*/
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
    // Ship(unsigned int length_, ShipCategory name_);
    /**
     * @brief Construct a new Ship object
     * @param name_ The name of the ship
     * TODO: Add except/assertion to make it safer
    */
    Ship(ShipCategory name_);

    /**
     * @brief Destroy the Ship object
    */
    ~Ship();

    /**
     * @brief update the damage and check if the ship is sunk
    */
    void shot_at();

    /**
     * @brief Get the length of the ship
     * @return The length of the ship
    */
    unsigned short get_length() const { return length; }

    /**
     * @brief Get the damage of the ship
     * @return The damage of the ship
    */
    unsigned short get_damage() const { return damage; }

    /**
     * @brief Get the name of the ship
     * @return The name of the ship
    */
    ShipCategory get_name() const { return name; }

    /**
     * @brief Get the is_sunk of the ship
     * @return The is_sunk of the ship
     * TODO: Add except/assertion to make it safer
     * TODO: Add a player message or something like that
    */
    bool get_is_sunk() const { return is_sunk; }

private:

    unsigned short length;
    bool is_sunk;
    unsigned short damage;
    ShipCategory name;
};
