#ifndef DSWTREE_H
#define DSWTREE_H

#include <iostream>
#include <cmath>
#include <stack>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class DSWTree {
public: // DO NOT CHANGE THIS PART.
    DSWTree();

    DSWTree(const DSWTree<T> &obj);

    ~DSWTree();

    bool isEmpty() const;

    int getHeight() const;
    
    const int getNodeHeight(const T& element) const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    DSWTree<T> &operator=(const DSWTree<T> &rhs);

    bool isBalanced();

    bool isBalancedHelper(Node<T> *node);

    void balance();

    void createBackbone(Node<T> *&root);

    void createCompleteTree(Node<T> *&root, int size);

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

    void rightRotation(Node<T> *parent, Node<T> *&t);

    void leftRotation(Node<T>* parent, Node<T> *&k2);

    void printRight(Node<T>* root);

    void updateHeights(Node<T> *node);

    bool insertHelper(Node<T>*& current, const T& element);

    Node<T>* copyHelper(const Node<T> *node);

    void destructorHelper(Node<T> *node);

    int getSizeHelper(const Node<T> *root) const;

    const T &getHelper(Node<T> *node, const T &element) const;

    void compress(Node<T> *node, int m);

    Node<T>*& getRoot() { return root; } // Public getter for root

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;

private: // DO NOT CHANGE THIS PART.
    Node<T> *root;
};

template<class T>
DSWTree<T>::DSWTree() {
    /* TODO */
    root = NULL;
}

template<class T>
DSWTree<T>::DSWTree(const DSWTree<T> &obj) // copy constructor
    
    : root(copyHelper(obj.root)) {} // initializer list 

template<class T>
Node<T>* DSWTree<T>::copyHelper(const Node<T> *node) {
    if (node == NULL)
    {
        return NULL;
    }
    
    Node<T> *newNode = new Node<T>(node->element, copyHelper(node->left), copyHelper(node->right), node->height);

    return newNode;
}

template<class T>
DSWTree<T>::~DSWTree() {
    destructorHelper(root);
    root = NULL;
}

template<class T>
void DSWTree<T>::destructorHelper(Node<T> *node) {
    if (!node) return;

    destructorHelper(node->left);
    destructorHelper(node->right);

    delete node;
}

template<class T>
bool DSWTree<T>::isEmpty() const {
    
    return root == NULL;
}

template<class T>
int DSWTree<T>::getHeight() const {
   
    if (!root) // empty node 
    {
        return -1;
    }
    
    return root->height;
}

template<class T>
int DSWTree<T>::getSize() const {
    
    return getSizeHelper(root);
}

template<class T>
int DSWTree<T>::getSizeHelper(const Node<T> *root) const { // the first const: cannot modify Node<T> ojbect that *root points to
                                                           // the second const: cannot modify any member of the current object(*this)
    if (!root) return 0;

    return (getSizeHelper(root->left) + getSizeHelper(root->right) + 1);
}

template<class T>
void DSWTree<T>::updateHeights(Node<T>* node) { // no need for this fuck??
    if (!node) return;

    updateHeights(node->left);
    updateHeights(node->right);

    int leftHeight = node->left ? node->left->height : -1;
    int rightHeight = node->right ? node->right->height : -1;

    node->height = std::max(leftHeight, rightHeight) + 1;
}

template<class T>
bool DSWTree<T>::insert(const T &element) { // No duplicate data is guaranteed && must adjust heights too!
    
    if (!root) // empty tree -> create new node with the element and make it root
    {
        root = new Node<T>(element, NULL, NULL, 0);
        return true;
    }

    bool res = insertHelper(root, element);
    updateHeights(root);
    return res;
}

template<class T>
bool DSWTree<T>::insertHelper(Node<T>*& current, const T& element) {
        if (!current) {
            current = new Node<T>(element, NULL, NULL, 0);
            return true;
        }

        bool inserted;
        if (element == current->element) { // Duplicate
            return false;
        } else if (element < current->element) {
            inserted = insertHelper(current->left, element);
        } else {
            inserted = insertHelper(current->right, element);
        }

        if (inserted) // Update the height of the current node
        {
        int leftHeight = current->left ? current->left->height : -1;
        int rightHeight = current->right ? current->right->height : -1;
        current->height = std::max(leftHeight, rightHeight) + 1;
        }

        return inserted;
    }

