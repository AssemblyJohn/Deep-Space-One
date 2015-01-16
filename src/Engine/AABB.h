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

#ifndef EN_AABB_H
#define EN_AABB_H

#include "types.h"
#include "Vector.h"

#undef min
#undef max

class enMat3x3;
class enMat4x3;
class enMat4x4;

class enAABB 
{	
public:
	enVector3 min;
	enVector3 max;

	enAABB() {}
	enAABB(const enVector3 min, const enVector3 max) : min(min), max(max) {}
	enAABB(const enVector3 *vectors, size_t count);
	
	/**
	 * Transfroms an AABB from local space to clip space.
	 *
	 * @param p
	 *				Projection matrix
	 */
	enAABB ToClip(const enMat4x4 &p) const;

	bool Intersects(const enAABB &other) const;

	/**
	 *
	 */
	static enAABB RecomputeBox(const enAABB &box, const enMat4x4 &m);

	static const enAABB FRUSTUM;
private:
};

#endif