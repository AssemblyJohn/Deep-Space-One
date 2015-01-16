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

#ifndef EN_MEMORY_H
#define EN_MEMORY_H

#include <memory.h>
#include "types.h"
#include "Profiler.h"

#define EN_MEMORY_DEF()										\
	void *operator new(size_t size) {						\
		void *ptr = enMemory::Alloc(size);					\
		return ptr;											\
	}														\
	void operator delete(void *ptr, size_t size) {			\
		if (ptr) enMemory::Free(ptr, size);					\
	}


void InitializeMemory();

/**
 * Class representing memory operations for our engine
 */
class enMemory
{
public:
	static void Initialize();

	static INLINE void Memcpy(void *dst, const void *src, size_t size)
	{
		EN_ASSERT(initialized);
		memcpy(dst, src, size);
	}

	static INLINE void Memset(void *dst, int val, size_t size)
	{
		EN_ASSERT(initialized);
		memset(dst, val, size);
	}

	// C runtime allocation routines
	static void *CAlloc(size_t size);
	static void CFree(void *ptr, size_t size);

	// Our allocation routines
	static void *Alloc(size_t size);
	static void Free(void *ptr, size_t size);

	// How much native memory we have allocated
	static size_t MemoryNativeAlloced();
	// How much engine memory we have allocated
	static size_t MemoryEngineAlloced();
private:
	static void *EnAlloc(size_t size);
	static void EnFree(void *ptr, size_t size);

	static bool initialized;
	static size_t memoryNative;
	static size_t memoryEngine;
};

#endif