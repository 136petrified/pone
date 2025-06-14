#include <gtest/gtest.h>

#include "poneboard.hpp"

TEST(poneboard, Constructor) {
    Board b1;
    EXPECT_EQ(b1.getLength(), 0);
    EXPECT_EQ(b1.getWidth(), 0);
    EXPECT_EQ(b1.getCurrentTile(), nullptr);

    Board b2{5, 4};
    EXPECT_EQ(b2.getLength(), 5);
    EXPECT_EQ(b2.getWidth(), 4);
}

TEST(poneboard, Length) {
    Board b;
    b.setLength(23);
    EXPECT_EQ(b.getLength(), 23);
}

TEST(poneboard, Width) {
    Board b;
    b.setWidth(-1);
    EXPECT_EQ(b.getWidth(), -1);
}

TEST(poneboard, CurrentTile) {
    Board b;
    Tile *t1 = &Tile{4, 0, "none", "empty"};
    b.setCurrentTile(t1);
    EXPECT_EQ(b.getCurrentTile(), t1);
}
