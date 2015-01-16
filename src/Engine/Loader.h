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

#ifndef EN_LOADER_H
#define EN_LOADER_H

#include "std.h"

struct enLoadMesh_s
{
	enProgramType_e program;
	enString meshpath;
	enList<enString> texturepaths;
};

struct enLoadModel_s
{
	enString modelname;
	enList<enLoadMesh_s> meshes;
};

// Must be initialized on the OpenGL thread
struct enLoadedMesh_s
{
	enProgramType_e program;
	enImportedData_s imported;
	enList<enTexture *> textures;
};

struct enLoadedData_s
{
	// Entity tag
	enString tag;
	enString modelname;

	enList<enLoadedMesh_s> meshes;
};

class enLoader : public enThread
{
public:
	enLoader(enGame *game) { this->game = game; }

	enImporter importer;
	
	enGame *game;

	// Entityies to load after the binding is finished
	enList<enEntity *> toAdd;

	// Post here the entity loads with LoadEntity
	virtual void DoEntityLoads() = 0;
	/**
	 * Will take place on the run loop, after all the entities had their textures and buffers initialized and
	 * before adding them to the game.
	 *
	 * Do here any component rigging.
	 */
	virtual void DoEntityRigging() = 0;

	void LoadEntity(const enString &tag, enLoadModel_s &model)
	{
		enLoadedData_s data;
		
		// Set tag and modelname
		data.tag = tag;
		data.modelname = model.modelname;

		enList<enLoadMesh_s> &meshes = model.meshes;
		for (size_t i = 0; i < meshes.size(); i++)
		{
			enLoadedMesh_s loaded;

			// Build data
			loaded.program = meshes[i].program;
			loaded.imported = importer.ParseObjFile(meshes[i].meshpath);			
			enList<enString> &textures = meshes[i].texturepaths;
			for (size_t j = 0; j < textures.size(); j++)
				loaded.textures.add(importer.ParseTexture(textures[j]));

			// Add to the meshes the loaded mesh
			data.meshes.add(loaded);
		}

		meshToAdd.add(data);
	}

	btRigidBody *AddBody(btCollisionShape *shape, enVector3 &position, enScalar mass)
	{
		btRigidBody *body = game->Engine()->AddRigidBody(shape, position, mass);
		body->setActivationState(DISABLE_DEACTIVATION);

		return body;
	}

	btRigidBody *AddSphere(btScalar radius, enVector3 &position, enScalar mass)
	{		
		btSphereShape *sphere = new btSphereShape(radius);
		return AddBody(sphere, position, mass);
	}

	btRigidBody *AddBox(btVector3 &extents, enVector3 &position, enScalar mass)
	{
		btBoxShape *box = new btBoxShape(extents);
		return AddBody(box, position, mass);
	}

	enPhysics *AddComponentSphere(btScalar radius, enVector3 &position, enScalar mass)
	{
		enPhysics *physics = (enPhysics *)enPhysics::NewObject();
		physics->Body(AddSphere(radius, position, mass));

		return physics;
	}

	enPhysics *AddComponentBox(enVector3 &extents, enVector3 &position, enScalar mass)
	{
		enPhysics *physics = (enPhysics *)enPhysics::NewObject();
		physics->Body(AddBox(btVector3(extents.x, extents.y, extents.z), position, mass));

		return physics;
	}

	enList<enEntity *> EntitiesWithTag(const enString &tag)
	{
		enList<enEntity *> entities;

		for (size_t i = 0; i < toAdd.size(); i++)
		{
			if (toAdd[i]->GetTag() == tag)
				entities.add(toAdd[i]);
		}

		return entities;
	}

	void AddComponentToEntities(const enString &tag, enComponent *component)
	{
		enList<enEntity *> e = EntitiesWithTag(tag);
		for (size_t i = 0; i < e.size(); i++)
			e[i]->AddComponent(component);
	}

