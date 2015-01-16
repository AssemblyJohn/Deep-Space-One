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

#ifndef EN_MODEL_H
#define EN_MODEL_H

#include "Memory.h"
#include "Class.h"
#include "String.h"

class enMesh;
template<class T> class enList;

/**
 * Holds one or more meshes.
 */
class enModel
{
public:
	// Model intialized with a model identifier to be able to search for it
	enModel(const enString &);
	~enModel();

	const enString &GetName();
	
	// After we added a mesh to this model it is managed by it. All data is cleared in the destructor. Do not manually touch it!
	void AddMesh(enMesh *);
	// Get a mesh for rendering
	enMesh *GetMesh(size_t) const;
	size_t MeshCount() const;

	EN_MEMORY_DEF()
private:
	enString name;
	enList<enMesh *> *meshes;
};

#endif