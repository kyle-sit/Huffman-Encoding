#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

using namespace std;

/** A class, instances of which are nodes in an HCTree.
 */
class BitOutputStream {
  private:
    char buf; //one byte buffer of bits
    int nbits; //how many bits have been written to buf
    std::ostream & out; //reference to output stream to use

  public:
    /* Constructor for intializing BitOutputStream */
    BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) {}
    
    /* Print buffer to outstream and clear buffer */
    void flush();

    /* Write bits out to the stream that will be displayed as chars */
    void writeBit(int i);
};

#endif
