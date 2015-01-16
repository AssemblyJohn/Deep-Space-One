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

#include "Class.h"

#include "Profiler.h"
#include "Memory.h"

#include "String.h"
#include "List.h"

#define TAG "EN_CLASS"

static enType *g_head = NULL;
static enList<enType *> *g_types;

/**
 * Begin enType
 */

void ScanDerived(enType *, enList<enType *> *);
void TreeInsert(enType *, enList<enType *> *);

bool enType::initialized = false;

enType::enType(const char *classname, const char *superclassname, enClass* (*newCallback)())
{	
	// Standard init
	this->newCallback = newCallback;
	this->classname = classname;
	this->superclassname = superclassname;
	derived = new enList<enType *>();
	// End standard init

	// Add to the global types
	if (!g_types)
		g_types = new enList<enType *>();

	g_types->add(this);
}

enType::~enType()
{
	delete derived;
}

void enType::Initialize()
{
	EN_ASSERT(initialized == false);

	enList<enType *> types = *g_types;

	// Scan for the base class
	for (size_t i = 0; i < types.size(); i++)
	{
		if ((enStrCmp(types[i]->classname, "enClass") == 0)) 
		{
			// We got our list's head
			g_head = types[i];
			types.erase(i);

			break;
		}		
	}

#ifdef EN_DEBUG
	assert(g_head);
#endif

	// If we are stuck in here it means that the hierarchy is broken somwhere
	while (types.size() > 0)
	{
		TreeInsert(g_head, &types);
	}

	initialized = true;
}

void TreeInsert(enType *base, enList<enType *> *derived)
{
	// Do operation
	ScanDerived(base, derived);

	for (size_t i = 0; i < base->derived->size(); i++)
	{
		TreeInsert(base->derived->get(i), derived);
	}
}

/**
 * Scans for the classes derrived from the provided base class. 
 * The received derived list it only a list of possibilites.
 */
void ScanDerived(enType *base, enList<enType *> *derived)
{
	for (int i = (derived->size() - 1); i >= 0; i--)
	{
		if (enStrCmp(base->classname, derived->get(i)->superclassname) == 0)
		{
			derived->get(i)->superclass = base;
			base->derived->add(derived->get(i));

			derived->erase(i);
		}
	}
}

/**
 * End enType
 */



/**
 * Begin enClass
 */

CLASS_FUNCTIONS(enClass, NULL)

enClass::~enClass() {}

int enClass::instances = 0;
int enClass::size = 0;
int enClass::memused = 0;
bool enClass::initialized = false;

void enClass::Initialize()
{
	EN_ASSERT(initialized == false);

	// Build the type graph
	enType::Initialize();

	// Any other initialization we need

	// We are initialized
	initialized = true;
}

void *enClass::operator new(size_t size) {	
	void *ptr = enMemory::Alloc(size);

	memused += size;
	instances++;

	return ptr;
}

void enClass::operator delete(void *ptr, size_t size) {
	if (ptr)
	{
		enMemory::Free(ptr, size);

		memused -= size;
		instances--;
	}
}

enType *enClass::GetClass(char const *clazz)
{
	EN_ASSERT(enClass::initialized);

	// Look for the class types
	size_t size = g_types->size();

	for (size_t i = 0; i < size; i++)
	{
		if (enStrCmp(g_types->get(i)->classname, clazz) == 0)
			return g_types->get(i);
	}

	return NULL;
}

enClass *enClass::NewObject(char const *clazz)
{
	EN_ASSERT(enClass::initialized);

	// Look for the class type and invoke it's new callback
	enType *type = GetClass(clazz);

	if (type != NULL)
		return type->newCallback();

	return NULL;
}

bool enClass::InstanceOf(enType &type)
{
	EN_ASSERT(enClass::initialized);

	enType *clz = GetType();

	while (clz)
	{
		if (enStrCmp(clz->classname, type.classname) == 0)
			return true;

		// Move up in the hierarchy
		clz = clz->superclass;
	}

	return false;
}

/**
 * End enClass
 */
