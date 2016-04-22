/*
 * Filename: HCNode.cpp
 * Name: Kyle Sit
 * Date: 4/21/16
 * Description: Contains implementation of HCNode methods 
 */

#include "HCNode.hpp"
#include <iostream>

typedef unsigned char byte;

using namespace std;

/* 
 * Function name: overloaded operator less than
 * Purpose: prioritize our nodes to create minHeap in main
 * Parameters: other - reference to other node to compare
 * Return: true or false
 */
bool HCNode::operator<(const HCNode& other) const {
  if( count != other.count ) {
    return count > other.count;
  }

  return symbol > other.symbol;
}

/* 
 * Function name: comp
 * Purpose: used to compare nodes when we build our tree
 * Parameters: one - first node to compare
 *             other - second node to compare
 * Return: none
 */
bool comp(HCNode* one, HCNode* other) {
  if( one->symbol != other->symbol ) {
    return one->symbol > other->symbol;
  }
  return false;
}
