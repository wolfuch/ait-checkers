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
protected:
	int m_color;
	string m_name;
public:
	Player();
	~Player();
	virtual unsigned int getNextMove(board* board)=0;
};

#endif /* PLAYER_H_ */
