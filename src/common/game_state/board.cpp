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
            shots[i][j] = false;
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
            shots[i][j] = false;
        }
    }
}



bool OwnShip::is_valid_placement(const std::pair<unsigned short, unsigned short> &coords[], ShipCategory shiptype){
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

bool OwnShip::place_ship(const std::pair<unsigned short, unsigned short> &coords[], ShipCategory shiptype){

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

bool OwnShip::rotate_ship(std::pair<unsigned short, unsigned short> &coords[], ShipCategory shiptype){
    std::pair<unsigned short, unsigned short> new_coords[coords.size()];
    
}
