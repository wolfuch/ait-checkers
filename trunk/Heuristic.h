/*
 ********************************************************
 *  Filename:   Heuristic.h
 ********************************************************
 *  Created on: Nov 5, 2008
 *      Author: marc
 ********************************************************
 */

#ifndef HEURISTIC_H_
#define HEURISTIC_H_
#include "board.hpp"
#include "AIPlayer.h"
#include <set>
#include <iostream>

class AIPlayer;

using namespace std;


	 #define PIECE_VALUE  100		// TODO: add static const
	 #define KING_VALUE  230
	 #define CORNER_PENALTY  40
	 #define EDGE_PENALTY  20
	 #define PLUS_INFINITY    1000000
	 #define MINUS_INFINITY  -1000000
	#define ARRAY_SIZE 15

class Heuristic {
public:
	Heuristic();
	Heuristic(AIPlayer * aiPlayer);
	~Heuristic();
	unsigned int bestMove(board* b, int color);
	void timeoutOccured();
private:
	unsigned long long timeoutMove;
	bool firstMove;
	int bestLeafValue;
	unsigned long long bestLeafPath[ARRAY_SIZE];		// best current path
	unsigned int actualMove;		// the best move founded form the beginning
	int evaluation();
	int minMax(int level, int alpha, int beta, unsigned long long * downArray);
	board* b;
	int color;		// 0 - white, 1 - black
	int maxLevel;
	int iteration;
	int counter;
	AIPlayer *aiPlayer;
};

#endif /* HEURISTIC_H_ */
