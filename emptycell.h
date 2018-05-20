#ifndef _EMPTYCELL_H_
#define _EMPTYCELL_H_

#include <vector>
#include <memory>
#include "cell.h"

class EmptyCell: public Cell {
	public:
	EmptyCell();
	
	int getPiece() override;
	void setTargets(std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard) override;
};

#endif
