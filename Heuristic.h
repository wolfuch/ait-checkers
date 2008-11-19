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

using namespace std;

class Heuristic {
public:
	Heuristic();
	~Heuristic();
	long bestMove(board* b);
};

#endif /* HEURISTIC_H_ */
