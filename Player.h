/*
 ********************************************************
 *  Filename:   Player.h
 ********************************************************
 *  Created on: Nov 5, 2008
 *      Author: marc
 ********************************************************
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include "board.hpp"

using namespace std;

class Player {
public:
	Player();
	~Player();
	virtual int getNextMove(board* board)=0;
};

#endif /* PLAYER_H_ */
