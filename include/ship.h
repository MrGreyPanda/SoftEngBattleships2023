#pragma once
#include <stdexcept>
#include <utility>
/*
The class attributes are:
length_: short, defines the length_ of the ship, for example 5, 4, 3, 2 or 1
is_sunk_: bool, defines if the ship has sunk (TRUE) or not (FALSE), this is the
case when ship_coord is empty damage_: short, holds remaining length_ of the
ship, gets updated by shot_at name_: ShipCategory, holds the unique name_ of a
ship

The class operations are:
shot_at, void, updates damage_ and checks is_sunk_, then sets the value
accordingly.
*/
// Enumerators to categorize the different ship types

enum ShipCategory {
    Carrier    = (unsigned short)5,  // size = 5
    Battleship = (unsigned short)4,  // size = 4
    Cruiser    = (unsigned short)3,  // size = 3
    Submarine  = (unsigned short)2,  // size = 3
    Destroyer  = (unsigned short)1   // size = 2
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
     * @brief Construct a new Ship object from the data struct
     * This is mainly used for the JSON serialization and deserialization
     * to efficiently pass the posistion and orientation of the ships after
     * they have been placed.
     *
     * @param data
     */
    Ship(ShipData data);

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
    unsigned short get_length() const;

    /**
     * @brief Get the damage_ of the ship
     * @return The damage_ of the ship
     */
    unsigned short get_damage() const;

    /**
     * @brief Get the name_ of the ship
     * @return The name_ of the ship
     */
    ShipCategory get_name() const;

    /**
     * @brief Get the is_sunk_ of the ship
     * @return The is_sunk_ of the ship
     * TODO: Add except/assertion to make it safer
     * TODO: Add a player message or something like that
     */
    bool get_is_sunk() const;

    /**
     * @brief Get the is_horizontal_ of the ship
     * @return The is_horizontal_ of the ship
     */
    bool get_is_horizontal() const;

    /**
     * @brief Set the is_horizontal_ of the ship
     * @param is_horizontal_ The new is_horizontal_ of the ship
     */
    void set_is_horizontal(bool is_horizontal);

    /**
     * @brief Get the is_placed_ of the ship
     * @return The is_placed_ of the ship
     */
    bool get_is_placed() const;
    /**
     * @brief Set the is_placed_ of the ship
     * @param is_placed_ The new is_placed_ of the ship
     */

    void set_is_placed(bool is_placed);

    /**
     * @brief Get the x_ of the ship
     * @return The x_ of the ship
     */
    short get_x() const;

    /**
     * @brief Get the y_ of the ship
     * @return The y_ of the ship
     */
    short get_y() const;

    /**
     * @brief Set the x_ of the ship
     * @param x, y The new x_ & y_ of the ship
     */
    void set_xy(const short &x, const short &y);

   private:
    unsigned short length_;
    bool is_sunk_;
    unsigned short damage_;
    ShipCategory name_;
    bool is_horizontal_;
    bool is_placed_;

    /**
     * Starting coordinates of the ship
     */
    short x_;
    short y_;
};

struct ShipData {
    ShipCategory name;
    bool is_horizontal;
    short x;
    short y;
};
