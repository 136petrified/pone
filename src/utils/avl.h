/*    Created:    06-30-2025
 *    Modified:   10-19-2025
 */

#pragma once

#include <algorithm>  // std::max
#include <compare>
#include <iostream>
#include <vector>

namespace pone {

template <typename T>
struct DefaultComparator {
    std::strong_ordering operator()(const T &lhs, const T &rhs) {
        if (lhs < rhs)
            return std::strong_ordering::less;
        else if (lhs > rhs)
            return std::strong_ordering::greater;
        return std::strong_ordering::equal;
    }
};

template <typename T, typename Compare = DefaultComparator<T>>
struct AVLNode {
    T data;
    AVLNode *left, *right;
    int height;
    static Compare m_compare;

    AVLNode(const T &key, Compare compare = Compare());

    static AVLNode *insert(AVLNode *root, const T &key);
    static AVLNode *find(AVLNode *root, const T &key);
    static AVLNode *remove(AVLNode *root, const T &key);

    static AVLNode *leftmost(AVLNode *root);
    static AVLNode *leftRotate(AVLNode *x);
    static AVLNode *rightRotate(AVLNode *y);
    static int setHeight(AVLNode *root);
    static int getHeight(AVLNode *root);
    static int numberChildNodes(AVLNode *root);
    static bool isLeaf(AVLNode *root);
    static int balanceFactor(AVLNode *root);
    static AVLNode *rebalance(AVLNode *root);
    static AVLNode *findSuccessor(AVLNode *target);

    static void print(AVLNode *root);
    static void preorder(AVLNode *root, std::vector<T> &vec);
    static void inorder(AVLNode *root, std::vector<T> &vec);
    static void postorder(AVLNode *root, std::vector<T> &vec);
    static void printPreorder(AVLNode *root);
    static void printInorder(AVLNode *root);
    static void printPostorder(AVLNode *root);

    static bool less(const T &lhs, const T &rhs);
    static bool equal(const T &lhs, const T &rhs);
    static bool greater(const T &lhs, const T &rhs);
};

template <typename T, typename Compare = DefaultComparator<T>>
class AVL {
   public:
    AVL(Compare compare = Compare());
    AVL(const AVL &other);
    AVL &operator=(const AVL &other);

    void insert(const T &key);
    AVLNode<T, Compare> *find(const T &key);
    void remove(const T &key);
    void removeAll();

    std::vector<T> preorder();
    std::vector<T> inorder();
    std::vector<T> postorder();
    void printPreorder();
    void printInorder();
    void printPostorder();

    bool empty() const;
    int size() const;

    ~AVL();

