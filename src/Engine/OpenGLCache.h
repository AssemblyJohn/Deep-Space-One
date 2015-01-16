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

#ifndef EN_OPENGL_CACHE_H
#define EN_OPENGL_CACHE_H

#include "RenderingCore.h"

#include "ReferenceCounting.h"

/**
 * Global cache that contains all OpenGL initialized or allocated data
 */
class enOpenGLCache
{
public:
	// Initialize what we need
	void Intialize();
	// Clear all OpenGL allocated data
	void ShutDown();

	static enOpenGLCache &Get();
private:
	enOpenGLCache(enOpenGLCache &other);
	void operator=(enOpenGLCache &other);

	enList<enRefPtr<enShaderResource>> renderResources;

};

// Vertex buffer/ uniform buffer globals

// Global pool that holds all the vertex buffers and uniform buffers
// With check if that buffer is already locked or unlocked
// The pool holds an array of index buffers
// Lock that maps buffer to main memory
// Unlock that unmaps buffer from main memory

#endif