#include "board.h"

Board::Board() : grid_size_(10) {
    ships_ = {new Ship(Destroyer), new Ship(Submarine), new Ship(Cruiser),
              new Ship(Battleship), new Ship(Carrier)};
}

// I should need to use delete here, but I don't know why it doesn't work
Board::~Board() {
    for(int i = 0; i < ships_.size(); i++) {
        if(ships_[i] != nullptr) delete ships_[i];
    }
}

const unsigned short Board::get_grid_size() const { return grid_size_; }

// unsigned short Board::get_num_active_ships() {
//     unsigned short num_active_ships = 0;
//     for (int i = 0; i < ships_.size(); i++) {
//         if (!ships_[i]->get_is_sunk()) num_active_ships++;
//     }
//     return num_active_ships;
// }

unsigned short Board::get_grid_value(const short &x, const short &y) const {
    return grid_[x][y];
}

unsigned short Board::get_num_ships() const { return ships_.size(); }

std::array<Ship *, 5> &Board::get_ship_vec() { return ships_; }

const std::array<const Ship *, 5> Board::get_ship_vec() const {
    std::array<const Ship *, 5> const_ships_pointers{nullptr};
    for (int i = 0; i < 5; i++) {
        const_ships_pointers[i] = (const Ship*)ships_[i];
    }
    return const_ships_pointers;
}

void Board::set_grid_value(const short &x, const short &y, int value) {
    grid_[x][y] = value;
}

bool Board::get_is_shot(const short &x, const short &y) const {
    return is_shot_[x][y];
}

void Board::set_is_shot(const short &x, const short &y, bool value) {
    is_shot_[x][y] = value;
}

Ship *Board::get_ship_by_name(const ShipCategory &type) {
    for (int i = 0; i < ships_.size(); i++) {
        if (ships_[i]->get_name() == type) return ships_[i];
    }
    return nullptr;
}

// OwnBoard::OwnBoard() : Board() {}

// OwnBoard::OwnBoard(unsigned int grid_size_) : Board(grid_size_) {}

// ------------ OwnBoard ------------- //

// OwnBoard::~OwnBoard() {
//     auto ships_vec = *this->get_ship_vec();
//     for (int i = 0; i < ships_vec.size(); i++) {
//         delete ships_vec[i];
//     }
//     ships_vec.clear();
// }

bool OwnBoard::is_valid_placement(const short &x, const short &y,
                                  const Ship &ship) const {
    int grid_size_ = this->get_grid_size();
    if (x >= grid_size_ || y >= grid_size_ || x < 0 || y < 0) return false;

    bool is_horizontal = ship.get_is_horizontal();
    short ship_length  = ship.get_length();
    if (is_horizontal) {
        if (x + ship_length > grid_size_) {
            // the ship doesn't fit in the grid
            return false;
        }
        ShipCategory shiptype = ship.get_name();
        for (int i = 0; i < ship_length; i++) {
            if (get_grid_value(x + i, y) != 0 &&
                get_grid_value(x + i, y) != shiptype) {
                std::cout << shiptype << "\n"
                          << "grid value = " << get_grid_value(x, y) << "\n";
                return false;
            }
        }
        return true;
    }

    else if (!is_horizontal) {
        if (y + ship_length > grid_size_) return false;
        ShipCategory shiptype = ship.get_name();

        for (int i = 0; i < ship_length; i++) {
            if (get_grid_value(x, y + i) != 0 &&
                get_grid_value(x, y + i) != shiptype)
                return false;
        }
        return true;
    }
    return false;  // Throw exception here
}

bool OwnBoard::place_ship(const short &x, const short &y,
                          const ShipCategory &shipname) {
    Ship *ship = this->get_ship_by_name(shipname);
    if (!this->is_valid_placement(x, y, *ship)) {
        std::cout << "Invalid placement\n"
                  << shipname << "\nx = " << x << "\ny = " << y << "\n";
        return false;
    }
    bool is_horizontal = ship->get_is_horizontal();
    short ship_length  = ship->get_length();
    bool is_placed     = ship->get_is_placed();
    short old_x        = ship->get_x();
    short old_y        = ship->get_y();

    if (is_horizontal) {
        if (is_placed) {
            // Remove old ship
            for (int i = 0; i < ship_length; i++) {
                set_grid_value(old_x + i, old_y, 0);
            }
        }
        // Place new ship
        for (int i = 0; i < ship_length; i++) {
            set_grid_value(x + i, y, shipname);
        }
        ship->set_xy(x, y);
        return true;
    } else if (!is_horizontal) {
        if (is_placed) {
            // Remove old ship
            for (int i = 0; i < ship_length; i++) {
                set_grid_value(old_x, old_y + i, 0);
            }
        }
        // Place new ship
        for (int i = 0; i < ship_length; i++) {
            set_grid_value(x, y + i, shipname);
        }
        ship->set_xy(x, y);
        return true;
    } else
        return false;  // Throw exception here, unexpected behaviour
}

