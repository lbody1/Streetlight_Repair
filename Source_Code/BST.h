#ifndef BST_H
#define BST_H

#include <iostream>

// Binary Search Tree Node (R5)
struct BSTNode {
    int poleID;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int id) : poleID(id), left(nullptr), right(nullptr) {}
};

// BST for Fast Pole ID Indexing and Lookup
class PoleBSTIndex {
private:
    BSTNode* root;
    int nodeCount;

    // Helper: Recursive insert (rejects duplicates)
    BSTNode* insertHelper(BSTNode* node, int id, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            nodeCount++;
            return new BSTNode(id);
        }

        if (id < node->poleID) {
            node->left = insertHelper(node->left, id, inserted);
        } else if (id > node->poleID) {
            node->right = insertHelper(node->right, id, inserted);
        } else {
            // Duplicate key
            inserted = false;
        }
        return node;
    }

    // Helper: Recursive search
    bool searchHelper(BSTNode* node, int id) const {
        if (node == nullptr) return false;
        if (node->poleID == id) return true;

        if (id < node->poleID) {
            return searchHelper(node->left, id);
        } else {
            return searchHelper(node->right, id);
        }
    }

    // Helper: Find minimum node (inorder successor)
    BSTNode* getSuccessor(BSTNode* curr) {
        curr = curr->right;
        while (curr != nullptr && curr->left != nullptr) {
            curr = curr->left;
        }
        return curr;
    }

    // Helper: Recursive delete (matches Lab 6 slide 27)
    BSTNode* delNodeHelper(BSTNode* node, int x, bool& deleted) {
        if (node == nullptr) return nullptr;

        if (node->poleID > x) {
            node->left = delNodeHelper(node->left, x, deleted);
        } else if (node->poleID < x) {
            node->right = delNodeHelper(node->right, x, deleted);
        } else {
            // Node found
            deleted = true;
            nodeCount--;

            // Case 1 & Case 2: 0 or 1 child
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: 2 children
            BSTNode* succ = getSuccessor(node);
            node->poleID = succ->poleID;
            node->right = delNodeHelper(node->right, succ->poleID, deleted);
        }
        return node;
    }

    // Helper: Traversals
    void inorderHelper(BSTNode* node) const {
        if (node == nullptr) return;
        inorderHelper(node->left);
        std::cout << node->poleID << " ";
        inorderHelper(node->right);
    }

    void preorderHelper(BSTNode* node) const {
        if (node == nullptr) return;
        std::cout << node->poleID << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }

    void postorderHelper(BSTNode* node) const {
        if (node == nullptr) return;
        postorderHelper(node->left);
        postorderHelper(node->right);
        std::cout << node->poleID << " ";
    }

    void destroyTree(BSTNode* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    PoleBSTIndex() : root(nullptr), nodeCount(0) {}

    ~PoleBSTIndex() {
        destroyTree(root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    int size() const {
        return nodeCount;
    }

    // Insert key. Returns false if duplicate.
    bool insert(int id) {
        bool inserted = false;
        root = insertHelper(root, id, inserted);
        return inserted;
    }

    // Search key
    bool search(int id) const {
        return searchHelper(root, id);
    }

    // Delete key. Returns false if key doesn't exist.
    bool remove(int id) {
        bool deleted = false;
        root = delNodeHelper(root, id, deleted);
        return deleted;
    }

    void inorder() const {
        if (root == nullptr) {
            std::cout << "[BST is empty]\n";
            return;
        }
        inorderHelper(root);
        std::cout << "\n";
    }

    void preorder() const {
        if (root == nullptr) {
            std::cout << "[BST is empty]\n";
            return;
        }
        preorderHelper(root);
        std::cout << "\n";
    }

    void postorder() const {
        if (root == nullptr) {
            std::cout << "[BST is empty]\n";
            return;
        }
        postorderHelper(root);
        std::cout << "\n";
    }
};

#endif // BST_H
