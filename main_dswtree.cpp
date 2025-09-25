#include <iostream>
#include "DSWTree.h"

void testCreateBackbone() {
    // Create a DSWTree instance
    DSWTree<int> tree;

    // Insert nodes into the tree
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Output the tree in its initial state
    std::cout << "Original tree (inorder):" << std::endl;
    tree.print(inorder);

    // Call createBackbone
    tree.createBackbone(tree.getRoot());

    // Check the linked list structure
    Node<int>* current = tree.getRoot();
    bool isBackbone = true;
    while (current) {
        if (current->left) {
            isBackbone = false;
            break;
        }
        current = current->right;
    }

    // Output the result of the test
    if (isBackbone) {
        std::cout << "Success: The tree has been converted to a linked list (backbone)." << std::endl;
    } else {
        std::cout << "Failure: The tree is not a proper linked list (backbone)." << std::endl;
    }

    // Output the backbone structure
    std::cout << "Backbone structure (right-linked nodes):" << std::endl;
    tree.printRight(tree.getRoot());
}

int main() {
    testCreateBackbone();
    return 0;
}
