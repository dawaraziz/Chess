#include <vector>
#include <memory>
#include "queen.h"
#include "emptycell.h"
using namespace std;

Queen::Queen(int colour): Cell{colour, 9} {}

int Queen::getPiece() {
	return 5;
}

void Queen::setTargets(vector<vector<shared_ptr<Cell>>> &theBoard) {
	targets.clear();
	int nRow = this->r + 1;
	int pRow = this->r - 1;
	int nCol = this->c + 1;
	int pCol = this->c - 1;
	
	for (int i = nRow; i < 8; ++i) {
		this->targets.emplace_back(theBoard[i][this->c]);
		if (!(theBoard[i][this->c]->getPiece() == 0)) break;
	}
	for (int i = pRow; i > -1; --i) {
		this->targets.emplace_back(theBoard[i][this->c]);
		if (!(theBoard[i][this->c]->getPiece() == 0)) break;
	}
	for (int i = nCol; i < 8; ++i) {
		this->targets.emplace_back(theBoard[r][i]);
		if (!(theBoard[this->r][i]->getPiece() == 0)) break;
	}
	for (int i = pCol; i > -1; --i) {
		this->targets.emplace_back(theBoard[r][i]);
		if (!(theBoard[this->r][i]->getPiece() == 0)) break;
	}
	for (int i = nRow, j = nCol; ((i < 8) && (j < 8)); ++i, ++j) {
		this->targets.emplace_back(theBoard[i][j]);
		if (!(theBoard[i][j]->getPiece() == 0)) break;
//		++j;
	}
	for (int i = pRow, j = pCol; ((i > -1) && (j > -1)); --i, --j) {
		this->targets.emplace_back(theBoard[i][j]);
		if (!(theBoard[i][j]->getPiece() == 0)) break;
//		--j;
	}
	for (int i = nRow, j = pCol; ((i < 8) && (j > -1)); ++i, --j) {
		this->targets.emplace_back(theBoard[i][j]);
		if (!(theBoard[i][j]->getPiece() == 0)) break;
//		--j;
	}
	for (int i = pRow, j = nCol; ((i > -1) && (j < 8)); --i, ++j) {
		this->targets.emplace_back(theBoard[i][j]);
		if (!(theBoard[i][j]->getPiece() == 0)) break;
//		++j;
	}
}

void Queen::move(int r, int c, vector<vector<shared_ptr<Cell>>> &theBoard) {
	if (!hasMoved) hasMoved = true;
	
	int oldRow = this->r;
	int oldCol = this->c;
		
	theBoard[r][c] = make_shared<Queen>(Queen(colour));
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
