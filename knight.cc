#include <vector>
#include <memory>
#include <iostream>
#include "knight.h"
#include "emptycell.h"
using namespace std;

Knight::Knight(int colour): Cell{colour, 3} {}

int Knight::getPiece() {
	return 3;
}

void Knight::setTargets(vector<vector<shared_ptr<Cell>>> &theBoard) {
	targets.clear();

	for (int i = -2; i < 3; ++i) {
		if (i != 0) {
			int x = (i % 2) + 1;
			if (i % 2 < 0) x = 2;
			for (int j = -1; j < 2; j += 2) {
				int row = r + i;
				int col = c + x * j;
				
				if (row >= 0 && row <= 7 && col >= 0 && col <= 7) {
					targets.emplace_back(theBoard[row][col]);
				}
			}
		}
	}
}

void Knight::move(int r, int c, vector<vector<shared_ptr<Cell>>> &theBoard) {
	if (!hasMoved) hasMoved = true;
	
	int oldRow = this->r;
	int oldCol = this->c;
		
	theBoard[r][c] = make_shared<Knight>(Knight(colour));
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