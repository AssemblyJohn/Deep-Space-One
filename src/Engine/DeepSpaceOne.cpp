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

#include <Windows.h>

#include "std.h"

#include "SceneLoader.h"

#include "SDL.h"

#include "Timing.h"

#include "ReferenceCounting.h"

#include "RenderingThread.h"

// Global video data like context and window

int main(int argc, char* argv[])
{	
	// TODO: global them
	SDL_Window *window;
	SDL_GLContext context;
	
	// Initialize memory
	InitializeMemory();
	// Initialize the object graph
	enClass::Initialize();
	// Initialize config data
	enConfig::Initialize();
	// Initialize video mode
	InitializeVideo(&window, &context);
	// Initialize OpenGL
	InitializeGL();

	// InitializeRendering();

	// TODO: a lot of work here
	class enThreadd : public enThread
	{
	public:
		SDL_Window *window;
		SDL_GLContext context;

		void Callback()
		{
			/*
			printf("Inited rendering thread!\n");

			SDL_GL_MakeCurrent(window, context);

			glClearColor(0.2, 0.4, 0.6, 1);

			while (1) {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				Sleep(500);

				SDL_GL_SwapWindow(window);
			}
			*/
		}
	};

	// Alloc and initialize game
	enGame *game = new enGame();
	game->Initialize();
	
	// Load all the data
	LoadAll(game);

	enDScalar time;

	// Start the game loop
	while (1) {
		// REmove any rendering from this thread, post it all to the rendering thread
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		game->Step();
		SDL_GL_SwapWindow(window);

#ifdef EN_DEBUG
		static unsigned int ticks = 0;
		if (SDL_GetTicks() - ticks > 5000) 
		{
			ticks = SDL_GetTicks();
			printf("=====\nTime last step: %f ms\nTime process work: %f ms\nTime world step: %f ms\nTime render step: %f ms\nEntities rendered: %d\n=====\n",
				game->TimeStep() * 1000.0f, game->TimeProcessWork() * 1000.0f, game->TimeWorldStep() * 1000.0f, game->TimeRenderStep() * 1000.0f, game->ActuallyRendered());
		}
#endif

		time = game->TimeStep() * 1000.0f;
		if (time < 16.0f) 
			Sleep((DWORD)(16.0f - time));
	}

	delete game;	

	return 0;
}