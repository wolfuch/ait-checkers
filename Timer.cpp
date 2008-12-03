/*
 * Timer.cpp
 *
 *  Created on: 2008-12-03
 *      Author: maciej
 */

#include <iostream>
#include "Timer.h"
#include <sys/time.h>

Timer::Timer(MUTEX* mutex) {
	this->mutex = mutex;
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void* Timer::Run(void* param) {
	int i;

	mutex->acquire();

	while(1) {
		mutex->acquire();		// mutex down, wait for signal to count time
		for(i=1; i<=17; ++i) {	// wait for 2:50
			sleep(10*1000);
			std::cout<<"time: "<<i*10<<std::endl;
		}
		sleep(8*1000);			// wait for 8 sec, 2 less for safety
		std::cout<<"-------- 3min! ------------"<<std::endl;
	}
}
