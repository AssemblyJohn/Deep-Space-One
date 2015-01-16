/**
* Copyright (c) 2015 Lazu Ioan-Bogdan
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, without any restrictions.
*/

#ifndef EN_THREAD_H
#define EN_THREAD_H

#include "types.h"
#include "Memory.h"

// TODO:

// Simple runnable object
class enRunnable
{
	// Run callback
	virtual void Run() = 0;

	// Attempt to stop the runnable
	void Stop();
	// If the runnable is stopped
	bool Stopped();
};

class enSimpleMutex
{
public:
	enSimpleMutex(const char * = NULL);

	void Lock();
	void Unlock();
private:
	void *handle;
};

class enGame;

// TODO: specialize for game callback
class enThread
{
public:
	enThread();
	~enThread();

	EN_MEMORY_DEF()

	// Callback operation executed when the thread is started. Do not directly use.
	virtual void Callback() {};	
	// Callback executed when it's added to the game operation queue. Do not directly use.
	virtual void GameCallback(enGame *) {};

	void Start();
	void Stop();

	// If we are started
	bool Started();
	// If we are stopped
	bool Stopped();
protected:
	volatile bool stopped;
	volatile bool started;
	volatile bool running;

	static size_t STACK_SIZE;
};

#endif