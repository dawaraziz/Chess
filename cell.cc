#include <vector>
#include <memory>
#include "cell.h"
using namespace std;

Cell::Cell(): colour{-1}, value{0} {}

Cell::Cell(int colour, int value): colour{colour}, value{value} {}

int Cell::getRow() {
	return r;
}

int Cell::getNumber(){
	return 0;
}

int Cell::getCol() {
	return c;
}

int Cell::getColour() {
	return colour;
}

void Cell::setCoords(int r, int c) {
	this->r = r;
	this->c = c;
}

void Cell::setObservers(vector<vector<shared_ptr<Cell>>> &theBoard) {
	observers.clear();
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			int size = theBoard[i][j]->targets.size();
			for (int k = 0; k < size; ++k) {
				if (theBoard[i][j]->targets[k]->getRow() == this->r && 
					theBoard[i][j]->targets[k]->getCol() == this->c) {
						observers.emplace_back(theBoard[i][j]);
						break;
				}
			}
		}
	}
}

void Cell::move(int r, int c, vector<vector<shared_ptr<Cell>>> &theBoard) {
	hasMoved = true;
}

void Cell::setCheckTargets(shared_ptr<Cell> king, vector<vector<shared_ptr<Cell>>> &theBoard) {
//	targets.clear();
	
	int size = king->observers.size();
	int attackers = 0;
	int opponent = -1 * (colour - 1);
	int row, col;
	int kRow = king->getRow();
	int kCol = king->getCol();
	for (int i = 0; i < size; ++i) {
		if (king->observers[i]->getColour() == opponent) {
			++attackers;
			row = king->observers[i]->getRow();
			col = king->observers[i]->getCol();
		}
	}



	if (attackers < 2) {
		int attackerType = theBoard[row][col]->getPiece();
		int size2 = targets.size();
		switch (attackerType) {
		case 1:
		case 3:
			for (int i = 0; i < size2; ++i) {
				if (targets[i]->getRow() != row && targets[i]->getCol() != col) {
					targets.erase(targets.begin() + i);
					--size2;
					--i;
				}
			}
			break;
		case 2:
		case 4:
		case 5:

			int range = r - row;
			range = (range > 0) ? range : -range;
			int rd = r - row;
			if (rd != 0) rd /= rd;
			int cd = c - col;
			if (cd != 0) cd /= cd;

                        vector<shared_ptr<Cell>> cellsBetween;
                        int directionRow = kRow - row;
                        int directionCol = kCol - col;
                        int absRow = (directionRow > 0) ? directionRow : -1 * directionRow;
                        int absCol = (directionCol > 0) ? directionCol : -1 * directionCol;

                        int directionRange = (absRow >= absCol) ? absRow : absCol;
                        if (directionRow > 0) directionRow /= directionRow;
                        else if (directionRow < 0) directionRow = directionRow * -1 / directionRow;
                        if (directionCol > 0) directionCol /= directionCol;
                        else if (directionCol < 0) directionCol = directionCol * -1 / directionCol;
                        for (int i = 0; i < directionRange; ++i){
                                cellsBetween.emplace_back(theBoard[row + (i * directionRow)][col + (i * directionCol)]);
                        }
			int cbSize = cellsBetween.size();
			for (int i = 0; i < size2; ++i) {
				bool valid = false;
				for(int j = 0; j < cbSize; ++j) {
					if ((targets[i]->getRow() == cellsBetween[j]->getRow()) && 
					(targets[i]->getCol() == cellsBetween[j]->getCol())) {
						valid = true;
						break;
					}
				}
				if (!valid) {
                                        targets.erase(targets.begin() + i);
                                        --size2;
                                        --i;
                                }

			}
			
//			for (int i = 0; i < size2; ++i) {
//				bool valid = false;
//				for (int j = 0; j < range; ++j) {
//					if (targets[i]->getRow() == theBoard[row][col]->getRow() + i * rd &&
//					targets[i]->getCol() == theBoard[row][col]->getCol() + i * cd) {
//						valid = true;
//						break;
//					}


/*				}
				if (!valid) {
					targets.erase(targets.begin() + i);
					--size2;
					--i;
				}
			}
*/

			break;
		}
	}
}

void Cell::notify(Cell &c) {
	int size = displays.size();
	for (int i = 0; i < size; ++i) {
		displays[i]->notify(*this);
	}
}
