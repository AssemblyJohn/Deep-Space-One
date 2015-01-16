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

#include "Memory.h"

#include "Allocator.h"
#include "Threading.h"

// Global allocator
static enAllocator g_Allocator;
// Memory mutex
static enSimpleMutex g_MemoryMutex;

static const size_t LIMIT = 1024 * 32;

void InitializeMemory()
{
	enMemory::Initialize();
}

bool enMemory::initialized = false;
size_t enMemory::memoryNative = 0;
size_t enMemory::memoryEngine = 0;

void enMemory::Initialize()
{
	initialized = true;
}

// Modify our allocator with a small allocator too so we can alloc efficiently objects < 256 bytes

// TODO: Change to use only our memory allocator
void *enMemory::Alloc(size_t size)
{
	EN_ASSERT(initialized);

	void *ptr;

	if (size < LIMIT)
		ptr = malloc(size);
	else
		ptr = EnAlloc(size);

#ifdef EN_DEBUG
	if (!ptr)
	{
		ELOG("Out of memory!\n");
		EN_ASSERT(ptr != NULL);
	}
#endif
	
	return ptr;
}

// TODO: Change to use only our memory allocator
void enMemory::Free(void *ptr, size_t size)
{
	EN_ASSERT(initialized);

	if (size < LIMIT)
		free(ptr);
	else
		EnFree(ptr, size);
}

void *enMemory::EnAlloc(size_t size)
{
	g_MemoryMutex.Lock();	

	void *ptr = g_Allocator.Alloc(size);
	memoryEngine += size;

	g_MemoryMutex.Unlock();

	return ptr;
}

void enMemory::EnFree(void *ptr, size_t size)
{
	g_MemoryMutex.Lock();

	g_Allocator.Dealloc(ptr);
	memoryEngine -= size;

	g_MemoryMutex.Unlock();
}

void *enMemory::CAlloc(size_t size)
{
	EN_ASSERT(initialized);

	g_MemoryMutex.Lock();
	memoryNative += size;
	g_MemoryMutex.Unlock();

	return malloc(size);
}

void enMemory::CFree(void *ptr, size_t size)
{
	EN_ASSERT(initialized);

	g_MemoryMutex.Lock();
	memoryNative -= size;
	g_MemoryMutex.Unlock();

	free(ptr);
}

size_t enMemory::MemoryNativeAlloced()
{
	return memoryNative;
}

size_t enMemory::MemoryEngineAlloced()
{
	return memoryEngine;
}