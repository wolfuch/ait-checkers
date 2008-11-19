/*
 ********************************************************
 *  Filename:   AIPlayer.cpp
 ********************************************************
 *  Created on: Nov 5, 2008
 *      Author: marc
 ********************************************************
 */

#include "AIPlayer.h"

AIPlayer::AIPlayer() {
	// TODO Auto-generated constructor stub

}

AIPlayer::~AIPlayer() {
	// TODO Auto-generated destructor stub
}

unsigned long AIPlayer::getNextMove(board* b){
	Heuristic* h = new Heuristic();
	return h->bestMove(b);
}
