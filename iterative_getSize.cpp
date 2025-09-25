#include <stack>
#include "DSWTree.h"

template<class T>
int DSWTree<T>::getSize() const {
    if (isEmpty()) return 0;

    int count = 0;
    std::stack<Node<T>*> nodeStack;
    Node<T>* current = root;

    while (current != nullptr || !nodeStack.empty()) {
        while (current != nullptr) {
            nodeStack.push(current);
            current = current->left;
        }

        current = nodeStack.top();
        nodeStack.pop();
        count++;

        current = current->right;
    }

    return count;
}
