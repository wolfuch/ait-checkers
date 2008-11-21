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

void AIPlayer::makeNextMove(board* b){
	//int move;
	Heuristic* h = new Heuristic();
	b->calculatePossibleMoves(m_color);					// Moves have to be calculated before moving
	//move 
	b->movePiece(h->bestMove(b, m_color), m_color);		// TRY
}
