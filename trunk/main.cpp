/*
 ********************************************************
 *  Filename:   run_game_test.cpp
 ********************************************************
 *  Created on: Nov 19, 2008
 *      Author: marc
 ********************************************************
 */
#include <iostream>
#include <set>
#include "board.hpp"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Timer.h"

using namespace std;

int main(int argc, char **argv) {
	std::set<int>::iterator iter;
	std::set <int> list;
	board* brd = new board();
	MUTEX* mutex;

	//int color=0;
	//std::cout<<(1+!(color)*7)<<std::endl;

	/* Create players */
	Player* whitePlayer = new HumanPlayer(0, "Marc");
	Player* blackPlayer = new AIPlayer(1, "Abraham", mutex);

	//timer->start(NULL);		// starts new thread for time counting
	//brd->cal
	do {
		// White player
		brd->printBoardAlternative();
		whitePlayer->makeNextMove(brd);

		// Black player
		brd->printBoardAlternative();
		blackPlayer->makeNextMove(brd);
	} while (true);
	return 0;
}


