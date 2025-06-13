#include <gtest/gtest.h>

#include "ponetile.hpp"

TEST(ponetile, Constructor) {
    Tile t;
    EXPECT_EQ(t.getX(), 0);
    EXPECT_EQ(t.getY(), 0);
    EXPECT_TRUE(t.isEmpty());
}

TEST(ponetile, X) {
    Tile t;
    t.setX(3);
    EXPECT_EQ(t.getX(), 3);

    t.setX(-2);
    EXPECT_EQ(t.getX(), -2);
}

// Test comment
