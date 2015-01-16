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

#include "Game.h"

#include "std.h"

#define TAG "GAME"

enRenderer *renderer;

enGame::enGame()
{
	renderer = new enRenderer();
	listener = new enInputListener();
	physics = new enPhysicsEngine();

	// TODO: See how we communicate between the game loop and rendering loop
	manager = new enModelManager();


	shaders = new enShaderUtils();
	driver = new enDriverOgl();

	mutex = new enSimpleMutex("GameMutex");

	work.clear();
	camera = NULL;
}

enGame::~enGame()
{

}

void enGame::Initialize()
{	
	// Initialize listener and physics
	listener->Initialize();
	physics->Initialize();

	// Don't initialize this on the main thread
	driver->Initalize();
	shaders->Initialize(this);

	for (size_t i = 0; i < objects.size(); i++)
		objects[i]->Initialize();
}

void enGame::Step()
{
	timer.Mark();
	ProcessWork();
	timeProcessWork = timer.Elapsed();

	timer.Mark();
	StepWorld();
	timeWorldStep = timer.Elapsed();

	timer.Mark();
	StepRender();
	timeRenderStep = timer.Elapsed();
}

void enGame::ProcessWork()
{
	// Process events posted to the main event loop
	if (work.isNotEmpty())
	{
		mutex->Lock();

		for (size_t i = 0; i < work.size(); i++)
		{
			// Call the game callback
			work[i]->GameCallback(this);
			delete work[i];
		}

		// After we're done clear the list
		work.clear();

		mutex->Unlock();
	}
}

void enGame::StepWorld()
{
	// Process input
	listener->ProcessEvents();
	
	// Step physics
	physics->Step();

	// Step entitys
	for (size_t i = 0; i < objects.size(); i++)
	{
		enEntity *entity = objects[i];

		if (entity->IsActive())
			entity->Step();
	}
}

void enGame::StepRender()
{	
	// Render entitys
	rendered = renderer->RenderEntities(objects, *camera);

	// Draw physics debug
	if (enConfig::DebugPhysics())
		renderer->RenderPhysics(*physics->World(), *camera);
}

void enGame::PostWork(enThread *thread)
{
	mutex->Lock();
	work.add(thread);
	mutex->Unlock();
}

void enGame::AddEntity(enEntity *entity)
{
	const enList<enComponent *> components = entity->GetComponents();
	for (size_t i = 0; i < components.size(); i++)
	{
		enComponent *cmp = components.get(i);

		cmp->SetGame(this);
		cmp->SetEntity(entity);
	}

	// Add it's model to the model manager
	if (entity->GetModel() != NULL)
		manager->LoadModel(const_cast<enModel*>(entity->GetModel()));

	// Initialize and add the entity to our list of objects
	entity->Initialize();
	objects.add(entity);
}

void enGame::SetCamera(enCamera *camera)
{
	if (this->camera == NULL)
	{
		this->camera = camera;
		AddEntity(camera);
	}
	else
		TDLOG(TAG, "Scene already contains camera!\n");
}

enList<enEntity *> enGame::EntityWithTag(const enString &tag)
{
	enList<enEntity *> entities;

	// For a few objects this linear search will do...
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetTag() == tag)
			entities.add(objects[i]);
	}

	return entities;
}

const enInputListener *enGame::Input() const
{
	return listener;
}

enModelManager *enGame::Manager() const
{
	return manager;
}

enDriverOgl *enGame::Driver() const
{
	return driver;
}

enShaderUtils *enGame::Shaders() const
{
	return shaders;
}

enPhysicsEngine *enGame::Engine() const
{
	return physics;
}

enDScalar enGame::TimeStep()
{
	return enDScalar(timeWorldStep + timeRenderStep + timeProcessWork);
}

enDScalar enGame::TimeProcessWork()
{
	return timeProcessWork;
}

enDScalar enGame::TimeWorldStep()
{
	return timeWorldStep;
}

enDScalar enGame::TimeRenderStep()
{
	return timeRenderStep;
}

size_t enGame::ActuallyRendered()
{
	return rendered;
}