#include <pthread.h>
#include <sys/time.h>
#include "Thread.h"

//constructor
THREAD::THREAD(void)
{
	Started = FALSE;
	Detached = FALSE;
}

//destructor
THREAD::~THREAD(void)
{
	stop();//stop thread
}


int THREAD::start(void* param)
{
	if(!Started)
	{
		pthread_attr_t attributes; //Used to identify a thread attributes object.
		pthread_attr_init(&attributes);//Initialize a thread attributes object.
		if(Detached)
			pthread_attr_setdetachstate(&attributes,PTHREAD_CREATE_DETACHED);
		Param=param;
		ThreadId =0;
		if(pthread_create(&ThreadHandle,&attributes,ThreadFunction,this)==0)//create the thread...
			Started=TRUE;
		pthread_attr_destroy(&attributes);//cleanly destroy a thread attributes object
	}
	return Started;
}

static void* ThreadFunction(void* object)
{
	THREAD* thread=(THREAD*)object;
	return thread->Run(thread->Param);//invoke the class instance specific run object
}

void* THREAD::Run(void* param)//default function stub...each derived class should define this...
{
	return NULL;
}

void THREAD::detach(void)//detaches a thread
{
	if(Started && !Detached)
		pthread_detach(ThreadHandle);//yeah, it detaches the thread
	Detached=TRUE;
}

void* THREAD::wait(void)
{
	void* status=NULL;
	if(Started && !Detached)
	{
		pthread_join(ThreadHandle,&status);//Synchronize with the termination of a thread ..IE, opposite of fork
		Detached=TRUE;
	}
	return status;
}

void THREAD::stop(void)//halts a thread
{
	if(Started && !Detached)
	{
		pthread_cancel(ThreadHandle);//cancels a thread....IE halts it
		pthread_detach(ThreadHandle);//sets the threads detached state
		Detached = TRUE;
	}
}

unsigned int THREAD::getthreadid(void)
{
	return ThreadId;
}

unsigned int THREAD::getcurrentthreadid(void)
{
	return 0;
}

void THREAD::sleep(int delay)//Sleep is not implemented for Unix as it is in windows
{
	timeval timeout = {(delay/1000),((delay*1000)%1000000)};
	select(0,(fd_set*)NULL,(fd_set*)NULL,(fd_set*)NULL,&timeout);//using the select funtion usually used with BSD sockets
}

void THREAD::reset(void)//reset class status flags...
{
	if(Detached==TRUE)
	{
		Started=FALSE;
		Detached=FALSE;
	}
}

//Mutex class code..........
MUTEX::MUTEX(void)
{
	pthread_mutex_init(&Mutex,(pthread_mutexattr_t*)NULL);//null initiates a standard mutex with default attributes...
}

MUTEX::~MUTEX(void)
{
	pthread_mutex_destroy(&Mutex);
}

void MUTEX::acquire(void)
{
	pthread_mutex_lock(&Mutex);//Acquire the indicated mutex
}

int MUTEX::acquired(void)
{
	return(pthread_mutex_trylock(&Mutex)==0);//Attempt to acquire the indicated mutex
}

void MUTEX::release(void)
{
	pthread_mutex_unlock(&Mutex);//Release the previously acquired mutex
}

//event code
EVENT::EVENT(int automatic)
{
	pthread_cond_init(&Event,(pthread_condattr_t*)NULL);//initialize our condition variable
	pthread_mutex_init(&Mutex,(pthread_mutexattr_t*)NULL);//initialize our mutex object
	Automatic = automatic;//set whether we are manual or automatic
	Active=FALSE;//init active state
}

EVENT::~EVENT(void)
{
	pthread_cond_destroy(&Event);//release our condition and mutex resources
	pthread_mutex_destroy(&Mutex);
}

void EVENT::signal(void)
{
	pthread_mutex_lock(&Mutex);//enter critical section
	Active=TRUE;
	if(Automatic)
		pthread_cond_signal(&Event);//for a single thread
	else
		pthread_cond_broadcast(&Event);//for all waiting threads
	pthread_mutex_unlock(&Mutex);//exit critical section
}

void EVENT::wait(void)
{
	pthread_mutex_lock(&Mutex);
	while(!Active)
		pthread_cond_wait(&Event,&Mutex);//wait on a signal
	if(Automatic)
		Active=FALSE;//if automatic..then first released thread resets the state..
	pthread_mutex_unlock(&Mutex);
}

void EVENT::reset(void)
{
	pthread_mutex_lock(&Mutex);
	Active=FALSE;//set active state to false..used for manual events
	pthread_mutex_unlock(&Mutex);
}

int EVENT::test(void)
{
	pthread_mutex_lock(&Mutex);
	int active = Active;
	if(Active&&Automatic)
		Active=FALSE;
	pthread_mutex_unlock(&Mutex);
	return active;
}
