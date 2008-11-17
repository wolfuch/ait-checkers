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

int HumanPlayer::getNextMove(board* b){
	unsigned int moveFrom = 0;
	unsigned int moveTo = 0;
	unsigned int move = 0;
	cout << "Which stone do you want to move? (xy):     ";
	cin >> moveFrom;
	cout << "Where to you want to move you stone? (xy): ";
	cin >> moveTo;
	move = moveTo*100 + moveFrom;		// Combine moveFrom and moveTo
	cout << "Move = " << move << endl;

	while(!b->movePiece(move, 1)){
		cout << "Which stone do you want to move? (xy):     ";
		cin >> moveFrom;
		cout << "Where to you want to move you stone? (xy): ";
		cin >> moveTo;
		move = moveTo*100 + moveFrom;		// Combine moveFrom and moveTo
		cout << "Move = " << move << endl;
	}

	return move;
}
