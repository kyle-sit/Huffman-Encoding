#include "HCTree.hpp"
#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

HCTree::~HCTree() {
  deleteAll( root );
}

void HCTree::deleteAll(HCNode* n) {
  /** If current node is null: return */
  if( n == nullptr ) {
    return;
  }

  /** Recursively delete left subtree */
  deleteAll( n->c0 );

  /** Recursively delete right subtree */
  deleteAll( n->c1 );

  /** Delete current node */
  delete n;
  n = NULL;
  return;
}

void HCTree::build(const vector<int>& freqs) {
  // Build our leaves vector from the vector of int frequencies
  int i = 0;
  for( i = 0; i < (signed int) freqs.capacity(); i++ ) {
    if( freqs[i] != 0 ) {
      leaves[i] = new HCNode(freqs[i], (unsigned char)(i), 0, 0, 0);
    }
  }

  // Insert these values into a minHeap priority queue
  std::priority_queue<HCNode*,vector<HCNode*>, HCNodePtrComp> minHeap;
  for( i = 0; i < (signed int) leaves.capacity(); i++ ) {
    if( leaves[i] != nullptr ) {
       minHeap.push( leaves[i] );
    }
  }

  // Now that minHeap is set up, start popping values and creating trees
  while( minHeap.size() > 0 ) {
    HCNode* temp1 = minHeap.top();
    minHeap.pop();
    
    // If we just popped off the last item, meaning we have our final tree
    if( minHeap.size() == 0) {
      root = temp1;
      return;
    }
    
    // Otherwise continue popping
    HCNode* temp2 = minHeap.top();
    minHeap.pop();

    // Two smallest elements have been retrieved so create new tree
    HCNode* newTree = new HCNode((temp1->count + temp2->count), 0, 0, 0, 0);
    temp1->p = newTree;
    temp2->p = newTree;
    
    // Sort left and right alphabetically
    if( comp( temp1, temp2 ) ) {
      newTree->c0 = temp2;
      newTree->c1 = temp1;
      newTree->symbol = temp1->symbol;
    }
    else {
      newTree->c0 = temp1;
      newTree->c1 = temp2;
      newTree->symbol = temp2->symbol;
    }

    // Push new tree onto the minHeap
    minHeap.push( newTree );
  }
}

void HCTree::encode(byte symbol, BitOutputStream& out) const {

  HCNode* temp = leaves[ (int)symbol ];
  std::string backward;
  HCNode* temp2 = temp->p;
  // Only root case
  if( temp2 == NULL ) {
    backward += '0';
  }
  // Multiple nodes
  while( temp2 != NULL ) {
    if( temp == temp2->c0 ) {
      backward += '0';
    }
    else {
      backward += '1';
    }
    temp = temp2;
    temp2 = temp2->p;
  }

  std::string::iterator it = backward.end();
  it--;
  while( it != backward.begin()) {
    if( *it == '0' ) {
      out.writeBit( 0 ); 
    }
    else {
    	out.writeBit( 1 );
    }
    it--;
  }

  //Get the last bit
  if( *it == '0' ) {
    out.writeBit( 0 );
  }
  else {
    out.writeBit( 1 );
  }
}


int HCTree::decode(BitInputStream& in) const {
  HCNode* tempNode = root;

  // While loop traversing the tree in huffman code path
  while( tempNode != NULL ) {
    int bit = in.readBit();
    if( tempNode->c0 == NULL && tempNode->c1 == NULL ) {
      return tempNode->symbol;
    }
    else if( bit == 0 ) {
      tempNode = tempNode->c0;
      //if we have found the code, RETURN, and do not get another int because
      //another call to decode will handle that for us. Otherwise, we need to
      //get another int because we'll still be in this while loop
      if (tempNode -> c0 == NULL && tempNode ->c1 == NULL) {
      	return tempNode->symbol;
      }
    }
    else {
      tempNode = tempNode->c1;
      //if we have found the code, RETURN, and do not get another int because
      //another call to decode will handle that for us. Otherwise, we need to
      //get another int because we'll still be in this while loop
      if (tempNode -> c0 == NULL && tempNode ->c1 == NULL) {
      	return tempNode->symbol;
      }
    }
  }
  return 1;  
}

void HCTree::encode(byte symbol, ofstream& out) const {
  // Create a temp node pointer for use
  HCNode* temp = leaves[ (int)symbol ];
  
  /* Loop through leaves and find appropriate symbol leaf
  for( int i = 0; i < leaves.size(); i++ ) {
    if( (leaves[i])->symbol == symbol ) {
      temp = leaves[i];
    }
  }*/
  
  // Loop for encoding output to stream
  std::string backward;
  HCNode* temp2 = temp->p;
  while( temp2 != NULL ) {
    if( temp == temp2->c0 ) {
      backward += '0';
    }
    else {
      backward += '1';
    }
    temp = temp2;
    temp2 = temp2->p;
  }
 
  std::string::iterator it = backward.end();
  std::string forward;
  it--;
  while( it != backward.begin() ) {
    forward += *it;
    it--;
  }
  forward += *it;

  out << forward;
}


int HCTree::decode(ifstream& in) const{
//why does this return an int
//print out everything, return presumably true or false
//
  unsigned char temp = in.get();
  HCNode* tempNode = root;

  while( tempNode != NULL ) {
    if( tempNode->c0 == NULL && tempNode->c1 == NULL ) {
      return tempNode->symbol;
    }

    else if( temp == '0' ) {
      tempNode = tempNode->c0;
      //if we have found the code, RETURN, and do not get another int because
      //another call to decode will handle that for us. Otherwise, we need to
      //get another int because we'll still be in this while loop
      if (tempNode -> c0 == NULL && tempNode ->c1 == NULL) {
      	return tempNode->symbol;
      }
      else {
      	temp = in.get();
      }
    }
    else {
      tempNode = tempNode->c1;
      //if we have found the code, RETURN, and do not get another int because
      //another call to decode will handle that for us. Otherwise, we need to
      //get another int because we'll still be in this while loop
      if (tempNode -> c0 == NULL && tempNode ->c1 == NULL) {
      	return tempNode->symbol;
      }
      else {
      	temp = in.get();
      }
    }
  }
  return 1;  
}
