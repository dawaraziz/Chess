
#include <iostream>
#include "textdisplay.h"
#include "cell.h"
#include <vector>
using namespace std;

TextDisplay::TextDisplay() {
        int r = 0;
	int c = 0;
        int numCells = 64;
        for (int i = 0; i < 8; ++i){     // initializes the display vector size
                vector<char> nothing;
                theDisplay.emplace_back(nothing);
        }
        for (int i = 0; i < numCells; ++i){
                char current;
		if ( r % 2 == c % 2){
			current = ' ';
		} else {
			current = '_';
		}
                theDisplay[r].emplace_back(current);
                if (c < 8) ++c;
                if (c == 8){
                        c = 0;
                        ++r;
                }
        }
}

void TextDisplay::notify(Cell &c) {     // notifies the display
        int r = c.getRow();
        int col = c.getCol();
		int current = c.getPiece();
		char checkChar = theDisplay[r][col];
		int curColor = c.getColour();
		if (current == 0){
			if (checkChar != ('_' || ' ')){
				if(r % 2 == col % 2 ) theDisplay[r][col] = ' ';
				else theDisplay[r][col] = '_';
			}
		}
		else if (current == 1){
			if (curColor == 1) theDisplay[r][col] = 'P';
			else theDisplay[r][col] = 'p';
		}
		else if (current == 2){
			if (curColor == 1) theDisplay[r][col] = 'B';
			else theDisplay[r][col] = 'b';	
		}
		else if (current == 3){
			if (curColor == 1) theDisplay[r][col] = 'N';
			else theDisplay[r][col] = 'n';
		}
		else if (current == 4){
			if (curColor == 1) theDisplay[r][col] = 'R';
			else theDisplay[r][col] = 'r';
		}
		else if (current == 5){
			if (curColor == 1) theDisplay[r][col] = 'Q';
			else theDisplay[r][col] = 'q';
		}
		else {
			if (curColor == 1) theDisplay[r][col] = 'K';
			else theDisplay[r][col] = 'k';	
		}
}

TextDisplay::~TextDisplay() {}

//SubscriptionType TextDisplay::subType() {
//  return SubscriptionType::All;
//}

ostream &operator<<(ostream &out, const TextDisplay &td) {      // prints the current board
        int r = 0;
        int c = 0;
        int numCells = 64;
	int counter = 8;
        for (int i = 0; i < numCells; ++i){
                char current = td.theDisplay[r][c];
				if (c == 0){
				out << counter << ' ';
				--counter;
				}
                out << current;
                if (c < 8) ++c;
                if (c == 8){
                        c = 0;
                        ++r;
                        out << endl;
                }
        }
		out << endl << "  abcdefgh" << endl;
		
        return out;

}
