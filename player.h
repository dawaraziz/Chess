#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include <memory>
#include <string>
#include "cell.h"
#include "emptycell.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

class Player {
	protected:
	int pieces, colour;
	
	public:
	std::vector<std::shared_ptr<Pawn>> pawns;
	std::vector<std::shared_ptr<Bishop>> bishops;
	std::vector<std::shared_ptr<Knight>> knights;
	std::vector<std::shared_ptr<Rook>> rooks;
	std::vector<std::shared_ptr<Queen>> queens;
	std::vector<std::shared_ptr<King>> king;
	
	Player();
	Player(int colour);
	~Player();
	
	virtual int getColour();
	virtual bool inCheckmate(std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard);
	virtual bool inCheck();
	virtual bool inStalemate();
//	virtual float score();
	virtual void addPiece(int pieceType, std::shared_ptr<Cell> piece);
	virtual void reset();
	virtual void setCheckTargets(std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard);
	virtual std::string move(int kRow, int kCol, std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard) ;
	virtual bool isHuman();
//	virtual void resign();
};

#endif
