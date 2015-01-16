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

#include "Renderer.h"

#include "Entity.h"
#include "Vector.h"
#include "Model.h"
#include "Mesh.h"
#include "Config.h"
#include "Physics.h"
#include "PhysicsEngine.h"
#include "Math.h"
#include "Profiler.h"
#include "Camera.h"
#include "Timing.h"

#include "glinclude.h"

#define TAG "RENDERER"

size_t enRenderer::RenderEntities(const enList<enEntity*> &objects, const enCamera &camera)
{
	size_t rendered = 0;

	for (size_t i = 0; i < objects.size(); i++)
	{
		enEntity *entity = objects[i];

		if (entity->IsVisible())
			rendered += RenderEntity(*entity, camera);
	}
	
	return rendered;
}

Uint32 q;

enAABB RecomputeBox(const enAABB &, enMat4x4 &);

size_t enRenderer::RenderEntity(const enEntity &entity, const enCamera &camera)
{	
	glGenQueries(1, &q);

	size_t rendered = 0;

	// Model matrix
	enMat4x4 m = enMath::Position(entity.Transform().rotation.axis, entity.Transform().rotation.angle, entity.Transform().position, entity.Transform().scale);

	// Model-View matrix
	enMat4x4 mv = m * camera.LookAt();	
	
	// Render the entity's model
	for (size_t i = 0; i < entity.GetModel()->MeshCount(); i++)
	{
		enAABB aabb = entity.GetModel()->GetMesh(i)->GetAABB();

		enAABB recomputed = enAABB::RecomputeBox(aabb, mv);

		bool render = AABBFrustumVisible(recomputed.ToClip(camera.Projection()));
		
		if (render) 
		{
			// TODO: implement some simple occlusion queryes
			// TODO: do not directly draw, but add to a different list and submit that list for render so we can occlude more performantly
			glBeginQuery(GL_SAMPLES_PASSED, q);			
			RenderMesh(*entity.GetModel()->GetMesh(i), camera, mv);
			glEndQuery(GL_SAMPLES_PASSED);

			Uint32 result;
			//glGetQueryObjectuiv(q, GL_QUERY_RESULT_AVAILABLE, &result);
			glGetQueryObjectuiv(q, GL_QUERY_RESULT, &result);
			//printf("Samples: %d\n", result);

			/*
			if (result != 0) 
			{
				glGetQueryObjectuiv(q, GL_QUERY_RESULT, &result);
			}
			else
			{
				result = 1;
			}
			*/

			//printf("Samples: %d\n", result);

			if (result != 0)
			{
				RenderMesh(*entity.GetModel()->GetMesh(i), camera, mv);
				rendered++;
			}			
		}

		// Render AABB if we have to
		if (enConfig::DebugAABB())
		{
			RenderAABB(recomputed, camera);
			RenderAABBNT(aabb, camera, mv);
		}
	}

	glDeleteQueries(1, &q);

	return rendered;
}

#include "Vector.h"



void enRenderer::RenderMesh(const enMesh &mesh, const enCamera &camera, const enMat4x4 &mv)
{
	enGeometryData_s data = mesh.GetGeometryData();
	enProgram_s program = mesh.GetProgram();

	glUseProgram(program.program);

	glEnableVertexAttribArray(program.attributeVertex);
	//glEnableVertexAttribArray(program.attributeNormal);
	glEnableVertexAttribArray(program.attributeUv);

	glBindBuffer(GL_ARRAY_BUFFER, data.handleVertex);
	glVertexAttribPointer(
		program.attributeVertex,
		enMesh::VERTEX_COORDS,
		GL_FLOAT, false,
		enMesh::VERTEX_STRIDE, NULL);
	
		/*
	glBindBuffer(GL_ARRAY_BUFFER, data.handleNormal);
	glVertexAttribPointer(
		program.attributeNormal,
		enMesh::NORMAL_COORDS,
		GL_FLOAT, false,
		enMesh::NORMAL_STRIDE, NULL);
		*/
		
	glBindBuffer(GL_ARRAY_BUFFER, data.handleUv);
	glVertexAttribPointer(
		program.attributeUv,
		enMesh::UV_COORDS,
		GL_FLOAT, false,
		enMesh::UV_STRIDE, NULL);

	// Bind all textures
	for (size_t i = 0, size = data.handleTextures.size(); i < size; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, data.handleTextures[i]);
		glUniform1i(program.uniformTextures[i], i);
	}
	
	glUniformMatrix4fv(program.uniformModelView, 1, false, mv.ToPtr());
	glUniformMatrix4fv(program.uniformProjection, 1, false, camera.ToProjectionPtr());

	glDrawArrays(GL_TRIANGLES, 0, data.vertexCount);	

	glDisableVertexAttribArray(program.attributeVertex);
	//glDisableVertexAttribArray(program.attributeNormal);
	glDisableVertexAttribArray(program.attributeUv);

	glUseProgram(0);
}

