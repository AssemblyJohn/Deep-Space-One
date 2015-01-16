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

#include "Allocator.h"

#include <stdlib.h>
#include <vector>
#include <algorithm>

#include "types.h"
#include "Profiler.h"

const size_t enAllocator::PAGE_SIZE = 1024 * 1024 * 16;

enAllocator::enAllocator()
{
	ptrData = malloc(enAllocator::PAGE_SIZE);

	// Push in the free blocks the first empty one
	Block block = { ptrData, (void *)((size_t)ptrData + enAllocator::PAGE_SIZE) };
	freeBlocks.add(block);
}

enAllocator::~enAllocator()
{
	free(ptrData);
}

void *enAllocator::Alloc(size_t size)
{
	void *ptr = InnerAlloc(size);

	if (ptr)
	{
		return ptr;
	}

	// If we didn't found any empty space try to defragment
	Defragment();

	// Try to alloc again
	ptr = InnerAlloc(size);

	return ptr;
}

void enAllocator::Dealloc(void *ptr)
{
	for (size_t i = 0, max = allocBlocks.size(); i < max; i++)
	{
		if (allocBlocks[i].pBegin == ptr)
		{
			Block block = allocBlocks[i];

			// Remove the block from the allocated blocks
			allocBlocks.erase(i);
			// Move it to the free blocks
			freeBlocks.add(block);

			break;
		}
	}
}

void *enAllocator::InnerAlloc(size_t size)
{
	size_t blockSize;

	for (size_t i = 0, max = freeBlocks.size(); i < max; i++)
	{
		blockSize = BlockSize(freeBlocks[i]);

		if (blockSize > size)
		{
			// We found a good block, make the operations
			Block &block = freeBlocks[i];
			Block newBlock;

			newBlock.pBegin = block.pBegin;
			block.pBegin = (void *)((size_t)block.pBegin + size);
			newBlock.pEnd = block.pBegin;

			// Add it to the allocated list
			allocBlocks.add(newBlock);

			return newBlock.pBegin;
		}
		else if (blockSize == size)
		{
			Block block = freeBlocks[i];

			// Get a pointer to the block data
			void *ptr = block.pBegin;

			// Erase the block
			freeBlocks.erase(i);
			// Add it to the allocated blocks
			allocBlocks.add(block);

			// Return the cached pointer to data
			return ptr;
		}
	}

	return NULL;
}

bool cmp(Block &data1, Block &data2)
{
	return (data1.pBegin < data2.pBegin);
}

void enAllocator::Defragment(bool sort)
{
	if (freeBlocks.size() <= 1)
		return;

	if (sort)
		freeBlocks.sort(cmp);

reiterate:
	// (size - 1) since we go from the first one to the one before the last. 
	for (size_t i = 0, max = (freeBlocks.size() - 1); i < max; i++)
	{
		// 2 by 2
		Block first = freeBlocks[i];
		Block after = freeBlocks[i + 1];

		// Found a merge
		if (first.pEnd == after.pBegin)
		{
			// Erase the two blocks
			freeBlocks.erase(i);
			freeBlocks.erase(i);

			// Create a new block from the merged blocks
			Block newBlock = { first.pBegin, after.pEnd };
			freeBlocks.insert(i, newBlock);

			// We should reiterate the process
			goto reiterate;
		}
	}
}

INLINE size_t enAllocator::BlockSize(Block &block)
{
	return ((size_t)block.pEnd) - ((size_t)block.pBegin);
}