/*
 * Filename: BitOutputStream.cpp
 * Name: Kyle Sit
 * Date: 4/21/16
 * Description: Implementation of Outputstream methods
 */

#include "BitOutputStream.hpp"
#include <iostream>

/* 
 * Function name: flush
 * Purpose: Send buffer to the output and clear it
 * Parameters: none
 * Return: none
 */
void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf = 0;
  nbits = 1;
}

/** Write the least significant bit of the argument to
 * the bit buffer, and increment the bit buffer index.
 * But flush the buffer first, if it is full.
 */

/* 
 * Function name: writeBit
 * Purpose: Write the least significant bit of the argument to
 * the bit buffer, and increment the bit buffer index.
 * But flush the buffer first, if it is full.
 * Parameters: i - the bit to be shifted and set
 * Return: none
 */
void BitOutputStream::writeBit(int i) {
  int charSize = 8;
  // Is bit buffer full? Then flush it.
  if (nbits == charSize + 1) {
    this->flush();
  }

  // Write least significant bit of i into buffer
  // at current index
  i = (i << (charSize - nbits));

  buf = buf | i;

  nbits++;

}

