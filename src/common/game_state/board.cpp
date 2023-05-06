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

Board::~Board() {}

unsigned short Board::get_grid_size() { return grid_size_; }

unsigned short Board::get_num_active_ships() {
    unsigned short num_active_ships = 0;
    for (int i = 0; i < ships_.size(); i++) {
        if (!ships_[i].get_is_sunk()) num_active_ships++;
    }
    return num_active_ships;
}

unsigned short Board::get_grid_value(const std::pair<unsigned short, unsigned short> &coord) {
    return grid_[coord.first][coord.second];
}

void Board::set_grid_value(const std::pair<unsigned short, unsigned short> &coord, int value) {
    grid_[coord.first][coord.second] = value;
}

bool Board::get_is_shot(const std::pair<unsigned short, unsigned short> &coord) {
    return is_shot_[coord.first][coord.second];
}

// OwnBoard::OwnBoard() : Board() {}

// OwnBoard::OwnBoard(unsigned int grid_size_) : Board(grid_size_) {}

OwnBoard::~OwnBoard() {}

bool OwnBoard::is_valid_placement(
    const std::vector<std::pair<unsigned short, unsigned short>> &coords,
    const ShipCategory &shiptype) {
    if (coords.size() != category_to_size(shiptype)) return false;
    // throw an error or something like that here

    int grid_size_ = this->get_grid_size();
    for (int i = 0; i < coords.size(); i++) {
        unsigned short x = coords[i].first;
        unsigned short y = coords[i].second;
        if (x < 0 || x > grid_size_) return false;
        if (y < 0 || y > grid_size_) return false;
        int curr_grid_value = get_grid_value(std::make_pair(x, y));
        if (curr_grid_value != 0 && curr_grid_value != shiptype) return false;
    }
    return true;
}

bool OwnBoard::place_ship(
    const std::vector<std::pair<unsigned short, unsigned short>> &coords,
    const ShipCategory &shiptype) {
    if (!this->is_valid_placement(coords, shiptype)) return false;
    int grid_size_ = this->get_grid_size();
    for (int i = 0; i < grid_size_; i++) {
        for (int j = 0; j < grid_size_; j++) {
            int curr_grid_value = get_grid_value(std::make_pair(i, j));
            if (curr_grid_value == shiptype) set_grid_value(std::make_pair(i, j), 0);
        }
    }
    for (int i = 0; i < coords.size(); i++) {
        set_grid_value(coords[i], shiptype);
    }
    return true;
}

bool OwnBoard::rotate_ship(
    std::vector<std::pair<unsigned short, unsigned short>> &coords,
    const ShipCategory &shiptype) {
    // if(coords.size() != category_to_size(shiptype)) throw
    // std::exception("Coordinate grid_size_ doesn't match shiptype!");
    bool is_rotated = false;
    int x         = coords[0].first;
    int y         = coords[0].second;
    is_rotated    = coords[1].first != x;

    int coords_size = coords.size();
    if (is_rotated) {
        if(coords_size + x > this->get_grid_size()) return false;
        for (int i = 1; i < coords.size(); i++) {
            coords[i] =
                std::make_pair<unsigned short, unsigned short>(x, y + i);
        }
    } else if(!is_rotated){
        if(coords_size + y > this->get_grid_size()) return false;
        for (int i = 1; i < coords.size(); i++) {
            coords[i] =
                std::make_pair<unsigned short, unsigned short>(x + i, y);
        }
    }
    else return false;
    return true;
}

// EnemyBoard::EnemyBoard() : Board() {}

// EnemyBoard::EnemyBoard(unsigned int grid_size_) : Board(grid_size_) {}

EnemyBoard::~EnemyBoard() {}

bool EnemyBoard::is_valid_shot(
    const std::pair<unsigned short, unsigned short> &coord) {
    unsigned short x = coord.first;
    unsigned short y = coord.second;
    int grid_size_        = this->get_grid_size();
    if (x < 0 || x > grid_size_) return false;
    if (y < 0 || y > grid_size_) return false;
    if (this->get_is_shot(coord)) return false;
    return true;
}
