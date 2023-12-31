#include "board.h"

Board::Board() : grid_size_(10) {
    ships_ = {new Ship(Destroyer), new Ship(Submarine), new Ship(Cruiser),
              new Ship(Battleship), new Ship(Carrier)};
}

Board::~Board() {
    for (unsigned short i = 0; i < ships_.size(); i++) {
        if (ships_[i] != nullptr) delete ships_[i];
    }
}

const unsigned short Board::get_grid_size() const { return grid_size_; }

unsigned short Board::get_grid_value(const unsigned short &x,
                                     const unsigned short &y) const {
    return grid_[y][x];
}

unsigned short Board::get_num_ships() const { return ships_.size(); }

std::array<Ship *, 5> &Board::get_ship_arr() { return ships_; }

const std::array<const Ship *, 5> Board::get_ship_arr() const {
    std::array<const Ship *, 5> const_ships_pointers{nullptr};
    for (unsigned short i = 0; i < 5; i++) {
        const_ships_pointers[i] = (const Ship *)ships_[i];
    }
    return const_ships_pointers;
}

void Board::set_grid_value(const unsigned short &x, const unsigned short &y,
                           unsigned short value) {
    assert(x >= 0 && y >= 0 && x < grid_size_ && y < grid_size_);
    grid_[y][x] = (unsigned short)value;
}

bool Board::get_is_shot(const unsigned short &x,
                        const unsigned short &y) const {
    assert(x >= 0 && y >= 0 && x < grid_size_ && y < grid_size_);
    return is_shot_[y][x];
}

void Board::set_is_shot(const unsigned short &x, const unsigned short &y,
                        bool value) {
    assert(x >= 0 && y >= 0 && x < grid_size_ && y < grid_size_);
    is_shot_[y][x] = value;
}

Ship *Board::get_ship_by_name(const ShipCategory &type) {
    for (unsigned short i = 0; i < ships_.size(); i++) {
        if (ships_[i]->get_name() == type) return ships_[i];
    }
    return nullptr;
}

bool Board::all_ships_sunk() const {
    unsigned short num_ships                     = get_num_ships();
    const std::array<const Ship *, 5> &ships_vec = get_ship_arr();
    for (unsigned short i = 0; i < num_ships; i++) {
        if (ships_vec.at(i)->get_is_sunk() == false) return false;
    }
    return true;
}

const Ship *Board::get_ship_by_index(const unsigned short &index) const {
    return ships_[index];
}

void Board::reset() {
    for (unsigned short i = 0; i < grid_size_; i++) {
        for (unsigned short j = 0; j < grid_size_; j++) {
            grid_[i][j]    = 0;
            is_shot_[i][j] = false;
        }
    }
    for (unsigned short i = 0; i < ships_.size(); i++) {
        if (ships_[i] != nullptr) ships_[i]->reset_ship();
    }
}

void Board::riddle_the_shiple(const ShipCategory &shipname) {
    for (unsigned short i = 0; i < grid_size_; i++) {
        for (unsigned short j = 0; j < grid_size_; j++) {
            if (grid_[i][j] == shipname) {
                grid_[i][j] = 0;
            }
        }
    }
}
// ------------ OwnBoard ------------- //

bool OwnBoard::is_valid_placement(const unsigned short &x,
                                  const unsigned short &y,
                                  const Ship &ship) const {
    unsigned short grid_size_ = this->get_grid_size();
    if (x >= grid_size_ || y >= grid_size_ || x < 0 || y < 0) {
        // coordinates are out of bounds
        return false;
    }

    bool is_horizontal         = ship.get_is_horizontal();
    unsigned short ship_length = ship.get_length();
    if (is_horizontal) {
        if (x + ship_length > grid_size_) {
            // the ship doesn't fit in the grid
            return false;
        }
        ShipCategory shiptype = ship.get_name();
        for (unsigned short i = 0; i < ship_length; i++) {
            if (get_grid_value(x + i, y) != 0 &&
                get_grid_value(x + i, y) != shiptype) {
                // there is already a ship in the way
                return false;
            }
        }
        return true;
    }

    else if (!is_horizontal) {
        if (y + ship_length > grid_size_) {
            // the ship doesn't fit in the grid
            return false;
        }
        ShipCategory shiptype = ship.get_name();

        for (unsigned short i = 0; i < ship_length; i++) {
            if (get_grid_value(x, y + i) != 0 &&
                get_grid_value(x, y + i) != shiptype) {
                // there is already a ship in the way
                return false;
            }
        }
        return true;
    } else {
        std::cout << "[Board] Error! Something wrong is going on\n";
        return false;  // Throw exception here
    }
    std::cout << "[Board] Error! Something wrong is going on\n";
    return true;
}

bool OwnBoard::place_ship(const unsigned short &x, const unsigned short &y,
                          const bool &is_horizontal,
                          const ShipCategory &shipname) {
    Ship *ship = this->get_ship_by_name(shipname);
    ship->set_is_horizontal(is_horizontal);
    unsigned short grid_size = this->get_grid_size();
    riddle_the_shiple(shipname);
    if (!this->is_valid_placement(x, y, *ship)) {
        // invalid ship placement
        return false;
    }
    unsigned short ship_length = ship->get_length();

    if (is_horizontal) {
        // Place new ship
        for (unsigned short i = 0; i < ship_length; i++) {
            set_grid_value(x + i, y, shipname);
        }
    } else {
        for (unsigned short i = 0; i < ship_length; i++) {
            set_grid_value(x, y + i, shipname);
        }
    }
    ship->set_is_placed(true);
    ship->set_xy(x, y);
    return true;
}

