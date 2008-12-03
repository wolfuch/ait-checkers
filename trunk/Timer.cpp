/*
 * Timer.cpp
 *
 *  Created on: 2008-12-03
 *      Author: maciej
 */

#include <iostream>
#include "Timer.h"
#include <sys/time.h>

Timer::Timer() {
	// TODO Auto-generated constructor stub

}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void* Timer::Run(void* param) {
	sleep(180*1000 -2);   // wait 3min - 2sec for safety
	std::cout<<"-------- 3min! ------------"<<std::endl;
}