void enRenderer::RenderAABB(const enAABB &aabb, const enCamera &camera)
{	
	const static enVector3 color(1, 1, 1);
	
	DebugPrimitiveProjectionSetup(camera);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	RenderBox(aabb.min, aabb.max, color);
}

// Render the AABB that is not transformed
void enRenderer::RenderAABBNT(const enAABB &aabb, const enCamera &camera, const enMat4x4 mv)
{
	const static enVector3 color(1, 0, 0);

	DebugPrimitiveProjectionSetup(camera);
	DebugPrimitiveMvSetup(mv);

	RenderBox(aabb.min, aabb.max, color);
}

void enRenderer::RenderLine(const enVector3 &from, const enVector3 &to, const enVector3 &color)
{	
	//glDisable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
	glColor3fv(color.ToPtr());
	glVertex3fv(from.ToPtr());
	glColor3fv(color.ToPtr());
	glVertex3fv(to.ToPtr());
	glEnd();
	//glEnable(GL_DEPTH_TEST);
}

void enRenderer::RenderPhysics(const btDiscreteDynamicsWorld &world, const enCamera &camera)
{

	DebugPrimitiveProjectionSetup(camera);
	glMultMatrixf(camera.ToLookAtPtr());

	//glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	btScalar mtx[16];
	for (int i = world.getNumCollisionObjects() - 1; i >= 0; i--)
	{
		glLoadIdentity();

		btCollisionObject *obj = world.getCollisionObjectArray()[i];
		btRigidBody *body = btRigidBody::upcast(obj);

		body->getWorldTransform().getOpenGLMatrix(mtx);
		glMultMatrixf(mtx);
		
		enVector3 phyColor(0.2f, 0.4f, 0.6f);
		btCollisionShape *shape = body->getCollisionShape();

		switch (shape->getShapeType())
		{
		case BOX_SHAPE_PROXYTYPE:  {
			const btBoxShape *boxShape = static_cast<const btBoxShape*>(shape);
			btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();

			// World center of mass
			btVector3 bbMin = -halfExtents;
			btVector3 bbMax = halfExtents;

			// Draw the AABB			
			RenderBox(enVector3(bbMin[0], bbMin[1], bbMin[2]), enVector3(bbMax[0], bbMax[1], bbMax[2]), phyColor);
			}
			break;
		case SPHERE_SHAPE_PROXYTYPE: {
			const btSphereShape *sphereShape = static_cast<const btSphereShape *>(shape);
			enScalar radius = sphereShape->getRadius() + 0.005f;

			RenderSphere(radius, phyColor);
			}
			break;
		default:
			TDLOG(TAG, "Unknown shape type: %d\n", shape->getShapeType());
		}		
	}

	//glEnable(GL_DEPTH_TEST);
}

void enRenderer::RenderSphere(enScalar radius, enVector3 &color, size_t segments)
{
	enVector3 x(1, 0, 0);
	enVector3 y(0, 1, 0);
	x *= radius;
	y *= radius;

	for (size_t i = 0; i < segments; i++)
	{
		float ang1 = (i + 0) * (360.0f / segments);
		float ang2 = (i + 1) * (360.0f / segments);

		enVector3 nrm1 = enMath::Rotation(ang1, X) * y;
		enVector3 nrm2 = enMath::Rotation(ang2, X) * y;

		enVector3 nrm3 = enMath::Rotation(ang1, Y) * x;
		enVector3 nrm4 = enMath::Rotation(ang2, Y) * x;

		RenderLine(nrm1, nrm2, color);
		RenderLine(nrm3, nrm4, color);
	}
}

