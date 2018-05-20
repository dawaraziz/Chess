#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include "board.h"
using namespace std;

Board::~Board(){
	theBoard.clear();
}

void Board::trueOver(){
	gOver = true;

}
void Board::setTandO() {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			theBoard[i][j]->setTargets(theBoard);
		}
	}
	for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                        theBoard[i][j]->setObservers(theBoard);
                }
        }
	int size = players.size();
	for (int i = 0; i < size; ++i) {
		players[i]->king[0]->trimTargets();
	}
}


Board::Board(Xwindow &xw): turn{1}, gOver{false}, blackWins{0}, whiteWins{0}, blackRooks{0}, whiteRooks{0}, whitePawns{0}, blackPawns{0} { 
	this->xw = make_shared<Xwindow>(xw); 
}


float Board::getBlackWins(){
	return blackWins; 

}

float Board::getWhiteWins(){
	return whiteWins;

}

void Board::setPlayers() {
	players[0]->reset();
	players[1]->reset();
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			int piece = theBoard[i][j]->getPiece();
			if (piece != 0) {
				int owner = theBoard[i][j]->getColour();
				players[owner]->addPiece(piece, theBoard[i][j]);
			}
		}
	}
}

void Board::init() {
	cin.exceptions(ios::eofbit|ios::failbit);

	if (gOver){
	theBoard.clear();
	players.clear();
	gOver = false;
	turn = 1;
	}

	string player1, player2;
	int po, pt;	
	cin >> player1 >> player2;
	if (player1 == "human") po = 0;
	else if (player1.substr(0, 8) == "computer") {
		po = player1[8] - '0';
		cout << "computer black" << endl;
	}
	if (player2 == "human") pt = 0;
	else if (player2.substr(0, 8) == "computer") pt = player2[8] - '0';
	
	td = make_shared<TextDisplay>(TextDisplay());
	gd = make_shared<GraphicsDisplay>(GraphicsDisplay(*xw));

	gd->clearG();
	
	for (int row = 0; row < 8; ++row) {
		vector<shared_ptr<Cell>> columns;
		for (int col = 0; col < 8; ++col) {
			if ((row == 0) || (row == 7)) {
				if ((col == 0) || (col == 7)) {

					if ((row / 7) == 0) {
						whiteRookMoved.emplace_back(false);
			       		        auto r = make_shared<Rook>(Rook((row / 7), whiteRooks));
                        	                columns.emplace_back(r);
						++whiteRooks;

					} 
					else {
						blackRookMoved.emplace_back(false);
						auto r = make_shared<Rook>(Rook((row / 7), blackRooks));
                                                columns.emplace_back(r);
						++blackRooks;

					}

		//			auto r = make_shared<Rook>(Rook(row / 7));
		//			columns.emplace_back(r);
				}
				else if ((col == 1) || (col == 6)) {
					auto k = make_shared<Knight>(Knight(row / 7));
					columns.emplace_back(k);
				}
				else if ((col == 2) || (col == 5)) {
					auto b = make_shared<Bishop>(Bishop(row / 7));
					columns.emplace_back(b);
				}
				else if (col == 4) {
					auto k = make_shared<King>(King(row / 7));
					columns.emplace_back(k);
				}
				else {
					auto q = make_shared<Queen>(Queen(row / 7));
					columns.emplace_back(q);
				}
			}
			else if ((row == 1) || (row == 6)) {
				if (row == 1){
                                	blackEnPassant.emplace_back(false);
                                	auto p = make_shared<Pawn>(Pawn(((row - 1) / 5), blackPawns));
                                	columns.emplace_back(p);
                                	++blackPawns;
                                }
                                else {
                                	whiteEnPassant.emplace_back(false);
                                	auto p = make_shared<Pawn>(Pawn(((row - 1) / 5), whitePawns));
                                	columns.emplace_back(p);
                                	++whitePawns;
                                }
			}
			else {
				auto ec = make_shared<EmptyCell>(EmptyCell());
				columns.emplace_back(ec);
			}
			columns[col]->setCoords(row, col);
		}
		theBoard.emplace_back(columns);
	}
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			theBoard[row][col]->setTargets(theBoard);
		}
	}
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			theBoard[row][col]->setObservers(theBoard);
			theBoard[row][col]->displays.emplace_back(td);
			theBoard[row][col]->displays.emplace_back(gd);
			theBoard[row][col]->notify(*theBoard[row][col]);
		}
	}

	if (po == 0) { 
		auto bp = make_shared<Player>(Player(0));
		players.emplace_back(bp);
	}
	else if (po > 0) { 
		auto bp = make_shared<Computer>(po, 0);
		players.emplace_back(bp);
	}
	if (pt == 0) { 
		auto wp = make_shared<Player>(Player(1));
		players.emplace_back(wp);
	}
	else if (pt > 0) { 
		auto wp = make_shared<Computer>(pt, 1);
		players.emplace_back(wp);
	}
	
	setPlayers();
}


