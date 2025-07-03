/*    Created:    06-30-2025
 *    Modified:   07-02-2025
 */

#ifndef PONE_AVL_HPP
#define PONE_AVL_HPP

#include <algorithm>  // std::max
// #include <cmath>
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
    static int setHeight(AVLNode *root, const int &height);
    static int getHeight(AVLNode *root);
    static int numberChildNodes(AVLNode *root);
    static bool isLeaf(AVLNode *root);
    static int balanceFactor(AVLNode *root);

    static AVLNode *findSuccessor(AVLNode *target);
    static AVLNode *removeWithTwo(AVLNode *root, AVLNode *target);

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
    bool find(const T &key) const;
    void remove(const T &key);

    void rebalance();
    bool empty() const;

   private:
    AVLNode<T> *root;
};

template <typename T>
AVLNode<T> *AVLNode<T>::insert(AVLNode *root, const T &key) {
    if (root == nullptr) return new AVLNode<T>{key};

    if (key < root->data)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
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
        // TODO: Handle root case
        return root;
    }

    AVLNode<T> *parent = nullptr;
    AVLNode<T> *target = root;

    while (target != nullptr) {
        if (key < target->data) {
            if (parent->left != nullptr) {
                target = parent->left;
                if (key == parent->left->data) {
                    switch (numberChildAVLNodes(target)) {
                        case 0:
                            delete target;
                            parent->left = nullptr;
                            return root;
                        case 1:
                            parent->left = (target->left == nullptr)
                                               ? target->right
                                               : target->left;
                            delete target;
                            return root;
                        case 2:
                            return removeWithTwo(root, target);
                    }
                }
            }
        } else {
            if (parent->right != nullptr) {
                target = parent->right;
                if (key == parent->right->data) {
                    switch (numberChildAVLNodes(target)) {
                        case 0:
                            delete target;
                            parent->right = nullptr;
                            return root;
                        case 1:
                            parent->right = (target->left == nullptr)
                                                ? target->right
                                                : target->left;
                            delete target;
                            return root;
                        case 2:
                            return removeWithTwo(root, target);
                    }
                }
            }
        }
    }
    return root;
}

template <typename T>
AVLNode<T> *AVLNode<T>::leftmost(AVLNode<T> *root) {
    AVLNode<T> *target = root;
    while (target != nullptr) target = target->left;
    return target;
}

template <typename T>
AVLNode<T> *AVLNode<T>::leftRotate(AVLNode<T> *x) {
    AVLNode<T> *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;  // parent of x will be assigned y;
}

template <typename T>
AVLNode<T> *AVLNode<T>::rightRotate(AVLNode<T> *y) {
    AVLNode<T> *x = y->left;
    y->left = x->right;
    x->right = y;
    return x;  // parent of y will be assigned x;
}

template <typename T>
int AVLNode<T>::setHeight(AVLNode<T> *root, const int &height) {
    root->height = height;
    return height;
}

template <typename T>
int AVLNode<T>::getHeight(AVLNode<T> *root) {
    if (isLeaf(root)) {
        return 0;
    }
    return setHeight(
        root, 1 + std::max(getHeight(root->left), getHeight(root->right)));
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
    return getHeight(root->left) - getHeight(root->right);
}

template <typename T>
void AVLNode<T>::preorder(AVLNode<T> *root, std::vector<T> &vec) {
    if (root == nullptr) {
        return;
    }
    vec.push_back(root->data);
    preorder(root->left, vec);
    preorder(root->right, vec);
}

template <typename T>
void AVLNode<T>::inorder(AVLNode<T> *root, std::vector<T> &vec) {
    if (root == nullptr) {
        return;
    }

    inorder(root->left, vec);
    vec.push_back(root->data);
    inorder(root->right, vec);
}

template <typename T>
void AVLNode<T>::postorder(AVLNode<T> *root, std::vector<T> &vec) {
    if (root == nullptr) {
        return;
    }

    postorder(root->left, vec);
    postorder(root->right, vec);
    vec.push_back(root->data);
}

template <typename T>
AVLNode<T> *AVLNode<T>::findSuccessor(AVLNode<T> *target) {
    if (target == nullptr) return nullptr;

    if (target->right != nullptr) {
        return leftmost(target->right);
    }

    return nullptr;
}

template <typename T>
AVLNode<T> *AVLNode<T>::removeWithTwo(AVLNode<T> *root, AVLNode<T> *target) {
    AVLNode<T> *succ;
    T succData = succ->data;
    remove(root, succ->data);
    target->data = succData;
    return root;
}

#endif  // PONE_AVL_HPP
