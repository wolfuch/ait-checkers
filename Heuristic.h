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

class Heuristic {
public:
	Heuristic();
	~Heuristic();
	unsigned int bestMove(board* b, int color);
};

#endif /* HEURISTIC_H_ */
