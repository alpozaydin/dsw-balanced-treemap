#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <vector>

#include "KeyValuePair.h"
#include "DSWTree.h"

template<class K, class V>
class TreeMap {
public: // DO NOT CHANGE THIS PART.
    TreeMap();

    void clear();

    const V &get(const K &key) const;

    V &operator[](const K &key) const;

    void put(const K &key, const V &value);

    bool containsKey(const K &key); // Declaration of the new method

    bool deletekey(const K &key); // Declaration of the new method

    const KeyValuePair<K, V> &ceilingEntry(const K &key);

    const KeyValuePair<K, V> &firstEntry();

    const KeyValuePair<K, V> &lastEntry();

    std::vector<KeyValuePair<K, V> > subMap(K fromKey, K toKey) const;

    void print() const;

    int size();

    void balance();

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    DSWTree<KeyValuePair<K, V> > stree;

};

template<class K, class V>
TreeMap<K, V>::TreeMap() {}

template<class K, class V>
void TreeMap<K, V>::clear() {

    stree.removeAllNodes();
}

template<class K, class V>
const V &TreeMap<K, V>::get(const K &key) const {
    
    // Create a KeyValuePair to use as a search element (only key matters for comparison)
    KeyValuePair<K, V> searchKey(key, V()); // Temporary pair with the key and a default value for V
    
    try {
        // Use DSWTree's get method to find the KeyValuePair
        const KeyValuePair<K, V> &result = stree.get(searchKey);

        // Return the value associated with the key
        return result.getValue();
    } catch (NoSuchItemException &e) {
        // If the key is not found, rethrow the exception
        throw NoSuchItemException();
    }
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::ceilingEntry(const K &key) {
    
    KeyValuePair<K, V> kvp(key, V());
    return stree.getCeiling(kvp);
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::firstEntry() { // smallest key
    
    return stree.getMin();
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::lastEntry() { // greatest key
    
    return stree.getMax();
}

template<class K, class V>
std::vector<KeyValuePair<K, V> > TreeMap<K, V>::subMap(K fromKey, K toKey) const {
    std::vector<KeyValuePair<K, V> > result;

    // Create KeyValuePair objects with fromKey and toKey
    // Values are default-constructed since they are not used in comparisons
    KeyValuePair<K, V> fromElement(fromKey, V());
    KeyValuePair<K, V> toElement(toKey, V());

    // Use stree.subMap to fill the result vector
    stree.subMap(fromElement, toElement, result);

    return result;
}

template<class K, class V>
void TreeMap<K, V>::print() const {

    std::cout << "# Printing the tree map ..." << std::endl;

    std::cout << "# DSWTree<KeyValuePair<K, V> > stree:" << std::endl;
    stree.printPretty();

    std::cout << "# Printing is done." << std::endl;
}

template<class K, class V>
void TreeMap<K, V>::put(const K &key, const V &value) {
    KeyValuePair<K, V> kvp(key, value);

    if (containsKey(key)) {
        // Key already exists, just update the value.
        // Get the existing pair
        const KeyValuePair<K, V> &existingPair = stree.get(kvp);
        // Remove constness and update the value
        KeyValuePair<K, V> &modifiablePair = const_cast<KeyValuePair<K, V>&>(existingPair);
        modifiablePair.setValue(value);
    } else {
        // Key does not exist, insert normally
        stree.insert(kvp);
    }
}

template<class K, class V>
V& TreeMap<K, V>::operator[](const K &key) const {
    
    KeyValuePair<K, V> kvp(key, V());
    //return stree.get(kvp).getValue();
    return const_cast<TreeMap<K, V>*>(this)->stree.get(kvp).getValue();
}

template<class K, class V>
bool TreeMap<K, V>::deletekey(const K &key) {
     // Create a KeyValuePair with the key and a dummy value
    KeyValuePair<K, V> kvp(key, V());

    // Use the remove function of DSWTree
    return stree.remove(kvp);
}

template<class K, class V>
bool TreeMap<K, V>::containsKey(const K &key) {

    try
    {
        get(key);
        return true;
    }
    catch(NoSuchItemException) // (const NoSuchItemException &) 
    {
        return false;
    }   
}

template<class K, class V>
void TreeMap<K, V>::balance() {
    stree.balance();
}

#endif //TREEMAP_H
