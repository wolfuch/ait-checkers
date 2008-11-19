/*
 ********************************************************
 *  Filename:   Heuristic.cpp
 ********************************************************
 *  Created on: Nov 5, 2008
 *      Author: marc
 ********************************************************
 */

#include "Heuristic.h"

Heuristic::Heuristic() {
	// TODO Auto-generated constructor stub

}

Heuristic::~Heuristic() {
	// TODO Auto-generated destructor stub
}

unsigned int Heuristic::bestMove(board* b, int color){
	set<int> possibleMoves;
	set<int>::iterator iter;
	b->calculatePossibleMoves(color);
	possibleMoves = b->getPossibleMoves(color);

	iter=possibleMoves.begin();
	cout << " ********* " << (*iter) << " **********" << endl;
	return *iter;
}
