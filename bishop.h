#ifndef _BISHOP_H_
#define _BISHOP_H_

#include <vector>
#include <memory>
#include "cell.h"

class Bishop: public Cell {
	public:
	Bishop(int colour);
	
	int getPiece() override;
	void setTargets(std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard) override;
	void move(int r, int c, std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard) override;
};

#endif