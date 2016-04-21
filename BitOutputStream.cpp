#include "BitOutputStream.hpp"
#include <iostream>

/* Send buffer to the output, and clear it */
void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

/** Write the least significant bit of the argument to
 * the bit buffer, and increment the bit buffer index.
 * But flush the buffer first, if it is full.
 */

void BitOutputStream::writeBit(int i) {
  // Is bit buffer full? Then flush it.
  if (nbits == sizeof(buf)) {
    this.flush();
  }

  // Write least significant bit of i into buffer
  // at current index.
  i = i >> nbits;

  buf = buf | i;

  nbits++;

}

