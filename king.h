#ifndef _KING_H_
#define _KING_H_

#include <vector>
#include <memory>
#include "cell.h"

class King: public Cell {
	public:
//	bool hasMoved;
	
	King(int colour); 
	
	int getPiece() override;
	void setTargets(std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard) override;
	void trimTargets();
	void move(int r, int c, std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard) override;
	void setCheckTargets(std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard);
};

#endif
