#include <vector>
#include <memory>
#include "bishop.h"
#include "emptycell.h"
using namespace std;

Bishop::Bishop(int colour): Cell{colour, 3} {}

int Bishop::getPiece() {
	return 2;
}

void Bishop::setTargets(vector<vector<shared_ptr<Cell>>> &theBoard) {
	targets.clear();
	for(int checkRow = r + 1, checkCol = c + 1; ((checkRow < 8) && (checkCol < 8)); ++checkRow, ++checkCol){
		targets.emplace_back(theBoard[checkRow][checkCol]);
		if (theBoard[checkRow][checkCol]->getPiece() != 0){
			break;
		}
	}
	for(int checkRow = r - 1, checkCol = c + 1; ((checkRow >= 0) && (checkCol < 8)); --checkRow, ++checkCol){
                targets.emplace_back(theBoard[checkRow][checkCol]);
		if (theBoard[checkRow][checkCol]->getPiece() != 0){
			break;
		}
	}
	for(int checkRow = r - 1, checkCol = c - 1; ((checkRow >= 0) && (checkCol >= 0)); --checkRow, --checkCol){
		targets.emplace_back(theBoard[checkRow][checkCol]);
		if (theBoard[checkRow][checkCol]->getPiece() != 0){
			break;
		}
	}
	for(int checkRow = r + 1, checkCol = c - 1; ((checkRow < 8) && (checkCol >= 0)); ++checkRow, --checkCol){
		targets.emplace_back(theBoard[checkRow][checkCol]);
		if (theBoard[checkRow][checkCol]->getPiece() != 0){
			break;
		}
	}
}

void Bishop::move(int r, int c, vector<vector<shared_ptr<Cell>>> &theBoard) {
	if (!hasMoved) hasMoved = true;
	
	int oldRow = this->r;
	int oldCol = this->c;
		
	theBoard[r][c] = make_shared<Bishop>(Bishop(colour));
	theBoard[r][c]->setCoords(r, c);
	theBoard[oldRow][oldCol] = make_shared<EmptyCell>(EmptyCell());
	theBoard[oldRow][oldCol]->setCoords(oldRow, oldCol);

/*	setTargets(theBoard);
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