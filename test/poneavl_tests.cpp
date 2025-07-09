#include <gtest/gtest.h>

#include "poneavl.hpp"
#include "ponetile.hpp"

TEST(AVL, Constructor) {
    AVL<Tile> tree;

    EXPECT_TRUE(tree.empty());
}

TEST(AVL, Insert) {
    AVL<Tile> tree;

    Tile t1{3, 6, "red", "collision"};
    Tile t2{2, 0, "yellow", "gswitch"};
    Tile t3{2, 4, "yellow", "empty"};
    Tile t4{8, 12, "violet", "goal"};
    Tile t5{22, 14, "none", "collision"};
    Tile t6{29, 2, "beige", "tswitch"};

    tree.insert(t1);
    tree.insert(t2);
    tree.insert(t3);
    tree.insert(t4);
    tree.insert(t5);
    tree.insert(t6);

    std::vector<Tile> expected{t2, t3, t1, t4, t5, t6};
    EXPECT_EQ(expected, tree.preorder(expected));
}
