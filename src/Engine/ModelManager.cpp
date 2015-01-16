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

#include "ModelManager.h"

#include "String.h"
#include "Timing.h"
#include "Memory.h"

#include "Threading.h"

#include "Model.h"
#include "DriverOgl.h"

enModelManager::enModelManager()
{
}

enModelManager::~enModelManager()
{
	// Delete any models that were previously allocated
	for (size_t i = 0; i < models.size(); i++)
		delete models[i];

	models.clear();
}

void enModelManager::LoadModel(enModel *model)
{	
	models.add(model);
}

void enModelManager::UnloadModel(enModel *model)
{
	for (size_t i = 0; i < models.size(); i++)
	{
		if (models[i]->GetName() == model->GetName())
		{
			// Remove from the list and deallocate
			models.erase(i);
			delete model;

			break;
		}
	}
}

enModel *enModelManager::GetModel(const enString &name)
{
	for (size_t i = 0; i < models.size(); i++)
	{
		if (models[i]->GetName() == name)
			return models[i];
	}

	return NULL;
}