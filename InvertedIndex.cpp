#include "InvertedIndex.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

InvertedIndex::InvertedIndex() {

}

InvertedIndex::InvertedIndex(const InvertedIndex &obj) {

    this->invertedIndex = obj.invertedIndex; // uses operator= of BST
}

InvertedIndex::~InvertedIndex() {

}

TreeMap<std::string, std::vector<int> >  &InvertedIndex::getInvertedIndex() {

    return invertedIndex;
}


InvertedIndex &InvertedIndex::addDocument(const std::string &documentName, int docid) {
    /* TODO */
    std::ifstream file(documentName.c_str(), std::ifstream::in);

    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << documentName << std::endl;
        return *this;
    }

    std::string word;
    while (file >> word) {
        // If the word exists, get its vector
        if (invertedIndex.containsKey(word)) {
            const std::vector<int> &id_vector = invertedIndex.get(word);
            // Make a modifiable copy
            std::vector<int> modified_id_vector = id_vector;

            // Insert docid into modified_id_vector maintaining sorted order and no duplicates
            // Binary search for insertion point
            int left = 0;
            int right = (int)modified_id_vector.size() - 1;
            int insertPos = (int)modified_id_vector.size(); 
            bool found = false;

            while (left <= right) {
                int mid = (left + right) / 2;
                if (modified_id_vector[mid] == docid) {
                    found = true;
                    break;
                } else if (modified_id_vector[mid] < docid) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }

            // If not found, 'left' will be the insertion position
            if (!found) {
                insertPos = left;
                modified_id_vector.insert(modified_id_vector.begin() + insertPos, docid);
                invertedIndex.put(word, modified_id_vector);
            }

        } else {
            // Add a new word with the document ID
            std::vector<int> id_vector;
            id_vector.push_back(docid);
            invertedIndex.put(word, id_vector);
        }
    }

    file.close();
    return *this;

}

std::vector<int> InvertedIndex::search(const std::string &query) {
    std::vector<int> result;

    // Step 1: Split the query string into individual words
    size_t length = query.length();
    size_t start = 0;
    std::vector<std::string> queryWords;
    for (size_t i = 0; i <= length; ++i) {
        if (i == length || query[i] == ' ') {
            if (i > start) {
                std::string word;
                for (size_t j = start; j < i; ++j) {
                    word += query[j];
                }
                // (Optional) Remove any trailing punctuation if necessary
                // but according to the PDF, query should be handled as given.
                // If needed:
                // while (!word.empty() && (word.back() < 'a' || word.back() > 'z')) {
                //     word.pop_back();
                // }

                if (!word.empty()) {
                    queryWords.push_back(word);
                }
            }
            start = i + 1;
        }
    }

    // If no words are present in the query, return empty result
    if (queryWords.empty()) {
        return result;
    }

    // Step 2 and 3: For each query word, retrieve docids and merge into result
    for (size_t w = 0; w < queryWords.size(); ++w) {
        if (!invertedIndex.containsKey(queryWords[w])) {
            // If a query word isn't in the index, that just means it contributes no docids.
            // Since we are doing union, we just skip it.
            continue;
        }

        const std::vector<int>& docIds = invertedIndex.get(queryWords[w]);

        if (result.empty()) {
            // If result is empty, just copy docIds directly.
            result = docIds;
        } else {
            // Merge docIds into result (union of two sorted vectors)
            std::vector<int> merged;
            merged.reserve(result.size() + docIds.size());
            size_t i = 0, j = 0;
            while (i < result.size() && j < docIds.size()) {
                if (result[i] == docIds[j]) {
                    // Same element, add one of them
                    merged.push_back(result[i]);
                    i++;
                    j++;
                } else if (result[i] < docIds[j]) {
                    merged.push_back(result[i]);
                    i++;
                } else {
                    merged.push_back(docIds[j]);
                    j++;
                }
            }

            // Add remaining elements from result (if any)
            while (i < result.size()) {
                merged.push_back(result[i]);
                i++;
            }

            // Add remaining elements from docIds (if any)
            while (j < docIds.size()) {
                merged.push_back(docIds[j]);
                j++;
            }

            result = merged;
        }
    }

    // 'result' now contains the union of docids for all query words, sorted and without duplicates.
    return result;
}


InvertedIndex & InvertedIndex::printInvertedIndex() const {

    invertedIndex.print();
    
}

InvertedIndex &InvertedIndex::operator=(const InvertedIndex &rhs) {

    this->invertedIndex = rhs.invertedIndex; // uses operator= of BST

    return *this;
}
