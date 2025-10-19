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
    EXPECT_EQ(7, tree.size());

    AVL<Tile> tileTree;

    Tile t1{"t1", 1, 5, 4, "purple", "collision", false};
    Tile t2{"t2", 2, 1, 9, "green", "empty", true};
    Tile t3{"t3", 3, 13, 1, "none", "tswitch", false};
    Tile t4{"t4", 4, 2, 30, "red", "gswitch", false};
    Tile t5{"t5", 5, 5, 0, "none", "key", false};
    Tile t6{"t6", 6, 3, 3, "gray", "collision", false};
    Tile t7{"t7", 7, 46, 4, "none", "goal", false};

    tileTree.insert(t1);
    tileTree.insert(t2);
    tileTree.insert(t3);
    tileTree.insert(t4);
    tileTree.insert(t5);
    tileTree.insert(t6);
    tileTree.insert(t7);

    std::vector<Tile> tileExpected = {t2, t4, t6, t5, t1, t3, t7};
    EXPECT_EQ(tileExpected, tileTree.inorder());
    EXPECT_EQ(7, tileTree.size());
}

TEST(AVL, Remove) {
    AVL<int> tree;

    tree.insert(20);
    tree.insert(-5);
    tree.insert(92);
    tree.insert(43);
    tree.insert(-17);
    tree.insert(58);
    tree.insert(-29);

    tree.remove(43);
    tree.remove(92);
    tree.remove(-5);
    tree.remove(-29);

    std::vector<int> expected = {-17, 20, 58};
    EXPECT_EQ(expected, tree.inorder());
    EXPECT_EQ(3, tree.size());

    AVL<Tile> tileTree;

    Tile t1{"t1", 1, 5, 4, "purple", "collision", false};
    Tile t2{"t2", 2, 1, 9, "green", "empty", true};
    Tile t3{"t3", 3, 13, 1, "none", "tswitch", false};
    Tile t4{"t4", 4, 2, 30, "red", "gswitch", false};
    Tile t5{"t5", 5, 5, 0, "none", "key", false};
    Tile t6{"t6", 6, 3, 3, "gray", "collision", false};
    Tile t7{"t7", 7, 46, 4, "none", "goal", false};

    tileTree.insert(t1);
    tileTree.insert(t2);
    tileTree.insert(t3);
    tileTree.insert(t4);
    tileTree.insert(t5);
    tileTree.insert(t6);
    tileTree.insert(t7);

    tileTree.remove(t5);
    tileTree.remove(t2);
    tileTree.remove(t7);

    std::vector<Tile> tileExpected = {t4, t6, t1, t3};
    EXPECT_EQ(tileExpected, tileTree.inorder());
    EXPECT_EQ(4, tileTree.size());
}

TEST(AVL, Find) {
    AVL<int> tree;

    tree.insert(20);
    tree.insert(-5);
    tree.insert(92);
    tree.insert(43);
    tree.insert(-17);
    tree.insert(58);
    tree.insert(-29);

    EXPECT_NE(nullptr, tree.find(-29));
    EXPECT_NE(nullptr, tree.find(92));
    EXPECT_NE(nullptr, tree.find(-5));
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_EQ(nullptr, tree.find(21));

    AVL<Tile> tileTree;

    Tile t1{"t1", 1, 5, 4, "purple", "collision", false};
    Tile t2{"t2", 2, 1, 9, "green", "empty", true};
    Tile t3{"t3", 3, 13, 1, "none", "tswitch", false};
    Tile t4{"t4", 4, 2, 30, "red", "gswitch", false};
    Tile t5{"t5", 5, 5, 0, "none", "key", false};
    Tile t6{"t6", 6, 3, 3, "gray", "collision", false};
    Tile t7{"t7", 7, 46, 4, "none", "goal", false};

    tileTree.insert(t1);
    tileTree.insert(t2);
    tileTree.insert(t3);
    tileTree.insert(t4);
    tileTree.insert(t5);
    tileTree.insert(t6);
    tileTree.insert(t7);

    EXPECT_NE(nullptr, tileTree.find(t2));
    EXPECT_NE(nullptr, tileTree.find(t7));
    EXPECT_NE(nullptr, tileTree.find(t3));
}

TEST(AVL, Preorder) {
    AVL<int> tree;

    tree.insert(20);
    tree.insert(-5);
    tree.insert(92);
    tree.insert(43);
    tree.insert(-17);
    tree.insert(58);
    tree.insert(-29);

    std::vector<int> expected = {20, -17, -29, -5, 58, 43, 92};
    EXPECT_EQ(expected, tree.preorder());
}

TEST(AVL, Inorder) {
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
}

TEST(AVL, Postorder) {
    AVL<int> tree;

    tree.insert(20);
    tree.insert(-5);
    tree.insert(92);
    tree.insert(43);
    tree.insert(-17);
    tree.insert(58);
    tree.insert(-29);

    std::vector<int> expected = {-29, -5, -17, 43, 92, 58, 20};
    EXPECT_EQ(expected, tree.postorder());
}

TEST(AVL, Size) {
    AVL<int> tree;

    EXPECT_EQ(0, tree.size());
    EXPECT_TRUE(tree.empty());

    tree.insert(20);
    tree.insert(-5);
    tree.insert(92);
    tree.insert(43);
    tree.insert(-17);
    tree.insert(58);
    tree.insert(-29);

    EXPECT_EQ(7, tree.size());
}
