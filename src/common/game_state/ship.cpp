#include "ship.h"

const unsigned short category_to_size(const ShipCategory &type) {
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

// Constructors
Ship::Ship(const ShipCategory &name_)
    : name_(name_),
      is_sunk_(false),
      is_placed_(false),
      is_horizontal_(true),
      length_(category_to_size(name_)) {}

Ship::Ship(const ShipData &data)
    : name_(data.name),
      is_sunk_(false),
      is_placed_(true),
      is_horizontal_(data.is_horizontal),
      x_(data.x),
      y_(data.y),
      length_(category_to_size(data.name)) {
    damage_ = 0;
}

Ship::Ship()
    : name_(Destroyer),
      is_sunk_(false),
      length_(2),
      damage_(0),
      is_placed_(false),
      is_horizontal_(true) {}

void Ship::shot_at() {
    assert(damage_ <= length_ && !is_sunk_);
    if (damage_ <= 0 || is_sunk_ || damage_ > length_) {
    }
    ++damage_;
    if (damage_ == length_) {
        is_sunk_ = true;
        std::cout << "Your " << name_ << " has been sunk!\n";
    }
}

unsigned short Ship::get_length() const { return length_; }

unsigned short Ship::get_damage() const { return damage_; }

ShipCategory Ship::get_name() const { return name_; }

bool Ship::get_is_sunk() const { return is_sunk_; }

void Ship::set_is_sunk(bool is_sunk) {
    assert(damage_ = length_);
    is_sunk_ = is_sunk;
}

bool Ship::get_is_horizontal() const { return is_horizontal_; }

void Ship::set_is_horizontal(bool is_horizontal) {
    is_horizontal_ = is_horizontal;
}

bool Ship::get_is_placed() const { return is_placed_; }

void Ship::set_is_placed(bool is_placed) { is_placed_ = is_placed; }

short Ship::get_x() const { return x_; }

short Ship::get_y() const { return y_; }

void Ship::set_xy(const unsigned short &x, const unsigned short &y) {
    x_ = x;
    y_ = y;
    set_is_placed(true);
}

ShipData Ship::get_data() const {
    ShipData ship_data;
    ship_data.name          = name_;
    ship_data.is_horizontal = is_horizontal_;
    ship_data.x             = x_;
    ship_data.y             = y_;

    return ship_data;
}

ShipData::ShipData(const ShipCategory &name, const bool &is_horizontal,
                   const unsigned short &x, const unsigned short &y)
    : name(name), is_horizontal(is_horizontal), x(x), y(y) {}

bool ShipData::operator==(const ShipData &other) const {
    return name == other.name && is_horizontal == other.is_horizontal &&
           x == other.x && y == other.y;
}

void from_json(const json &j, ShipData &data) {
    j.at("name").get_to(data.name);
    j.at("is_horizontal").get_to(data.is_horizontal);
    j.at("x").get_to(data.x);
    j.at("y").get_to(data.y);
}

void to_json(json &j, const ShipData &data) {
    j = json{{"name", data.name},
             {"is_horizontal", data.is_horizontal},
             {"x", data.x},
             {"y", data.y}};
}

void Ship::reset_ship() {
    is_sunk_       = false;
    is_placed_     = false;
    is_horizontal_ = true;
    damage_        = 0;
    x_             = 0;
    y_             = 0;
}