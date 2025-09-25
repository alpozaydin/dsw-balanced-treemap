#include <iostream>

#include "TreeMap.h"

int main() {

    TreeMap<std::string, int> treeMap;

    treeMap.print();

    treeMap.put("tokyo", 37468000);
    treeMap.put("delhi", 28514000);
    treeMap.put("shangai", 25582000);
    treeMap.put("sao paulo", 21650000);
    treeMap.put("mexico city", 21581000);
    treeMap.put("cairo", 20076000);
    treeMap.put("mumbai", 19980000);
    treeMap.put("beijing", 19618000);
    treeMap.put("dhaka", 19578000);
    treeMap.put("osaka", 19281000);

    treeMap.print();

    return 0;
}


/* ITERATIVE CLEAR USING STACK /// 32k calls to fill up the 8mb stack size?
template<class K, class V>
void TreeMap<K, V>::clear() {
    if (!stree.root) return;

    std::stack<Node<KeyValuePair<K, V>>*> stack;
    stack.push(stree.root);

    while (!stack.empty()) {
        Node<KeyValuePair<K, V>>* node = stack.top();
        stack.pop();

        if (node->left) stack.push(node->left);
        if (node->right) stack.push(node->right);

        delete node;
    }

    stree.root = nullptr; // Set the root to nullptr after deletion
}

*/
