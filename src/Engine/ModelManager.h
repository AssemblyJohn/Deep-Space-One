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

#ifndef EN_MODEL_MANAGER
#define EN_MODEL_MANAGER

#include "types.h"
#include "List.h"
#include "String.h"
#include "Importer.h"
#include "ReferenceCounting.h"

class enModel;
class enDriverOgl;

class enModelManager : public enRefObject
{
public:
	enModelManager();
	~enModelManager();

	// Adds a model to the managed models list.
	void LoadModel(enModel *);
	// Deallocats a model. Will search the model in the list based on it's name.
	void UnloadModel(enModel *);
	// Retrieve an already loaded model or NULL if it is not loaded.
	enModel *GetModel(const enString &name);
private:
	enList<enModel *> models;
};

#endif