#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

using namespace std;

/** A class, instances of which are nodes in an HCTree.
 */
class BitInputStream {
  private:
    char buf; //one byte buffer of bits
    int nbits; //how many bits have been read from buf
    std::istream & in; //istream to use for input
  public:
    BitInputStream(std::istream & is) : in(is) {
      buf = 0; //clear buffer
      nbits = 9; //initialize bit index
    }

    /* Fill buffer from input */
    void fill();

    /* Read bits from input file and put in buffer to go to file */
    int readBit();
};

#endif
