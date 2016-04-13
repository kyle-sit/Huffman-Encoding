#include "HCTree.hpp"
#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

HCTree::~HCTree() {
}

void HCTree::build(const vector<int>& freqs) {
  // Build our leaves vector from the vector of int frequencies
  int i = 0;
  for( i = 0; i < freqs.size(); i++ ) {
    leaves[i] = new HCNode(freqs[i], (unsigned char)(i+1), 0, 0, 0);
  }

  // Insert these values into a minHeap priority queue
  std::priority_queue<HCNode*,vector<HCNode*>, HCNodePtrComp> minHeap;
  for( i = 0; i < leaves.size(); i++ ) {
    minHeap.push( leaves[i] );
  }

  // Now that minHeap is set up, start popping values and creating trees
  while( !(minHeap.empty()) ) {
    HCNode* temp1 = minHeap.top();
    minHeap.pop();
    
    // If we have come to the last item in the heap return
    if( !minHeap.top() ) {
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
}

void HCTree::encode(byte symbol, ofstream& out) const {
}

int HCTree::decode(BitInputStream& in) const {
}

int HCTree::decode(ifstream& in) const{
}
