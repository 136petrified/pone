/*    Created:    06-30-2025
 *    Modified:   07-01-2025
 */

#ifndef PONE_AVL_HPP
#define PONE_AVL_HPP

#include <vector>

template <typename T>
struct Node {
    T data;
    Node *left, *right;
    int height = 0;

    Node(const T &key) : data{key}, left{nullptr}, right{nullptr} {}

    static Node *insert(Node *root, const T &key);
    static Node *find(Node *root, const T &key);
    static Node *remove(Node *root, const T &key);

    static Node *leftmost(Node *root);
    static Node *leftRotate(Node *root);
    static Node *rightRotate(Node *root);
    static Node *getHeight(Node *root);
    static int numberChildNodes(Node *root);

    static Node *findSuccessor(Node *target);
    static Node *findLeftSuccessor(Node *parent, Node *target);
    static Node *findRightSuccessor(Node *parent, Node *target);
    static Node *removeWithTwo(Node *root, Node *target);

    static void print(Node *root);
    static std::vector<T> preorder(Node *root);
    static std::vector<T> inorder(Node *root);
    static std::vector<T> postorder(Node *root);
    static void printPreorder(Node *root);
    static void printInorder(Node *root);
    static void printPostorder(Node *root);
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

   private:
    Node<T> *root;
};

template <typename T>
Node<T> *Node<T>::insert(Node *root, const T &key) {
    if (root == nullptr) return new Node{key};

    if (key < root->data)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

template <typename T>
Node<T> *Node<T>::find(Node<T> *root, const T &key) {
    if (root == nullptr) return nullptr;

    if (key == root->data)
        return root;
    else if (key < root->data)
        return find(root->left, key);

    return find(root->right, key);
}

template <typename T>
Node<T> *Node<T>::remove(Node<T> *root, const T &key) {
    if (root == nullptr) return nullptr;

    if (key == root->data) {
        // TODO: Handle root case
        return root;
    }

    Node *parent = nullptr;
    Node *target = root;

    while (target != nullptr) {
        if (key < target->data) {
            if (parent->left != nullptr) {
                target = parent->left;
                if (key == parent->left->data) {
                    switch (numberChildNodes(target)) {
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
                    switch (numberChildNodes(target)) {
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
Node<T> *Node<T>::leftmost(Node<T> *root) {
    Node *target = root;
    while (target != nullptr) target = target->left;
    return target;
}

template <typename T>
Node<T> *Node<T>::findSuccessor(Node<T> *target) {
    if (target == nullptr) return nullptr;

    if (target->right != nullptr) {
        return leftmost(target->right);
    }

    return nullptr;
}

template <typename T>
Node<T> *Node<T>::removeWithTwo(Node<T> *root, Node<T> *target) {
    Node *succ;
    T succData = succ->data;
    remove(root, succ->data);
    target->data = succData;
    return root;
}

#endif  // PONE_AVL_HPP
