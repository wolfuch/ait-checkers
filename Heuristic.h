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
#include <set>
#include <iostream>

using namespace std;


	 #define PIECE_VALUE  100		// TODO: add static const
	 #define KING_VALUE  200
	 #define CORNER_PENALTY  40
	 #define EDGE_PENALTY  20
	 #define PLUS_INFINITY    1000000
	 #define MINUS_INFINITY  -1000000

class Heuristic {
public:
	Heuristic();
	~Heuristic();
	unsigned int bestMove(board* b, int color);
private:
	std::set<unsigned int> bestMoveHistory;
	unsigned int actualMove;
	int evaluation();
	int minMax(int level, int alpha, int beta);
	board* b;
	int color;		// 0 - white, 1 - black
	int maxLevel;
	int iteration;
};

#endif /* HEURISTIC_H_ */
