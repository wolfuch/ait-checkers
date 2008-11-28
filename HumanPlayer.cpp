/*
 ********************************************************
 *  Filename:   HumanPlayer.cpp
 ********************************************************
 *  Created on: Nov 5, 2008
 *      Author: marc
 ********************************************************
 */

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int color, string name) {
	m_color = color;
	m_name = name;
}

HumanPlayer::~HumanPlayer() {
	// Nothing yet to do here
}

/**
 * Method which reads the next move from the human (over keyboard) and executed the move if possible.
 * If not, the player will be asked as long until he enters a legal move.
 */
void HumanPlayer::makeNextMove(board* b){
	unsigned int move = 0;		// Move "sequence"
	bool moved = false;			// If the tried move has been made (was legal) or not.

	/* Ask move until it is a legal one */
	while(!moved){
		cout << "Player '" << m_name << "':" << endl;
		cout << "What will be your move?:  ";
		cin >> move;		// Combine moveFrom and moveTo
		cout << "Move = " << move << endl;
		b->calculatePossibleMoves(m_color);		// Moves have to be calculated before moving
		moved = b->movePiece(move, m_color);	// TRY
	}
}
