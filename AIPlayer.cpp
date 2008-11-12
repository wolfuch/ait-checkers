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

int AIPlayer::getNextMove(/* Board* board */){
	Heuristic* h = new Heuristic();
	return h->analyse(/* board */);
}
