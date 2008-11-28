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
	AIPlayer(int color, string name);		// Create user
	~AIPlayer();							// Destroy user (Empty implementation yet)
	void makeNextMove(board* b);			// Make the next best move
};

#endif /* AIPLAYER_H_ */
