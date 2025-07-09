#include <gtest/gtest.h>

#include "poneavl.hpp"
#include "ponetile.hpp"

TEST(AVL, Constructor) {
    AVL<int> tree;

    EXPECT_TRUE(tree.empty());

    AVL<Tile> tileTree;

    EXPECT_TRUE(tileTree.empty());
}

TEST(AVL, Insert) {
    AVL<int> tree;

    tree.insert(20);
    tree.insert(-5);
    tree.insert(92);
    tree.insert(43);
    tree.insert(-17);
    tree.insert(58);
    tree.insert(-29);

    std::vector<int> expected = {-29, -17, -5, 20, 43, 58, 92};
    EXPECT_EQ(expected, tree.inorder());

    AVL<Tile> tileTree;

    Tile t1{5, 4, "purple", "collision"};
    Tile t2{1, 9, "green", "empty"};
    Tile t3{13, 1, "none", "tswitch"};
    Tile t4{2, 30, "red", "gswitch"};
    Tile t5{5, 0, "none", "key"};
    Tile t6{3, 3, "gray", "collision"};
    Tile t7{46, 4, "none", "goal"};

    tileTree.insert(t1);
    tileTree.insert(t2);
    tileTree.insert(t3);
    tileTree.insert(t4);
    tileTree.insert(t5);
    tileTree.insert(t6);
    tileTree.insert(t7);

    std::vector<Tile> tileExpected = {t2, t4, t6, t5, t1, t3, t7};
    EXPECT_EQ(tileExpected, tileTree.inorder());
}
