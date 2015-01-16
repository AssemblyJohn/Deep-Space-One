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

#ifndef EN_RENDERER_H
#define EN_RENDERER_H

#include "ReferenceCounting.h"

template<class T> class enList;
class enAABB;
class enVector3;
class enMat4x4;
class enEntity;
class enMesh;
class enCamera;
class btDiscreteDynamicsWorld;

class enRenderer : public enRefObject
{
public:
	// Returns the number of entities actualy rendered
	size_t RenderEntities(const enList<enEntity*> &, const enCamera &);
	// Returns the number of models actually rendered
	size_t RenderEntity(const enEntity &, const enCamera &);
	void RenderPhysics(const btDiscreteDynamicsWorld &, const enCamera &);

	void DebugPrimitiveProjectionSetup(const enCamera &);
	void DebugPrimitiveMvSetup(const enMat4x4 &);
	void RenderLine(const enVector3 &, const enVector3 &, const enVector3 &);
private:
	void RenderMesh(const enMesh &, const enCamera &, const enMat4x4 &);
	void RenderAABB(const enAABB &, const enCamera &);
	void RenderAABBNT(const enAABB &, const enCamera &, const enMat4x4);

	void RenderBox(const enVector3 &min, const enVector3 &max, const enVector3 &color);
	void RenderSphere(enScalar radius, enVector3 &color, size_t segments = 50);

	bool AABBFrustumVisible(const enAABB &);
	
};

#endif