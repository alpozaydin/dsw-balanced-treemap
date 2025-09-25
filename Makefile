CC=g++
CFLAGS=-c -ansi -Wall -pedantic-errors -O0

all: dswtree treemap invertedindex

treemap: main_treemap.o
	$(CC) main_treemap.o -o treemap

dswtree: main_dswtree.o
	$(CC) main_dswtree.o -o dswtree

İnvertedindex: main_invertedindex.o
	$(CC) main_invertedindex.o -o invertedindex

main_treemap.o: main_treemap.cpp
	$(CC) $(CFLAGS) main_treemap.cpp -o main_treemap.o

main_dswtree.o: main_dswtree.cpp
	$(CC) $(CFLAGS) main_dswtree.cpp -o main_dswtree.o

main_invertedindex.o: main_invertedindex.cpp
	$(CC) $(CFLAGS) main_invertedindex.cpp -o main_invertedindex.o

clean:
	rm *o
	rm dswtree
	rm treemap
	rm invertedindex
