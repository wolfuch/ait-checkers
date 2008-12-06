/*
 ********************************************************
 *  Filename:   HumanPlayer.h
 ********************************************************
 *  Created on: Nov 5, 2008
 *      Author: marc
 ********************************************************
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_
#include "Player.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

class HumanPlayer: public Player {
public:
	HumanPlayer(int color, string name);		// Creates user
	~HumanPlayer();								// Destroys user
	void makeNextMove(board* b);				// Requests the move from the user
	string getName();
};

#endif /* HUMANPLAYER_H_ */
