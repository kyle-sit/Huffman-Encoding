/*
 * Filename: compress.cpp
 * Name: Kyle Sit, Louis Leung
 * Date: 4/12/16
 * Description: Implements the compression of a code using huffman tree.
 */

#include "HCTree.hpp"
#include "HCNode.hpp"
#include <iostream>
#include <vector>
#include<fstream>
#include<string>
#include "BitOutputStream.hpp"

using namespace std;

int compress(int argc, char * argv[]);
int asciiSize = 256;

int main(int argc, char* argv[]) {
	compress(argc, argv);
	return 1;
}

/* 
 * Function name: compress
 * Purpose: Runs the user interface and command line prompts for use 
 * of the huffman code tree.
 * Parameters: 
 *   argc - number of arguments
 *   argv - array containing arguments
 * Return: 0 or -1 representing true or false repsectively
 */

int compress(int argc, char* argv[])
{
	//Check for Arguments
	if(argc != 3){
		cout << "Invalid number of arguments.\n" 
			<< "Usage: ./compress <input filename> <output filename>.\n";
		return -1;
	}

	//Open files 
	ifstream in;
	in.open(argv[1], ios::binary);
	ofstream out;
	out.open(argv[2], ios::binary);

	//Check if input file was actually opened
	if(!in.is_open()) 
	{
		if(out.is_open()) {
			out.close();
		}
		cout<< "Invalid input file. No file was opened. Please try again.\n";
		return -1;
	}

	//Check if output file was actually opened
	if(!out.is_open())
	{
		in.close();
		cout<< "Invalid output file. No file was opened. Please try again.\n";
		return -1;
	}

	//Check for empty file
	in.seekg(0, ios_base::end); 
	unsigned int len = in.tellg();
	if(len==0) 
	{
		cout << "The input file is empty. \n";
		return -1;
	}

	//Resets the stream to beginning of file
	in.seekg(0, ios_base::beg); 

  //create output stream
	BitOutputStream bitOut = BitOutputStream(out);

	int nextChar;

	//create vector of size 256 zero initialized, then fill in the
	//appropriate slots according to ASCII value of whatever chars you read
	//from infile 
	vector<int> freqs(256,0);
  char charToStore;
  int tempInt;
  int uniqueValCount = 0;
	while ((nextChar = in.get()) != EOF) {
		freqs[(char)nextChar] = freqs[(char)nextChar] + 1;
	}
	
	for (vector<int>::iterator i = freqs.begin(); i != freqs.end(); i++) {
    /* if the frequency was 0, put in a null char */
    if (*i == 0) {
      out << "000";
      //cerr << "no frequency here, Stored a 420\n";
    }
    /* frequency wasn't 0, put in 3 chars representing that frequency, instead
     * so it's 3 bytes not 4, since max freq is around ~10 mil, able to be
     * stored in 3 bytes */
    else {
      tempInt = *i;
      for (int j = 0; j < 3; j++) {
        switch (j) {
          case 0:
            charToStore = tempInt & 0xFF0000;
            break;
          case 1:
            charToStore = tempInt & 0xFF00;
            break;
          case 2:
            charToStore = tempInt & 0xFF;
            break;
        }
       out << charToStore;
       //cerr << "Stored a byte of significant data \n" << charToStore << "\n";
      }
      //uniqueValCount++;
      //cerr << "Stored a significant byte(s)";
		//out << *i;
		//out << "\n";
    }
  }
  //out << uniqueValCount;
	
	//create a tree, built based on 
	HCTree huffTree;
	huffTree.build(freqs);

	in.clear();
	in.seekg(0, ios::beg);

  while ((nextChar = in.get()) != EOF) {
		huffTree.encode((char)nextChar, bitOut);
	}
	
	bitOut.flush();

	in.close();
	out.close();

	return 1;
}

