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

#include "Entity.h"

#include "String.h"
#include "Memory.h"
#include "Script.h"

CLASS_FUNCTIONS(enEntity, enClass)

enEntity::enEntity() 
{
	InnerInit();
}

enEntity::enEntity(const enString &tag)
{
	InnerInit();
	this->tag = tag;
}

enEntity::~enEntity()
{
	for (size_t i = 0; i < components.size(); i++)
		delete components[i];

	components.clear();
}

void enEntity::InnerInit()
{
	enMemory::Memset(&transform, 0, sizeof(enTransform));

	// Default scale
	transform.scale.Set(1, 1, 1);

	active = true;
	visible = true;

	model = NULL;
}

const enTransform &enEntity::Transform() const
{
	return transform;
}

enTransform &enEntity::Transform()
{
	return transform;
}

void enEntity::SetModel(enModel *model)
{
	this->model = model;
}

const enModel *enEntity::GetModel() const
{
	return model;
}

const bool enEntity::IsVisible() const
{
	return visible;
}

void enEntity::SetVisible(bool visible)
{
	this->visible = visible;
}

const bool enEntity::IsActive() const
{
	return active;
}

void enEntity::SetActive(bool active)
{
	this->active = active;
}

const enString &enEntity::GetTag() const
{
	return tag;
}

void enEntity::SetTag(enString &tag)
{
	this->tag = tag;
}

void enEntity::AddComponent(enComponent *component)
{
	components.add(component);
}

enList<enComponent *> enEntity::GetComponentsOfType(enType &type)
{
	enList<enComponent *> cmp;

	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i]->InstanceOf(type))
			cmp.add(components[i]);
	}

	return cmp;
}

// Returns the component with the matched name
enComponent *enEntity::GetComponentWithName(const enString &name)
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i]->GetName() == name)
			return components[i];
	}

	return NULL;
}

const enList<enComponent *> enEntity::GetComponents() const
{
	return components;
}

void enEntity::Step()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i]->IsActive())
			components[i]->Step();
	}		
}

void enEntity::Initialize()
{
	for (size_t i = 0; i < components.size(); i++)
		components[i]->Initialize();
}