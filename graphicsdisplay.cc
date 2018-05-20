#include "graphicsdisplay.h"
#include "cell.h"
#include <string>
#include <sstream>

using namespace std;
GraphicsDisplay::GraphicsDisplay(Xwindow &w): size{gameSize / 8}, w{&w} {
        for (int i = 0; i < 8; ++i) {
                vector<int> row;
                for (int j = 0; j < 8; ++j) {
						if (i % 2 == j % 2) row.emplace_back(8);    // GraphicsDisplay uses 1 and 0 to denote status/colour
						else row.emplace_back(9);
                }                               // i.e. Black = OFF, White = ON
                gDisplay.emplace_back(row);
        }
}
GraphicsDisplay::~GraphicsDisplay() {
        gDisplay.clear();
}
void GraphicsDisplay::notify(Cell &c) {
	
        int col = c.getRow();
        int row = c.getCol();
	    int current = c.getPiece();
		int curColor = c.getColour();
		int x = border + (row * size);
		int y = border + (col * size);
		int stringX = x + 20;
		int stringY = y + 30;
		w->fillRectangle(x, y, size, size, gDisplay[row][col]);
//		cout << "square" << endl;
		if (current == 0){
			return;
		}
		else if (current == 1){
			if (curColor == 1) w->drawString(stringX, stringY, "P", 0);
			else w->drawString(stringX, stringY, "P", 1);
				
		}
		else if (current == 2){
			if (curColor == 1) w->drawString(stringX, stringY, "B", 0);
			else w->drawString(stringX, stringY, "B", 1);
		}
		else if (current == 3){
			if (curColor == 1) w->drawString(stringX, stringY, "N", 0);
			else w->drawString(stringX, stringY, "N", 1);
		}
		else if (current == 4){
			if (curColor == 1) w->drawString(stringX, stringY, "R", 0);
			else w->drawString(stringX, stringY, "R", 1);
		}
		else if (current == 5){
			if (curColor == 1) w->drawString(stringX, stringY, "Q", 0);
			else w->drawString(stringX, stringY, "Q", 1);
		}
		else {
			if (curColor == 1) w->drawString(stringX, stringY, "K", 0);
			else w->drawString(stringX, stringY, "K", 1);
		}
		
		
//        gDisplay[row][col] = (gDisplay[row][col] == 0) ? 1 : 0;
}
//SubscriptionType GraphicsDisplay::subType() {
//       return SubscriptionType::All;
//}

/*void GraphicsDisplay::display() {
        w->fillRectangle(0, 0, windowSize, windowSize, 0);      // "Clear" screen
        for (int i = 0; i < rows; ++i){ 
                for (int j = 0; j < rows; ++j) {
                        int x = border + (j * size);
                        int y = border + (i * size);
                        w->fillRectangle(x, y, size, size, gDisplay[i][j]);
                }
        }
} */

void GraphicsDisplay::clearG(){
        w->fillRectangle(0, 0, windowSize, windowSize, 0); 		// "Clear" screen
		w->drawString(230, 35, "CHESS", 1);
		int curNum = 8;
		string curString = to_string(curNum);
        for (int i = 0; i < 8; ++i){ 
				int numY = border + (i * size) + 30;
				w->drawString(15, numY, curString, 1);	// prints 8, 7, 6, ... on board
				--curNum;
				curString = to_string(curNum);
                for (int j = 0; j < 8; ++j) {
                        int x = border + (j * size);
                        int y = border + (i * size);
                        w->fillRectangle(x, y, size, size, gDisplay[i][j]);
                }
        }
		
		for (int i = 0; i < 8; ++i){	// prints "a b c d ..." on board
				int numX = border + (i * size) + 20;
				char curChar = 'a' + i;
				string s = "";
				s += curChar;
				w->drawString(numX, 485, s, 1);
		}
}


