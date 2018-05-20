#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>
#include "observer.h"
#include "cell.h"
#include "emptycell.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
#include "player.h"
#include "board.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "window.h"
using namespace std;

int main() {
	cin.exceptions(ios::eofbit|ios::failbit);
	string cmd;
	Xwindow xw;
	Board b = Board(xw);
	int test = 0;
	try{	
	while (true) {
		cin >> cmd;
		if (cmd == "game") {
			if (test > 0) b.trueOver();
			b.init();
			++test;
			cout << b;
		}
		else if (cmd == "resign") {
			b.gameOver();
		}
		else if (cmd == "move") {
			b.move();
			cout << b;
		}
		else if (cmd == "setup") {
			b.setup();
			cout << b;
		}
	}
	}
	catch(...){

		cout << "Final Score:" << endl;
		cout << "White: " << b.getWhiteWins() << endl;
		cout << "Black: " << b.getBlackWins() << endl;
	}
	}
