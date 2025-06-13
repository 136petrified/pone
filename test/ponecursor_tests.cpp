#include <gtest/gtest.h>

#include <cmath>

#include "ponecursor.hpp"

TEST(ponecursor, Constructor) {
    Cursor c1;
    EXPECT_EQ(c1.getX(), 0);
    EXPECT_EQ(c1.getY(), 0);

    Cursor c2{10, 20};
    EXPECT_EQ(c2.getX(), 10);
    EXPECT_EQ(c2.getY(), 20);
}

TEST(ponecursor, X) {
    Cursor c;

    c.setX(2);
    EXPECT_EQ(c.getX(), 2);
}

TEST(ponecursor, Y) {
    Cursor c;

    c.setY(10);
    EXPECT_EQ(c.getY(), 10);
}

TEST(ponecursor, getPos) {
    Cursor c{-3, -7};

    std::pair<int, int> coords = c.getPos();
    EXPECT_EQ(coords.first, -3);
    EXPECT_EQ(coords.second, -7);
}
