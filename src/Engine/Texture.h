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

#ifndef EN_TEXTURE_H
#define EN_TEXTURE_H

#include "types.h"
#include "Class.h"
#include "Memory.h"

struct SDL_Surface;

class enTexture
{
public:
	enTexture() {}
	enTexture(SDL_Surface *);

	size_t Width();
	size_t Height();

	size_t MemoryUsed() const;

	// Pixel pointer
	void *ToPtr();

	// Loads a texture from the given path
	static enTexture *LoadTexture(const char *);
	// Deallocs a previously allocated texture
	static void Dealloc(enTexture *);

	friend class Profiler;
private:
	SDL_Surface *surf;

	// Only used internally
	EN_MEMORY_DEF()

	// Memory data. Textures can take a lot of memory so we must be carefull with them.
	// Unfortunately we will use SDL for loading and holding the allocated data.
	static size_t memused;
	static size_t instances;
};

#endif