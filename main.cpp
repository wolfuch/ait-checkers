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
	MUTEX* mutex = new MUTEX();


	//int color=0;
	//std::cout<<(1+!(color)*7)<<std::endl;

	/* Create players */
	Player* whitePlayer = new HumanPlayer(0, "Marc");
	Player* blackPlayer = new AIPlayer(1, "Abraham", mutex);
	int terminal = 0;
	Timer *timer = new Timer(mutex,(AIPlayer*) blackPlayer);

	timer->start(NULL);		// starts new thread for time counting
	//brd->cal
	do {
		// White player
		brd->printBoardAlternative();
		whitePlayer->makeNextMove(brd);


		// Black player
		brd->printBoardAlternative();
		blackPlayer->makeNextMove(brd);

		terminal = brd->terminal();
	} while (terminal==0);

	brd->printBoardAlternative();

	if(terminal==1){
		cout << "Game finished! DRAW!" << endl;
	} else if(terminal==2){
		cout << "Game finished! " << whitePlayer->getName() << " won!" << endl;
	} else if(terminal==3){
		cout << "Game finished! " << blackPlayer->getName() << " won!" << endl;
	}

	return 0;
}


