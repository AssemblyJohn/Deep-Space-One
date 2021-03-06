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

#include "AABB.h"

#include "Matrix.h"

const enAABB enAABB::FRUSTUM = enAABB(enVector3(-1, -1, -1), enVector3(1, 1, 1));

enAABB::enAABB(const enVector3 *vectors, size_t count)
{
	float minX = SCALAR_MAX, maxX = SCALAR_MIN,
		minY = SCALAR_MAX, maxY = SCALAR_MIN,
		minZ = SCALAR_MAX, maxZ = SCALAR_MIN;

	// Search for the min/max values
	for (size_t i = 0; i < count; i++)
	{
		if (minX > vectors[i].x)
			minX = vectors[i].x;
		if (maxX < vectors[i].x)
			maxX = vectors[i].x;

		if (minY > vectors[i].y)
			minY = vectors[i].y;
		if (maxY < vectors[i].y)
			maxY = vectors[i].y;

		if (minZ > vectors[i].z)
			minZ = vectors[i].z;
		if (maxZ < vectors[i].z)
			maxZ = vectors[i].z;
	}

	min.Set(minX, minY, minZ);
	max.Set(maxX, maxY, maxZ);
}

enAABB enAABB::ToClip(const enMat4x4 &p) const
{	
	enVector3 tMin, tMax;

	// To view
	tMin = min;
	// Get z component (we trick it since it's a 3 vector not 4)
	float w = tMin.z;
	// Project and divide by z (now w)
	tMin = p * tMin;
	tMin /= w;

	// Same for max
	tMax = max;
	w = tMax.z;
	tMax = p * tMax;
	tMax /= w;

	return enAABB(tMin, tMax);
}

bool enAABB::Intersects(const enAABB &other) const
{
	if ((min.x > other.max.x) || (other.min.x > max.x))
		return false;
	if ((min.y > other.max.y) || (other.min.y > max.y))
		return false;
	if ((min.z > other.max.z) || (other.min.z > max.z))
		return false;

	return true;
}

enAABB enAABB::RecomputeBox(const enAABB &box, const enMat4x4 &m)
{
	enVector3 min(0.0f), max(0.0f);

	// Translate
	min = max = m[3];

	if (m[0][0] > 0.0f)
	{
		min.x += m[0][0] * box.min.x; max.x += m[0][0] * box.max.x;
	}
	else
	{
		min.x += m[0][0] * box.max.x; max.x += m[0][0] * box.min.x;
	}

	if (m[0][1] > 0.0f)
	{
		min.y += m[0][1] * box.min.x; max.y += m[0][1] * box.max.x;
	}
	else
	{
		min.y += m[0][1] * box.max.x; max.y += m[0][1] * box.min.x;
	}

	if (m[0][2] > 0.0f)
	{
		min.z += m[0][2] * box.min.x; max.z += m[0][2] * box.max.x;
	}
	else
	{
		min.z += m[0][2] * box.max.x; max.z += m[0][2] * box.min.x;
	}

	if (m[1][0] > 0.0f)
	{
		min.x += m[1][0] * box.min.y; max.x += m[1][0] * box.max.y;
	}
	else
	{
		min.x += m[1][0] * box.max.y; max.x += m[1][0] * box.min.y;
	}

	if (m[1][1] > 0.0f)
	{
		min.y += m[1][1] * box.min.y; max.y += m[1][1] * box.max.y;
	}
	else
	{
		min.y += m[1][1] * box.max.y; max.y += m[1][1] * box.min.y;
	}

	if (m[1][2] > 0.0f)
	{
		min.z += m[1][2] * box.min.y; max.z += m[1][2] * box.max.y;
	}
	else
	{
		min.z += m[1][2] * box.max.y; max.z += m[1][2] * box.min.y;
	}

	if (m[2][0] > 0.0f)
	{
		min.x += m[2][0] * box.min.z; max.x += m[2][0] * box.max.z;
	}
	else
	{
		min.x += m[2][0] * box.max.z; max.x += m[2][0] * box.min.z;
	}

	if (m[2][1] > 0.0f)
	{
		min.y += m[2][1] * box.min.z; max.y += m[2][1] * box.max.z;
	}
	else
	{
		min.y += m[2][1] * box.max.z; max.y += m[2][1] * box.min.z;
	}

	if (m[2][2] > 0.0f)
	{
		min.z += m[2][2] * box.min.z; max.z += m[2][2] * box.max.z;
	}
	else
	{
		min.z += m[2][2] * box.max.z; max.z += m[2][2] * box.min.z;
	}

	return enAABB(min, max);
}