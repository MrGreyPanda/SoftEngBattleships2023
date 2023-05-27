#pragma once

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <utility>
#include <cassert>
#include <iostream>

using json = nlohmann::json;

// Enumerators to categorize the different ship types
/**
 * @brief Enum to categorize the different ship types
 * ShipPart is used to represent a part of a ship that has been hit
*/
enum ShipCategory {
    Destroyer  = (unsigned short)1,  // size = 2
    Submarine  = (unsigned short)2,  // size = 3
    Cruiser    = (unsigned short)3,  // size = 3
    Battleship = (unsigned short)4,  // size = 4
    Carrier    = (unsigned short)5,   // size = 5
    ShipPart   = (unsigned short)6   // size = 1
};

/**
 * @brief Struct to hold the data of a ship
 * Used for efficient communication between the server and the client
 */
struct ShipData {
    ShipData() = default;
    ShipData(const ShipCategory &name, const bool &is_horizontal,
             const unsigned short &x, const unsigned short &y);

    ShipCategory name;
    bool is_horizontal;
    unsigned short x;
    unsigned short y;

    bool operator==(const ShipData &other) const;
};
/**
 * @brief Casts ship data from JSON to a ShipData object
 *
 * @param j
 * @param data
 */
void from_json(const json &j, ShipData &data);

/**
 * @brief Parses json to ship data.
 *
 * @param j
 * @param data
 */
void to_json(json &j, const ShipData &data);

/**
 * @brief Converts a ShipCategory to the size of the ship
 * @param type The ShipCategory to be converted
 */
const unsigned short category_to_size(const ShipCategory &type);

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
    Ship(const ShipCategory &name_);

    /**
     * @brief Construct a new Ship object from the data struct
     * This is mainly used for the JSON serialization and deserialization
     * to efficiently pass the posistion and orientation of the ships after
     * they have been placed.
     *
     * @param data
     */
    Ship(const ShipData &data);

    // /**
    //  * @brief Copy constructor
    // */
    // Ship(const Ship &other);

    // /**
    //  * @brief Copy assignment operator
    //  */
    // Ship &operator=(const Ship &other);

    /**
     * @brief Destroy the Ship object
     */
    ~Ship();

    /**
     * @brief update the damage_ and check if the ship is sunk
     * TODO: Add except/assertion to make it safer
     * TODO: Add a player message or something like that
     */
    void shot_at();

    /**
     * @brief Get the length_ of the ship
     * @return The length_ of the ship
     */
    unsigned short get_length() const;

    /**
     * @brief Get the damage_ of the ship
     * @return The damage_ of the ship, just for testing purposes
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
     * @brief Set the is_sunk_ of the ship, for the client side
     */
    void set_is_sunk(bool is_sunk);

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
    void set_xy(const unsigned short &x, const unsigned short &y);

    /**
     * @brief Get the data object
     *
     * @return ShipData
     */
    ShipData get_data() const;


    /**
     * @brief Resets the ship to its default values
    */
    void reset_ship();

   private:
    const unsigned short length_;
    bool is_sunk_;
    unsigned short damage_ = 0;
    const ShipCategory name_;
    bool is_horizontal_;
    bool is_placed_;

    /**
     * Starting coordinates of the ship
     */
    unsigned short x_;
    unsigned short y_;
};
