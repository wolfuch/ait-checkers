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

using namespace std;

class Player {
public:
	Player();
	~Player();
	virtual int getNextMove(/* Board* board */)=0;
};

#endif /* PLAYER_H_ */
