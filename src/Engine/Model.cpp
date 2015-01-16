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

#include "Model.h"

#include "Memory.h"

#include "List.h"
#include "Mesh.h"

// Model intialized with a model identifier to be able to search for it
enModel::enModel(const enString &name)
{
	this->name = name;

	// Default allocator
	meshes = new enList<enMesh*>();
}

enModel::~enModel()
{
	// Clear all mesh data
	for (size_t i = 0; i < meshes->size(); i++)
	{
		// Delete the meshes
		delete (*meshes)[i];
	}

	// Default allocator
	delete meshes;
}

const enString &enModel::GetName()
{
	return name;
}

void enModel::AddMesh(enMesh *v)
{
	meshes->add(v);
}

enMesh *enModel::GetMesh(size_t i) const
{
	return (*meshes)[i];
}

size_t enModel::MeshCount() const
{
	return meshes->size();
}