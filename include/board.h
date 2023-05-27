#pragma once
#include <array>
#include <iostream>
#include <memory>
#include <utility>
#include <exception>

#include "ship.h"


// ---------------------------------Board---------------------------- //
class Board {
   public:

    /**
     * @brief Construct a new Board object
     */
    Board();

    /**
     * @brief Destroy the Board object
     */
    ~Board();

    /**
     * @brief Get the grid_size_ of the board
     * @return The grid_size_ of the board
     */
    const unsigned short get_grid_size() const;

    /**
     * @brief Get the grid value at a given coordinate
     * @param x, y The coordinates
     * @return The grid value at the given coordinate
     */
    unsigned short get_grid_value(const unsigned short &x, const unsigned short &y) const;

    /**
     * @brief Set the grid value at a given coordinate
     * @param x, y The coordinates
     * @param value The value to set the grid value to
     */
    void set_grid_value(const unsigned short &x, const unsigned short &y, unsigned short value);

    /**
     * @brief Get number of ships_ on the board
     */
    unsigned short get_num_ships() const;

    /**
     * @brief Get the ships_ on the board
     * @return The ships_ on the board
     */
    std::array<Ship *, 5> &get_ship_arr();

    /**
     * @brief Get the ships_ on the board (unmodifiable)
     * @return The ships_ on the board
     */
    const std::array<const Ship *, 5> get_ship_arr() const;

    /**
     * @brief Get the is_shot_ value at a given coordinate
     * @param x, y The coordinates
     * @return The is_shot_ value at the given coordinate
     */
    bool get_is_shot(const unsigned short &x, const unsigned short &y) const;

    /**
     * @brief Set the is_shot_ value at a given coordinate
     * @param x, y The coordinates
     * @param value The value to set the is_shot_ value to
     */
    void set_is_shot(const unsigned short &x, const unsigned short &y, bool value);

    /**
     * @brief get ship of vector of that type
     * @param type type of the ship
     * @return ship* of that ship
     */
    Ship *get_ship_by_name(const ShipCategory &type);

    /**
     * @brief Check if all the ships on this board have been destroyed
     */
    bool all_ships_sunk() const;

    const Ship* get_ship_by_index(const unsigned short &index) const;


    /**
     * @brief Reset the board to its initial state
     */
    void reset();


   /**
    * @brief riddle the shiple a.k.a. delete the ship from the board
    * @param shipname name of the ship to get rid of
   */
   void riddle_the_shiple(const ShipCategory &shipname);


   private:
    /**
     * @brief The grid_size_ of the board, default is 10 -> grid_size_ *
     * grid_size_ board
     */
    const unsigned short grid_size_ = 10;
    std::array<std::array<unsigned short, 10>, 10> grid_{0};
    std::array<std::array<bool, 10>, 10> is_shot_{false};
    std::array<Ship *, 5> ships_;
};

// ---------------------------------OwnBoard---------------------------- //
class OwnBoard : public Board {
   public:

   /**
    * @brief Inherit constructor and destructor from Board
   */
    using Board::Board;


    /**
     * @brief Checks if a given placement is valid
     * @param x, y The coordinates of the ship to be placed
     * @param ship The ship to be checked
     */
    bool is_valid_placement(const unsigned short &x, const unsigned short &y,
                            const Ship &ship) const;

    /**
     * @brief Places a ship on the board
     * @param x, y  The coordinates of the ship to be placed
     * @param ship The ship to be placed
     */
    bool place_ship(const unsigned short &x, const unsigned short &y, const bool &is_horizontal,
                    const ShipCategory &shipname);

    /**
     * @brief Set the ships on the board from the ShipData objects
     *
     * @return true if the configuration is valid
     */
    bool set_ship_configuration(const std::array<ShipData, 5> &ships);


    /**
     * @brief Get the ship at a given coordinate
     * @param x, y The coordinates
     * @return The ship at the given coordinate
     */
    Ship *get_ship(const unsigned short &x, const unsigned short &y);

    /**
     * @brief update the ship at a given coordinate
     * @param x, y The coordinates
     */
    void update_ship(const unsigned short &x, const unsigned short &y);

   /**
    * @brief Checks if the ship configuration is valid
   */
    bool is_valid_configuration() const;


   /**
    * @brief Checks if the ship configuration is ultimate
   */
    bool is_ultimate_configuration() const;

   /**
    * @brief Get the ship configuration
    * @return The ship configuration in the form of an array of ShipData objects
   */
    std::array<ShipData, 5> get_ship_configuration() const;

   private:
};

// ---------------------------------EnemyBoard---------------------------- //

class EnemyBoard : public Board {
   public:

   /**
    * @brief Inherit constructor and destructor from Board
   */
    using Board::Board;

    /**
     * @brief Checks if a given shot is valid
     * @param x, y The coordinates of the shot to be placed
     */
    bool is_valid_shot(const unsigned short &x, const unsigned short &y) const;

    void update_ship_vec(ShipCategory ship);

    void set_ship_data(const std::array<ShipData, 5> &ships);

   private:
};