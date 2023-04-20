#include "board.h"

Board::Board(unsigned short size_) : size(size_) {}

Board::Board(unsigned short size_, unsigned short n_ships) : size(size_) {
    ships.resize(n_ships);
}

bool OwnShip::is_valid_placement(const std::pair<unsigned short> &coords[]){
    for(int i = 0; i < coords.size; i++){
        if(coords[i].first < 0 || coords[i].first > this.size) return false;
        if(coords[i].second < 0 || coords[i].second > this.size) return false;
    }
    return true;
}

bool OwnShip::place_ship(const std::pair<unsigned short> &coords[][]){
    if(!this.is_valid_placement(coords)) return false;
    

}

bool OwnShip::rotate_ship(std::pair<unsigned short> &coords[][]){

}
