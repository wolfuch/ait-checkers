/*
 * Timer.cpp
 *
 *  Created on: 2008-12-03
 *      Author: maciej
 */

#include <iostream>
#include "Timer.h"
#include <sys/time.h>

Timer::Timer(MUTEX* mutex, AIPlayer* aIPlayer) {
	this->mutex = mutex;
	this->aIPlayer = aIPlayer;
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void* Timer::Run(void* param) {
	int i;

	mutex->acquire();

	while(1) {
		mutex->acquire();		// mutex down, wait for signal to count time
		for(i=1; i<=58; ++i) {	// wait for 58 seconds
			if (!aIPlayer->working)
				break;
			sleep(1000);
			//std::cout<<"time: "<<i<<std::endl;
		}
		if (aIPlayer->working) {	// if game is stopped during search tree
			std::cout<<"-------- 1min! ------------"<<std::endl;
			aIPlayer->timeoutOccurred();		// inform aiPlayer that time is finished
			aIPlayer->working = false;			// stop searching tree
		}


// test measuring time
//		for(i = 1; i<=3600; ++i) {
//			sleep(1000);
//			if (!aIPlayer->working) {
//				std::cout<<std::endl<<" sekundy: "<<i<<std::endl;
//				break;
//			}
//		}

	}
}
