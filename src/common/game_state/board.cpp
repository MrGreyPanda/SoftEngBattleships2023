#include "board.h"

Board::Board() : grid_size_(10) {
    ships_ = {new Ship(Destroyer), new Ship(Submarine), new Ship(Cruiser),
              new Ship(Battleship), new Ship(Carrier)};
}

// I should need to use delete here, but I don't know why it doesn't work
Board::~Board() {
    for (int i = 0; i < ships_.size(); i++) {
        if (ships_[i] != nullptr) delete ships_[i];
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
    return grid_[y][x];
}

unsigned short Board::get_num_ships() const { return ships_.size(); }

std::array<Ship *, 5> &Board::get_ship_vec() { return ships_; }

const std::array<const Ship *, 5> Board::get_ship_vec() const {
    std::array<const Ship *, 5> const_ships_pointers{nullptr};
    for (int i = 0; i < 5; i++) {
        const_ships_pointers[i] = (const Ship *)ships_[i];
    }
    return const_ships_pointers;
}

void Board::set_grid_value(const short &x, const short &y, int value) {
    grid_[y][x] = value;
}

bool Board::get_is_shot(const short &x, const short &y) const {
    return is_shot_[y][x];
}

void Board::set_is_shot(const short &x, const short &y, bool value) {
    is_shot_[y][x] = value;
}

Ship *Board::get_ship_by_name(const ShipCategory &type) {
    for (int i = 0; i < ships_.size(); i++) {
        if (ships_[i]->get_name() == type) return ships_[i];
    }
    return nullptr;
}

bool Board::all_ships_sunk() const {
    int num_ships                              = get_num_ships();
    const std::array<const Ship *, 5> &ships_vec = get_ship_vec();
    for (int i = 0; i < num_ships; i++) {
        if (ships_vec.at(i)->get_is_sunk() == false) return false;
    }
    return true;
}


const Ship* Board::get_ship_by_index(const unsigned short &index) const {
    return ships_[index];
}

void Board::reset(){
    for(int i = 0; i < grid_size_; i++){
        for(int j = 0; j < grid_size_; j++){
            grid_[i][j] = 0;
            is_shot_[i][j] = false;
        }
    }
    for(int i = 0; i < ships_.size(); i++){
        if(ships_[i] != nullptr)
            ships_[i]->reset_ship();
    }
    has_been_reset = true;
}


void Board::riddle_the_shiple(const ShipCategory &shipname){
    for(int i = 0; i < grid_size_; i++){
        for(int j = 0; j < grid_size_; j++){
            if(grid_[i][j] == shipname){
               grid_[i][j] = 0;
            }
        }
    }
}
// ------------ OwnBoard ------------- //

bool OwnBoard::is_valid_placement(const short &x, const short &y,
                                  const Ship &ship) const {
    int grid_size_ = this->get_grid_size();
    if (x >= grid_size_ || y >= grid_size_ || x < 0 || y < 0) {
        std::cout << "Invalid coordinates\n";
        return false;
    }

    bool is_horizontal = ship.get_is_horizontal();
    short ship_length  = ship.get_length();
    if (is_horizontal) {
        if (x + ship_length > grid_size_) {
            // the ship doesn't fit in the grid
            std::cout << "Ship doesn't fit in the grid\n";
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
        std::cout << "Ship fits\n";
        return true;
    }

    else if (!is_horizontal) {
        if (y + ship_length > grid_size_){
            std::cout << "Ship to long: " << ship_length + y << "\n";
            return false;
        }
        ShipCategory shiptype = ship.get_name();

        for (int i = 0; i < ship_length; i++) {
            if (get_grid_value(x, y + i) != 0 && get_grid_value(x, y + i) != shiptype){
                std::cout << shiptype << "\n"
                          << "grid value = " << get_grid_value(x, y) << "\n";
                return false;
            }
        }
        std::cout << "Ship fits\n";
        return true;
    }
    else {
        std::cout << "Something wrong is going on\n";
        return false;  // Throw exception here
    }
    std::cout << "Something wrong is going on\n";
    return true;
}

bool OwnBoard::place_ship(const short &x, const short &y, const bool &is_horizontal,
                          const ShipCategory &shipname) {
    Ship *ship = this->get_ship_by_name(shipname);
    ship->set_is_horizontal(is_horizontal);
    unsigned short grid_size = this->get_grid_size();
    for(int i = 0; i < grid_size; i++){
        for(int j = 0; j < grid_size; j++){
            unsigned short grid_value = this->get_grid_value(i, j);
            if(grid_value == shipname){
                this->set_grid_value(i, j, 0);
            }
        }
    }
    if (!this->is_valid_placement(x, y, *ship)) {
        std::cout << "Invalid placement\n"
                  << "Shiptype = " << shipname << "\nx = " << x << "\ny = " << y << "\n";
        return false;
    }
    short ship_length  = ship->get_length();
    bool is_placed     = ship->get_is_placed();
    short old_x        = ship->get_x();
    short old_y        = ship->get_y();

    if(is_horizontal){
        // Place new ship
        for (int i = 0; i < ship_length; i++) {
            set_grid_value(x + i, y, shipname);
        }
    }
    else if (!is_horizontal){
         for(int i = 0; i < ship_length; i++){
            set_grid_value(x, y + i, shipname);
        }
    }
    ship->set_is_placed(true);
    ship->set_xy(x, y);
    return true;
}

// bool OwnBoard::rotate_ship(const unsigned short x, const unsigned short y = 0, const bool &is_horizontal, const ShipCategory &shipname) {
//     Ship *ship         = this->get_ship_by_name(shipname);
//     bool is_horizontal = ship->get_is_horizontal();
//     if (ship->get_is_placed() == true) {
//         short ship_length = ship->get_length();
//         short old_x           = ship->get_x();
//         short old_y           = ship->get_y();

//         // ship->set_is_horizontal(!is_horizontal);
//         // if (!this->is_valid_placement(x, y, *ship)) {
//         //     // ship->set_is_horizontal(is_horizontal);
//         //     return false;
//         // }
//         if (is_horizontal) {
//             // Remove old ship & place new ship
//             for (int i = 0; i < ship_length; i++) {
//                 set_grid_value(old_x + i, old_y, 0);
//                 set_grid_value(x, y + i, shipname);
//             }
//             ship->set_xy(x, y);
//             ship->set_is_horizontal(!is_horizontal);
//             return true;
//         } else if (!is_horizontal) {
//             // Remove old ship
//             for (int i = 0; i < ship_length; i++) {
//                 set_grid_value(old_x, old_y + i, 0);
//                 set_grid_value(x + i, y, shipname);
//             }
//             ship->set_xy(x, y);
//             ship->set_is_horizontal(!is_horizontal);
//             return true;
//         } else
//             return false;  // Throw exception here unexpected behaviour
//     } else {
//         ship->set_is_horizontal(!is_horizontal);

//         return true;
//     }
// }

Ship *OwnBoard::get_ship(const short &x, const short &y) {
    ShipCategory shiptype        = (ShipCategory)get_grid_value(x, y);
    int num_ships                = get_num_ships();
    std::array<Ship *, 5> &ships = get_ship_vec();
    for (int i = 0; i < num_ships; i++) {
        if (ships[i]->get_name() == shiptype) return ships[i];
    }

    // TODO Throw exception here unexpected behaviour
    return nullptr;
}

void OwnBoard::update_ship(const short &x, const short &y) {
    Ship *ship = get_ship(x, y);
    if (ship == nullptr) return;  // maybe throw exception here
    ship->shot_at();
}

bool OwnBoard::set_ship_configuration(
    const std::array<ShipData, 5> &ship_data) {
    // for (Ship *ship_ptr : get_ship_vec()) {
    //     ship_ptr->set_is_placed(false);
    // }
    // for (int i = 0; i < get_grid_size(); i++) {
    //     for (int j = 0; j < get_grid_size(); j++) {
    //         set_grid_value(i, j, 0);
    //     }
    // }
    for (const ShipData &ship : ship_data) {
        std::cout << "[Board] (debug) before placing ship: " << ship.name
                  << ", x=" << ship.x << ", y=" << ship.y
                  << ", is_horizontal=" << ship.is_horizontal << "\n";
        Ship *ship_ptr = get_ship_by_name(ship.name);
        ship_ptr->set_is_horizontal(ship.is_horizontal);
        if (!place_ship(ship.x, ship.y, ship.is_horizontal, ship.name)) return false;
    }
    return true;
}

bool OwnBoard::is_valid_configuration() const {
    int num_ships = this->get_num_ships();
    auto ships    = this->get_ship_vec();
    for (int i = 0; i < num_ships; i++) {
        if (ships[i]->get_is_placed() == false) return false;
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
    // for (int i = 0; i < 6; i++) {
    //     if (ship_lengths[i] != 0) {
    //         std::cout << "Ship " << (ShipCategory)i << " has wrong length!"
    //                   << std::endl;
    //         return false;
    //     }
    // }

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

std::array<ShipData, 5> OwnBoard::get_ship_configuration() const {
    std::array<ShipData, 5> ship_data;
    auto ships = this->get_ship_vec();

    for (int i = 0; i < 5; i++) {
        ship_data[i].name          = ships[i]->get_name();
        ship_data[i].x             = ships[i]->get_x();
        ship_data[i].y             = ships[i]->get_y();
        ship_data[i].is_horizontal = ships[i]->get_is_horizontal();
    }
    return ship_data;
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
    int num_ships                  = this->get_num_ships();
    std::array<Ship *, 5> ship_vec = get_ship_vec();
    for (int i = 0; i < num_ships; i++) {
        if (ship_vec[i]->get_name() == ship) {
            ship_vec[i]->set_is_sunk(true);
            return;
        }
    }
}

void EnemyBoard::set_ship_data(const std::array<ShipData, 5> &ship_data) {
    
    
    for (const ShipData &ship : ship_data) {
        Ship *ship_ptr = get_ship_by_name(ship.name);
        ship_ptr->set_is_horizontal(ship.is_horizontal);
        ship_ptr->set_xy(ship.x, ship.y);
        ship_ptr->set_is_placed(true);
        // unsigned short x = ship.x;
        // unsigned short y = ship.y;
        // unsigned short length = ship_ptr->get_length();
        // for(int i = 0; i < length; i++){
        //     if(ship.is_horizontal){
        //         this->set_grid_value(x+i, y, ship.name);
        //     }else{
        //         this->set_grid_value(x, y+i, ship.name);
        //     }
        // }
    }
}