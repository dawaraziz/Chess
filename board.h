#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <memory>
#include <iostream>
#include "observer.h"
#include "player.h"
#include "computer.h"
#include "cell.h"
#include "emptycell.h"
#include "pawn.h"				// NOTIFY ON SETUP
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "window.h"

class Board {
	const int boardSize = 8;
	std::shared_ptr<TextDisplay> td;
	std::shared_ptr<GraphicsDisplay> gd;
	std::shared_ptr<Xwindow> xw;
	int turn;
	bool gOver;	
	void setPlayers();
	void setTandO();
	float whiteWins;
	float blackWins;
	int whiteRooks;
	int blackRooks;
	int whitePawns;
	int blackPawns;
	std::vector<bool> whiteRookMoved;
	std::vector<bool> blackRookMoved;
	std::vector<bool> whiteEnPassant;
        std::vector<bool> blackEnPassant;
//	float draws;
	
	protected:
	std::vector<std::vector<std::shared_ptr<Cell>>> theBoard;
	std::vector<std::shared_ptr<Player>> players;
	
	public:
	Board(Xwindow &xw);
	~Board();
	float getBlackWins();
	void trueOver();
	float getWhiteWins();
//	int getDraws;
	void setScore();	
	void init();
	void setup();
	void move();
	void gameOver();
//	void resign();
	friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
