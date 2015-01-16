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

#ifndef EN_ALLOCATOR_H
#define EN_ALLOCATOR_H

#include "List.h"

// Memory block
struct Block {
	void *pBegin;
	void *pEnd;
};

/**
* Class for large allocations. Ideal for model data or textures. There is an 8 byte (16 on x64) overhead for each allocation.
*
* TODO: add pages for the future and small object allocator (obj < 256 kb)
*/
class enAllocator
{
public:
	enAllocator();
	~enAllocator();

	// Allocs a chunk of memory from the pool
	void *Alloc(size_t size);
	// Marks a chunk of memory from the pool as unused
	void Dealloc(void *ptr);
private:
	void *InnerAlloc(size_t size);
	// Merges contiguous blocks from the pool.
	void Defragment(bool = true);
	// Returns the size of a block
	size_t BlockSize(Block &block);

	// Data pointer. Replace with pages for the future so we can have more than this.
	void *ptrData;
	// List of blocks
	enList<Block> freeBlocks;
	enList<Block> allocBlocks;

	static const size_t PAGE_SIZE;
};

#endif