	void SetEntitiesScale(const enString &tag, enVector3 scale)
	{
		enList<enEntity *> e = EntitiesWithTag(tag);
		for (size_t i = 0; i < e.size(); i++)
			e[i]->Transform().scale = scale;		
	}

	void SetEntitiesRotation(const enString &tag, enVector3 axis, enScalar angle)
	{
		enList<enEntity *> e = EntitiesWithTag(tag);
		for (size_t i = 0; i < e.size(); i++) 
		{
			e[i]->Transform().rotation.angle = angle;
			e[i]->Transform().rotation.axis = axis;
		}
	}

	void SetEntitiesPosition(const enString &tag, enVector3 position)
	{
		enList<enEntity *> e = EntitiesWithTag(tag);
		for (size_t i = 0; i < e.size(); i++)
			e[i]->Transform().position = position;
	}

	void SetRotationPosition(const enString &tag, enVector3 axis, enScalar angle)
	{
		enList<enEntity *> e = EntitiesWithTag(tag);
		for (size_t i = 0; i < e.size(); i++)
		{
			e[i]->Transform().rotation.angle = angle;
			e[i]->Transform().rotation.axis = axis;
		}
	}

	void Callback()
	{
		DoEntityLoads();

		game->PostWork(this);
	}

	void GameCallback(enGame *game)
	{		
		// Create entities here
		for (size_t i = 0; i < meshToAdd.size(); i++)
		{
			enLoadedData_s &entity = meshToAdd[i];

			enModel *model = new enModel(entity.modelname);

			// Initialize meshes, bind their data and add to model
			for (size_t j = 0; j < entity.meshes.size(); j++)
			{
				enLoadedMesh_s &mesh = entity.meshes[j];
				enMesh *gameMesh = new enMesh();

				enGeometryData_s geometry;

				// Initialize geometry
				geometry.vertexCount = mesh.imported.vertex->size();
				geometry.normalCount = mesh.imported.normal->size();
				geometry.uvCount = mesh.imported.uv->size();
				geometry.triangleCount = geometry.vertexCount / 3;
				

				byte *ptr = (byte *) &(mesh.imported.vertex->get(0));

				for (size_t i = 0; i < geometry.vertexCount; i++)
				{
					enVector3 *vec = (enVector3 *)ptr;

					ptr += 12;
				}

				geometry.handleVertex = game->Driver()->CreateBuffer(geometry.vertexCount * sizeof(enVector3), &(mesh.imported.vertex->get(0)));
				geometry.handleNormal = game->Driver()->CreateBuffer(geometry.normalCount * sizeof(enVector3), &mesh.imported.normal->get(0));
				geometry.handleUv = game->Driver()->CreateBuffer(geometry.uvCount * sizeof(enVector2), &mesh.imported.uv->get(0));

				// Initialize textures
				for (size_t k = 0; k < mesh.textures.size(); k++)
					geometry.handleTextures.add(game->Driver()->InitializeTexture(*mesh.textures[k])); // Driver will release texture automatically

				// Delete impoerted data, OpenGL has it
				delete mesh.imported.vertex;
				delete mesh.imported.normal;
				delete mesh.imported.uv;
				
				// Set data and add the mesh to the model
				gameMesh->SetGeometryData(geometry);
				gameMesh->SetAABB(mesh.imported.aabb);
				gameMesh->SetProgram(game->Shaders()->GetProgram(mesh.program));

				model->AddMesh(gameMesh);
			}

			// Create entity, set it's data and add to the add list.
			enEntity *gameEntity = (enEntity*)enEntity::NewObject();
			gameEntity->SetTag(entity.tag);
			gameEntity->SetModel(model);

			toAdd.add(gameEntity);			
		}

		meshToAdd.clear();

		// Do rigging
		DoEntityRigging();

		// Finally add the entities to the game
		for (size_t i = 0; i < toAdd.size(); i++)
			game->AddEntity(toAdd[i]); // Will add the entiti's model to the model manager
	}
private:
	// Meshes to add and bind to opengl on the main thread
	enList<enLoadedData_s> meshToAdd;
};

#endif