#include <gtest/gtest.h>
#include <vector>

#include "game/pone_avl.hpp"
using namespace pone;

TEST(avl_test, Constructor) {
    AVL<int> tree;
    EXPECT_TRUE(tree.empty());
}

TEST(avl_test, Insert) {
    AVL<int> tree;

    tree.insert(5);
    tree.insert(8);
    tree.insert(7);
    tree.insert(2);
    tree.insert(1);
    tree.insert(0);
    tree.insert(8);
    tree.insert(9);
    tree.insert(4);
    tree.insert(3);

    std::vector<int> solution = {0, 2, 3, 4, 5, 6, 7, 8, 9};

    EXPECT_EQ(solution, tree.preorder());
}
