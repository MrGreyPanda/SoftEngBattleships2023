#include "board.h"

Board::Board() : size(10) {
    ships.resize(5);
    ships[Carrier] = Ship(Carrier);
    ships[Battleship] = Ship(Battleship);
    ships[Cruiser] = Ship(Cruiser);
    ships[Submarine] = Ship(Submarine);
    ships[Destroyer] = Ship(Destroyer);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            grid[i][j] = 0;
            is_shot[i][j] = false;
        }
    }
}

Board::Board(unsigned short size_) : size(size_) {
    ships.resize(5);
    ships[Carrier] = Ship(Carrier);
    ships[Battleship] = Ship(Battleship);
    ships[Cruiser] = Ship(Cruiser);
    ships[Submarine] = Ship(Submarine);
    ships[Destroyer] = Ship(Destroyer);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            grid[i][j] = 0;
            is_shot[i][j] = false;
        }
    }
}



bool OwnBoard::is_valid_placement(const std::pair<unsigned short, unsigned short> &coords[], ShipCategory shiptype){
    if(coords.size() != category_to_size(shiptype)) return false;
    for(int i = 0; i < coords.size(); i++){
        unsigned short x = coords[i].first;
        unsigned short y = coords[i].second;
        if(x < 0 || x > size) return false;
        if(y < 0 || y > size) return false;
        if(grid[x][y] != 0 && grid[x][y] != shiptype) return false;
    }
    return true;
}

bool OwnBoard::place_ship(const std::pair<unsigned short, unsigned short> &coords[], ShipCategory shiptype){

    if(!this.is_valid_placement(coords)) return false;
    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(grid[i][j] == shiptype) grid[i][j] = 0;
        }
    }
    for(int i = 0; i < coords.size(); i++){
        grid[coords[i].first][coords[i].second] = shiptype;
    }

}

bool OwnBoard::rotate_ship(std::pair<unsigned short, unsigned short> &coords[], ShipCategory shiptype){
    if(coords.size() != category_to_size(shiptype)) throw std::exception("Coordinate size doesn't match shiptype!");
    bool is_rotated = false;
    std::pair<unsigned short, unsigned short> new_coords[coords.size()];
    int x = coords[0].first;
    int y = coords[0].second;
    new_coords[0] = std::make_pair<unsigned short, unsigned short>(x, y);
    is_rotated = coords[1].first != x;

    if(is_rotated){
        for(int i = 1; i < coords.size(); i++){
            new_coords[i] = std
        }
    }
}

bool EnemyBoard::is_valid_shot(const std::pair<unsigned short, unsigned short> &coord){
    unsigned short x = coord.first;
    unsigned short y = coord.second;
    if(x < 0 || x > size) return false;
    if(y < 0 || y > size) return false;
    if(is_shot[x][y]) return false;
    return true;
}