void Board::setup() {
	cin.exceptions(ios::failbit|ios::eofbit);
	
	string cmd;
	
//	int whiteRooks = 0;
//	int blackRooks = 0;
	while (1) {
		cin >> cmd;
		
		if (cmd == "+") {
			string piece, location;
			int r, c;
			
			cin >> piece >> location;
			
			r = -1 * (location[1] - '0' - 8);
			c = location[0] - 'a';
			
			int player = 0;
			if (piece[0] >= 'a' && piece[0] <= 'z') {
				player = 0;
			}
			if (piece[0] >= 'A' && piece[0] <= 'Z') {
				player = 1;
			}
			int opponent = (player == 1) ? 0 : 1;
			
			if (piece == "P" || piece == "p") {
				if (player == 1) {
                                        theBoard[r][c] = make_shared<Pawn>(player, whitePawns);
                                        whiteEnPassant.emplace_back(false);
                                        ++whitePawns;
                                } else {
                                        theBoard[r][c] = make_shared<Pawn>(player, blackPawns);
                                        blackEnPassant.emplace_back(false);
                                        ++blackPawns;
                                }
			}
			if (piece == "B" || piece == "b") {
				theBoard[r][c] = make_shared<Bishop>(player);
			}
			if (piece == "N" || piece == "n") {
				theBoard[r][c] = make_shared<Knight>(player);
			}
			if (piece == "R" || piece == "r") {
				if (player == 1) {
					theBoard[r][c] = make_shared<Rook>(player, whiteRooks);
					whiteRookMoved.emplace_back(false);
					++whiteRooks;
				} else {
					theBoard[r][c] = make_shared<Rook>(player, blackRooks);
					blackRookMoved.emplace_back(false);
                                        ++blackRooks;
				}
			}
			if (piece == "Q" || piece == "q") {
				theBoard[r][c] = make_shared<Queen>(player);
			}
			if (piece == "K" || piece == "k") {
				theBoard[r][c] = make_shared<King>(player);
			}
			theBoard[r][c]->setCoords(r, c);
			td->notify(*theBoard[r][c]);
			gd->notify(*theBoard[r][c]);
		}
		else if (cmd == "-") {
			string location;
			int r, c;
			
			cin >> location;
			
			r = -1 * (location[1] - '0' - 8);
			c = location[0] - 'a';

			if (theBoard[r][c]->getPiece() == 4) {
				if (theBoard[r][c]->getColour() == 0) {
					blackRookMoved[theBoard[r][c]->getNumber()] = true;
				}
				else {
					whiteRookMoved[theBoard[r][c]->getNumber()] = true;
				}
			}

			if (theBoard[r][c]->getPiece() != 0) {
				theBoard[r][c] = make_shared<EmptyCell>();
			}
			theBoard[r][c]->setCoords(r, c);
			td->notify(*theBoard[r][c]);
			gd->notify(*theBoard[r][c]);
		}
		else if (cmd == "=") {
			string colour;
			
			cin >> colour;
			
			if (colour == "black") turn = 0;
			else if (colour == "white") turn = 1;
			
		}
		else if (cmd == "done") {
			setTandO();
			setPlayers();
			bool done = true;
			for (auto player: players){
				if (player->king.size() != 1) done = false; 
				for (auto pawn: player->pawns){
					if ((pawn->getRow() == 0) || (pawn->getRow() == 7)) done = false;
				}
				if (player->inCheck()) done = false;
			}
			if (done) break;
		}
	}

	

}