template<class T>
bool DSWTree<T>::remove(const T &element) { 
    
    if (!root) return false;

    std::stack<Node<T>*> path;
    Node<T> *current = root;
    Node<T> *parent = NULL;
    bool found = false;

    while (current)
    {
        if (current->element == element)
        {
            found = true;
            if (!current->left && !current->right) 
            {
                if (parent) {
                    if (parent->left == current) {
                        parent->left = NULL;
                    } else {
                        parent->right = NULL;
                    }
                } else {
                    // Deleting the root node
                    root = NULL;
                }
                delete current;
                break;
            }
            else if (!current->left && current->right) // only right child
            {
                if (parent) {
                    if (parent->left == current) {
                        parent->left = current->right;
                    } else {
                        parent->right = current->right;
                    }
                } else {
                    // Deleting the root node
                    root = current->right;
                    root->height = current->right->height;
                }
                delete current;
                break;
            }
            else if (current->left && !current->right) // only left child
            {
                if (parent) {
                    if (parent->left == current) {
                        parent->left = current->left;
                    } else {
                        parent->right = current->left;
                    }
                } else {
                    // Deleting the root node
                    root = current->left;
                    root->height = current->left->height;
                }
                delete current;
                break;
            }
            else // both children 
            {
                // Find the in-order successor (smallest element in the right subtree)
                Node<T> *successor = current->right;
                Node<T> *successorParent = current;

                while (successor->left) {
                    successorParent = successor;
                    successor = successor->left;
                }

                // Replace the current node's element with the successor's element
                current->element = successor->element;

                // Remove the successor node
                if (successorParent->left == successor) {
                    successorParent->left = successor->right;
                } else {
                    successorParent->right = successor->right;
                }
                delete successor;
            }
        }
        else if (current->element < element) // move to right subtree
        {
            parent = current;
            current = current->right;
            path.push(parent);
        }
        else // move to left subtree
        {
            parent = current;
            current = current->left;
            path.push(parent);
        }
    }

    if (found)
    {
        // update heights somehow
        while (!path.empty()) {
        Node<T>* node = path.top();
        path.pop();
        node->height = std::max(node->left ? node->left->height : -1, node->right ? node->right->height : -1) + 1;
        }
        updateHeights(root);
        return true;
    } else
    {
        return false;
    }
}

template<class T>
void DSWTree<T>::removeAllNodes() {
    
    if (!root) return;
    destructorHelper(root);
    root = NULL; // Set root to null
}

template<class T>
const T &DSWTree<T>::get(const T &element) const {
    /* TODO */
    if (!root) 
    {
        throw NoSuchItemException();
    }

    Node<T> *current = root;
    while (current) {
        if (current->element == element) 
        {
            return current->element;
        } else if (element < current->element) 
        {
            current = current->left;
        } else 
        {
            current = current->right;
        }
    }

    throw NoSuchItemException(); // reached empty node -> element not found
}

template<class T>
const T &DSWTree<T>::getHelper(Node<T> *node, const T &element) const { // No need!
    if (!node) {
        throw NoSuchItemException(); // Element not found
    }

    if (node->element == element) // Found the element
    {
        return node->element; 
    } else if (element < node->element) 
    {
        return getHelper(node->left, element); // Search in the left subtree
    } else 
    {
        return getHelper(node->right, element); // Search in the right subtree
    }
}

