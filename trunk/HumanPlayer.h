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

using namespace std;

class HumanPlayer: public Player {
public:
	HumanPlayer(int color, string name);
	~HumanPlayer();
	void makeNextMove(board* b);
};

#endif /* HUMANPLAYER_H_ */
