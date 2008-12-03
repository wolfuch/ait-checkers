/*
 ********************************************************
 *  Filename:   AIPlayer.cpp
 ********************************************************
 *  Created on: Nov 5, 2008
 *      Author: marc
 ********************************************************
 */

#include "AIPlayer.h"

/* Initializes the player with color and name */
AIPlayer::AIPlayer(int color, string name, MUTEX* mutex) {
	m_color = color;
	m_name = name;
	m_heuristic = new Heuristic();
	m_mutex = mutex;
}

AIPlayer::~AIPlayer() {
	delete m_heuristic;
}

/* Requests the best move from the Heuristic and makes the move */
void AIPlayer::makeNextMove(board* b){
	m_mutex->release();
	b->calculatePossibleMoves(m_color);					// Moves have to be calculated before moving
	b->movePiece(m_heuristic->bestMove(b, m_color), m_color);		// TRY
}
