/*    Created:    06-30-2025
 *    Modified:   06-30-2025
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

    static void print(Node *root);
    static std::vector<T> preorder();
    static std::vector<T> inorder();
    static std::vector<T> postorder();
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
Node<T> *Node<T>::find(Node *root, const T &key) {
    if (root == nullptr) return nullptr;

    if (key == root->data)
        return root;
    else if (key < root->data)
        return find(root->left, key);

    return find(root->right, key);
}

#endif  // PONE_AVL_HPP
