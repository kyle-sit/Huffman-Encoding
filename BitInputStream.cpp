
/*
 * Filename: BSTNode.hpp
 * Name: Kyle Sit
 * Date: 4/4/16
 * Description: Contains class definiton for our Binary Search Tree 
 * Node class and contains member methods and variables.
 */
#include "BitInputStream.hpp"
#include <iostream>

  /* 
   * Function name: constructor
   * Purpose: initialize a BSTNode with the given data item
   * Parameters: d - the data to be saved in the node
   * Return: none
   */
/* Fill buffer from input */
void BitInputStream::fill() {
  buf = 0;
  buf = in.get();
  nbits = 1;
}

  /* 
   * Function name: constructor
   * Purpose: initialize a BSTNode with the given data item
   * Parameters: d - the data to be saved in the node
   * Return: none
   */
/** Read the next bit from the bit buffer.
 * Fill the buffer from the input stream first if needed.
 * Return 1 if the bit read is 1;
 * return 0 if the bit read is 0.
 *
 */
int BitInputStream::readBit() {
  int charSize = 8;
  //If all bits in the buffer are read, fill the buffer first.
  if (nbits == charSize + 1) {
    this->fill();
  }

  //Get the bit at the appropriate location in the bit
  //buffer, and return the appropriate int.
  char temp = buf;
  temp = temp << (nbits - 1);
  temp = temp >> (charSize - 1);

  //Increment the index
  nbits++;
  
  return (int)temp;
}
