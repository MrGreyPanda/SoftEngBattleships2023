#pragma once
#include <stdexcept>
#include <utility>
/*
The class attributes are:
length_: short, defines the length_ of the ship, for example 5, 4, 3, 2 or 1
is_sunk_: bool, defines if the ship has sunk (TRUE) or not (FALSE), this is the case when ship_coord is empty
damage_: short, holds remaining length_ of the ship, gets updated by shot_at
name_: ShipCategory, holds the unique name_ of a ship

The class operations are:
shot_at, void, updates damage_ and checks is_sunk_, then sets the value accordingly.
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
unsigned short category_to_size(ShipCategory type);

class Ship {
public:

    /**
     * @brief Default constructor
    */
   Ship();

    // Ship(unsigned int length_, ShipCategory name_);
    /**
     * @brief Construct a new Ship object
     * @param name_ The name_ of the ship
     * TODO: Add except/assertion to make it safer
    */
    Ship(ShipCategory name_);

    /**
     * @brief Destroy the Ship object
    */
    ~Ship();

    /**
     * @brief update the damage_ and check if the ship is sunk
    */
    void shot_at();

    /**
     * @brief Get the length_ of the ship
     * @return The length_ of the ship
    */
    unsigned short get_length() const { return length_; }

    /**
     * @brief Get the damage_ of the ship
     * @return The damage_ of the ship
    */
    unsigned short get_damage() const { return damage_; }

    /**
     * @brief Get the name_ of the ship
     * @return The name_ of the ship
    */
    ShipCategory get_name() const { return name_; }

    /**
     * @brief Get the is_sunk_ of the ship
     * @return The is_sunk_ of the ship
     * TODO: Add except/assertion to make it safer
     * TODO: Add a player message or something like that
    */
    bool get_is_sunk() const { return is_sunk_; }

private:

    unsigned short length_;
    bool is_sunk_;
    unsigned short damage_;
    ShipCategory name_;
};
