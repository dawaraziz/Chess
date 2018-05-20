#include <vector>
#include <memory>
#include "emptycell.h"
using namespace std;

EmptyCell::EmptyCell(): Cell{-1, 0} {}

int EmptyCell::getPiece() {
	return 0;
}

void EmptyCell::setTargets(vector<vector<shared_ptr<Cell>>> &theBoard) {
	targets.clear();
}
