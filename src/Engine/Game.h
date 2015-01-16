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

#ifndef EN_GAME_H
#define EN_GAME_H

#include "List.h"
#include "Timing.h"
#include "ReferenceCounting.h"

class enString;
class enThread;
class enEntity;
class enRenderer;
class enScript;
class enInputListener;
class enPhysicsEngine;
class enModelManager;
class enDriverOgl;
class enSimpleMutex;
class enShaderUtils;
class enCamera;

class enGame
{
public:
	enGame();
	~enGame();

	void Initialize();
	void Step();

	// How much it took us to take the last step
	enDScalar TimeStep();
	// How much it took us to process posted work
	enDScalar TimeProcessWork();
	// How much it took us to step the physics engine, entities and process input
	enDScalar TimeWorldStep();
	// How much it took us to render the scene
	enDScalar TimeRenderStep();
	// How many entities we rendered last step
	size_t ActuallyRendered();

	/**
	 * Adds an entity to the games. It's components 'game' and 'owner' fields will
	 * be initialized. The 'name' field will NOT be initialized.
	 * Call this only on the main thread.
	 */
	void AddEntity(enEntity *);
	// Set the scene's camera
	void SetCamera(enCamera *);

	// Post work on the main thread. Safe to call from any thread. After the work is done the threads are deleted.
	void PostWork(enThread *);	

	enList<enEntity *> EntityWithTag(const enString &);

	const enInputListener *Input() const;
	enModelManager *Manager() const;
	enPhysicsEngine *Engine() const;

	enRefPtr<enDriverOgl> driver;
	enRefPtr<enShaderUtils> shaders;


	enDriverOgl *Driver() const;
	enShaderUtils *Shaders() const;

	void ProcessWork();
	void StepWorld();
	void StepRender();
private:
	
	enCamera *camera;
	
	//enRefPtr<enRenderer> renderer;
	enRefPtr<enInputListener> listener;
	enRefPtr<enPhysicsEngine> physics;
	enRefPtr<enModelManager> manager;

	enSimpleMutex *mutex;

	// Work list
	enList<enThread *> work;

	// Game objects
	enList<enEntity *> objects;

	enTimer timer;
	enDScalar timeProcessWork;
	enDScalar timeWorldStep;
	enDScalar timeRenderStep;
	size_t rendered;
};

#endif