#ifndef _PAWN_H_
#define _PAWN_H_

#include <vector>
#include <memory>
#include "cell.h"

class Pawn: public Cell {
	int direction;
	int number;
	
	public:
//	bool hasMoved;
	
	Pawn(int colour, int number);
	
	int getPiece() override;
	int getNumber();
	void setTargets(std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard) override;
	void move(int r, int c, std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard) override;
};

#endif
