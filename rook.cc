#include <vector>
#include <memory>
#include "rook.h"
#include "emptycell.h"
using namespace std;

Rook::Rook(int colour, int number): Cell{colour, 5}, number{number} {}

int Rook::getPiece() {
	return 4;
}

int Rook::getNumber() {
	return number;
}

void Rook::setTargets(vector<vector<shared_ptr<Cell>>> &theBoard) {
	targets.clear();
	for(int checkRow = r + 1; checkRow < 8; ++checkRow){
		targets.emplace_back(theBoard[checkRow][c]);
		if (theBoard[checkRow][c]->getPiece() != 0){
			break;
		}
	}
	for(int checkRow = r - 1; checkRow >= 0; --checkRow){
		targets.emplace_back(theBoard[checkRow][c]);
		if (theBoard[checkRow][c]->getPiece() != 0){
			break;
		}
	}
	for(int checkCol = c + 1; checkCol < 8; ++checkCol){
	   	targets.emplace_back(theBoard[r][checkCol]);
		if (theBoard[r][checkCol]->getPiece() != 0){
			break;
		}
	}
	for(int checkCol = c - 1; checkCol >= 0; --checkCol){
		targets.emplace_back(theBoard[r][checkCol]);
		if (theBoard[r][checkCol]->getPiece() != 0){
			break;
		}
	}
}

void Rook::move(int r, int c, vector<vector<shared_ptr<Cell>>> &theBoard) {
	//if (!hasMoved) hasMoved = true;	
	int oldRow = this->r;
	int oldCol = this->c;
	int number = theBoard[oldRow][oldCol]->getNumber();
	theBoard[r][c] = make_shared<Rook>(Rook(colour, number));
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
