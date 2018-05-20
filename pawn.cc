#include <vector>
#include <memory>
#include <iostream>
#include "pawn.h"
#include "emptycell.h"
using namespace std;

Pawn::Pawn(int colour, int number): Cell{colour, 1}, direction{-1 * (colour * 2 - 1)}, number{number} {}

int Pawn::getPiece() {
	return 1;
}

int Pawn::getNumber() {
	return number;
}

void Pawn::setTargets(vector<vector<shared_ptr<Cell>>> &theBoard) {
	targets.clear();
	
	for (int i = -1; i < 2; ++i) {
		if (c + i >= 0 && c + i <= 7) {
			if (i == 0) {
				int forward;
				if (((colour == 0) && (r == 1)) || ((colour == 1) && (r == 6))) forward = 2;
				else if ((r == 0) || (r == 7)) break;
				else forward = 1;
				
				for (int j = 1; j < forward + 1; ++j) {
                                        if (theBoard[r + (direction * j)][c + i]->getPiece() != 0) break;

                                        if (((r + (direction * j)) >= 0) && ((r + (direction * j)) < 8))
                                        targets.emplace_back(theBoard[r + (direction * j)][c + i]);
				}
			}
			else {
				if ((r + direction >= 0) && (r + direction < 8))
				targets.emplace_back(theBoard[r + direction][c + i]);
			}
		}
	}
}

void Pawn::move(int r, int c, vector<vector<shared_ptr<Cell>>> &theBoard) {
	if (!this->hasMoved) this->hasMoved = true;
	
	int oldRow = this->r;
	int oldCol = this->c;
		
	theBoard[r][c] = make_shared<Pawn>(Pawn(colour, number));
	theBoard[r][c]->setCoords(r, c);
	theBoard[oldRow][oldCol] = make_shared<EmptyCell>(EmptyCell());
	theBoard[oldRow][oldCol]->setCoords(oldRow, oldCol);

	/*setTargets(theBoard);
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
	theBoard[oldRow][oldCol]->notify(*theBoard[oldRow][oldCol]); */
}