template<class T>
void DSWTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) 
    {
        if (isEmpty())
        {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }

        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == inorder) 
    {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) 
    {
        if (isEmpty())
        {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
void DSWTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (!node) // empty node given 
    {
        return;
    }

    if (tp == preorder) 
    {
        
        std::cout << "\t" << node->element;
        if (node->left)
        {
            std::cout << "," << std::endl;
        }
        
        print(node->left, preorder);
        if (node->right)
        {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);

    } else if (tp == inorder) 
    {

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == postorder) 
    {

        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->element;
    }
}

template<class T>
void DSWTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void DSWTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
DSWTree<T> &DSWTree<T>::operator=(const DSWTree<T> &rhs) {
    
    if (this != &rhs) // pass this as a reference for efficiency 
    {
        destructorHelper(root);
        root = copyHelper(rhs.root);
    }

    return *this;
}

template <class T>
void DSWTree<T>::balance() {
    createBackbone(root);
    createCompleteTree(root, getSize());
}

template <class T>
bool DSWTree<T>::isBalanced() {
    return isBalancedHelper(root);
}

template <class T>
bool DSWTree<T>::isBalancedHelper(Node<T> *node) {
    
    if (!node) return true;

    int leftHeight = (node->left) ? node->left->height : -1;
    int rightHeight = (node->right) ? node->right->height : -1;

    if (std::abs(leftHeight - rightHeight) > 1)
    {
        return false;
    }
    else
    {
        return (isBalancedHelper(node->left) && isBalancedHelper(node->right));
    }
}

template <class T>
void DSWTree<T>::rightRotation(Node<T>* parent, Node<T>*& k2) {
    Node<T>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    // Update heights
    k2->height = std::max(k2->left ? k2->left->height : -1,
                          k2->right ? k2->right->height : -1) + 1;
    k1->height = std::max(k1->left ? k1->left->height : -1,
                          k1->right ? k1->right->height : -1) + 1;
    // Update parent's child pointer
    if (parent == NULL) {
        root = k1;
    } else if (parent->left == k2) {
        parent->left = k1;
    } else {
        parent->right = k1;
    }
    k2 = k1; // Update the reference
}


template <class T>
void DSWTree<T>::leftRotation(Node<T>* parent, Node<T>*& k2) {
    Node<T>* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    // Update heights
    k2->height = std::max(
        k2->left ? k2->left->height : -1,
        k2->right ? k2->right->height : -1
    ) + 1;
    k1->height = std::max(
        k1->left ? k1->left->height : -1,
        k1->right ? k1->right->height : -1
    ) + 1;

    // Update parent's child pointer
    if (parent == NULL) {
        root = k1;
    } else if (parent->left == k2) {
        parent->left = k1;
    } else if (parent->right == k2) {
        parent->right = k1;
    }

    // Update the reference to point to the new subtree root
    k2 = k1;
}



template <class T>
void DSWTree<T>::createBackbone(Node<T> *&root) {
    Node<T>* parent = root;
    Node<T>* grandParent = NULL;

    while (parent != NULL) {
        if (parent->left != NULL) {
            rightRotation(grandParent, parent);
            if (grandParent == NULL) {
                root = parent;
            } else {
                grandParent->right = parent;
            }
            // No need to update `grandParent` here
        } else {
            grandParent = parent;
            parent = parent->right;
        }
    }
}


template <class T>
void DSWTree<T>::printRight(Node<T>* root) {
    Node<T>* temp = root; // Start from the root
    while (temp) {
        std::cout << temp->element;  // Print the current node's value
        if (temp->right) {
            std::cout << " -> ";  // Indicate the link to the next node
        }
        temp = temp->right; // Move to the next node in the backbone
    }
    std::cout << std::endl;
}

template<class T>
void DSWTree<T>::compress(Node<T>* root, int m) {
    Node<T>* grandParent = NULL;
    Node<T>* parent = root;
    Node<T>* child = NULL;

    for (int i = 0; i < m; i++) {
        if (parent != NULL && parent->right != NULL) {
            child = parent->right;

            // Perform left rotation at 'parent' with 'grandParent' as its parent
            leftRotation(grandParent, parent);

            // After rotation, 'parent' now points to 'child', which is the new subtree root
            // Update 'grandParent' and 'parent' for next iteration
            grandParent = parent;
            parent = parent->right;
        } else {
            break;
        }
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


template<class T>
const T &DSWTree<T>::getCeiling(const T &element) const { // the smallest element greater than the given element 
    if(!root) throw NoSuchItemException();

    Node<T> *current = root;
    Node<T> *ceiling = NULL;
    while (current)
    {
        if (element > current->element)
        {
            current = current->right;
        }
        else // element < current->element, so current is a potential candidate for the ceiling element
        {
            ceiling = current;
            current = current->left;
        }
    }

    if (ceiling)
    {
        return ceiling->element;
    }
    else
    {
        throw NoSuchItemException();
    }
}

template<class T>
const T &DSWTree<T>::getFloor(const T &element) const {
    if(!root) throw NoSuchItemException();

    Node<T> *current = root;
    Node<T> *floor = NULL;
    while (current)
    {
        if (element >= current->element) // element > current->element, so current is a potential candidate for the floor element
        {
            floor = current;
            current = current->right;
        }
        else 
        {
            current = current->left;
        }
    }

    if (floor)
    {
        return floor->element;
    }
    else
    {
        throw NoSuchItemException();
    }
}

template<class T>
const T &DSWTree<T>::getMin() const {
    
    if (!root)
    {
        throw NoSuchItemException();
    }

    Node<T> *temp = root;
    while (temp->left)
    {
        temp = temp->left;
    }
    
    return temp->element;
}

template<class T>
const T &DSWTree<T>::getMax() const {
    
    if (!root)
    {
        throw NoSuchItemException();
    }

    Node<T> *temp = root;
    while (temp->right)
    {
        temp = temp->right;
    }
    
    return temp->element;
}

template<class T>
const T &DSWTree<T>::getNext(const T &element) const {
        if(!root) throw NoSuchItemException();

    Node<T> *current = root;
    Node<T> *ceiling = NULL;
    while (current)
    {
        if (element >= current->element)
        {
            current = current->right;
        }
        else // element < current->element, so current is a potential candidate for the ceiling element
        {
            ceiling = current;
            current = current->left;
        }
    }

    if (ceiling)
    {
        return ceiling->element;
    }
    else
    {
        throw NoSuchItemException();
    }
}

template<class T>
const int DSWTree<T>:: getNodeHeight(const T& element) const {
    
    if ( !root ) return -1;

    Node<T> *current = root;
    while (current) {
        if (current->element == element) 
        {
            return current->height;
        }
        else if (current->element < element)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }

    return -1;
}

#endif //DSWTREE_H
