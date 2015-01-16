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

#ifndef EN_MESH_H
#define EN_MESH_H

#include "types.h"
#include "Class.h"
#include "List.h"
#include "Memory.h"

#include "AABB.h"
#include "Program.h"

#include "Vector.h"

#include "ShaderBase.h"

class enTexture;

// TODO: resizable list of shader resources

// Should be packed
struct enMeshVector_s
{
	enVector3 position;
	enVector3 normal;
	enVector2 texcoord;
};

// TODO: change to resource handles
struct enGeometryData_s
{
	// Some counts
	size_t vertexCount;
	size_t normalCount;
	size_t uvCount;
	//size_t textureCount;

	// Data allocated in opengl
	Uint32 handleVertex;
	Uint32 handleNormal;
	Uint32 handleUv;
	enList<Uint32> handleTextures;

	// Actual triangle count
	size_t triangleCount;
};

/**
 * A mesh is a 3d object or a part of a 3d object. A model can have multiple meshes.
 */
class enMesh 
{
public:
	// TODO: change it to a list of resources so we know for sure what to bind
	// Don't use list
	// Changed from the clumsy data struct we currently have
	enList<enShaderResource> resources;
	// Shader program
	enRefPtr<enShaderProgram> shader;

	enMesh();
	enMesh(const enGeometryData_s &, const enProgram_s &, const enAABB &);

	void SetGeometryData(const enGeometryData_s &);
	void SetProgram(const enProgram_s &);
	void SetAABB(const enAABB &);

	const enGeometryData_s &GetGeometryData() const;
	const enProgram_s &GetProgram() const;
	const enAABB &GetAABB() const;
	
	//EN_MEMORY_DEF()

	void *operator new(size_t size)
	{
		void *ptr = enMemory::Alloc(size);
		return ptr;
	}
	void operator delete(void *ptr, size_t size) 
	{
		if (ptr) enMemory::Free(ptr, size);
	}

	// Move somwhere else
	static const size_t VERTEX_COORDS;
	static const size_t NORMAL_COORDS;
	static const size_t UV_COORDS;
	static const size_t BYTE_PER_COORD;

	static const size_t VERTEX_STRIDE;
	static const size_t NORMAL_STRIDE;
	static const size_t UV_STRIDE;
private:
	enGeometryData_s data;
	enProgram_s program;
	enAABB aabb;
};

#endif