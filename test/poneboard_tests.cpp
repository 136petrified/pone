#include <gtest/gtest.h>

#include "poneboard.hpp"

TEST(poneboard, Constructor) {
    Board b;
    
    EXPECT_EQ(b.getLength(), 0);
    EXPECT_EQ(b.getWidth(), 0);
    EXPECT_EQ(b.getCurrentTile(), nullptr);
}