#include <gtest/gtest.h>

#include "poneavl.hpp"

TEST(AVL, Constructor) {
    AVL<int> tree;

    EXPECT_TRUE(tree.empty());
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

    tree.printInorder();
}
