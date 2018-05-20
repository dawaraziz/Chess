#include <iostream>
#include <vector>
#include <memory>
#include "king.h"
#include "emptycell.h"
using namespace std;

King::King(int colour): Cell{colour, 12} {}

int King::getPiece() {
	return 6;
}

void King::trimTargets() {
//	cout << "Trimming" << endl;
	int size = targets.size();
	for (int i = 0; i < size; ++i) {
		bool dangerous = false;
		int opponent = (colour == 0) ? 1 : 0;
		if (targets[i]->getColour() == opponent) {
			int size2 = targets[i]->observers.size();
			for (int j = 0; j < size2; ++j) {
				if (targets[i]->observers[j]->getColour() == opponent) {
					dangerous = true;
					break;
				}
			}
		}
		if (dangerous) {
//			cout << targets[i]->getRow() << "   " << targets[i]->getCol() << endl;
			targets.erase(targets.begin() + i);
                	--size;
                        --i;
                        break;
		}
	}
}


void King::setTargets(vector<vector<shared_ptr<Cell>>> &theBoard) {
	targets.clear();

//	cout << "King targets" << endl;
	
	for (int i = r - 1; i < r + 2; ++i) {
		for (int j = c - 1; j < c + 2; ++j) {
			if (!(i == r && j == c) && (i >= 0 && i <= 7 && j >=0 && j <= 7)) {
				targets.emplace_back(theBoard[i][j]);
//				cout << i << "   " << j << endl;
			}
		}
	}
}

void King::setCheckTargets(vector<vector<shared_ptr<Cell>>> &theBoard) {
	targets.clear();
	
	for (int i = r - 1; i < r + 2; ++i) {
		for (int j = c - 1; j < c + 2; ++j) {
			if (!(i == r && j == c) && (i >= 0 && i <= 7 && j >=0 && j <= 7)) {
				cout << "checking: " << theBoard[i][j]->getPiece() << endl;
				cout << "coordinates: " << i << " " << j << endl;
				if (theBoard[i][j]->getColour() != colour) {
					bool dangerous = false;
					int size = theBoard[i][j]->observers.size();
					for (int k = 0; k < size; ++k) {
						if (theBoard[i][j]->observers[k]->getColour() != colour) {
	cout << theBoard[i][j]->getPiece() << endl;
	cout << theBoard[i][j]->observers[k]->getCol() << endl;
							cout << theBoard[i][j]->observers[k]->getRow() << endl;
							dangerous = true;
							break;
						}
					}
					if (!dangerous) targets.emplace_back(theBoard[i][j]);
				}
			}
		}
	}
}

void King::move(int r, int c, vector<vector<shared_ptr<Cell>>> &theBoard) {
	if (!hasMoved) hasMoved = true;
	
	int oldRow = this->r;
	int oldCol = this->c;
		
	theBoard[r][c] = make_shared<King>(King(colour));
	theBoard[r][c]->setCoords(r, c);
	theBoard[oldRow][oldCol] = make_shared<EmptyCell>(EmptyCell());
	theBoard[oldRow][oldCol]->setCoords(oldRow, oldCol);	

/*
	setTargets(theBoard);
	theBoard[oldRow][oldCol]->setTargets(theBoard);
	
	int size2 = targets.size();
	int size3 = observers.size();
	
	for (int j = 0; j < size2; ++j) {
		targets[j]->setTargets(theBoard);
	}
	for (int j = 0; j < size3; ++j) {
		observers[j]->setTargets(theBoard);
	}
	
	theBoard[r][c]->setObservers(theBoard);
	theBoard[oldRow][oldCol]->setObservers(theBoard);
	for (int j = 0; j < size2; ++j) {
		targets[j]->setObservers(theBoard);
	}
	for (int j = 0; j < size3; ++j) {
		observers[j]->setObservers(theBoard);
	}
	
	theBoard[r][c]->notify(*theBoard[r][c]);
	theBoard[oldRow][oldCol]->notify(*theBoard[oldRow][oldCol]);*/
}
