#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include <vector>
#include <cstdlib>
#include "player.h"
#include <string>

class Computer: public Player {
	int level;

	public:
	Computer(int level, int colour);
	
	std::string move(int kRow, int kCol, std::vector<std::vector<std::shared_ptr<Cell>>> &theBoard) override;
	void increaseLevel();
	void decreaseLevel();
	bool isHuman() override;			
};

#endif
