/*    Created:    06-30-2025
 *    Modified:   07-09-2025
 */

#ifndef PONE_AVL_HPP
#define PONE_AVL_HPP

#include <algorithm>  // std::max
#include <iostream>
#include <vector>

template <typename T>
struct AVLNode {
    T data;
    AVLNode *left, *right;
    int height;

    AVLNode(const T &key)
        : data{key}, left{nullptr}, right{nullptr}, height{0} {}

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
};

template <typename T>
class AVL {
   public:
    AVL();
    AVL(const AVL &other);
    AVL &operator=(const AVL &other);

    void insert(const T &key);
    AVLNode<T> *find(const T &key);
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
    AVLNode<T> *root;
    int m_size;
};

template <typename T>
AVLNode<T> *AVLNode<T>::insert(AVLNode *root, const T &key) {
    if (root == nullptr) return new AVLNode<T>{key};

    if (key < root->data) {
        root->left = insert(root->left, key);
    } else
        root->right = insert(root->right, key);

    setHeight(root);
    return rebalance(root);
}

template <typename T>
AVLNode<T> *AVLNode<T>::find(AVLNode<T> *root, const T &key) {
    if (root == nullptr) return nullptr;

    if (key == root->data)
        return root;
    else if (key < root->data)
        return find(root->left, key);

    return find(root->right, key);
}

template <typename T>
AVLNode<T> *AVLNode<T>::remove(AVLNode<T> *root, const T &key) {
    if (root == nullptr) return nullptr;

    if (key == root->data) {
        AVLNode<T> *newRoot, *succ;
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
                succ = leftmost(root->right);
                T succData = succ->data;
                root->right = remove(root->right, succData);
                root->data = succData;
                break;
        }
    } else if (key < root->data) {
        root->left = remove(root->left, key);
    } else {
        root->right = remove(root->right, key);
    }

    setHeight(root);
    return rebalance(root);
}

template <typename T>
AVLNode<T> *AVLNode<T>::leftmost(AVLNode<T> *root) {
    if (root == nullptr) return nullptr;
    AVLNode<T> *target = root;
    while (target->left != nullptr) target = target->left;
    return target;
}

template <typename T>
AVLNode<T> *AVLNode<T>::leftRotate(AVLNode<T> *x) {
    AVLNode<T> *y = x->right;
    x->right = y->left;
    y->left = x;

    setHeight(x);
    setHeight(y);
    return y;  // parent of x will be assigned y
}

template <typename T>
AVLNode<T> *AVLNode<T>::rightRotate(AVLNode<T> *y) {
    AVLNode<T> *x = y->left;
    y->left = x->right;
    x->right = y;

    setHeight(y);
    setHeight(x);
    return x;  // parent of y will be assigned x
}

template <typename T>
int AVLNode<T>::setHeight(AVLNode<T> *root) {
    if (root == nullptr) return 0;
    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
    return root->height;
}

template <typename T>
int AVLNode<T>::getHeight(AVLNode<T> *root) {
    return (root == nullptr) ? 0 : setHeight(root);
}

template <typename T>
int AVLNode<T>::numberChildNodes(AVLNode<T> *root) {
    if (root->left == nullptr && root->right == nullptr) {
        return 0;
    } else if (root->left != nullptr && root->right != nullptr) {
        return 2;
    }

    return 1;
}

template <typename T>
bool AVLNode<T>::isLeaf(AVLNode<T> *root) {
    return numberChildNodes(root) <= 0;
}

template <typename T>
int AVLNode<T>::balanceFactor(AVLNode<T> *root) {
    if (root == nullptr) return 0;
    return getHeight(root->right) - getHeight(root->left);
}

template <typename T>
void AVLNode<T>::preorder(AVLNode<T> *root, std::vector<T> &vec) {
    if (root == nullptr) return;
    vec.push_back(root->data);
    preorder(root->left, vec);
    preorder(root->right, vec);
}

template <typename T>
void AVLNode<T>::inorder(AVLNode<T> *root, std::vector<T> &vec) {
    if (root == nullptr) return;
    inorder(root->left, vec);
    vec.push_back(root->data);
    inorder(root->right, vec);
}

