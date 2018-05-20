#ifndef _ROOK_H_
#define _ROOK_H_

#include <vector>
#include <memory>
#include "cell.h"

class Rook: public Cell {
	public:
//	bool hasMoved;
	int number;
	
	Rook(int colour, int number);
	
	int getPiece() override;
	int getNumber();
	void setTargets(std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard) override;
	void move(int r, int c, std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard) override;
};

#endif
