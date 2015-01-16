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

#ifndef EN_CAMERA_SCRIPT
#define EN_CAMERA_SCRIPT

#include "std.h"

class enCameraScript : public enScript
{
public:
	CLASS_VARS();

	enCameraScript();
	enCameraScript(const enString &);

	void Initialize();
	void Step();
private:
	float speed;
	enVector3 temp;

	enCamera *camera;
	const enInputListener *listener;
};

CLASS_FUNCTIONS(enCameraScript, enScript)

enCameraScript::enCameraScript() : speed(0.05f)
{

}

enCameraScript::enCameraScript(const enString &name) : enScript(name)
{
	enCameraScript();
}

void enCameraScript::Initialize()
{
	camera = (enCamera*) owner;
	listener = game->Input();

	temp.Zero();
}

void enCameraScript::Step()
{
	
	enMouseInput val = listener->MouseState();

	// It means we have the first press
	if (val.leftPressed)
		temp = camera->Transform().rotation.axis;

	if (val.leftDragging)
	{		
		camera->Transform().rotation.axis.Set(			
			enClamp((temp.y + val.deltaLeftY), -89.9f, 89.9f), // Rotation round x
			enFmodf((temp.x - val.deltaLeftX), 360.0f), // Rotation around y
			0);
	}
	
	if (listener->InputPressed(EN_MOUSE_SCROLL_UP)) 
		speed += 0.1f;
	else if (listener->InputPressed(EN_MOUSE_SCROLL_DOWN))
		if (speed > 0.2f) speed -= 0.1f;
	
	enCamera_s directions = camera->GetDirections();
	if (listener->InputPressed(EN_KEY_W))
		camera->Transform().position += directions.direction * speed;
	if (listener->InputPressed(EN_KEY_S))
		camera->Transform().position -= directions.direction * speed;
	if (listener->InputPressed(EN_KEY_D))
		camera->Transform().position += directions.right * speed;
	if (listener->InputPressed(EN_KEY_A))
		camera->Transform().position -= directions.right * speed;
	if (listener->InputPressed(EN_KEY_E))
		camera->Transform().position += directions.up * speed;
	if (listener->InputPressed(EN_KEY_Q))
		camera->Transform().position -= directions.up * speed;
}

#endif