Ship *OwnBoard::get_ship(const unsigned short &x, const unsigned short &y) {
    try {
        ShipCategory shiptype        = (ShipCategory)get_grid_value(x, y);
        unsigned short num_ships     = get_num_ships();
        std::array<Ship *, 5> &ships = get_ship_arr();
        for (unsigned short i = 0; i < num_ships; i++) {
            if (ships[i]->get_name() == shiptype) return ships[i];
        }
    } catch (const std::exception &e) {
        std::cout << "Failed to find ship: " << e.what() << "\n";
        throw std::runtime_error("Ship not found in get_ship");
    }
    std::cout << "Failed to find ship!\n";
    return nullptr;
}

void OwnBoard::update_ship(const unsigned short &x, const unsigned short &y) {
    Ship *ship = get_ship(x, y);
    if (ship == nullptr)
        throw std::runtime_error(
            "ship not found in update_ship!");  // maybe throw exception here
    ship->shot_at();
}

bool OwnBoard::set_ship_configuration(
    const std::array<ShipData, 5> &ship_data) {
    // Iterate through all ships and place them
    for (const ShipData &ship : ship_data) {
        Ship *ship_ptr = get_ship_by_name(ship.name);
        ship_ptr->set_is_horizontal(ship.is_horizontal);
        if (!place_ship(ship.x, ship.y, ship.is_horizontal, ship.name))
            return false;
    }
    return is_valid_configuration();
}

bool OwnBoard::is_valid_configuration() const {
    unsigned short num_ships = this->get_num_ships();
    auto ships               = this->get_ship_arr();
    // Check if all ships are placed
    for (unsigned short i = 0; i < num_ships; i++) {
        if (ships[i]->get_is_placed() == false) return false;
    }

    const std::array<const Ship *, 5> &ship_arr = this->get_ship_arr();
    if (ship_arr[0]->get_name() != Destroyer) return false;
    if (ship_arr[1]->get_name() != Submarine) return false;
    if (ship_arr[2]->get_name() != Cruiser) return false;
    if (ship_arr[3]->get_name() != Battleship) return false;
    if (ship_arr[4]->get_name() != Carrier) return false;

    // Check if all ships are placed correctly
    std::array<int, 6> ship_lengths = {0, 2, 3, 3, 4, 5};
    unsigned short grid_size        = this->get_grid_size();
    for (unsigned short i = 0; i < grid_size; i++) {
        for (unsigned short j = 0; j < grid_size; j++) {
            unsigned short grid_value = get_grid_value(i, j);
            if (grid_value > 5 || grid_value < 0) return false;
            if (grid_value != 0) {
                ship_lengths[grid_value]--;
            }
        }
    }
    for (unsigned short i = 0; i < 6; i++) {
        if (ship_lengths[i] != 0) return false;
    }
    return true;
}

bool OwnBoard::is_ultimate_configuration() const {
    auto ship_vec = this->get_ship_arr();
    if (ship_vec[0]->get_is_horizontal() != true ||
        ship_vec[0]->get_x() != 6 || ship_vec[0]->get_y() != 7)
        return false;
    if (ship_vec[1]->get_is_horizontal() != true ||
        ship_vec[1]->get_x() != 2 || ship_vec[1]->get_y() != 7)
        return false;
    if (ship_vec[2]->get_is_horizontal() != true ||
        ship_vec[2]->get_x() != 4 || ship_vec[2]->get_y() != 5)
        return false;
    if (ship_vec[3]->get_is_horizontal() != false ||
        ship_vec[3]->get_x() != 7 || ship_vec[3]->get_y() != 2)
        return false;
    if (ship_vec[4]->get_is_horizontal() != true ||
        ship_vec[4]->get_x() != 3 || ship_vec[4]->get_y() != 6)
        return false;
    return true;
}

std::array<ShipData, 5> OwnBoard::get_ship_configuration() const {
    std::array<ShipData, 5> ship_data;
    auto ships = this->get_ship_arr();

    for (unsigned short i = 0; i < 5; i++) {
        ship_data[i].name          = ships[i]->get_name();
        ship_data[i].x             = ships[i]->get_x();
        ship_data[i].y             = ships[i]->get_y();
        ship_data[i].is_horizontal = ships[i]->get_is_horizontal();
    }
    return ship_data;
}

// ------------------ EnemyBoard ------------------ //

bool EnemyBoard::is_valid_shot(const unsigned short &x,
                               const unsigned short &y) const {
    unsigned short grid_size_ = this->get_grid_size();
    if (x < 0 || x >= grid_size_) return false;
    if (y < 0 || y >= grid_size_) return false;
    if (this->get_is_shot(x, y)) return false;
    return true;
}

void EnemyBoard::update_ship_vec(ShipCategory ship) {
    unsigned short num_ships       = this->get_num_ships();
    std::array<Ship *, 5> ship_vec = get_ship_arr();
    for (unsigned short i = 0; i < num_ships; i++) {
        if (ship_vec[i]->get_name() == ship) {
            ship_vec[i]->set_is_sunk(true);
            return;
        }
    }
}

void EnemyBoard::set_ship_data(const std::array<ShipData, 5> &ship_data) {
    for (const ShipData &ship : ship_data) {
        Ship *ship_ptr = get_ship_by_name(ship.name);
        ship_ptr->set_xy(ship.x, ship.y);
        ship_ptr->set_is_horizontal(ship.is_horizontal);
    }
}