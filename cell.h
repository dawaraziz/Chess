#ifndef _CELL_H_
#define _CELL_H_

#include <vector>
#include <string>
#include <memory>
#include "observer.h"

class EmptyCell;
class Pawn;
class Bishop;
class Knight;
class Rook;
class Queen;
class King;

class Cell: public Observer {
	protected:
	int r, c, value, colour;

	public:
	bool hasMoved;
	std::vector<std::shared_ptr<Cell>> targets;
	std::vector<std::shared_ptr<Cell>> observers;
	std::vector<std::shared_ptr<Observer>> displays;
	
	Cell();
	Cell(int colour, int value);
	
	virtual int getRow();
	virtual int getCol();
	virtual int getColour();
	virtual int getNumber();
	virtual int getPiece() = 0;
	virtual void setCoords(int r, int c);
	virtual void setTargets(std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard) = 0;
	virtual void setCheckTargets(std::shared_ptr<Cell> king, std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard);
	virtual void setObservers(std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard);
	virtual void move(int r, int c, std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard);
	
	void notify(Cell &c) override;
};
#endif
