/**
* Copyright (c) 2014 Lazu Ioan-Bogdan
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, without any restrictions.
*/

#ifndef EN_CONFIG_H
#define EN_CONFIG_H

// TODO: modify to a key/value structure
class enConfig
{
public:
	static void Initialize();

	static int WindowWidth();
	static int WindowHeight();

	static bool Fullscreen();
	static bool DebugAABB();
	static bool DebugPhysics();
private:
	static bool initialized;

	static bool fullscreen;
	static bool debugAabb;
	static bool debugPhysics;

	static int windowWidth;
	static int windowHeight;
};

#endif