void enRenderer::RenderBox(const enVector3 &min, const enVector3 &max, const enVector3 &color)
{
	RenderLine(enVector3(min[0], min[1], min[2]), enVector3(max[0], min[1], min[2]), color);
	RenderLine(enVector3(max[0], min[1], min[2]), enVector3(max[0], max[1], min[2]), color);
	RenderLine(enVector3(max[0], max[1], min[2]), enVector3(min[0], max[1], min[2]), color);
	RenderLine(enVector3(min[0], max[1], min[2]), enVector3(min[0], min[1], min[2]), color);
	RenderLine(enVector3(min[0], min[1], min[2]), enVector3(min[0], min[1], max[2]), color);
	RenderLine(enVector3(max[0], min[1], min[2]), enVector3(max[0], min[1], max[2]), color);
	RenderLine(enVector3(max[0], max[1], min[2]), enVector3(max[0], max[1], max[2]), color);
	RenderLine(enVector3(min[0], max[1], min[2]), enVector3(min[0], max[1], max[2]), color);
	RenderLine(enVector3(min[0], min[1], max[2]), enVector3(max[0], min[1], max[2]), color);
	RenderLine(enVector3(max[0], min[1], max[2]), enVector3(max[0], max[1], max[2]), color);
	RenderLine(enVector3(max[0], max[1], max[2]), enVector3(min[0], max[1], max[2]), color);
	RenderLine(enVector3(min[0], max[1], max[2]), enVector3(min[0], min[1], max[2]), color);
}

int computeOutCode(float x, float y, float z, float w) {
	// Start with an outcode of 0, assuming the point is in the frustum
	int code = 0;
	// Check each of the six planes, and turn on the bit
	// if we detect the point is outside the plane
	if (x < -w) code |= 0x01; // left
	if (x > w) code |= 0x02; // right
	if (y < -w) code |= 0x04; // bottom
	if (y > w) code |= 0x08; // top
	if (z < -w) code |= 0x10; // near
	if (z > w) code |= 0x20; // far

	return code;
}

bool inFrustum(const enVector3 &v)
{
	if (v.x > -1 && v.x < 1
		|| v.y > -1 && v.y < 1
		|| v.z > -1 && v.z < 1)
	{
		return true;
	}

	return false;
}

// Test only a trivial reject
bool enRenderer::AABBFrustumVisible(const enAABB &aabb)
{			
	// Test if any point is in frustum

	enVector3 min = aabb.min;
	enVector3 max = aabb.max;

	enVector3 temp;

	// 8 tests	
	temp.Set(min[0], min[1], min[2]);
	if (inFrustum(temp))
		return true;

	temp.Set(max[0], min[1], min[2]);
	if (inFrustum(temp))
		return true;

	temp.Set(max[0], max[1], min[2]);
	if (inFrustum(temp))
		return true;

	temp.Set(max[0], max[1], max[2]);
	if (inFrustum(temp))
		return true;

	temp.Set(min[0], min[1], max[2]);
	if (inFrustum(temp))
		return true;

	temp.Set(min[0], max[1], max[2]);
	if (inFrustum(temp))
		return true;

	temp.Set(min[0], max[1], min[2]);
	if (inFrustum(temp))
		return true;

	temp.Set(max[0], min[1], max[2]);
	if (inFrustum(temp))
		return true;

	return false;

	/*
	int code[8];

	enVector3 min = aabb.min;
	enVector3 max = aabb.max;

	code[0] = computeOutCode(min[0], min[1], min[2], 1);
	code[1] = computeOutCode(max[0], min[1], min[2], 1);
	code[2] = computeOutCode(max[0], max[1], min[2], 1);
	code[3] = computeOutCode(max[0], max[1], max[2], 1);
	code[4] = computeOutCode(min[0], min[1], max[2], 1);
	code[5] = computeOutCode(min[0], max[1], max[2], 1);
	code[6] = computeOutCode(min[0], max[1], min[2], 1);
	code[7] = computeOutCode(max[0], min[1], max[2], 1);

	unsigned int trivial = (unsigned int)~0;

	// If AND != 0 it's off screen
	for (int i = 0; i < 8; i++)
	{
		trivial &= code[i];
	}

	return (trivial == 0);
	*/
}

void enRenderer::DebugPrimitiveMvSetup(const enMat4x4 &mv)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMultMatrixf(mv.ToPtr());
}

void enRenderer::DebugPrimitiveProjectionSetup(const enCamera &camera)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glLoadMatrixf(camera.ToProjectionPtr());
}