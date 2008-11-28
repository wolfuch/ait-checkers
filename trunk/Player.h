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

/* Abstract class for the player */
class Player {
protected:
	int m_color;			// Player color
	string m_name;			// Player name
public:
	Player();				// Constructor
	~Player();				// Destructor
	virtual void makeNextMove(board* board)=0;	//Interface for the next move
};

#endif /* PLAYER_H_ */
