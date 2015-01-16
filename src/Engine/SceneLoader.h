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

#include "Loader.h"

#include "MtRandom.h"

#include "CameraScript.h"
#include "ShipScript.h"

void LoadAll(enGame *game)
{
	enCamera *cam = new enCamera("camera");
	cam->Transform().position.Set(0, 0, -5);
	cam->SetVisible(false);
	//cam->AddComponent((enComponent*)enCameraScript::NewObject());

	game->SetCamera(cam);	

	class localLoader : public enLoader
	{
	public:
		localLoader(enGame *game) : enLoader(game) {}

		enum VAR { AST_1, AST_2 };

		void RandomizeVector(enVector3 &v, enMtRandom &rand, Uint32 range)
		{
			for (int i = 0; i < 3; i++)
			{
				v[i] = rand.Rand(range);

				if (rand.Rand(100) < 50)
					v[i] = -v[i];
			}
		}

		void LoadAsteroid(const enString &tag, VAR var) 
		{
			enLoadMesh_s mesh;
			mesh.program = EN_TEXTURED1;

			switch (var){
			case AST_1: mesh.meshpath = "asteroid1.obj"; break;
			case AST_2: mesh.meshpath = "asteroid2.obj"; break;
			}
			
			mesh.texturepaths.add("asteroid.png");

			enLoadModel_s load;
			load.modelname = "asteroid";
			load.meshes.add(mesh);

			LoadEntity(tag, load);
		}

		void LoadShuttle()
		{
			enLoadMesh_s mesh;
			mesh.program = EN_TEXTURED1;
			mesh.meshpath = "shuttle.obj";
			mesh.texturepaths.add("shuttle.png");

			enLoadModel_s load;
			load.modelname = "shuttle";
			load.meshes.add(mesh);

			char *tag = "shuttle";
			LoadEntity(tag, load);

		}

		void LoadEarth()
		{
			enLoadMesh_s mesh;
			mesh.program = EN_TEXTURED1;
			mesh.meshpath = "planet.obj";
			mesh.texturepaths.add("earth.png");

			enLoadModel_s load;
			load.modelname = "earth";
			load.meshes.add(mesh);

			char *tag = "earth";
			LoadEntity(tag, load);
		}

		void DoEntityLoads()
		{	
			LoadShuttle();

			for (int i = 0; i < 10; i++) 
			{
				enString str = "asteroid";
				str.Append(i);

				LoadAsteroid(str, (i % 3 == 0) ? AST_1 : AST_2);
			}
			
			LoadAsteroid("bigasteroid", AST_2);

			LoadEarth();
		}

		void DoEntityRigging()
		{						
			AddComponentToEntities("shuttle", AddComponentBox(enVector3(0.3f, 0.3f, 1.0f), enVector3(0, 0, 0), 1));
			AddComponentToEntities("shuttle", (enComponent*)enShipScript::NewObject());
			
			enMtRandom rand;
			for (int i = 0; i < 10; i++)
			{
				enString str = "asteroid";
				str.Append(i);

				enVector3 pos;

				RandomizeVector(pos, rand, 5);

				// Move the field a litle further
				pos.z += 11;

				enVector3 extent;

				if (i % 3 == 0) extent = enVector3(1.0f, 0.5f, 0.5f);
				else extent = enVector3(0.5f, 0.55f, 0.7f);

				enPhysics *p = AddComponentBox(extent, pos, 1);

				RandomizeVector(pos, rand, 20);
				pos.Normalize();

				// Apply a weak inertial force
				p->ApplyCentralForce(pos);

				RandomizeVector(pos, rand, 5);

				// Apply a weak rotation
				p->ApplyTorque(pos);

				AddComponentToEntities(str, p);
			}
			
			
			enPhysics *bigasteroid = AddComponentBox(enVector3(0.5f, 0.55f, 0.7f) * 50, enVector3(-1500.0f, 0.0f, 300.0f), 3000);
			AddComponentToEntities("bigasteroid", bigasteroid);
			SetEntitiesScale("bigasteroid", enVector3(50.0f));

			// Sets the asteroid towards the earth. Save it!
			bigasteroid->SetAngularVelocity(enVector3(0.3, 0.2f, 0.3f));
			bigasteroid->ApplyCentralForce(enVector3(250.0f, 0, 0) * 100000);

			enPhysics *p = AddComponentSphere(172.103f, enVector3(0, 0, 300.0f), 10000);
			AddComponentToEntities("earth", p);
			p->SetAngularVelocity(enVector3(-0.005f, -.01f, 0));
		}
	};

	localLoader *l = new localLoader(game);
	l->Start();
}