#include <gtest/gtest.h>

#include "ponegate.hpp"
#include "ponetile.hpp"

TEST(ponegate, Constructor) {
    Gate g1;
    GATE tilePair = g1.getGate();
    EXPECT_EQ(tilePair.first, nullptr);
    EXPECT_EQ(tilePair.second, nullptr);

    Gate g2{Tile{2, 3, "none", "empty"}, Tile{4, 5, "none", "empty"}};

    Tile *t1 = g2.getTile1();
    EXPECT_EQ(t1->getX(), 2);
    EXPECT_EQ(t1->getY(), 3);

    Tile *t2 = g2.getTile2();
    EXPECT_EQ(t2->getX(), 4);
    EXPECT_EQ(t2->getY(), 5);
}
