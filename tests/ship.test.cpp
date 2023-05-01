#include "include/ship.h"

#include "gtest/gtest.h"

TEST(ShipTest, CreateShipDestroyer) {
    ShipCategory dest = Destroyer;
    Ship destroyer(dest);
    EXCEPT_EQ(0, destroyer.name);
    EXCEPT_EQ(0, Destroyer);
    EXCEPT_EQ(2, category_to_size(dest));
    EXCEPT_EQ(2, category_to_size(destroyer.name));
}

TEST(ShipTest, ShootAtShip) {
    ShipCategory sub = Submarine;
    Ship my_ship(sub);
    EXCEPT_EQ(1, sub);
    EXCEPT_EQ(3, category_to_size(sub));
    EXCEPT_EQ(3, category_to_size(my_ship.name));
    EXCEPT_EQ(3, my_ship.remaining_length);
    EXCEPT_EQ(3, my_ship.length);
    EXCEPT_EQ(false, my_ship.is_sunk);
    my_ship.shot_at();
    EXCEPT_EQ(2, my_ship.remaining_length);
    EXCEPT_EQ(3, my_ship.length);
    EXCEPT_EQ(false, my_ship.is_sunk);
    my_ship.shot_at();
    EXCEPT_EQ(1, my_ship.remaining_length);
    EXCEPT_EQ(3, my_ship.length);
    EXCEPT_EQ(false, my_ship.is_sunk);
    my_ship.shot_at();
    EXCEPT_EQ(0, my_ship.remaining_length);
    EXCEPT_EQ(3, my_ship.length);
    EXCEPT_EQ(true, my_ship.is_sunk);
    EXCEPT_THROW(my_ship.shot_at(), std::exception);
}
