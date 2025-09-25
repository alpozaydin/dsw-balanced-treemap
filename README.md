# DSW TreeMap & Inverted Index

A comprehensive implementation of self-balancing binary search trees using the Day-Stout-Warren (DSW) algorithm, with applications in TreeMap data structure and text retrieval systems.

## Overview

This project demonstrates advanced tree data structures and algorithms through two main components:

1. **DSWTree**: A self-balancing binary search tree using the Day-Stout-Warren algorithm
2. **TreeMap**: A key-value mapping data structure built on top of DSWTree
3. **InvertedIndex**: A text retrieval system using TreeMap for efficient document search

## Key Features

### DSWTree Implementation
- **Self-Balancing**: Automatically maintains optimal tree height using DSW algorithm
- **Complete Tree Structure**: Transforms arbitrary BSTs into complete binary trees
- **Efficient Operations**: O(log n) search, insert, delete operations
- **Rotation-Based Balancing**: Uses left/right rotations for tree restructuring

### TreeMap Data Structure
- **Key-Value Storage**: Generic template supporting any comparable key types
- **Sorted Ordering**: Maintains keys in natural sorted order
- **Range Operations**: Support for ceiling, floor, submap operations
- **Dynamic Balancing**: Automatic rebalancing for optimal performance

### Inverted Index System
- **Text Processing**: Parses documents and builds word-to-document mappings
- **Efficient Search**: Fast multi-word query processing
- **Sorted Document Lists**: Maintains sorted, duplicate-free document IDs
- **Query Processing**: Supports both single-word and multi-word searches

## Algorithm Details

### Day-Stout-Warren (DSW) Algorithm

The DSW algorithm transforms any binary search tree into a complete binary tree in two phases:

#### Phase 1: Create Backbone (Vine)
```cpp
// Transform tree into right-skewed linked list
while (current_node != null) {
    if (current_node has left child) {
        rotate_right(current_node, left_child);
        current_node = left_child; // now parent
    } else {
        current_node = current_node->right;
    }
}
```

#### Phase 2: Create Complete Tree
```cpp
// Transform backbone into complete binary tree
m = 2^floor(log2(n+1)) - 1;
perform n-m left rotations from top;
while (m > 1) {
    m = m / 2;
    perform m left rotations from top;
}
```

### TreeMap Operations
- **Insert/Update**: `put(key, value)` - O(log n)
- **Retrieve**: `get(key)` - O(log n)
- **Delete**: `deletekey(key)` - O(log n)
- **Range Queries**: `subMap(fromKey, toKey)` - O(log n + k)
- **Boundary Operations**: `firstEntry()`, `lastEntry()`, `ceilingEntry()`

### Inverted Index Processing
1. **Document Parsing**: Split text into words, normalize case
2. **Index Building**: Map each word to sorted list of document IDs
3. **Query Processing**: Intersect document lists for multi-word queries
4. **Result Ranking**: Return combined document IDs

## Build and Run

### Prerequisites
- C++11 compatible compiler (g++, clang++)
- Make (optional)

### Compilation

#### TreeMap Demo
```bash
g++ -std=c++11 -g -Wall -pedantic-errors -O0 main_treemap.cpp -o treemap_demo
./treemap_demo
```

#### Inverted Index Demo
```bash
g++ -std=c++11 -g -Wall -pedantic-errors -O0 main_invertedindex.cpp InvertedIndex.cpp -o invertedindex_demo
./invertedindex_demo
```

#### DSW Tree Demo
```bash
g++ -std=c++11 -g -Wall -pedantic-errors -O0 main_dswtree.cpp -o dswtree_demo
./dswtree_demo
```

### Sample Output

#### TreeMap Demo
```
# Printing the tree map ...
# DSWTree<KeyValuePair<K, V> > stree:
Empty
# Printing is done.

# Printing the tree map ...
# DSWTree<KeyValuePair<K, V> > stree:
        tokyo: 37468000
    shangai: 25582000
        sao paulo: 21650000
mexico city: 21581000
        cairo: 20076000
    mumbai: 19980000
        beijing: 19618000
    dhaka: 19578000
        osaka: 19281000
    delhi: 28514000
# Printing is done.
```

#### Inverted Index Demo
```
# Printing the inverted index ...
# TreeMap<std::string, std::vector<int> > invertedIndex:
        document_4: [4]
    document_1: [1]
# Printing is done.
```

## Project Structure

```
dsw-treemap-invertedindex/
├── README.md                 # This file
├── DSWTree.h                 # Self-balancing BST implementation
├── TreeMap.h                 # Key-value mapping data structure
├── KeyValuePair.h            # Key-value pair template
├── InvertedIndex.h/.cpp      # Text retrieval system
├── Node.h                    # BST node structure
├── NoSuchItemException.h     # Exception handling
├── main_treemap.cpp          # TreeMap demonstration
├── main_invertedindex.cpp    # Inverted index demonstration
├── main_dswtree.cpp          # DSW tree demonstration
├── document_*.txt            # Sample text documents
└── Makefile                  # Build configuration
```

## Technical Highlights

### Data Structure Design
- **Template Programming**: Generic implementations for type flexibility
- **Memory Management**: RAII with proper cleanup and exception safety
- **Iterator Support**: Range-based operations for efficient traversal
- **Exception Handling**: Robust error management throughout

### Algorithm Complexity
- **DSW Balancing**: O(n) time complexity for complete tree transformation
- **Tree Operations**: O(log n) average case for all operations
- **Inverted Index**: O(k log n) for k-word queries across n documents
- **Space Efficiency**: O(n) space for n elements with optimal height

### Performance Optimizations
- **Rotation Efficiency**: Minimal pointer manipulation during balancing
- **Cache Locality**: Optimized memory layout for better performance
- **Sorted Storage**: Enables efficient range queries and binary search
- **Dynamic Rebalancing**: Maintains optimal tree structure automatically

## Use Cases

### TreeMap Applications
- **Database Indexing**: Efficient key-value storage and retrieval
- **Configuration Management**: Sorted parameter storage
- **Range Queries**: Time-series data analysis
- **Symbol Tables**: Compiler and interpreter implementations

### Inverted Index Applications
- **Search Engines**: Document retrieval and ranking
- **Text Mining**: Content analysis and keyword extraction
- **Information Retrieval**: Academic paper and article search
- **Content Management**: Website and document indexing

## Academic Context

*This project was developed as part of METU CENG213 (Data Structures) coursework, Fall 2024. It demonstrates advanced tree algorithms, self-balancing data structures, and practical applications in information retrieval systems.*

## Related Projects

- [Hospital Discrete Event Simulation](../hospital-simulation) - Custom linked lists and event scheduling
- [Social Graph with Hash Table](../social-graph-hashtable) - Graph algorithms and hash table implementation

## License

This project is for educational purposes. Please respect academic integrity policies.
