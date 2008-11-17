/*
 ********************************************************
 *  Filename:   AIPlayer.h
 ********************************************************
 *  Created on: Nov 5, 2008
 *      Author: marc
 ********************************************************
 */

#ifndef AIPLAYER_H_
#define AIPLAYER_H_
#include "Player.h"
#include "Heuristic.h"

using namespace std;

class AIPlayer: public Player {
public:
	AIPlayer();
	~AIPlayer();
	int getNextMove(board* b);
};

#endif /* AIPLAYER_H_ */
