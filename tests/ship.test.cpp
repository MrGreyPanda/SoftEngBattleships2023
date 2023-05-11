#include "ship.h"

#include "gtest/gtest.h"

TEST(ShipTest, CreateShipDestroyer) {
    ShipCategory dest = Destroyer;
    Ship destroyer(dest);
    EXPECT_EQ(Destroyer, destroyer.get_name());
    EXPECT_EQ(1, Destroyer);
    EXPECT_EQ(2, category_to_size(dest));
    EXPECT_EQ(2, category_to_size(destroyer.get_name()));
}

TEST(ShipTest, ShootAtShip) {
    ShipCategory sub = Submarine;
    Ship my_ship(sub);
    EXPECT_EQ(2, sub);
    EXPECT_EQ(2, Submarine);
    EXPECT_EQ(3, category_to_size(sub));
    EXPECT_EQ(3, category_to_size(my_ship.get_name()));
    EXPECT_EQ(3, my_ship.get_damage());
    EXPECT_EQ(3, my_ship.get_length());
    EXPECT_EQ(false, my_ship.get_is_sunk());
    my_ship.shot_at();
    EXPECT_EQ(2, my_ship.get_damage());
    EXPECT_EQ(3, my_ship.get_length());
    EXPECT_EQ(false, my_ship.get_is_sunk());
    my_ship.shot_at();
    EXPECT_EQ(1, my_ship.get_damage());
    EXPECT_EQ(3, my_ship.get_length());
    EXPECT_EQ(false, my_ship.get_is_sunk());
    my_ship.shot_at();
    EXPECT_EQ(0, my_ship.get_damage());
    EXPECT_EQ(3, my_ship.get_length());
    EXPECT_EQ(true, my_ship.get_is_sunk());
}

TEST(ShipTest, ChangeOrientation){
    ShipCategory sub = Submarine;
    Ship my_ship(sub);
    EXPECT_EQ(2, sub);
    EXPECT_EQ(2, Submarine);
    EXPECT_EQ(3, category_to_size(sub));
    EXPECT_EQ(3, category_to_size(my_ship.get_name()));
    EXPECT_EQ(3, my_ship.get_damage());
    EXPECT_EQ(3, my_ship.get_length());
    EXPECT_EQ(false, my_ship.get_is_sunk());
    my_ship.shot_at();
    EXPECT_EQ(2, my_ship.get_damage());
    EXPECT_EQ(3, my_ship.get_length());
    EXPECT_EQ(false, my_ship.get_is_sunk());
    my_ship.shot_at();
    EXPECT_EQ(1, my_ship.get_damage());
    EXPECT_EQ(3, my_ship.get_length());
    EXPECT_EQ(false, my_ship.get_is_sunk());
    my_ship.shot_at();
    EXPECT_EQ(0, my_ship.get_damage());
    EXPECT_EQ(3, my_ship.get_length());
    EXPECT_EQ(true, my_ship.get_is_sunk());
}