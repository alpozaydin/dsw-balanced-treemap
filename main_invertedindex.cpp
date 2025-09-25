#include <iostream>

#include "InvertedIndex.h"

int main() {

InvertedIndex II;
    II.addDocument("document_4.txt",4);
    II.addDocument("document_1.txt",1);

    II.printInvertedIndex();
    return 0;
}
