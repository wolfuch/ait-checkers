/*
 * Timer.h
 *
 *  Created on: 2008-12-03
 *      Author: maciej
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "Thread.h"
#include "AIPlayer.h"

class Timer: public THREAD {
public:
	Timer(MUTEX* mutex, AIPlayer* aIPlayer);
	virtual ~Timer();
	void* Run(void *prm);
private:
	MUTEX* mutex;
	AIPlayer* aIPlayer;
};

#endif /* TIMER_H_ */
