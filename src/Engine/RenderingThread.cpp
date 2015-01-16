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

#include "RenderingThread.h"

#include "SDL.h"
#include "Video.h"
#include "glinclude.h"

void InitializeRendering()
{
	
}

void enRenderingThread::Run()
{
	SDL_Window *window;

	//InitializeVideo(&window);
	InitializeGL();

	while (running)
	{
		// Do the posted work

		// Do the rendering
	}
}
