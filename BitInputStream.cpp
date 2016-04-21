#include "BitInputStream.hpp"
#include <iostream>

/* Fill buffer from input */
void BitInputStream::fill() {
  buf = in.get();
  nbits = 0;
}

/** Read the next bit from the bit buffer.
 * Fill the buffer from the input stream first if needed.
 * Return 1 if the bit read is 1;
 * return 0 if the bit read is 0.
 *
 */
int BitInputStream::readBit() {
  //If all bits in the buffer are read, fill the buffer first.
  if (nbits == 8) {
    this->fill();
  }
  return 0;

  //Get the bit at the appropriate location in the bit
  //buffer, and return the appropriate int.




  

  //Increment the index
}