void Board::move() {


	int row, col, newRow, newCol, count;
	bool moved = false;
	int kRow, kCol;

	count = 0;
	int opp = (turn == 0) ? 1 : 0;

	kRow = players[opp]->king[0]->getRow();
	kCol = players[opp]->king[0]->getCol();

	while (!moved) {
	if (!players[turn]->isHuman()) {
		shared_ptr<Computer> ai = static_pointer_cast<Computer>(players[turn]);
                if (count > 15) ai->decreaseLevel();
		string result = ai->move(kRow, kCol, theBoard);
		row = result[0] - '0';
		col = result[1] - '0';
		newRow = result[2] - '0';
		newCol = result[3] - '0';

		if (count > 15) {
			count = 0;
			ai->increaseLevel();
		}
		++count;
	}
	else {
		string start, end;
		cin >> start >> end;

		row = -1 * (start[1] - '0' - 8); // current row
		col = start[0] - 'a';		 // current column
		newRow = -1 * (end[1] - '0' - 8);
		newCol = end[0] - 'a';
		moved = true;
	}
	
	if (theBoard[row][col]->getColour() == players[turn]->getColour()) {

		if (theBoard[row][col]->getPiece() == 6 && (newCol - col >= 2 || col - newCol >= 2)) {
			if (!players[turn]->inCheck()) {
				int rookCol = (newCol == 6) ? 7 : 0;
				if (theBoard[row][rookCol]->getPiece() == 4) {
					if (((turn == 0) && ((blackRookMoved[theBoard[row][rookCol]->getNumber()]) == false)) || 
					    ((turn == 1) && ((whiteRookMoved[theBoard[row][rookCol]->getNumber()]) == false))) {

						int left = (rookCol < col) ? rookCol : col;
						int right = (rookCol > col) ? rookCol : col;
						bool clear = true;
						for (int c = left + 1; c < right; ++c) {
							if (theBoard[row][c]->getPiece() != 0) {
								clear = false;
								break;
							}
							else if (c != 1) {
								int size = theBoard[row][c]->observers.size();
								for (int i = 0; i < size; ++i) {
									if (theBoard[row][c]->observers[i]->getColour() != turn) {
										clear = false;
										break;
									}
								}
								if (!clear) break;
							}
						}
						if (clear) {
							theBoard[row][rookCol]->move(row, rookCol / 7 * 2 + 3, theBoard);
							td->notify(*theBoard[row][rookCol]);
							td->notify(*theBoard[row][rookCol / 7 * 2 + 3]);
							gd->notify(*theBoard[row][rookCol]);
							gd->notify(*theBoard[row][rookCol / 7 * 2 + 3]);
							theBoard[row][col]->move(newRow, newCol, theBoard);
									
							if (turn == 1) {
                                int sizeW = whiteRookMoved.size();
                                for (int i = 0; i < sizeW; ++i) {
                                    whiteRookMoved[i] = true;
                                }
                            }
                            else {
                                int sizeB = blackRookMoved.size();
                                for (int i = 0; i < sizeB; ++i) {
                                    blackRookMoved[i] = true;
                                }
                            }
							td->notify(*theBoard[row][col]);
							td->notify(*theBoard[newRow][newCol]);
							gd->notify(*theBoard[row][col]);
							gd->notify(*theBoard[newRow][newCol]);
							setTandO();
							setPlayers();
							turn = (turn == 0) ? 1 : 0;
						}
					}
				}
			}
		}
		else { // if valid move and not castling situation

			int size = theBoard[row][col]->targets.size();
			for (int i = 0; i < size; ++i) { // breaking out of this for loop will restart the players move
				
				if (theBoard[row][col]->targets[i]->getRow() == newRow && 
				    theBoard[row][col]->targets[i]->getCol() == newCol &&
				    theBoard[newRow][newCol]->getColour() != players[turn]->getColour()) { // destination is a target and not a friendly piece
					if (theBoard[row][col]->getPiece() == 1) {
						
						if (theBoard[row][col]->getColour() == 0){
                                                	int testnum2 = theBoard[row][col]->getNumber();
                                                        if (newRow - row > 1){
                                                        	blackEnPassant[testnum2] = true;
                                                        }
                                                        else {
                                                        	if (!(col != newCol && theBoard[newRow][newCol]->getPiece() == 0)) blackEnPassant[testnum2] = false;
                                                        }
                                                }
                                                else {
                                                	int testnum2 = theBoard[row][col]->getNumber();
                                                        if (row - newRow > 1){
                                                        	whiteEnPassant[testnum2] = true;
                                                        }
                                                        else {
                                                        	if (!(col != newCol && theBoard[newRow][newCol]->getPiece() == 0)) whiteEnPassant[testnum2] = false;
                                                        }
                                                }
                                                if (col != newCol && theBoard[newRow][newCol]->getPiece() == 0){
                                                	bool testEnPassant = false;
                                                        if (theBoard[row][col]->getColour() == 0){
                                                        	if ((theBoard[newRow - 1][newCol]->getPiece() == 1) && 
								    (theBoard[newRow - 1][newCol]->getColour() == 1)){
                                                                       	int testnum = theBoard[newRow - 1][newCol]->getNumber();
                                                                        if (whiteEnPassant[testnum] == true){
                                                                               	testEnPassant = true;
										theBoard[newRow - 1][newCol] = make_shared<EmptyCell>();
                                                                                theBoard[newRow - 1][newCol]->setCoords(newRow - 1, newCol);
                                                                                td->notify(*theBoard[newRow - 1][newCol]);
                                                                                gd->notify(*theBoard[newRow - 1][newCol]);
									}
                                                                }
                                                        } else {
                                                          	if ((theBoard[newRow + 1][newCol]->getPiece() == 1) && 
								    (theBoard[newRow + 1][newCol]->getColour() == 0)){
                                                                      	int testnum = theBoard[newRow + 1][newCol]->getNumber();
                                                                        if (blackEnPassant[testnum] == true){
                                                                               	testEnPassant = true;
                                                                                theBoard[newRow + 1][newCol] = make_shared<EmptyCell>();
                                                                                theBoard[newRow + 1][newCol]->setCoords(newRow + 1, newCol);
                                                                                td->notify(*theBoard[newRow + 1][newCol]);
                                                                                gd->notify(*theBoard[newRow + 1][newCol]);
                                                                        }
                                                                }
                                                        }
                                                        if (!testEnPassant) break;
                                                 }
					}
					else if (theBoard[row][col]->getPiece() == 6) { // if moving a king, make sure it is not going into a check 
						bool dangerous = false;
						for (auto observer : theBoard[newRow][newCol]->observers) {
							if (observer->getColour() != turn) {
								if (observer->getPiece() != 1 || observer->getCol() != newCol) {
									dangerous = true;
									break;
								}
							}
						}
						if (dangerous) break;
					}

					int pPiece = theBoard[row][col]->getPiece();
					int number = theBoard[row][col]->getNumber();
				
					theBoard[row][col]->move(newRow, newCol, theBoard);

					if (pPiece == 6) {
						if (turn == 1) {
                            				int sizeW = whiteRookMoved.size();
                            				for (int i = 0; i < sizeW; ++i) {
                                				whiteRookMoved[i] = true;
                            				}
                        			}
                        			else {
                            				int sizeB = blackRookMoved.size();
                           				 for (int i = 0; i < sizeB; ++i) {
                            					blackRookMoved[i] = true;
                            				}
                        			}
					}

					else if (pPiece == 4) {
						if (turn == 1) {
                            				whiteRookMoved[number] = true;
                        			}
                        			else {
                            				blackRookMoved[number] = true;
                        			}
					}

					setPlayers();
					setTandO();
	
					if (players[turn]->inCheck()) {
						theBoard[newRow][newCol] = make_shared<EmptyCell>();
          					theBoard[newRow][newCol]->setCoords(newRow, newCol);

						if (pPiece == 1) {
							theBoard[row][col] = make_shared<Pawn>(turn, number);
                            				theBoard[row][col]->setCoords(row, col);
						}
			                        if (pPiece == 2) {
                       					theBoard[row][col] = make_shared<Bishop>(turn);
                            				theBoard[row][col]->setCoords(row, col);
                        			}
                        			if (pPiece == 3) {
                            				theBoard[row][col] = make_shared<Knight>(turn);
                            				theBoard[row][col]->setCoords(row, col);
                        			}
                        			if (pPiece == 4) {
							if (theBoard[row][col]->getColour() == 0){
                                				theBoard[row][col] = make_shared<Rook>(turn, number);
                                				theBoard[row][col]->setCoords(row, col);
							} 
							else {
      								theBoard[row][col] = make_shared<Rook>(turn, number);
                                				theBoard[row][col]->setCoords(row, col);
							}
                        			}
                        			if (pPiece == 5) {
                            				theBoard[row][col] = make_shared<Queen>(turn);
                            				theBoard[row][col]->setCoords(row, col);
						}
                        			if (pPiece == 6) {
                            				theBoard[row][col] = make_shared<King>(turn);
                            				theBoard[row][col]->setCoords(row, col);
                        			}
						setTandO();
						setPlayers();
        				}
					else {
						td->notify(*theBoard[row][col]);
						td->notify(*theBoard[newRow][newCol]);
        			                gd->notify(*theBoard[row][col]);
                        			gd->notify(*theBoard[newRow][newCol]);
						int pawns = players[turn]->pawns.size();

						for (int j = 0; j < pawns; ++j) {
							if (players[turn]->pawns[j]->getRow() == -7 * (turn - 1)) {
								char piece;
								if (players[turn]->isHuman())cin >> piece;
								else piece = 'q';
									
								switch (piece) {
								case 'b':
								case 'B':
									theBoard[newRow][newCol] = make_shared<Bishop>(turn);
									break;
								case 'n':
								case 'N':
									theBoard[newRow][newCol] = make_shared<Knight>(turn);
									break;
								case 'r':
								case 'R':
									if (theBoard[newRow][newCol]->getColour() == 0){
                                           					theBoard[newRow][newCol] = make_shared<Rook>(turn, blackRooks);
                                           					blackRookMoved.emplace_back(true);
                                           					++blackRooks;
                                       					}
                                       					else {
                                           					theBoard[newRow][newCol] = make_shared<Rook>(turn, whiteRooks);
                                          					whiteRookMoved.emplace_back(true);
                                           					++whiteRooks;
                                       					}
									break;
								case 'q':
								case 'Q':
									theBoard[newRow][newCol] = make_shared<Queen>(turn);
									break;
								}
								theBoard[newRow][newCol]->setCoords(newRow, newCol);
								theBoard[newRow][newCol]->setTargets(theBoard);
								theBoard[newRow][newCol]->setObservers(theBoard);
								td->notify(*theBoard[newRow][newCol]);
								gd->notify(*theBoard[newRow][newCol]);
							}
						}

						setTandO();
						setPlayers();

						turn = (turn == 0) ? 1 : 0;
						moved = true;
						break;
					}
				}
			}
		}
	}
	
	}

	int opponent = (turn == 0) ? 1 : 0;
	
	 if (players[turn]->inCheck()) {

		players[turn]->setCheckTargets(theBoard);
		if (players[turn]->inCheckmate(theBoard)) {
               		cout << "Checkmate! ";
                	if (opponent == 0) blackWins += 1.0f;
			else whiteWins += 1.0f;
                	gameOver();
        	}

		setTandO();
		if (!gOver) {
			switch (turn) {
			case 0:
				cout << "Black is in check." << endl;
				break;
			case 1:
				cout << "White is in check." << endl;
				break;
			}
		}
	}
	else {
		setTandO();
		if (players[turn]->inStalemate()) {
			cout << "Stalemate!" << endl;
			whiteWins -= 0.5f;
			blackWins -= 0.5f;


			turn = 2;
			gameOver();
		}
	}
}

void Board::gameOver() {
	int opponent = (turn == 0) ? 1 : 0;
	if (opponent == 0) blackWins += 1.0f;
        else whiteWins += 1.0f;

	switch (turn) {
	case 0:
		cout << "White wins!" << endl;
		break;
	case 1:
		cout << "Black wins!" << endl;
		break;
	}

	int size = theBoard.size();
	gOver = true;
	whiteRookMoved.clear();
	blackRookMoved.clear();
	whiteRooks = 0;
	blackRooks = 0;
	whitePawns = 0;
	blackPawns = 0;
	whiteEnPassant.clear();
	blackEnPassant.clear();
}



ostream &operator<<(ostream &out, const Board &b) {
	return out << *b.td;
}
