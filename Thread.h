/*************************************************
//Basic pthread class library...by Fallenhobit
//07/12/03.....more to be added later as the need
//deems it necessary.............................
*************************************************/
#ifndef _thread_header
#define _thread_header
#include <pthread.h>

#define		TRUE		1
#define		FALSE		0

//under unix related threads must share a common function...
static void* ThreadFunction(void*);
class THREAD
{
	friend void* ThreadFunction(void*);
public:
	THREAD(void);
	virtual	~THREAD(void);
	int start(void* = NULL);
	void detach(void);
	void* wait(void);
	void stop(void);
	void reset(void);
	unsigned int getthreadid(void);
	static unsigned int getcurrentthreadid(void);
	static void sleep(int);
protected:
	virtual void* Run(void*);
private:
	pthread_t ThreadHandle;
	unsigned int ThreadId;
	int Started;
	int Detached;
	void* Param;
};

class MUTEX
{
public:
	MUTEX(void);
	virtual ~MUTEX(void);
	virtual void acquire(void);
	virtual int acquired(void);
	virtual void release(void);
private:
	pthread_mutex_t Mutex;
};

class EVENT
{
public:
	EVENT(int = TRUE);
	~EVENT(void);
	void signal(void);
	void wait(void);
	void reset(void);
	int test(void);
private:
	pthread_cond_t Event;
	pthread_mutex_t Mutex;
	int Automatic;
	int Active;
};
#endif
