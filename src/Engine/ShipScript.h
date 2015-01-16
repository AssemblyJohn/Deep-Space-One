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

#ifndef EN_SHIP_SCRIPT
#define EN_SHIP_SCRIPT

#include "std.h"

class enShipScript : public enScript
{
public:
	CLASS_VARS();

	void Initialize();
	void Step();
private:
	enCamera *camera;
	enPhysics *ship;	
	const enInputListener *listener;	
};

CLASS_FUNCTIONS(enShipScript, enScript)

void enShipScript::Initialize()
{
	enList<enComponent*> physics = owner->GetComponentsOfType(enPhysics::Type);

	EN_ASSERT(physics.size() == 1);

	ship = (enPhysics *)physics[0];
	
	listener = game->Input();

	camera = (enCamera *) game->EntityWithTag("camera")[0];
}

#include "Math.h"

extern enRenderer *renderer;

void enShipScript::Step()
{
	// Lock onto the ship.
	static float distance = 4;	

	static enVector3 force;

	bool apply = false;

	enMouseInput val = listener->MouseState();
	
	static enVector3 temp(0.0f);
	enVector3 def(0, 0, -1);
	
	if (val.leftPressed)
	{
		temp.y = camera->Transform().rotation.axis.x;
		temp.x = camera->Transform().rotation.axis.y;
	}

	static float tempy = 0, tempx = 0;

	if (val.leftDragging)
	{
		tempx = enClamp((temp.y + val.deltaLeftY), -89.9f, 89.9f); // Rotation round x				
		tempy = enFmodf((temp.x - val.deltaLeftX), 360.0f); // Rotation around y
	}
	
	enMat3x3 rot = enMath::Rotation(tempy, Y) * enMath::Rotation(tempx, X);

	def = rot * def;
	def *= distance;

	camera->Transform().rotation.axis.y = tempy;
	camera->Transform().rotation.axis.x = tempx;
	camera->Transform().position = def + ship->GetEntity()->Transform().position;

	// Ship rotation. Were changing only if we are not dragging with both mouse buttons
	if ((val.leftDragging && val.rightDragging) == false)
	{
		ship->SetAngularVelocity(enVector3(0.0f));
		ship->SetRotation(-camera->Yaw()- 180, camera->Pitch(), 0.0f);
	}

	if (listener->InputPressed(EN_KEY_W))
	{
		force = camera->GetDirections().direction;
		apply = true;
	}
		
	if (listener->InputPressed(EN_KEY_S))
	{
		force = -camera->GetDirections().direction;
		apply = true;
	}		

	if (apply)
	{
		ship->ApplyCentralForce(force);
	}

	if (listener->InputPressed(EN_MOUSE_SCROLL_DOWN))
		distance += 0.2f;
	else if (listener->InputPressed(EN_MOUSE_SCROLL_UP))
		if (distance > 0.5f) distance -= 0.2f;
}

#endif