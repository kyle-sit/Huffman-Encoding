# A simple makefile for CSE 100 PA2

CC=g++
#CXXFLAGS=-std=c++11 -g
CXXFLAGS = -gdwarf-3 -Wall -std=c++11
LDFLAGS=-g

all: compress uncompress

compress: compress.cpp HCNode.o HCTree.o
	$(CC) -o compress $(CXXFLAGS) compress.cpp 

uncompress: uncompress.cpp HCNode.o HCTree.o
	$(CC) -o uncompress $(CXXFLAGS) uncompress.cpp HCNode.o HCTree.o

HCTree.o: HCNode.hpp HCTree.hpp

HCNode.o: HCNode.hpp

BitOutputStream.o: BitOutputStream.hpp

BitInputStream.o: BitInputStream.hpp

clean:
	rm -f compress uncompress *.o core*

