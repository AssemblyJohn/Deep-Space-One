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

#include "Component.h"

CLASS_FUNCTIONS(enComponent, enClass)

enComponent::enComponent()
{

}

enComponent::enComponent(const enString &name)
{
	this->name = name;
}

void enComponent::SetGame(enGame *game)
{
	this->game = game;
}

const enGame *enComponent::GetGame() const
{
	return game;
}

void enComponent::SetEntity(enEntity *owner)
{
	this->owner = owner;
}
const enEntity *enComponent::GetEntity() const
{
	return owner;
}

const bool enComponent::IsActive() const
{
	return active;
}

void enComponent::SetActive(bool active)
{
	this->active = active;
}

void enComponent::SetName(enString &name)
{
	this->name = name;
}

const enString &enComponent::GetName() const
{
	return name;
}