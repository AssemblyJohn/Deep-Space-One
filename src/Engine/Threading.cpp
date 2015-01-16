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

#include "Threading.h"

// TODO: port for linux too
#ifdef WIN32
	#include <Windows.h>
	#include <process.h>
#else if LINUX
	#include <pthread.h>
#endif

#include "Memory.h"

/**
 * Begin enSimpleMutex
 */

enSimpleMutex::enSimpleMutex(const char *name)
{
	handle = CreateMutexA(NULL, NULL, name);
}

void enSimpleMutex::Unlock()
{
	ReleaseMutex(handle);	
}

void enSimpleMutex::Lock()
{
	WaitForSingleObject(handle, INFINITE);
}

/**
 * End enSimpleMutex
 */


/**
 * Begin enThread
 */

// 64 kb should do...
size_t enThread::STACK_SIZE = 1024 * 64;

enThread::enThread() : stopped(false), started(false) { }
enThread::~enThread() { }

DWORD WINAPI callback(void *arg)
{
	enThread *thrd = (enThread *)arg;
	thrd->Callback();

	return 0;
}

void enThread::Start()
{
	started = true;

	CreateThread(NULL, enThread::STACK_SIZE, callback, this, NULL, NULL);
}

void enThread::Stop()
{
	stopped = true;
}

bool enThread::Stopped() 
{
	return stopped;
}

bool enThread::Started()
{
	return started;
}

/**
 * End enThread
 */