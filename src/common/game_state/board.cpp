#include "board.h"

Board::Board(unsigned short size_) : size(size_) {
    ships.resize(5);
    ships[Carrier] = Ship(Carrier);
    ships[Battleship] = Ship(Battleship);
    ships[Cruiser] = Ship(Cruiser);
    ships[Submarine] = Ship(Submarine);
    ships[Destroyer] = Ship(Destroyer);
}

// Board::Board(unsigned short size_, unsigned short n_ships) : size(size_) {
//     ships.resize(n_ships);
// }

bool OwnShip::is_valid_placement(const std::pair<unsigned short, unsigned short> &coords[]){
    for(int i = 0; i < coords.size; i++){
        if(coords[i].first < 0 || coords[i].first > this.size) return false;
        if(coords[i].second < 0 || coords[i].second > this.size) return false;
    }
    return true;
}

bool OwnShip::place_ship(const std::pair<unsigned short, unsigned short> &coords[][], ShipCategory shiptype){
    if(!this.is_valid_placement(coords)) return false;
    
    for()
    for(int i = 0; i < coords.size(); i++){

    }

}

bool OwnShip::rotate_ship(std::pair<unsigned short, unsigned short> &coords[][]){

}
