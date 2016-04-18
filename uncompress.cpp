/*
 * Filename: uncompress.cpp
 * Name: Kyle Sit
 * Date: 4/12/16
 * Description: Implements the decompression of a code using huffman tree.
 */

#include "HCTree.hpp"
#include "HCNode.hpp"
#include <iostream>
#include <vector>
#include<fstream>
#include<string>

using namespace std;
int uncompress(int argc, char*argv[]);
int vectorSize = 256;


int main(int argc, char* argv[]) {
	(void) uncompress (argc, argv);
	return 1;
}
/* 
 * Function name: uncompress
 * Purpose: Runs the user interface and command line prompts for use 
 * of the huffman code tree.
 * Parameters: 
 *   argc - number of arguments
 *   argv - array containing arguments
 * Return: 0 or -1 representing true or false repsectively
 */
int uncompress(int argc, char* argv[])
{
	//Check for Arguments
	if(argc != 3){
		cout << "Invalid number of arguments.\n" 
			<< "Usage: ./uncompress <input filename> <output filename>.\n";
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
	
	
	int nextChar;
	vector<int> freqs(vectorSize,0);
	for (int i = 0; i < vectorSize; i++) {
		//std::getline(in, nextChar);
		//this knows to get one int, stop at the newline
		//the next time it grabs, it'll be pointing at the newline but
		//knows to skip it
		in >> nextChar;
		if (nextChar != 0) {
			freqs[i] = nextChar;
			cerr << "Populated with" << i << "\n";
			cerr << "NextChar was " << nextChar;
		}
	}
	
	
	HCTree huffTree;
	huffTree.build(freqs);
	
	//might have to increment pointer once before, because we haven't
	//skipped the last newline before the huffman encoding
	int testChar = in.get();	
	while (!in.eof()) {
		out << (char)huffTree.decode(in);
		cerr << "Looping once\n";
	}
	

	in.close();
	out.close();

	return 0;
}
