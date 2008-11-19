/*
 ********************************************************
 *  Filename:   HumanPlayer.cpp
 ********************************************************
 *  Created on: Nov 5, 2008
 *      Author: marc
 ********************************************************
 */

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer() {
	// Nothing yet to do here
}

HumanPlayer::~HumanPlayer() {
	// Nothing yet to do here
}

/**
 * Method which reads the next move from the human (over keyboard) and executed the move if possible.
 * If not, the player will be asked as long until he enters a legal move.
 */
unsigned long HumanPlayer::getNextMove(board* b){
	unsigned int moveFrom = 0;	// Position from where to move
	unsigned int moveTo = 0;	// Position to where to move
	unsigned long move = 0;		// Move "sequence"
	bool moved = false;			// If the tried move has been made (was legal) or not.

	/* Ask move until it is a legal one */
	while(!moved){
		cout << "Which stone do you want to move? (xy):     ";
		cin >> moveFrom;
		cout << "Where to you want to move you stone? (xy): ";
		cin >> moveTo;
		move = moveTo*100 + moveFrom;		// Combine moveFrom and moveTo
		cout << "Move = " << move << endl;
		b->calculatePossibleMoves(0);		// Moves have to be calculated before moving
		moved = b->movePiece(move, 0);		// TRY
	}

	return move;
}
