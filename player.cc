#include <vector>
#include <iostream>
#include <memory>
#include "player.h"
using namespace std;

Player::Player(): pieces{16} {}

Player::Player(int colour): colour{colour}, pieces{16} /*, wins{0}, draws{0}, losses{0} */{}

Player::~Player() {}

int Player::getColour() {
	return colour;
}

bool Player::inCheckmate(vector<vector<shared_ptr<Cell>>> &theBoard) { // this is wrong
	int size = king[0]->targets.size();
	
	if (!inCheck()) return false;
	for (int i = 0; i < size; ++i) {
		if (king[0]->targets[i]->getColour() != colour) {
			bool safe = true;
			int size2 = king[0]->targets[i]->observers.size();
			for (int j = 0; j < size2; ++j) {
				if (king[0]->targets[i]->observers[j]->getColour() != colour) {
					cout << king[0]->targets[i]->observers[j]->getRow() << king[0]->targets[i]->observers[j]->getCol() << endl;
					safe = false;
					break;
				}
			}
			if (safe) return false;
	//		return false;
		}
	}
	cout << "shouldn't be here" << endl;
	int attackers = 0;
	for (auto observer : king[0]->observers) {
		if (observer->getColour() != colour) {
			++attackers;
			if (attackers > 1) return true;
			
			for (auto pawn : pawns) {
				if (pawn->targets.size() > 0) return false;
			}
			for (auto bishop : bishops) {
				if (bishop->targets.size() > 0) return false;
			}
			for (auto knight : knights) {
				if (knight->targets.size() > 0) return false;
			}
			for (auto rook : rooks) {
				if (rook->targets.size() > 0) return false;
			}
			for (auto queen : queens) {
				if (queen->targets.size() > 0) return false;
			}
		}
	}
	return true;
}

bool Player::inCheck() {
	int opponent = (colour == 0)? 1 : 0;
	int size = king[0]->observers.size();
	for (int i = 0; i < size; ++i) {
		if (king[0]->observers[i]->getColour() == opponent) return true;
	}
	return false;
}

bool Player::inStalemate() {
	int size = 0;
	size = pawns.size();
	for (int i = 0; i < size; ++i) {
		int size2 = pawns[i]->targets.size();
		for (int j = 0; j < size2; ++j) {
			if (pawns[i]->targets[j]->getColour() != colour) return false;
		}
	}
	size = bishops.size();
	for (int i = 0; i < size; ++i) {
		int size2 = bishops[i]->targets.size();
		for (int j = 0; j < size2; ++j) {
			if (bishops[i]->targets[j]->getColour() != colour) return false;
		}
	}
	size = knights.size();
	for (int i = 0; i < size; ++i) {
		int size2 = knights[i]->targets.size();
		for (int j = 0; j < size2; ++j) {
			if (knights[i]->targets[j]->getColour() != colour) return false;
		}
	}
	size = rooks.size();
	for (int i = 0; i < size; ++i) {
		int size2 = rooks[i]->targets.size();
		for (int j = 0; j < size2; ++j) {
			if (rooks[i]->targets[j]->getColour() != colour) return false;
		}
	}
	size = queens.size();
	for (int i = 0; i < size; ++i) {
		int size2 = queens[i]->targets.size();
		for (int j = 0; j < size2; ++j) {
			if (queens[i]->targets[j]->getColour() != colour) return false;
		}
	}
	bool kingStuck = true;
	for (auto target : king[0]->targets) {
		if (target->getColour() != colour) {
			bool dangerous = false;
			for (auto observer : target->observers) {
				if (observer->getColour() != colour) dangerous = true;
			}
			if (!dangerous) kingStuck = false;
		}
	}
	if (kingStuck) return true;
	else return false;
}

//float Player::score() {
//	float w = wins;
//	float d = draws;
//	return w + d * 0.5;
//}

void Player::addPiece(int pieceType, shared_ptr<Cell> piece) {
//	cout << piece->getRow() << " " << piece->getCol() << endl;
	switch (pieceType) {
	case 1:
		pawns.emplace_back(static_pointer_cast<Pawn>(piece)); 
	//	cout << pawns.back()->getRow() << " " << pawns.back()->getCol() << endl;
		break;
	case 2:
		bishops.emplace_back(static_pointer_cast<Bishop>(piece)); break;
	case 3:
		knights.emplace_back(static_pointer_cast<Knight>(piece)); break;
	case 4:
		rooks.emplace_back(static_pointer_cast<Rook>(piece)); break;
	case 5:
		queens.emplace_back(static_pointer_cast<Queen>(piece)); break;
	case 6:
		king.emplace_back(static_pointer_cast<King>(piece)); break;
	}
	++pieces;
}

void Player::reset() {
	pieces = 0;
	pawns.clear();
	bishops.clear();
	knights.clear();
	rooks.clear();
	queens.clear();
	king.clear();
}

void Player::setCheckTargets(vector<vector<shared_ptr<Cell>>> &theBoard) {
	king[0]->setCheckTargets(theBoard);
	for (auto piece : pawns) {
		piece->setCheckTargets(king[0], theBoard);
	}
	for (auto piece : bishops) {
		piece->setCheckTargets(king[0], theBoard);
	}
	for (auto piece : knights) {
		piece->setCheckTargets(king[0], theBoard);
	}
	for (auto piece : rooks) {
		piece->setCheckTargets(king[0], theBoard);
	}
	for (auto piece : queens) {
		piece->setCheckTargets(king[0], theBoard);
	}
}

string Player::move(int kRow, int kCol, vector<vector<shared_ptr<Cell>>> &theBoard) {
/*	int size = 0;
	size = pawns.size();
	for (int i = 0; i < size; ++i) {
		if (pawns[i]->getRow() == r && pawns[i]->getCol() == c) {
			pawns[i] = dest;
			return;
		}
	}
	size = bishops.size();
	for (int i = 0; i < size; ++i) {
		if (bishops[i]->getRow() == r && bishops[i]->getCol() == c) {
			bishops[i] = dest;
			return;
		}
	}
	size = knights.size();
	for (int i = 0; i < size; ++i) {
		if (knights[i]->getRow() == r && knights[i]->getCol() == c) {
			knights[i] = dest;
			return;
		}
	}
	size = rooks.size();
	for (int i = 0; i < size; ++i) {
		if (rooks[i]->getRow() == r && rooks[i]->getCol() == c) {
			rooks[i] = dest;
			return;
		}
	}
	size = queens.size();
	for (int i = 0; i < size; ++i) {
		if (queens[i]->getRow() == r && queens[i]->getCol() == c) {
			queens[i] = dest;
			return;
		}
	}
	if (king[0]->getRow() == r && king[0]->getCol() == c) {
		king[0] = dest;
		return;
	}*/
	return "";
}

bool Player::isHuman() {
	return true;
}
