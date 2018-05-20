#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "computer.h"
using namespace std;

Computer::Computer(int level, int colour): level{level}, Player(colour) {
        srand(76);
}

void Computer::increaseLevel() {
	++level;
}

void Computer::decreaseLevel() {
	--level;
}

string Computer::move(int kRow, int kCol, vector<vector<shared_ptr<Cell>>> &theBoard) {
	string result = "";
        switch (level) {
        case 4: {
         	vector<string> moves;
         	for (auto pawn : pawns) {
                	for (auto target: pawn->targets) {
                        	bool capture = false;
                                for (auto observer: target->observers){
                                	if (observer->getColour() != colour){
                                        	capture = true;
                                         	break;
                                         }
                                         if (capture) break;


                                 }
                                 if (capture) continue;
                                 if ((target->getCol() != pawn->getCol()) 
					&& ((theBoard[target->getRow()][target->getCol()]->getColour() == colour)||
                                                (theBoard[target->getRow()][target->getCol()]->getPiece() == 0)) ) continue;
                                        if (colour == 0){
                                                if ((target->getRow() == kRow - 1) && ((target->getCol() == kCol + 1) || (target->getCol() == kCol - 1))){

					int advantage = 0;
	                                  for (auto observer: target->observers){
                                                if (observer->getColour() == colour){
                                                         ++advantage;
                                                } else {
						--advantage;
						}
                                        	}
                                        if (advantage > 0) {

                                                        result += pawn->getRow() + '0';
                                                        result += pawn->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                       if (advantage == 0) moves.emplace_back(result);
							else {
							for (int i = 0; i < 30; ++i){
							moves.emplace_back(result);
							}
                                                        result = "";

                                                	}
						}
					}
                                        }
                                        else {
                                                if ((target->getRow() == kRow + 1) && ((target->getCol() == kCol + 1) || (target->getCol() == kCol - 1))){
                                                        
	                                                                    int advantage = 0;
                                          for (auto observer: target->observers){
                                                if (observer->getColour() == colour){
                                                         ++advantage;
                                                } else {
                                                --advantage;
                                                }
                                                }
                                        if (advantage > 0) {

                                                        result += pawn->getRow() + '0';
                                                        result += pawn->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                       if (advantage == 0) moves.emplace_back(result);
                                                        else {
                                                        for (int i = 0; i < 30; ++i){
                                                        moves.emplace_back(result);
                                                        }
                                                        result = "";

                                                        }
                                                }
                                        }

                                        }




                                        if ((target->getColour() != colour) && (target->getColour() != -1)) {
                                                result += pawn->getRow() + '0';
                                                result += pawn->getCol() + '0';
                                                result += target->getRow() + '0';
                                                result += target->getCol() + '0';
						int howMany = target->getPiece();
						for (int i = 0; i < 10 * howMany; ++i){
                                                	moves.emplace_back(result);
						}
						if (target->getPiece() != 1){
							for (int i = 0; i < 100; ++i) moves.emplace_back(result);
						
						}
                                                result = "";
                                        }



                                }
                        }

                        for (auto bishop : bishops) {
                                for (auto target: bishop->targets){
                                        bool capture = false;
                                        for (auto observer: target->observers){
                                                if (observer->getColour() != colour){
                                                         capture = true;
                                                         break;
                                                }
                                             if (capture == true) break;


                                        }
                                        if (capture == true) continue;


                                        int tRow = target->getRow();
                                        int tCol = target->getCol();
                                        int rowDif = kRow - tRow;
                                        int colDif = kCol - tCol;
                                        int range = (rowDif > 0) ? rowDif : -1 * rowDif;
                                        int rowDir = rowDif;
                                        int colDir = colDif;
                                        rowDir = ((rowDif > 0) && (rowDif != 0)) ? 1 : -1;
                                        colDir = ((colDif > 0) && (colDif != 0)) ? 1 : -1;

                                        for (int i = 1; i <= range; ++i){
                                                if (rowDif != colDif) break;
                                                if (((i * rowDir) + tRow >= 8) ||((i * rowDir) + tRow < 0)
                                                 || ((i * colDir) + tCol >= 8) ||((i * colDir) + tCol < 0)) break;
                                                if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() == 6){
                                               
							if (range != 1){
						        result += bishop->getRow() + '0';
                                                        result += bishop->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                                        break;
							} else{
								int advantage = 0;
								for (auto observer: target->observers){
									if (observer->getColour() == colour) ++advantage;
									else --advantage;
								}
   								if (advantage > 0){
                                                        result += bishop->getRow() + '0';
                                                        result += bishop->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                      if (advantage == 0)  moves.emplace_back(result);
							else {
								for (int i = 0; i < 30; ++i){
								moves.emplace_back(result);
								}
							}
                                                        result = "";
                                                        break;


								}

							}
                                                } else if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() != 0  ) break;
                                        }

                                        if ((target->getColour() != colour) && (target->getColour() != -1)) {
                                                result += bishop->getRow() + '0';
                                                result += bishop->getCol() + '0';
                                                result += target->getRow() + '0';
                                                result += target->getCol() + '0';
						int howMany = target->getPiece();
						for (int i = 0; i < 10 * howMany / 3; ++i){
                                                	moves.emplace_back(result);
						}
				                                                if (target->getPiece() == 6 || target->getPiece() == 4){
                                                        for (int i = 0; i < 100; ++i) moves.emplace_back(result);

                                                }

                                                result = "";
                                        }
                                }
                        }

                        for (auto knight : knights) {
                                for (auto target: knight->targets) {
                                        bool capture = false;
                                        for (auto observer: target->observers){
                                                if (observer->getColour() != colour){
                                                         capture = true;
                                                         break;
                                                }
                                             if (capture == true) break;


                                        }
                                        if (capture == true) continue;



                                int tRow = target->getRow();
                                int tCol = target->getCol();
                                int rowDif = kRow - tRow;
                                int colDif = kCol - kCol;
                                if ((((rowDif == 2) || (rowDif == -2)) && (colDif == 1 || colDif == -1)) ||
                                   ( ((rowDif == 1) || (rowDif == -1)) && (colDif == 2 || colDif == -2)) ){
                                                                 
                                                                int advantage = 0;
                                                                for (auto observer: target->observers){
                                                                        if (observer->getColour() == colour) ++advantage;
                                                                        else --advantage;
                                                                }
                                                                if (advantage >= 0){
                                                        result += knight->getRow() + '0';
                                                        result += knight->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                      if (advantage == 0)  moves.emplace_back(result);
                                                        else {
                                                                for (int i = 0; i < 30; ++i){
                                                                moves.emplace_back(result);
                                                                }
                                                        }
                                                        result = "";
                                                        break;


                                                                }

                                                        




                                }




                                        if ((target->getColour() != colour) && (target->getColour() != -1)) {
                                                result += knight->getRow() + '0';
                                                result += knight->getCol() + '0';
                                                result += target->getRow() + '0';
                                                result += target->getCol() + '0';
						int howMany = target->getPiece();
						for (int i = 0; i < 10 * howMany / 3; ++i){
                                                	moves.emplace_back(result);
						}
						       if (target->getPiece() == 6 || target->getPiece() == 4){
                                                        for (int i = 0; i < 100; ++i) moves.emplace_back(result);

                                                }

                                                result = "";
                                        }
                                }
                        }

                        for (auto rook : rooks) {
                                for (auto target: rook->targets) {

                                        bool capture = false;
                                        for (auto observer: target->observers){
                                                if (observer->getColour() != colour){
                                                         capture = true;
                                                         break;
                                                }
                                             if (capture == true) break;


                                        }
                                        if (capture == true) continue;

                                        int tRow = target->getRow();
                                        int tCol = target->getCol();
                                        int rowDif = kRow - tRow;
                                        int colDif = kCol - tCol;
                                        int range = (rowDif > 0) ? rowDif : -1 * rowDif;
                                        int rowDir = rowDif;
                                        int colDir = colDif;
                                        rowDir = ((rowDif > 0) && (rowDif != 0)) ? 1 : -1;
                                        colDir = ((colDif > 0) && (colDif != 0)) ? 1 : -1;

                                        for (int i = 1; i <= range; ++i){
                                                if (((i * rowDir) + tRow >= 8) ||((i * rowDir) + tRow < 0)
                                                 || ((i * colDir) + tCol >= 8) ||((i * colDir) + tCol < 0)) break;
                                                if ( (tRow != kRow) && (tCol != kCol)) break;
                                                if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() == 6){
                                             

/*

						           result += rook->getRow() + '0';
                                                        result += rook->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                                        break; 


*///comment out

						if (range != 1){
                                                        result += rook->getRow() + '0';
                                                        result += rook->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                                        break;
                                                        } else{
                                                                int advantage = 0;
                                                                for (auto observer: target->observers){
                                                                        if (observer->getColour() == colour) ++advantage;
                                                                        else --advantage;
                                                                }
                                                                if (advantage > 0){
                                                        result += rook->getRow() + '0';
                                                        result += rook->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                      if (advantage == 0)  moves.emplace_back(result);
                                                        else {
                                                                for (int i = 0; i < 30; ++i){
                                                                moves.emplace_back(result);
                                                                }
                                                        }
                                                        result = "";
                                                        break;


                                                                }

                                                        }

                                                } else if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() != 0  ) break;
                                        }


                                        if ((target->getColour() != colour) && (target->getColour() != -1)) {
                                                result += rook->getRow() + '0';
                                                result += rook->getCol() + '0';
                                                result += target->getRow() + '0';
                                                result += target->getCol() + '0';
						int howMany = target->getPiece();
						for (int i = 0; i < 10 * howMany / 5; ++i){
                                                	moves.emplace_back(result);
						}
						                                                if (target->getPiece() == 6){
                                                        for (int i = 0; i < 100; ++i) moves.emplace_back(result);

                                                }

                                                result = "";
                                        }
                                }
                        }

                        for (auto queen : queens) {
                                for (auto target: queen->targets) {
                                        bool capture = false;
                                        for (auto observer: target->observers){
                                                if (observer->getColour() != colour){
                                                         capture = true;
                                                         break;
                                                }
                                             if (capture == true) break;


                                        }
                                        if (capture == true) continue;



                                        int tRow = target->getRow();
                                        int tCol = target->getCol();
                                        int rowDif = kRow - tRow;
                                        int colDif = kCol - tCol;
                                        int range = (rowDif > 0) ? rowDif : -1 * rowDif;
                                        int rowDir = rowDif;
                                        int colDir = colDif;
                                        rowDir = ((rowDif > 0) && (rowDif != 0)) ? 1 : -1;
                                        colDir = ((colDif > 0) && (colDif != 0)) ? 1 : -1;

                                        for (int i = 1; i <= range; ++i){
                                                 if ((rowDif != colDif) && ((tRow != kRow) && (tCol != kCol)) ) break;

                                                if (((i * rowDir) + tRow >= 8) ||((i * rowDir) + tRow < 0)
                                                 || ((i * colDir) + tCol >= 8) ||((i * colDir) + tCol < 0)) break;
                                                if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() == 6){
                                                
/*/comment out
					        result += queen->getRow() + '0';
                                                        result += queen->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                                        break; 
*///comment out
						if (range != 1){
                                                        result += queen->getRow() + '0';
                                                        result += queen->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                                        break;
                                                        } else{
                                                                int advantage = 0;
                                                                for (auto observer: target->observers){
                                                                        if (observer->getColour() == colour) ++advantage;
                                                                        else --advantage;
                                                                }
                                                                if (advantage > 0){
                                                        result += queen->getRow() + '0';
                                                        result += queen->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                      if (advantage == 0)  moves.emplace_back(result);
                                                        else {
                                                                for (int i = 0; i < 30; ++i){
                                                                moves.emplace_back(result);
                                                                }
                                                        }
                                                        result = "";
                                                        break;


                                                                }

                                                        }



                                                } else if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() != 0  ) break;
                                        }







                                        if ((target->getColour() != colour) && (target->getColour() != -1)) {
                                                result += queen->getRow() + '0';
                                                result += queen->getCol() + '0';
                                                result += target->getRow() + '0';
                                                result += target->getCol() + '0';
						int howMany = target->getPiece();
							bool nobody = true;
                                                        for (auto observer: target->observers){
                                                                if (observer->getColour() != colour){
								nobody = false;
                                                                break;
                                                                }
							}
						
						if (nobody) {
							howMany *= 100;
							moves.clear();
						}
						for (int i = 0; i < howMany; ++i){
                                                	moves.emplace_back(result);
						}
                                                result = "";
                                        }
                                }
                        }

                        for (auto kin : king) {
                                for (auto target: kin->targets) {
                                        if ((target->getColour() != colour) && (target->getColour() != -1 )  ) {
                                                result += kin->getRow() + '0';
                                                result += kin->getCol() + '0';
                                                result += target->getRow() + '0';
                                                result += target->getCol() + '0';
                                                moves.emplace_back(result);
                                                result = "";
                                        }
                                }
                        }

                        for (auto pawn : pawns) {
                                bool capture = false;
                                for (auto observer : pawn->observers) {
                                        if (observer->getColour() != colour) {
                                                capture = true;
                                                break;
                                        }
                                }
                                if (capture) {

                                        for (auto target : pawn->targets) {



                                        if ((target->getCol() != pawn->getCol()) && ((theBoard[target->getRow()][target->getCol()]->getColour() == colour)||
                                                (theBoard[target->getRow()][target->getCol()]->getPiece() == 0)) ) continue;



                                                int advantage = 0;
			//			int friendly = 0;
                                                for (auto observer : target->observers) {


                                                        if (observer->getColour() != colour) {
                                                                --advantage;
                                                        }
							else ++advantage;
                                                }
                                                if (advantage >= 0) {
                                                        result += pawn->getRow() + '0';
                                                        result += pawn->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        if (advantage == 0) moves.emplace_back(result);
							else {
							for (int m = 0; m < 10; ++m){
								moves.emplace_back(result);
							}
                                                        result = "";
							}
                                                }
                                        }
                                }
                        }
                        for (auto bishop : bishops) {
                                bool capture = false;
                                for (auto observer : bishop->observers) {
                                        if (observer->getColour() != colour) {
                                                capture = true;
                                                break;
                                        }
                                }
                                if (capture) {
                                        for (auto target : bishop->targets) {
                                                bool dangerous = false;
                                               		
		                              int advantage = 0;
                        //                      int friendly = 0;
                                                for (auto observer : target->observers) {


                                                        if (observer->getColour() != colour) {
                                                                --advantage;
                                                        }
                                                        else ++advantage;
                                                }
                                                if (advantage > 0) {
                                                        result += bishop->getRow() + '0';
                                                        result += bishop->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        if (advantage == 0) moves.emplace_back(result);
                                                        else {
                                                        for (int m = 0; m < 10; ++m){
                                                                moves.emplace_back(result);
                                                        }
                                                        result = "";
							}
                                                }
/*/ comment out



							 for (auto observer : target->observers) {
                                                        if (observer->getColour() != colour) {
                                                                dangerous = true;
                                                                break;
                                                        }
                                                }
                                                if (!dangerous) {
                                                        result += bishop->getRow() + '0';
                                                        result += bishop->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
              

                                  } 
*///comment out
                                        }
                                }
                        }
                        for (auto knight : knights) {
                                bool capture = false;
                                for (auto observer : knight->observers) {
                                        if (observer->getColour() != colour) {
                                                capture = true;
                                                break;
                                        }
                                }
                                if (capture) {
                                        for (auto target : knight->targets) {

	                                    int advantage = 0;
                        //                      int friendly = 0;
                                                for (auto observer : target->observers) {


                                                        if (observer->getColour() != colour) {
                                                                --advantage;
                                                        }
                                                        else ++advantage;
                                                }
                                                if (advantage > 0) {
                                                        result += knight->getRow() + '0';
                                                        result += knight->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        if (advantage == 0) moves.emplace_back(result);
                                                        else {
                                                        for (int m = 0; m < 10; ++m){
                                                                moves.emplace_back(result);
                                                        }
                                                        result = "";
                                                        }
                                                }

					



/*/ comment out

                                                bool dangerous = false;
                                                for (auto observer : target->observers) {
                                                        if (observer->getColour() != colour) {
                                                                dangerous = true;
                                                                break;
                                                        }
                                                }
                                                if (!dangerous) {
                                                        result += knight->getRow() + '0';
                                                        result += knight->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                             } 


*/// comment out
                                        }
                                }
                        }
                        for (auto rook : rooks) {
                                bool capture = false;
                                for (auto observer : rook->observers) {
                                        if (observer->getColour() != colour) {
                                                capture = true;
                                                break;
                                        }
                                }
                                if (capture) {
                                        for (auto target : rook->targets) {
                                                                                                int advantage = 0;
                        //                      int friendly = 0;
                                                for (auto observer : target->observers) {


                                                        if (observer->getColour() != colour) {
                                                                --advantage;
                                                        }
                                                        else ++advantage;
                                                }
                                                if (advantage > 0) {
                                                        result += rook->getRow() + '0';
                                                        result += rook->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        if (advantage == 0) moves.emplace_back(result);
                                                        else {
                                                        for (int m = 0; m < 10; ++m){
                                                                moves.emplace_back(result);
                                                        }
                                                        result = "";
                                                        }
                                                }

                                        }
                                }
                        }
                        for (auto queen : queens) {
                                bool capture = false;
                                for (auto observer : queen->observers) {
                                        if (observer->getColour() != colour) {
                                                capture = true;
                                                break;
                                        }
                                }
                                if (capture) {
                                        for (auto target : queen->targets) {
                                                                                                int advantage = 0;
                        //                      int friendly = 0;
                                                for (auto observer : target->observers) {


                                                        if (observer->getColour() != colour) {
                                                                --advantage;
                                                        }
                                                        else ++advantage;
                                                }
                                                if (advantage > 0) {
                                                        result += queen->getRow() + '0';
                                                        result += queen->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        if (advantage == 0) moves.emplace_back(result);
                                                        else {
                                                        for (int m = 0; m < 10; ++m){
                                                                moves.emplace_back(result);
                                                        }
                                                        result = "";
                                                        }
                                                }

                                        }
                                }
              

          }

