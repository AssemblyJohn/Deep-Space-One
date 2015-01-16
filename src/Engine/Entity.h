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

#ifndef EN_ENTITY_H
#define EN_ENTITY_H

#include "Class.h"

#include "String.h"
#include "Vector.h"
#include "List.h"

class enScript;
class enModel;
class enComponent;

// TODO: move this in separate classes that extend component
typedef struct 
{
	float angle;
	enVector3 axis;
} enRotation;

typedef struct 
{
	enVector3 position;
	enRotation rotation;
	enVector3 scale;
} enTransform;

/**
 * Base type for all game objects
 */
class enEntity : public enClass
{
public:
	CLASS_VARS();

	enEntity();
	enEntity(const enString &tag);
	virtual ~enEntity();

	// Adds a component to the entity. After it is added it is owned by this entity. Will be deleted in the destructor
	void AddComponent(enComponent *);
	// Returns a list of the components that match the specified type.
	enList<enComponent *> GetComponentsOfType(enType &);
	// Returns the component with the matched name
	enComponent *GetComponentWithName(const enString &);
	// Returns the list of components.
	const enList<enComponent *> GetComponents() const;

	// The entity does not own this model after it has been set since the model can be shared with another entity
	void SetModel(enModel *);
	const enModel *GetModel() const;

	void SetTag(enString &);
	const enString &GetTag() const;

	// If this class is overriden do not forget to call the superclasses version
	virtual void Initialize();
	virtual void Step();

	// If we are visible (a.k.a not an invizible game controller for example)
	const bool IsVisible() const;
	void SetVisible(bool);

	// If the object should have it's Step function called
	const bool IsActive() const;
	void SetActive(bool);

	const enTransform &Transform() const;
	enTransform &Transform();
protected:
	enTransform transform;

private:	
	void InnerInit();

	enList<enComponent *> components;
	enModel *model;
	enString tag;

	bool visible;
	bool active;
};

#endif