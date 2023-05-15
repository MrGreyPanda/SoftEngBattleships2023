#include "board.h"

Board::Board() : grid_size_(10) {
    // ships_.resize(5);
    ships_ = {Ship(Carrier),
    Ship(Battleship),
    Ship(Cruiser),
    Ship(Submarine),
    Ship(Destroyer)};
}

// Board::Board(unsigned short grid_size) : grid_size_(grid_size) {
//     ships_.resize(5);
//     ships_[Carrier]    = Ship(Carrier);
//     ships_[Battleship] = Ship(Battleship);
//     ships_[Cruiser]    = Ship(Cruiser);
//     ships_[Submarine]  = Ship(Submarine);
//     ships_[Destroyer]  = Ship(Destroyer);
//     grid_ = std::vector<std::vector<int>>(grid_size_, std::vector<int>(grid_size_, 0));
//     is_shot_ = std::vector<std::vector<bool>>(grid_size_, std::vector<bool>(grid_size_, false));
// }

Board::~Board() {
    for (int i = 0; i < ships_.size(); i++) {
        delete ships_[i];
    }
    ships_.clear();
}

unsigned short Board::get_grid_size() { return grid_size_; }

unsigned short Board::get_num_active_ships() {
    unsigned short num_active_ships = 0;
    for (int i = 0; i < ships_.size(); i++) {
        if (!ships_[i].get_is_sunk()) num_active_ships++;
    }
    return num_active_ships;
}

unsigned short Board::get_grid_value(const short &x, const short &y) {
    return grid_[y][x];
}

void Board::set_grid_value(const short &x, const short &y, int value) {
    grid_[y][x] = value;
}

bool Board::get_is_shot(const short &x, const short &y) {
    return is_shot_[y][x];
}

void Board::set_is_shot(const short &x, const short &y, bool value) {
    is_shot_[y][x] = value;
}

// OwnBoard::OwnBoard() : Board() {}

// OwnBoard::OwnBoard(unsigned int grid_size_) : Board(grid_size_) {}


// ------------ OwnBoard ------------- //

OwnBoard::~OwnBoard() {}

bool OwnBoard::is_valid_placement(const short &x, const short &y, const Ship &ship) {
    int grid_size_ = this->get_grid_size();
    if (x >= grid_size_ || y >= grid_size_ ||
        x < 0 || y < 0) return false;

    bool is_horizontal = ship.get_is_horizontal();
    short ship_length = ship.get_length();

    if(is_horizontal){
        if(x + ship_length > grid_size_) return false;
        ShipCategory shiptype = ship.get_name();
        for(int i = 0; i < ship_length; i++){
            if(get_grid_value(x + i, y) != 0 && get_grid_value(x + i, y) != shiptype) return false;
        }
        return true;
    }

    else if(!is_horizontal){
        if(y + ship_length > grid_size_) return false;
        ShipCategory shiptype = ship.get_name();

        for(int i = 0; i < ship_length; i++){
            if(get_grid_value(x, y + i) != 0 && get_grid_value(x, y + i) != shiptype) return false;
        }
        return true;
    }
    return false; // Throw exception here
}

bool OwnBoard::place_ship(const short &x, const short &y, Ship &ship) {
    if (!this->is_valid_placement(x, y, ship)) return false;
    bool is_horizontal = ship.get_is_horizontal();
    short ship_length = ship.get_length();
    bool is_placed = ship.get_is_placed();
    short old_x = ship.get_x();
    short old_y = ship.get_y();
    ShipCategory shiptype = ship.get_name();

    if(is_horizontal){
        if(is_placed){
            // Remove old ship
            for(int i = 0; i < ship_length; i++){
                set_grid_value(old_x + i, old_y, 0);
            }
        }
        // Place new ship
        for(int i = 0; i < ship_length; i++){
            set_grid_value(x + i, y, shiptype);
        }
        ship.set_xy(x, y);
        return true;
    }
    else if(!is_horizontal){
        if(is_placed){
            // Remove old ship
            for(int i = 0; i < ship_length; i++){
                set_grid_value(old_x, old_y + i, 0);
            }
        }
        // Place new ship
        for(int i = 0; i < ship_length; i++){
            set_grid_value(x, y + i, shiptype);
        }
        ship.set_xy(x, y);
        return true;
    }
    else return false; // Throw exception here, unexpected behaviour
}

bool OwnBoard::rotate_ship(Ship &ship) {
    bool is_horizontal = ship.get_is_horizontal();
    if(ship.get_is_placed() == true){
        
        short ship_length = ship.get_length();
        short x = ship.get_x();
        short y = ship.get_y();
        ShipCategory shiptype = ship.get_name();
        ship.set_is_horizontal(!is_horizontal);
        if(!this->is_valid_placement(x, y, ship)){
            ship.set_is_horizontal(is_horizontal);
            return false;
        }
        if(is_horizontal){
            // Remove old ship & place new ship
            for(int i = 0; i < ship_length; i++){
                set_grid_value(x + i, y, 0);
                set_grid_value(x, y + i, shiptype);
            }
            return true;
        }
        else if(!is_horizontal){
            // Remove old ship
            for(int i = 0; i < ship_length; i++){
                set_grid_value(x, y + i, 0);
                set_grid_value(x + i, y, shiptype);
            }
            return true;
        }
        else return false; // Throw exception here unexpected behaviour
    }
    else {
        ship.set_is_horizontal(!is_horizontal);
        return true;
    }
}

Ship* OwnBoard::get_ship(const short &x, const short &y){
    ShipCategory shiptype = (ShipCategory) get_grid_value(x, y);
    for(int i = 0; i < ships_.size(); i++){
        if(ships_[i].get_name() == shiptype) return &ships_[i];
    }

    // TODO Throw exception here unexpected behaviour
    return nullptr;
}

bool OwnBoard::all_ships_sunk(){
    for(int i = 0; i < ships_.size(); i++){
        if(ships_[i].get_is_sunk() == false) return false;
    }
    return true;
}

void OwnBoard::update_ship(const short &x, const short &y){
    Ship* ship = get_ship(x, y);
    if(ship == nullptr) return; //maybe throw exception here
    ship->shot_at();
}


// ------------ EnemyBoard ------------- //
EnemyBoard::~EnemyBoard() {}

bool EnemyBoard::is_valid_shot(
    const short &x, const short &y) {
    int grid_size_ = this->get_grid_size();
    if (x < 0 || x > grid_size_) return false;
    if (y < 0 || y > grid_size_) return false;
    if (this->get_is_shot(x, y)) return false;
    return true;
}


void update_ship_vec(ShipCategory ship){
    for(int i = 0; i < ships_.size(); i++){
        if(ships_[i].get_name() == ship){
            ships_[i].set_is_sunk(true)
            return true;
        }
    }
}