/*/ comment out
                      if (checkMoves.size() != 0){
                                int ran = rand();
                                int num = ran %  checkMoves.size();
                                int i = (num > 0) ? num : num * -1;

                                result = checkMoves[i];
                                return result;


                        } 


*/// comment out
//
  //                      cout << " further than checkMoves" << endl;

                        if (moves.size() != 0) {
				bool valid = false;
				for (auto move : moves) {
					if (theBoard[move[2] - '0'][move[3] - '0']->getColour() != colour) valid = true;
				}
				if (valid) {
                                int ran = rand();
                                int num = ran %  moves.size();
                                int i = (num > 0) ? num : num * -1;

                                result = moves[i];
                                return result;
				}
                        }
        }
















        case 3: {
			cout << 3 << endl;
		//	vector<string> checkMoves;
			vector<string> moves;
			
			for (auto pawn : pawns) {
				for (auto target: pawn->targets) {
					bool capture = false;
					for (auto observer: target->observers){
						if (observer->getColour() != colour){
							 capture = true;
							 break;
						}
					     if (capture == true) break;
						

					}
					if (capture == true) continue;
					



					if ((target->getCol() != pawn->getCol()) && ((theBoard[target->getRow()][target->getCol()]->getColour() == colour)||
						(theBoard[target->getRow()][target->getCol()]->getPiece() == 0)) ) continue;
					if (colour == 0){
						if ((target->getRow() == kRow - 1) && ((target->getCol() == kCol + 1) || (target->getCol() == kCol - 1))){
					        	result += pawn->getRow() + '0';
                                                	result += pawn->getCol() + '0';
                                                	result += target->getRow() + '0';
                                                	result += target->getCol() + '0';
                                                	moves.emplace_back(result);
                                                	result = "";

						}
					}
					else {
                                                if ((target->getRow() == kRow + 1) && ((target->getCol() == kCol + 1) || (target->getCol() == kCol - 1))){
                                                        result += pawn->getRow() + '0';
                                                        result += pawn->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";

                                                }
					}




					if ((target->getColour() != colour) && (target->getColour() != -1)) {
						result += pawn->getRow() + '0';
						result += pawn->getCol() + '0';
						result += target->getRow() + '0';
						result += target->getCol() + '0';
						moves.emplace_back(result);
						result = "";
					} 
				}
			}
		
			for (auto bishop : bishops) {
				for (auto target: bishop->targets){
	                                bool capture = false;
                                        for (auto observer: target->observers){
                                                if (observer->getColour() != colour){
                                                         capture = true;
                                                         break;
                                                }
                                             if (capture == true) break;


                                        }
                                        if (capture == true) continue;


					int tRow = target->getRow();
					int tCol = target->getCol();
					int rowDif = kRow - tRow;
					int colDif = kCol - tCol;
					int range = (rowDif > 0) ? rowDif : -1 * rowDif;
					int rowDir = rowDif;
					int colDir = colDif;
					rowDir = ((rowDif > 0) && (rowDif != 0)) ? 1 : -1;
					colDir = ((colDif > 0) && (colDif != 0)) ? 1 : -1;

					for (int i = 1; i <= range; ++i){
						if (rowDif != colDif) break;
						if (((i * rowDir) + tRow >= 8) ||((i * rowDir) + tRow < 0)  
						 || ((i * colDir) + tCol >= 8) ||((i * colDir) + tCol < 0)) break;
						if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() == 6){
						      	result += bishop->getRow() + '0';
        	                                        result += bishop->getCol() + '0';
                	                                result += target->getRow() + '0';
                        	                        result += target->getCol() + '0';
                                	               	moves.emplace_back(result);
                                        	        result = "";
							break;
						} else if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() != 0  ) break;
					}

					if ((target->getColour() != colour) && (target->getColour() != -1)) {
						result += bishop->getRow() + '0';
						result += bishop->getCol() + '0';
						result += target->getRow() + '0';
						result += target->getCol() + '0';
						moves.emplace_back(result);
						result = "";
					} 
				}
			}
			
			for (auto knight : knights) {
				for (auto target: knight->targets) {
				        bool capture = false;
                                        for (auto observer: target->observers){
                                                if (observer->getColour() != colour){
                                                         capture = true;
                                                         break;
                                                }
                                             if (capture == true) break;


                                        }
                                        if (capture == true) continue;


					
				int tRow = target->getRow();
				int tCol = target->getCol();
				int rowDif = kRow - tRow;
				int colDif = kCol - kCol;
				if ((((rowDif == 2) || (rowDif == -2)) && (colDif == 1 || colDif == -1)) ||
				   ( ((rowDif == 1) || (rowDif == -1)) && (colDif == 2 || colDif == -2)) ){
			     		        result += knight->getRow() + '0';
                                                result += knight->getCol() + '0';
                                                result += target->getRow() + '0';
                                                result += target->getCol() + '0';
                                                moves.emplace_back(result);
                                                result = "";


				
				}
				



					if ((target->getColour() != colour) && (target->getColour() != -1)) {
						result += knight->getRow() + '0';
						result += knight->getCol() + '0';
						result += target->getRow() + '0';
						result += target->getCol() + '0';
						moves.emplace_back(result);
						result = "";
					} 
				}
			}
			
			for (auto rook : rooks) {
				for (auto target: rook->targets) {

					bool capture = false;
                                        for (auto observer: target->observers){
                                                if (observer->getColour() != colour){
                                                         capture = true;
                                                         break;
                                                }
                                             if (capture == true) break;


                                        }
                                        if (capture == true) continue;

                                        int tRow = target->getRow();
                                        int tCol = target->getCol();
                                        int rowDif = kRow - tRow;
                                        int colDif = kCol - tCol;
                                        int range = (rowDif > 0) ? rowDif : -1 * rowDif;
                                        int rowDir = rowDif;
                                        int colDir = colDif;
                                        rowDir = ((rowDif > 0) && (rowDif != 0)) ? 1 : -1;
                                        colDir = ((colDif > 0) && (colDif != 0)) ? 1 : -1;

                                        for (int i = 1; i <= range; ++i){
                                                if (((i * rowDir) + tRow >= 8) ||((i * rowDir) + tRow < 0)
                                                 || ((i * colDir) + tCol >= 8) ||((i * colDir) + tCol < 0)) break;
						if ( (tRow != kRow) && (tCol != kCol)) break;
                                                if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() == 6){
                                                        result += rook->getRow() + '0';
                                                        result += rook->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                                        break;
                                                } else if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() != 0  ) break;
                                        }


					if ((target->getColour() != colour) && (target->getColour() != -1)) {
						result += rook->getRow() + '0';
						result += rook->getCol() + '0';
						result += target->getRow() + '0';
						result += target->getCol() + '0';
						moves.emplace_back(result);
						result = "";
					} 
				}
			}
			
			for (auto queen : queens) {
				for (auto target: queen->targets) {
					bool capture = false;
                                        for (auto observer: target->observers){
                                                if (observer->getColour() != colour){
                                                         capture = true;
                                                         break;
                                                }
                                             if (capture == true) break;


                                        }
                                        if (capture == true) continue;

					

                                        int tRow = target->getRow();
                                        int tCol = target->getCol();
                                        int rowDif = kRow - tRow;
                                        int colDif = kCol - tCol;
                                        int range = (rowDif > 0) ? rowDif : -1 * rowDif;
                                        int rowDir = rowDif;
                                        int colDir = colDif;
                                        rowDir = ((rowDif > 0) && (rowDif != 0)) ? 1 : -1;
                                        colDir = ((colDif > 0) && (colDif != 0)) ? 1 : -1;

                                        for (int i = 1; i <= range; ++i){
						 if ((rowDif != colDif) && ((tRow != kRow) && (tCol != kCol)) ) break;

                                                if (((i * rowDir) + tRow >= 8) ||((i * rowDir) + tRow < 0)
                                                 || ((i * colDir) + tCol >= 8) ||((i * colDir) + tCol < 0)) break;
                                                if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() == 6){
                                                        result += queen->getRow() + '0';
                                                        result += queen->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                                        break;
                                                } else if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() != 0  ) break;
                                        }







					if ((target->getColour() != colour) && (target->getColour() != -1)) {
						result += queen->getRow() + '0';
						result += queen->getCol() + '0';
						result += target->getRow() + '0';
						result += target->getCol() + '0';
						moves.emplace_back(result);
						result = "";
					} 
				}
			}
			
			for (auto kin : king) {
				for (auto target: kin->targets) {
					if ((target->getColour() != colour) && (target->getColour() != -1)) {
						result += kin->getRow() + '0';
						result += kin->getCol() + '0';
						result += target->getRow() + '0';
						result += target->getCol() + '0';
						moves.emplace_back(result);
						result = "";
					} 
				}
			}

			for (auto pawn : pawns) {
				bool capture = false;
				for (auto observer : pawn->observers) {
					if (observer->getColour() != colour) {
						capture = true;
						break;
					}
				}
				if (capture) {
					for (auto target : pawn->targets) {
                                        if ((target->getCol() != pawn->getCol()) && ((theBoard[target->getRow()][target->getCol()]->getColour() == colour)||
                                                (theBoard[target->getRow()][target->getCol()]->getPiece() == 0)) ) continue;
						bool dangerous = false;
						for (auto observer : target->observers) {
							if (observer->getColour() != colour) {
								dangerous = true;
								break;
							}
						}
						if (!dangerous) {
							result += pawn->getRow() + '0';
							result += pawn->getCol() + '0';
							result += target->getRow() + '0';
							result += target->getCol() + '0';
							moves.emplace_back(result);
							result = "";
						}
					}
				}
			}
                        for (auto bishop : bishops) {
                                bool capture = false;
                                for (auto observer : bishop->observers) {
                                        if (observer->getColour() != colour) {
                                                capture = true;
                                                break;
                                        }
                                }
                                if (capture) {
                                        for (auto target : bishop->targets) {
                                                bool dangerous = false;
                                                for (auto observer : target->observers) {
                                                        if (observer->getColour() != colour) {
                                                                dangerous = true;
                                                                break;
                                                        }
                                                }
                                                if (!dangerous) {
                                                        result += bishop->getRow() + '0';
                                                        result += bishop->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                                }
                                        }
                                }
                        }
                        for (auto knight : knights) {
                                bool capture = false;
                                for (auto observer : knight->observers) {
                                        if (observer->getColour() != colour) {
                                                capture = true;
                                                break;
                                        }
                                }
                                if (capture) {
                                        for (auto target : knight->targets) {
                                                bool dangerous = false;
                                                for (auto observer : target->observers) {
                                                        if (observer->getColour() != colour) {
                                                                dangerous = true;
                                                                break;
                                                        }
                                                }
                                                if (!dangerous) {
                                                        result += knight->getRow() + '0';
                                                        result += knight->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                                }
                                        }
                                }
                        }
                        for (auto rook : rooks) {
                                bool capture = false;
                                for (auto observer : rook->observers) {
                                        if (observer->getColour() != colour) {
                                                capture = true;
                                                break;
                                        }
                                }
                                if (capture) {
                                        for (auto target : rook->targets) {
                                                bool dangerous = false;
                                                for (auto observer : target->observers) {
                                                        if (observer->getColour() != colour) {
                                                                dangerous = true;
                                                                break;
                                                        }
                                                }
                                                if (!dangerous) {
                                                        result += rook->getRow() + '0';
                                                        result += rook->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                                }
                                        }
                                }
                        }
                        for (auto queen : queens) {
                                bool capture = false;
                                for (auto observer : queen->observers) {
                                        if (observer->getColour() != colour) {
                                                capture = true;
                                                break;
                                        }
                                }
                                if (capture) {
                                        for (auto target : queen->targets) {
                                                bool dangerous = false;
                                                for (auto observer : target->observers) {
                                                        if (observer->getColour() != colour) {
                                                                dangerous = true;
                                                                break;
                                                        }
                                                }
                                                if (!dangerous) {
                                                        result += queen->getRow() + '0';
                                                        result += queen->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                                }
                                        }
                                }
                        }
			bool capture = false;
			for (auto observer : king[0]->observers) {
				if (observer->getColour() != colour) {
                                        capture = true;
                                                break;
                                        }
                                }
                                if (capture) {
                                        for (auto target : king[0]->targets) {
                                                bool dangerous = false;
                                                for (auto observer : target->observers) {
                                                        if (observer->getColour() != colour) {
                                                                dangerous = true;
                                                                break;
                                                        }
                                                }
                                                if (!dangerous) {
                                                        result += king[0]->getRow() + '0';
                                                        result += king[0]->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                                }
                                        }
                                }
			if (moves.size() != 0) {
				bool valid = false;
				for (auto move : moves) {
					if (theBoard[move[2] - '0'][move[3] - '0']->getColour() != colour) valid = true;
				}
				if (valid) {
					int ran = rand();
                			int num = ran %  moves.size();
                			int i = (num > 0) ? num : num * -1;
					result = moves[i];
					return result;
				}
			}			
	}
        case 2: {

			vector<string> moves;			
			for (auto pawn : pawns) {
				for (auto target: pawn->targets) {
					if ((target->getCol() != pawn->getCol()) && ((theBoard[target->getRow()][target->getCol()]->getColour() == colour)||
						(theBoard[target->getRow()][target->getCol()]->getPiece() == 0)) ) continue;
					if (colour == 0){
						if ((target->getRow() == kRow - 1) && ((target->getCol() == kCol + 1) || (target->getCol() == kCol - 1))){
					        	result += pawn->getRow() + '0';
                                                	result += pawn->getCol() + '0';
                                                	result += target->getRow() + '0';
                                                	result += target->getCol() + '0';
                                                	moves.emplace_back(result);
                                                	result = "";

						}
					}
					else {
                                                if ((target->getRow() == kRow + 1) && ((target->getCol() == kCol + 1) || (target->getCol() == kCol - 1))){
                                                        result += pawn->getRow() + '0';
                                                        result += pawn->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";

                                                }
					}
					if ((target->getColour() != colour) && (target->getColour() != -1)) {
						result += pawn->getRow() + '0';
						result += pawn->getCol() + '0';
						result += target->getRow() + '0';
						result += target->getCol() + '0';
						moves.emplace_back(result);
						result = "";
					} 
				}
			}
			
			for (auto bishop : bishops) {
				for (auto target: bishop->targets) {
					int tRow = target->getRow();
					int tCol = target->getCol();
					int rowDif = kRow - tRow;
					int colDif = kCol - tCol;
					int range = (rowDif > 0) ? rowDif : -1 * rowDif;
					int rowDir = rowDif;
					int colDir = colDif;
					rowDir = ((rowDif > 0) && (rowDif != 0)) ? 1 : -1;
					colDir = ((colDif > 0) && (colDif != 0)) ? 1 : -1;

					for (int i = 1; i <= range; ++i){
						if (rowDif != colDif) break;
						if (((i * rowDir) + tRow >= 8) ||((i * rowDir) + tRow < 0)  
						 || ((i * colDir) + tCol >= 8) ||((i * colDir) + tCol < 0)) break;
						if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() == 6){
						      	result += bishop->getRow() + '0';
        	                                        result += bishop->getCol() + '0';
                	                                result += target->getRow() + '0';
                        	                        result += target->getCol() + '0';
                                	               	moves.emplace_back(result);
                                        	        result = "";
							break;
						} else if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() != 0  ) break;
					}

					if ((target->getColour() != colour) && (target->getColour() != -1)) {
						result += bishop->getRow() + '0';
						result += bishop->getCol() + '0';
						result += target->getRow() + '0';
						result += target->getCol() + '0';
						moves.emplace_back(result);
						result = "";
					} 
				}
			}
			
			for (auto knight : knights) {
				for (auto target: knight->targets) {

					
				int tRow = target->getRow();
				int tCol = target->getCol();
				int rowDif = kRow - tRow;
				int colDif = kCol - kCol;
				if ((((rowDif == 2) || (rowDif == -2)) && (colDif == 1 || colDif == -1)) ||
				   ( ((rowDif == 1) || (rowDif == -1)) && (colDif == 2 || colDif == -2)) ){
			     		        result += knight->getRow() + '0';
                                                result += knight->getCol() + '0';
                                                result += target->getRow() + '0';
                                                result += target->getCol() + '0';
                                                moves.emplace_back(result);
                                                result = "";


				
				}

					if ((target->getColour() != colour) && (target->getColour() != -1)) {
						result += knight->getRow() + '0';
						result += knight->getCol() + '0';
						result += target->getRow() + '0';
						result += target->getCol() + '0';
						moves.emplace_back(result);
						result = "";
					} 
				}
			}
			
			for (auto rook : rooks) {
				for (auto target: rook->targets) {
                                        int tRow = target->getRow();
                                        int tCol = target->getCol();
                                        int rowDif = kRow - tRow;
                                        int colDif = kCol - tCol;
                                        int range = (rowDif > 0) ? rowDif : -1 * rowDif;
                                        int rowDir = rowDif;
                                        int colDir = colDif;
                                        rowDir = ((rowDif > 0) && (rowDif != 0)) ? 1 : -1;
                                        colDir = ((colDif > 0) && (colDif != 0)) ? 1 : -1;

                                        for (int i = 1; i <= range; ++i){
                                                if (((i * rowDir) + tRow >= 8) ||((i * rowDir) + tRow < 0)
                                                 || ((i * colDir) + tCol >= 8) ||((i * colDir) + tCol < 0)) break;
						if ( (tRow != kRow) && (tCol != kCol)) break;
                                                if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() == 6){
                                                        result += rook->getRow() + '0';
                                                        result += rook->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                                        break;
                                                } else if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() != 0  ) break;
                                        }


					if ((target->getColour() != colour) && (target->getColour() != -1)) {
						result += rook->getRow() + '0';
						result += rook->getCol() + '0';
						result += target->getRow() + '0';
						result += target->getCol() + '0';
						moves.emplace_back(result);
						result = "";
					} 
				}
			}
			
			for (auto queen : queens) {
				for (auto target: queen->targets) {



                                        int tRow = target->getRow();
                                        int tCol = target->getCol();
                                        int rowDif = kRow - tRow;
                                        int colDif = kCol - tCol;
                                        int range = (rowDif > 0) ? rowDif : -1 * rowDif;
                                        int rowDir = rowDif;
                                        int colDir = colDif;
                                        rowDir = ((rowDif > 0) && (rowDif != 0)) ? 1 : -1;
                                        colDir = ((colDif > 0) && (colDif != 0)) ? 1 : -1;

                                        for (int i = 1; i <= range; ++i){
						 if ((rowDif != colDif) && ((tRow != kRow) && (tCol != kCol)) ) break;

                                                if (((i * rowDir) + tRow >= 8) ||((i * rowDir) + tRow < 0)
                                                 || ((i * colDir) + tCol >= 8) ||((i * colDir) + tCol < 0)) break;
                                                if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() == 6){
                                                        result += queen->getRow() + '0';
                                                        result += queen->getCol() + '0';
                                                        result += target->getRow() + '0';
                                                        result += target->getCol() + '0';
                                                        moves.emplace_back(result);
                                                        result = "";
                                                        break;
                                                } else if (theBoard[(i * rowDir) + tRow][(i * colDir) + tCol]->getPiece() != 0  ) break;
                                        }

					if ((target->getColour() != colour) && (target->getColour() != -1)) {
						result += queen->getRow() + '0';
						result += queen->getCol() + '0';
						result += target->getRow() + '0';
						result += target->getCol() + '0';
						moves.emplace_back(result);
						result = "";
					} 
				}
			}
			
			for (auto kin : king) {
				for (auto target: kin->targets) {
					if ((target->getColour() != colour) && (target->getColour() != -1)) {
						result += kin->getRow() + '0';
						result += kin->getCol() + '0';
						result += target->getRow() + '0';
						result += target->getCol() + '0';
						moves.emplace_back(result);
						result = "";
					} 
				}
			}

			
			if (moves.size() != 0) {
				bool valid = false;
				for (auto move : moves) {
					if (theBoard[move[2] - '0'][move[3] - '0']->getColour() != colour) valid = true;
				}
				if (valid) {
				int ran = rand();
                		int num = ran %  moves.size();
                		int i = (num > 0) ? num : num * -1;

				result = moves[i];
				return result;
				}
			}
		}	
        case 1: {
			while(result == "") {

				int ran = rand();


				int num = ran % pieces;

				int pieceChoice = (num > 0) ? num : num * -1;

				int size;
				if (pieceChoice < pawns.size()) {

					ran = rand();
					num = ran %  pawns[pieceChoice]->targets.size();
					int targetChoice = (num > 0) ? num : num * -1;               
							
					result += pawns[pieceChoice]->getRow() + '0';

					result += pawns[pieceChoice]->getCol() + '0';
					result += pawns[pieceChoice]->targets[targetChoice]->getRow()  + '0';

					result += pawns[pieceChoice]->targets[targetChoice]->getCol() + '0';

				}
				else if (pieceChoice - pawns.size() < bishops.size()) {

					pieceChoice = pieceChoice - pawns.size();
					ran = rand();
                                        num = ran %  bishops[pieceChoice]->targets.size();
                                        int targetChoice = (num > 0) ? num : num * -1;            
							
					result += bishops[pieceChoice]->getRow() + '0';
					result += bishops[pieceChoice]->getCol() + '0';
					result += bishops[pieceChoice]->targets[targetChoice]->getRow() + '0';
					result += bishops[pieceChoice]->targets[targetChoice]->getCol() + '0';
				}
				else if (pieceChoice - pawns.size() - bishops.size() < knights.size()) {

					pieceChoice = pieceChoice - pawns.size() - bishops.size();
					ran = rand();
                                        num = ran %  knights[pieceChoice]->targets.size();
                                        int targetChoice = (num > 0) ? num : num * -1;               
							
					result += knights[pieceChoice]->getRow() + '0';
					result += knights[pieceChoice]->getCol() + '0';
					result += knights[pieceChoice]->targets[targetChoice]->getRow() + '0';
					result += knights[pieceChoice]->targets[targetChoice]->getCol() + '0';
				}
				else if (pieceChoice - pawns.size() - bishops.size() - knights.size() < rooks.size()) {

					pieceChoice = pieceChoice - pawns.size() - bishops.size() - knights.size();
					ran = rand();
                                        num = ran %  rooks[pieceChoice]->targets.size();
                                        int targetChoice = (num > 0) ? num : num * -1;
               
							
					result += rooks[pieceChoice]->getRow() + '0';
					result += rooks[pieceChoice]->getCol() + '0';
					result += rooks[pieceChoice]->targets[targetChoice]->getRow() + '0';
					result += rooks[pieceChoice]->targets[targetChoice]->getCol() + '0';
				}
				else if (pieceChoice - pawns.size() - bishops.size() - knights.size() - rooks.size() < queens.size()) {

					pieceChoice = pieceChoice - pawns.size() - bishops.size() - knights.size() - rooks.size();
					ran = rand();
                                        num = ran %  queens[pieceChoice]->targets.size();
                                        int targetChoice = (num > 0) ? num : num * -1;               
							
					result += queens[pieceChoice]->getRow() + '0';
					result += queens[pieceChoice]->getCol() + '0';
					result += queens[pieceChoice]->targets[targetChoice]->getRow() + '0';
					result += queens[pieceChoice]->targets[targetChoice]->getCol() + '0';
				}
				else {
					pieceChoice = pieceChoice - pawns.size() - bishops.size() - knights.size() - rooks.size() - queens.size();
					ran = rand();
                                        num = ran %  king[pieceChoice]->targets.size();
                                        int targetChoice = (num > 0) ? num : num * -1;               
							
					result += king[pieceChoice]->getRow() + '0';
					result += king[pieceChoice]->getCol() + '0';
					result += king[pieceChoice]->targets[targetChoice]->getRow() + '0';
					result += king[pieceChoice]->targets[targetChoice]->getCol() + '0';
				}
			}
			break;
		}
        }
	return result;
}

bool Computer::isHuman() {
        return false;
}

