#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <algorithm>

enum Color { RED, BLACK };

template <typename T>
struct Node {
    T data;
    Color color;
    Node *left, *right, *parent;

    Node(T value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class RBTree {
private:
    Node<T> *root;
    Node<T> *TNULL; // Sentinel node representing NIL (leaves)

    // --- Helper Functions ---

    void initializeTNULL() {
        TNULL = new Node<T>(T());
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
    }

    void preOrderHelper(Node<T> *node) {
        if (node != TNULL) {
            std::cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inorderHelper(Node<T> *node) {
        if (node != TNULL) {
            inorderHelper(node->left);
            std::cout << node->data << " ";
            inorderHelper(node->right);
        }
    }

    Node<T>* searchHelper(Node<T>* node, T key) {
        if (node == TNULL || key == node->data) {
            return node;
        }
        if (key < node->data) {
            return searchHelper(node->left, key);
        }
        return searchHelper(node->right, key);
    }

    // --- Rotations ---
    // Rotations are essential for rebalancing the tree after insertion or deletion.
    
    // Left Rotation
    void leftRotate(Node<T> *x) {
        Node<T> *y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // Right Rotation
    void rightRotate(Node<T> *x) {
        Node<T> *y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // --- Insertion Fix-up ---
    void insertFix(Node<T> *k) {
        Node<T> *u;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // Uncle
                if (u->color == RED) {
                    // Case 1: Uncle is Red
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        // Case 2: Uncle is Black and k is left child
                        k = k->parent;
                        rightRotate(k);
                    }
                    // Case 3: Uncle is Black and k is right child
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; // Uncle
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = BLACK;
    }

    // --- Deletion Helpers ---

    void transplant(Node<T> *u, Node<T> *v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteFix(Node<T> *x) {
        Node<T> *s;
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == BLACK && s->right->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->right->color == BLACK) {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }
                if (s->right->color == BLACK && s->left->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->left->color == BLACK) {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    Node<T>* minimum(Node<T>* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    Node<T>* maximum(Node<T>* node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

public:
    RBTree() {
        initializeTNULL();
        root = TNULL;
    }

    // Insert Function
    void insert(T key) {
        Node<T> *node = new Node<T>(key);
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;

        Node<T> *y = nullptr;
        Node<T> *x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        insertFix(node);
    }

    // Delete Function
    void remove(T key) {
        Node<T> *z = TNULL;
        Node<T> *x, *y;
        
        // Find node
        Node<T> *curr = root;
        while (curr != TNULL) {
            if (curr->data == key) {
                z = curr;
            }
            if (curr->data <= key) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }

        if (z == TNULL) {
            std::cout << "Key not found in the tree" << std::endl;
            return;
        }

        y = z;
        Color y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == BLACK) {
            deleteFix(x);
        }
    }

    // Search
    bool search(T key) {
        return searchHelper(this->root, key) != TNULL;
    }

    // Minimum
    T getMinimum() {
        if (root == TNULL) throw std::runtime_error("Tree is empty");
        return minimum(root)->data;
    }

    // Maximum
    T getMaximum() {
        if (root == TNULL) throw std::runtime_error("Tree is empty");
        return maximum(root)->data;
    }

    // Helpers for display
    void inorder() {
        inorderHelper(this->root);
        std::cout << std::endl;
    }
};

#endif
