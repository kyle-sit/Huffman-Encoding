#include "HCNode.hpp"
#include <iostream>

typedef unsigned char byte;

using namespace std;

bool HCNode::operator<(const HCNode& other) const {
  if( count != other.count ) {
    return count > other.count;
  }

  return symbol > other.symbol;
}

bool comp(HCNode* one, HCNode* other) {
  if( one->symbol != other->symbol ) {
    return one->symbol > other->symbol;
  }
  return false;
}
