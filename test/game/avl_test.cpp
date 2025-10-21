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
    tree.insert(7);
    tree.insert(2);
    tree.insert(1);
    tree.insert(0);
    tree.insert(8);
    tree.insert(9);
    tree.insert(4);
    tree.insert(3);
    tree.insert(6);

    std::vector<int> solution = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    EXPECT_EQ(solution, tree.inorder());
}

TEST(avl_test, Find) {
    AVL<int> tree;

    tree.insert(5);
    tree.insert(7);
    tree.insert(2);
    tree.insert(1);
    tree.insert(0);
    tree.insert(8);
    tree.insert(9);
    tree.insert(4);
    tree.insert(3);
    tree.insert(6);

    for (int i = 0; i < 10; ++i)
        EXPECT_NE(tree.find(i), nullptr);
}

TEST(avl_test, Remove) {
    AVL<int> tree;

    tree.insert(5);
    tree.insert(7);
    tree.insert(2);
    tree.insert(1);
    tree.insert(0);
    tree.insert(8);
    tree.insert(9);
    tree.insert(4);
    tree.insert(3);
    tree.insert(6);

    tree.remove(0);
    tree.remove(9);
    tree.remove(1);
    tree.remove(5);
    tree.remove(4);
    tree.remove(7);

    std::vector<int> solution = {2, 3, 6, 8};

    EXPECT_EQ(solution, tree.inorder());

    tree.remove(2);
    tree.remove(8);
    tree.remove(3);
    tree.remove(6);

    EXPECT_TRUE(tree.empty());
}

TEST(avl_test, Less) {
    AVLNode<int> node{-4};
    EXPECT_TRUE(node.less(-4, 7));
}

TEST(avl_test, Equal) {
    AVLNode<int> node{-4};
    EXPECT_TRUE(node.equal(-4, -4));
}

TEST(avl_test, Greater) {
    AVLNode<int> node{-4};
    EXPECT_TRUE(node.greater(-4, -7));
}
