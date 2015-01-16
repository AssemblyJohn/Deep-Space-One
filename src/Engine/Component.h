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

#ifndef EN_COMPONENT
#define EN_COMPONENT

#include "Class.h"
#include "String.h"

class enGame;
class enEntity;

// TODO: add some default variables, like 'camera', 'owner', 'transform', 'physics'
class enComponent : public enClass
{
public:
	CLASS_VARS()

	enComponent();
	enComponent(const enString &);

	virtual void Initialize() {};
	virtual void Step() {};

	void SetEntity(enEntity *);
	const enEntity *GetEntity() const;

	void SetGame(enGame *);
	const enGame *GetGame() const;

	const bool IsActive() const;
	void SetActive(bool);

	void SetName(enString &);
	const enString &GetName() const;
protected:
	enGame *game;
	enEntity *owner;
private:
	enString name;
	bool active;	
};

#endif