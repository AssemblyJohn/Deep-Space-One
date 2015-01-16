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

#ifndef EN_PROFILER_H
#define EN_PROFILER_H

#include <assert.h>
#include "types.h"

void dprintf(const char *fmt, ...);
void eprintf(const char *fmt, ...);

// With tag
void tdprintf(const char *tag, const char *fmt, ...);
void teprintf(const char *tag, const char *fmt, ...);

#ifdef EN_DEBUG
	#define DLOG dprintf
	#define ELOG eprintf

	#define TDLOG tdprintf
	#define TELOG teprintf
	
	#define EN_ASSERT(x) assert(x)
#else
	#define DLOG(x, ...)
	#define ELOG(x, ...)

	#define TDLOG(t, x, ...)
	#define TELOG(t, x, ...)

	#define EN_ASSERT(x)
#endif

class enClass;
class enThread;

/**
 *Class for various runtime data. Thread count, allocated objects, memory usage etc...
 */
class Profiler
{
public:
	static size_t MemoryTextureUsed();
	static size_t MemoryRuntimeClassesUsed();
};

#endif