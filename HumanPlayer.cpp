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
	bool stringValid = true;
	string moveStr;		// Move string
	unsigned int move = 0;		// Move "sequence"
	bool moved = false;			// If the tried move has been made (was legal) or not.
	set<unsigned long long> tempMoveSet,tempMoveSet2;

	/* Ask move until it is a legal one */
	while(!moved || !stringValid){
		stringValid = true;
		b->calculatePossibleMoves(m_color);		// Moves have to be calculated before moving
		tempMoveSet2 = b->getPossibleMoves(m_color);
		std::cout<<"*recently calculated : ";b->printSet(tempMoveSet2);
		cout << "Player '" << m_name << "':" << endl;
		cout << "What will be your move?:  ";
		cin >> moveStr;		// Combine moveFrom and moveTo
		cout << "Move = " << moveStr << endl;

		/* Check if the sequence is valid */
		for(unsigned int i = 0; i<strlen(moveStr.c_str());i++){
			if(((int)moveStr[i])-48<((int)'1')-48 || ((int)moveStr[i])-48>((int)'9')-48 ||
					strlen(moveStr.c_str())<4 || strlen(moveStr.c_str())%2!=0){
				stringValid = false;
			} else {
				move = move*10 + ((int)moveStr[i])-48;
			}
		}

		if(stringValid){
			moved = b->movePiece(move, m_color);	// TRY
		} else {
			cout << "Invalid move sequence!" << endl;
			move = 0;
		}
	}

	b->cleanUndo();
}

string HumanPlayer::getName(){
	return m_name;
}
