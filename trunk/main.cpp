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

using namespace std;

int main(int argc, char **argv) {
	std::set<int>::iterator iter;
	std::set <int> list;
	board* brd = new board();

	/* Create players */
	Player* whitePlayer = new HumanPlayer(0, "Marc");
	Player* blackPlayer = new AIPlayer(1, "Abraham");

	//brd->cal
	do {
		// White player
		brd->printBoard();
		whitePlayer->makeNextMove(brd);

		// Black player
		brd->printBoard();
		blackPlayer->makeNextMove(brd);
	} while (true);
	return 0;
}


