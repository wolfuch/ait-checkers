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
#include "Thread.h"

using namespace std;

class AIPlayer: public Player {
public:
	AIPlayer(int color, string name, MUTEX* mutex);		// Create user
	~AIPlayer();							// Destroy user (Empty implementation yet)
	void makeNextMove(board* b);			// Make the next best move
	string getName();
private:
	Heuristic* m_heuristic;
	MUTEX* m_mutex;
};

#endif /* AIPLAYER_H_ */
