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


	
	//char nextChar1, nextChar2, nextChar3;;
  //int finalInt;
  int uniqueVals;
	vector<int> freqs(vectorSize,0);
  char charArray[BUFSIZ];
	//loop through header, if a frequency is greater than 0, populate a
	//frequency vector spot with the appropriate frequency, which is the
	//char we just processed 

	for (int i = 0; i < (int)freqs.size(); i++) {
    in.read(charArray, 3);
    int* loc = (int*)charArray;
    int temp = *loc;
    uniqueVals = uniqueVals + temp;
    
    freqs[i] = temp;

		//this >> knows to get one int, stop at the newline
		//the next time it grabs, it'll be pointing at the newline but
		//knows to skip it
		/*in >> nextChar1;
    in >> nextChar2;
    in >> nextChar3;
		if ((nextChar1 != '0') && (nextChar2 != '0') && (nextChar3 != '0')) {
      finalInt = 0;
      nextChar1 = nextChar1 << 16;
      nextChar2 = nextChar2 << 8;
      finalInt = finalInt | nextChar1 | nextChar2 | nextChar3;
      freqs[i] = finalInt;
      uniqueVals = uniqueVals + finalInt;
      cerr << "Processed a significant 3 bytes from header \n";
      */
    /*
   finalInt = finalInt | nextChar;
      nextChar = 0;
      in >> nextChar;
      nextChar = nextChar << 8;
      finalInt = finalInt | nextChar;
      nextChar = 0;
      in >> nextChar;
      finalInt = finalInt | nextChar;
			freqs[i] = finalInt;
      */
		//}
  
    /*
    else {
    }
    */
	}
	
	//build our huffman tree	
	HCTree huffTree;
	huffTree.build(freqs);
	
	//pointer is currently at the last newline right before huffcode, we
	//need to eat up the newline before processing actual huff code

	//(void) in.get();
  
  // Create inputstream
  BitInputStream bitIn = BitInputStream(in);
	
	//now our poitner is at beginning of huffcode, we can begin decoding,
	//and cast the returned int value to a char and write to our final
	//outfile, which is written like "AAABBC" for example
  //int uniqueVals = in.get();
  //cerr << uniqueVals << "\n\n\n";
	char testChar;
	for (int i = 0; i < uniqueVals; i++) {
		testChar = (char)huffTree.decode(bitIn);
		if (in.eof()) {
      cerr << "Broke cause EOF";
			break;
		}
	  out << testChar;
	}

	in.close();
	out.close();

	return 0;
}
