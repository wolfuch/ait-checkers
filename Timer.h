/*
 * Timer.h
 *
 *  Created on: 2008-12-03
 *      Author: maciej
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "Thread.h"

class Timer: public THREAD {
public:
	Timer(MUTEX* mutex);
	virtual ~Timer();
	void* Run(void *prm);
private:
	MUTEX* mutex;
};

#endif /* TIMER_H_ */
