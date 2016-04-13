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
}

void HCTree::encode(byte symbol, BitOutputStream& out) const {
}

void HCTree::encode(byte symbol, ofstream& out) const {
}

int HCTree::decode(BitInputStream& in) const {
}

int HCTree::decode(ifstream& in) const{
}
