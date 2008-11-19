/*
 ********************************************************
 *  Filename:   AIPlayer.cpp
 ********************************************************
 *  Created on: Nov 5, 2008
 *      Author: marc
 ********************************************************
 */

#include "AIPlayer.h"

AIPlayer::AIPlayer(int color, string name) {
	m_color = color;
	m_name = name;

}

AIPlayer::~AIPlayer() {
	// TODO Auto-generated destructor stub
}

unsigned int AIPlayer::getNextMove(board* b){
	Heuristic* h = new Heuristic();
	return h->bestMove(b);
}
