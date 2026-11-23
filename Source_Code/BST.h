#ifndef BST_H
#define BST_H

#include <iostream>

struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int val) : data(val), left(NULL), right(NULL) {}
};

class PoleBST {
private:
    BSTNode* root;

    BSTNode* insertHelper(BSTNode* node, int val) {
        if (node == NULL) {
            return new BSTNode(val);
        }
        if (val < node->data) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->data) {
            node->right = insertHelper(node->right, val);
        }
        return node;
    }

    bool searchHelper(BSTNode* node, int val) const {
        if (node == NULL) return false;
        if (node->data == val) return true;
        if (val < node->data) return searchHelper(node->left, val);
        return searchHelper(node->right, val);
    }

    BSTNode* findMin(BSTNode* node) {
        while (node != NULL && node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    BSTNode* deleteHelper(BSTNode* node, int val) {
        if (node == NULL) return NULL;

        if (val < node->data) {
            node->left = deleteHelper(node->left, val);
        } else if (val > node->data) {
            node->right = deleteHelper(node->right, val);
        } else {
            if (node->left == NULL) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == NULL) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            BSTNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteHelper(node->right, temp->data);
        }
        return node;
    }

    void inorderHelper(BSTNode* node) const {
        if (node == NULL) return;
        inorderHelper(node->left);
        std::cout << node->data << " ";
        inorderHelper(node->right);
    }

    void preorderHelper(BSTNode* node) const {
        if (node == NULL) return;
        std::cout << node->data << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }

    void postorderHelper(BSTNode* node) const {
        if (node == NULL) return;
        postorderHelper(node->left);
        postorderHelper(node->right);
        std::cout << node->data << " ";
    }

    void clearHelper(BSTNode* node) {
        if (node == NULL) return;
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }

public:
    PoleBST() : root(NULL) {}

    ~PoleBST() {
        clearHelper(root);
        root = NULL;
    }

    bool isEmpty() const {
        return root == NULL;
    }

    void insert(int val) {
        root = insertHelper(root, val);
    }

    bool search(int val) const {
        return searchHelper(root, val);
    }

    void remove(int val) {
        root = deleteHelper(root, val);
    }

    void inorder() const {
        if (root == NULL) {
            std::cout << "BST is empty.\n";
            return;
        }
        inorderHelper(root);
        std::cout << "\n";
    }

    void preorder() const {
        if (root == NULL) {
            std::cout << "BST is empty.\n";
            return;
        }
        preorderHelper(root);
        std::cout << "\n";
    }

    void postorder() const {
        if (root == NULL) {
            std::cout << "BST is empty.\n";
            return;
        }
        postorderHelper(root);
        std::cout << "\n";
    }
};

#endif