template <typename T>
void AVLNode<T>::postorder(AVLNode<T> *root, std::vector<T> &vec) {
    if (root == nullptr) return;
    postorder(root->left, vec);
    postorder(root->right, vec);
    vec.push_back(root->data);
}

template <typename T>
AVLNode<T> *AVLNode<T>::rebalance(AVLNode<T> *root) {
    if (root == nullptr) return nullptr;

    int bf = AVLNode<T>::balanceFactor(root);
    int bfl = AVLNode<T>::balanceFactor(root->left);
    int bfr = AVLNode<T>::balanceFactor(root->right);
    // bf = height(right) - height(left)

    if (bf == 0) {
        return root;
    } else if (bf < -1 || bf > 1) {
        if (bf < -1) {  // This means that the left subtree is higher
            // Do right rotation
            if (bfl > 0) {
                root->left = AVLNode<T>::leftRotate(root->left);
            }

            root = AVLNode<T>::rightRotate(root);
        } else {
            if (bfr < 0) {
                root->right = AVLNode<T>::rightRotate(root->right);
            }

            root = AVLNode<T>::leftRotate(root);
        }
    }

    return root;
}

template <typename T>
AVLNode<T> *AVLNode<T>::findSuccessor(AVLNode<T> *target) {
    if (target == nullptr) return nullptr;
    return leftmost(target->right);
}

template <typename T>
void AVLNode<T>::printPreorder(AVLNode<T> *root) {
    std::vector<T> vec;
    preorder(root, vec);
    for (const auto &item : vec) std::cout << item << std::endl;
}

template <typename T>
void AVLNode<T>::printInorder(AVLNode<T> *root) {
    std::vector<T> vec;
    inorder(root, vec);
    for (const auto &item : vec) std::cout << item << std::endl;
}

template <typename T>
void AVLNode<T>::printPostorder(AVLNode<T> *root) {
    std::vector<T> vec;
    postorder(root, vec);
    for (const auto &item : vec) std::cout << item << std::endl;
}

template <typename T>
AVL<T>::AVL() : root{nullptr}, m_size{0} {}

template <typename T>
AVL<T>::AVL(const AVL &other) : m_size{0} {
    std::vector<T> vec;
    AVLNode<T>::preorder(other.root, vec);
    for (const auto &item : vec) insert(item);
}

template <typename T>
AVL<T> &AVL<T>::operator=(const AVL<T> &other) {
    if (this == &other) return *this;

    removeAll();

    std::vector<T> vec;
    AVLNode<T>::preorder(other.root, vec);
    for (const auto &item : vec) insert(item);

    return *this;
}

template <typename T>
void AVL<T>::insert(const T &key) {
    root = AVLNode<T>::insert(root, key);
    ++m_size;
}

template <typename T>
AVLNode<T> *AVL<T>::find(const T &key) {
    return AVLNode<T>::find(root, key);
}

template <typename T>
void AVL<T>::remove(const T &key) {
    root = AVLNode<T>::remove(root, key);
    --m_size;
}

template <typename T>
void AVL<T>::removeAll() {
    while (!empty()) remove(root->data);
}

template <typename T>
std::vector<T> AVL<T>::preorder() {
    std::vector<T> vec;
    AVLNode<T>::preorder(root, vec);
    return vec;
}

template <typename T>
std::vector<T> AVL<T>::inorder() {
    std::vector<T> vec;
    AVLNode<T>::inorder(root, vec);
    return vec;
}

template <typename T>
std::vector<T> AVL<T>::postorder() {
    std::vector<T> vec;
    AVLNode<T>::postorder(root, vec);
    return vec;
}

template <typename T>
void AVL<T>::printPreorder() {
    AVLNode<T>::printPreorder(root);
}

template <typename T>
void AVL<T>::printInorder() {
    AVLNode<T>::printInorder(root);
}

template <typename T>
void AVL<T>::printPostorder() {
    AVLNode<T>::printPostorder(root);
}

template <typename T>
bool AVL<T>::empty() const {
    return root == nullptr;
}

template <typename T>
int AVL<T>::size() const {
    return m_size;
}

template <typename T>
AVL<T>::~AVL() {
    removeAll();
}

#endif  // PONE_AVL_HPP