   private:
    AVLNode<T, Compare> *root;
    Compare m_compare;
    int m_size;
};

template <typename T, typename Compare>
Compare AVLNode<T, Compare>::m_compare;

template <typename T, typename Compare>
AVLNode<T, Compare>::AVLNode(const T &key, Compare compare)
    : data{key}, left{nullptr}, right{nullptr}, height{0} {
    m_compare = compare;
}

template <typename T, typename Compare>
AVLNode<T, Compare> *AVLNode<T, Compare>::insert(AVLNode *root, const T &key) {
    if (root == nullptr)
        return new AVLNode<T, Compare>{key};

    if (less(key, root->data)) {
        root->left = insert(root->left, key);
    } else
        root->right = insert(root->right, key);

    setHeight(root);
    return rebalance(root);
}

template <typename T, typename Compare>
AVLNode<T, Compare> *AVLNode<T, Compare>::find(AVLNode<T, Compare> *root,
                                               const T &key) {
    if (root == nullptr)
        return nullptr;

    if (equal(key, root->data))
        return root;
    else if (less(key, root->data))
        return find(root->left, key);

    return find(root->right, key);
}

template <typename T, typename Compare>
AVLNode<T, Compare> *AVLNode<T, Compare>::remove(AVLNode<T, Compare> *root,
                                                 const T &key) {
    if (root == nullptr)
        return nullptr;

    if (equal(key, root->data)) {
        AVLNode<T, Compare> *newRoot, *succ;
        switch (numberChildNodes(root)) {
            case 0:
                delete root;
                return nullptr;
            case 1:
                newRoot = (root->left != nullptr) ? root->left : root->right;
                delete root;
                root = newRoot;
                break;
            case 2:
                succ        = leftmost(root->right);
                T succData  = succ->data;
                root->right = remove(root->right, succData);
                root->data  = succData;
                break;
        }
    } else if (less(key, root->data)) {
        root->left = remove(root->left, key);
    } else {
        root->right = remove(root->right, key);
    }

    setHeight(root);
    return rebalance(root);
}

template <typename T, typename Compare>
AVLNode<T, Compare> *AVLNode<T, Compare>::leftmost(AVLNode<T, Compare> *root) {
    if (root == nullptr)
        return nullptr;
    AVLNode<T, Compare> *target = root;
    while (target->left != nullptr)
        target = target->left;
    return target;
}

template <typename T, typename Compare>
AVLNode<T, Compare> *AVLNode<T, Compare>::leftRotate(AVLNode<T, Compare> *x) {
    AVLNode<T, Compare> *y = x->right;
    x->right               = y->left;
    y->left                = x;

    setHeight(x);
    setHeight(y);
    return y;  // parent of x will be assigned y
}

template <typename T, typename Compare>
AVLNode<T, Compare> *AVLNode<T, Compare>::rightRotate(AVLNode<T, Compare> *y) {
    AVLNode<T, Compare> *x = y->left;
    y->left                = x->right;
    x->right               = y;

    setHeight(y);
    setHeight(x);
    return x;  // parent of y will be assigned x
}

template <typename T, typename Compare>
int AVLNode<T, Compare>::setHeight(AVLNode<T, Compare> *root) {
    if (root == nullptr)
        return 0;
    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
    return root->height;
}

template <typename T, typename Compare>
int AVLNode<T, Compare>::getHeight(AVLNode<T, Compare> *root) {
    return (root == nullptr) ? 0 : setHeight(root);
}

template <typename T, typename Compare>
int AVLNode<T, Compare>::numberChildNodes(AVLNode<T, Compare> *root) {
    if (root->left == nullptr && root->right == nullptr) {
        return 0;
    } else if (root->left != nullptr && root->right != nullptr) {
        return 2;
    }

    return 1;
}

template <typename T, typename Compare>
bool AVLNode<T, Compare>::isLeaf(AVLNode<T, Compare> *root) {
    return numberChildNodes(root) <= 0;
}

template <typename T, typename Compare>
int AVLNode<T, Compare>::balanceFactor(AVLNode<T, Compare> *root) {
    if (root == nullptr)
        return 0;
    return getHeight(root->right) - getHeight(root->left);
}

template <typename T, typename Compare>
void AVLNode<T, Compare>::preorder(AVLNode<T, Compare> *root,
                                   std::vector<T> &vec) {
    if (root == nullptr)
        return;
    vec.push_back(root->data);
    preorder(root->left, vec);
    preorder(root->right, vec);
}

template <typename T, typename Compare>
void AVLNode<T, Compare>::inorder(AVLNode<T, Compare> *root,
                                  std::vector<T> &vec) {
    if (root == nullptr)
        return;
    inorder(root->left, vec);
    vec.push_back(root->data);
    inorder(root->right, vec);
}

template <typename T, typename Compare>
void AVLNode<T, Compare>::postorder(AVLNode<T, Compare> *root,
                                    std::vector<T> &vec) {
    if (root == nullptr)
        return;
    postorder(root->left, vec);
    postorder(root->right, vec);
    vec.push_back(root->data);
}

template <typename T, typename Compare>
AVLNode<T, Compare> *AVLNode<T, Compare>::rebalance(AVLNode<T, Compare> *root) {
    if (root == nullptr)
        return nullptr;

    int bf  = AVLNode<T, Compare>::balanceFactor(root);
    int bfl = AVLNode<T, Compare>::balanceFactor(root->left);
    int bfr = AVLNode<T, Compare>::balanceFactor(root->right);
    // bf = height(right) - height(left)

    if (bf == 0) {
        return root;
    } else if (bf < -1 || bf > 1) {
        if (bf < -1) {  // This means that the left subtree is higher
            // Do right rotation
            if (bfl > 0) {
                root->left = AVLNode<T, Compare>::leftRotate(root->left);
            }

            root = AVLNode<T, Compare>::rightRotate(root);
        } else {
            if (bfr < 0) {
                root->right = AVLNode<T, Compare>::rightRotate(root->right);
            }

            root = AVLNode<T, Compare>::leftRotate(root);
        }
    }

    return root;
}

template <typename T, typename Compare>
AVLNode<T, Compare> *AVLNode<T, Compare>::findSuccessor(
    AVLNode<T, Compare> *target) {
    if (target == nullptr)
        return nullptr;
    return leftmost(target->right);
}

template <typename T, typename Compare>
void AVLNode<T, Compare>::printPreorder(AVLNode<T, Compare> *root) {
    std::vector<T> vec;
    preorder(root, vec);
    for (const auto &item : vec)
        std::cout << item << std::endl;
}

template <typename T, typename Compare>
void AVLNode<T, Compare>::printInorder(AVLNode<T, Compare> *root) {
    std::vector<T> vec;
    inorder(root, vec);
    for (const auto &item : vec)
        std::cout << item << std::endl;
}

template <typename T, typename Compare>
void AVLNode<T, Compare>::printPostorder(AVLNode<T, Compare> *root) {
    std::vector<T> vec;
    postorder(root, vec);
    for (const auto &item : vec)
        std::cout << item << std::endl;
}

template <typename T, typename Compare>
bool AVLNode<T, Compare>::less(const T &lhs, const T &rhs) {
    return m_compare(lhs, rhs) < 0;
}

template <typename T, typename Compare>
bool AVLNode<T, Compare>::equal(const T &lhs, const T &rhs) {
    return m_compare(lhs, rhs) == 0;
}

template <typename T, typename Compare>
bool AVLNode<T, Compare>::greater(const T &lhs, const T &rhs) {
    return m_compare(lhs, rhs) > 0;
}

template <typename T, typename Compare>
AVL<T, Compare>::AVL(Compare compare)
    : root{nullptr}, m_compare{compare}, m_size{0} {}

template <typename T, typename Compare>
AVL<T, Compare>::AVL(const AVL &other)
    : root{nullptr}, m_compare{other.m_compare}, m_size{0} {
    std::vector<T> vec;
    AVLNode<T, Compare>::preorder(other.root, vec);
    for (const auto &item : vec)
        insert(item);
}

template <typename T, typename Compare>
AVL<T, Compare> &AVL<T, Compare>::operator=(const AVL<T, Compare> &other) {
    if (this == &other)
        return *this;

    removeAll();

    std::vector<T> vec;
    AVLNode<T, Compare>::preorder(other.root, vec);
    for (const auto &item : vec)
        insert(item);

    return *this;
}

template <typename T, typename Compare>
void AVL<T, Compare>::insert(const T &key) {
    root = AVLNode<T, Compare>::insert(root, key);
    ++m_size;
}

template <typename T, typename Compare>
AVLNode<T, Compare> *AVL<T, Compare>::find(const T &key) {
    return AVLNode<T, Compare>::find(root, key);
}

template <typename T, typename Compare>
void AVL<T, Compare>::remove(const T &key) {
    root = AVLNode<T, Compare>::remove(root, key);
    --m_size;
}

template <typename T, typename Compare>
void AVL<T, Compare>::removeAll() {
    while (!empty())
        remove(root->data);
}

template <typename T, typename Compare>
std::vector<T> AVL<T, Compare>::preorder() {
    std::vector<T> vec;
    AVLNode<T, Compare>::preorder(root, vec);
    return vec;
}

template <typename T, typename Compare>
std::vector<T> AVL<T, Compare>::inorder() {
    std::vector<T> vec;
    AVLNode<T, Compare>::inorder(root, vec);
    return vec;
}

template <typename T, typename Compare>
std::vector<T> AVL<T, Compare>::postorder() {
    std::vector<T> vec;
    AVLNode<T, Compare>::postorder(root, vec);
    return vec;
}

template <typename T, typename Compare>
void AVL<T, Compare>::printPreorder() {
    AVLNode<T, Compare>::printPreorder(root);
}

template <typename T, typename Compare>
void AVL<T, Compare>::printInorder() {
    AVLNode<T, Compare>::printInorder(root);
}

template <typename T, typename Compare>
void AVL<T, Compare>::printPostorder() {
    AVLNode<T, Compare>::printPostorder(root);
}

template <typename T, typename Compare>
bool AVL<T, Compare>::empty() const {
    return root == nullptr;
}

template <typename T, typename Compare>
int AVL<T, Compare>::size() const {
    return m_size;
}

template <typename T, typename Compare>
AVL<T, Compare>::~AVL() {
    removeAll();
}

}  // namespace pone