bool OwnBoard::rotate_ship(const ShipCategory &shipname) {
    Ship *ship         = this->get_ship_by_name(shipname);
    bool is_horizontal = ship->get_is_horizontal();
    if (ship->get_is_placed() == true) {
        short ship_length = ship->get_length();
        short x           = ship->get_x();
        short y           = ship->get_y();

        ship->set_is_horizontal(!is_horizontal);
        if (!this->is_valid_placement(x, y, *ship)) {
            ship->set_is_horizontal(is_horizontal);
            return false;
        }
        if (is_horizontal) {
            // Remove old ship & place new ship
            for (int i = 0; i < ship_length; i++) {
                set_grid_value(x + i, y, 0);
                set_grid_value(x, y + i, shipname);
            }
            return true;
        } else if (!is_horizontal) {
            // Remove old ship
            for (int i = 0; i < ship_length; i++) {
                set_grid_value(x, y + i, 0);
                set_grid_value(x + i, y, shipname);
            }
            return true;
        } else
            return false;  // Throw exception here unexpected behaviour
    } else {
        ship->set_is_horizontal(!is_horizontal);

        return true;
    }
}

Ship *OwnBoard::get_ship(const short &x, const short &y) {
    ShipCategory shiptype          = (ShipCategory)get_grid_value(x, y);
    int num_ships                  = get_num_ships();
    std::array<Ship *, 5> &ships_vec = get_ship_vec();
    for (int i = 0; i < num_ships; i++) {
        if (ships_vec[i]->get_name() == shiptype) return ships_vec[i];
    }

    // TODO Throw exception here unexpected behaviour
    return nullptr;
}

bool OwnBoard::all_ships_sunk() const {
    int num_ships                              = get_num_ships();
    const std::array<const Ship *, 5> &ships_vec = get_ship_vec();
    for (int i = 0; i < num_ships; i++) {
        if (ships_vec.at(i)->get_is_sunk() == false) return false;
    }
    return true;
}

void OwnBoard::update_ship(const short &x, const short &y) {
    Ship *ship = get_ship(x, y);
    if (ship == nullptr) return;  // maybe throw exception here
    ship->shot_at();
}

bool OwnBoard::set_ship_configuration(const std::vector<ShipData> &ships) {
    // for (Ship *ship_ptr : get_ship_vec()) {
    //     ship_ptr->set_is_placed(false);
    // }
    // for (int i = 0; i < get_grid_size(); i++) {
    //     for (int j = 0; j < get_grid_size(); j++) {
    //         set_grid_value(i, j, 0);
    //     }
    // }
    for (const ShipData &ship : ships) {
        std::cout << "[Board] (debug) before placing ship: " << ship.name
                  << ", x=" << ship.x << ", y=" << ship.y
                  << ", is_horizontal=" << ship.is_horizontal << "\n";
        Ship *ship_ptr = get_ship_by_name(ship.name);
        ship_ptr->set_is_horizontal(ship.is_horizontal);
        if (!place_ship(ship.x, ship.y, ship.name)) return false;
    }
    return true;
}

bool OwnBoard::is_valid_configuration() const {
    int num_ships  = this->get_num_ships();
    auto ships_vec = this->get_ship_vec();
    for (int i = 0; i < num_ships; i++) {
        if (ships_vec[i]->get_is_placed() == false) return false;
    }
    std::array<int, 6> ship_lengths = {0, 2, 3, 3, 4, 5};
    short grid_size                 = this->get_grid_size();
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            int grid_value = get_grid_value(i, j);
            if (grid_value > 5 || grid_value < 0) return false;
            if (grid_value != 0) {
                ship_lengths[grid_value]--;
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        if (ship_lengths[i] != 0) {
            std::cout << "Ship " << (ShipCategory)i << " has wrong length!"
                      << std::endl;
            return false;
        }
    }

    return true;
}

bool OwnBoard::is_ultimate_configuration() const {
    auto ship_vec = this->get_ship_vec();
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

// ------------ EnemyBoard ------------- //
// EnemyBoard::~EnemyBoard() {
//     auto ship_vec = *this->get_ship_vec();
//     for (auto ship : ship_vec) {
//         delete ship;
//     }
//     ship_vec.clear();
// }

bool EnemyBoard::is_valid_shot(const short &x, const short &y) const {
    int grid_size_ = this->get_grid_size();
    if (x < 0 || x > grid_size_) return false;
    if (y < 0 || y > grid_size_) return false;
    if (this->get_is_shot(x, y)) return false;
    return true;
}

void EnemyBoard::update_ship_vec(ShipCategory ship) {
    int num_ships                = this->get_num_ships();
    std::array<Ship *, 5> ship_vec = get_ship_vec();
    for (int i = 0; i < num_ships; i++) {
        if (ship_vec[i]->get_name() == ship) {
            ship_vec[i]->set_is_sunk(true);
            return;
        }
    }
}