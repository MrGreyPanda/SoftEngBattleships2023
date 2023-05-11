#include "ship.h"
/*
The class attributes are:
length_: short, defines the length_ of the ship, for example 5, 4, 3, 2
is_sunk_: bool, defines if the ship has sunk (TRUE) or not (FALSE), this is the
case when ship_coord is empty damage_: short, holds remaining length_ of the
ship, gets updated by shot_at

The class operations are:
shot_at, void, updates damage_ and checks is_sunk_, then sets the value
accordingly.
*/

// // Constructor
// Ship::Ship(unsigned int length_, ShipCategory name_) : length_(length_),
// name_(name_), is_sunk_(false) {
//     damage_ = length_;
// }

unsigned short category_to_size(ShipCategory type) {
    switch (type) {
        case Carrier:
            return 5;
        case Battleship:
            return 4;
        case Cruiser:
            return 3;
        case Submarine:
            return 3;
        case Destroyer:
            return 2;
        default:
            return 0;
    }
}

// Constructor
Ship::Ship(ShipCategory name_) : name_(name_), is_sunk_(false), is_placed_(false), is_horizontal_(false){
    length_ = category_to_size(name_);
    // if(length_ == 0) throw std::runtime_error(std::string("Not a valid
    // ShipCategory"));
    damage_ = length_;
}

Ship::Ship() : name_(Destroyer), is_sunk_(false), length_(2), damage_(0), is_placed_(false), is_horizontal_(false){}

Ship::~Ship() {
    // Nothing to do here
}

void Ship::shot_at() {
    if (damage_ <= 0 || is_sunk_) {
        // throw std::exception("This ship is already sunk and therefore can't
        // be shot at. Invalid shot.");
    }
    --damage_;
    if (damage_ == 0) {
        is_sunk_ = true;
        // std::cout << "Your " << name_ << " has been sunk!\n";
    }
}

unsigned short Ship::get_length() const { return length_; }

unsigned short Ship::get_damage() const { return damage_; }

ShipCategory Ship::get_name() const { return name_; }

bool Ship::get_is_sunk() const { return is_sunk_; }

bool Ship::get_is_horizontal() const{
    return is_horizontal_;
}

void Ship::set_is_horizontal(bool is_horizontal){
    is_horizontal_ = is_horizontal;
}

bool Ship::get_is_placed() const{
    return is_placed_;
}

void Ship::set_is_placed(bool is_placed){
    is_placed_ = is_placed;
}

short Ship::get_x() const{
    return x_;
}

short Ship::get_y() const{
    return y_;
}

void Ship::set_xy(const short &x, const short &y){
    x_ = x;
    y_ = y;
    set_is_placed(true);
}