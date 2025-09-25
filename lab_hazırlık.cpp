#include <vector>
#include <iostream>
#include <cmath>
#include <stack>
#include "Node.h"
#include "NoSuchItemException.h"
#include "DSWTree.h"


template<class T>
bool DSWTree<T>::remove(const T &element) {
    root = removeRec(root, element);
    return root != nullptr;
}

template<class T>
typename DSWTree<T>::Node* removeRec(Node<T>* node, const T &element) {
    // Base case: if the node is null, the element is not in the tree
    if (node == nullptr) {
        return nullptr;
    }

    // Recurse down the tree to find the element
    if (element < node->data) {
        node->left = removeRec(node->left, element);
    } else if (element > node->data) {
        node->right = removeRec(node->right, element);
    } else {
        // Found the node to be deleted
        // Case 1: Node with only one child or no child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Case 2: Node with two children
        // Find the in-order successor (smallest in the right subtree)
        Node* temp = findMin(node->right);

        // Copy the in-order successor's data to this node
        node->data = temp->data;

        // Delete the in-order successor
        node->right = removeRec(node->right, temp->data);
    }

    return node;
}

template<class T>
typename DSWTree<T>::Node* findMin(Node<T>* node) {
    // The leftmost leaf is the minimum
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}


template <class T>
void DSWTree<T>::createBackbone(Node<T>*& root) {
    Node<T>** current = &root; // pointer to a pointer to the current node
    while (*current != NULL) {
        if ((*current)->left != NULL) {
            // Rotate right at *current
            rightRotation(*current);
            // After rotation, we do NOT advance current because we may need to repeat if there's still a left child
        } else {
            // Move to the next node in the chain
            current = &((*current)->right);
        }
    }
}


template <class T>
void DSWTree<T>::createBackbone(Node<T>*& root) {
    while (root->left) rightRotation(root);
    if (root->right) createBackbone(root->right);
}

template<class T>
void DSWTree<T>::compress(Node<T>*& root, int m) {
    while (root != nullptr && root->right != nullptr && m > 0) {
        leftRotation(root);
        root = root->right;
        --m;
    }
}

template <class T>
void DSWTree<T>::createCompleteTree(Node<T>*& root, int size) {
    int m = pow(2, floor(log2(size + 1))) - 1; // Largest power of 2 less than size
    int rotations = size - m;

    // Perform initial compressions
    compress(root, rotations);

    // Perform successive compressions
    while (m > 1) {
        m /= 2;
        compress(root, m); 
    }

    // Update heights after balancing
    updateHeights(root);
}