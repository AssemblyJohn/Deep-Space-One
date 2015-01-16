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

#ifndef EN_SCALAR_H
#define EN_SCALAR_H

#include "types.h"

#include <math.h>

const enScalar PI = 3.141592653589793238f;
const enScalar D2R = PI / 180.0f;
const enScalar R2D = 180.0f / PI;

// Got them from <float.h>
const enScalar SCALAR_MIN = 1.175494351e-38F;
const enScalar SCALAR_MAX = 3.402823466e+38F;

#define DEG2RAD(x) ((x) * D2R)
#define RAD2DEG(x) ((x) * R2D)

INLINE enScalar enSqrt(enScalar x)
{
	return sqrtf(x);
}

INLINE enScalar enFabs(enScalar x)
{	
	return fabsf(x);
}

INLINE enScalar enCos(enScalar x)
{
	return cosf(x);
}

INLINE enScalar enSin(enScalar x)
{
	return sinf(x);
}

INLINE enScalar enAcos(enScalar x)
{
	return acosf(x);
}

INLINE enScalar enAsin(enScalar x)
{
	return asinf(x);
}

INLINE enScalar enClamp(enScalar v, enScalar min, enScalar max)
{
	if (v < min) return min;
	if (v > max) return max;

	return v;
}

INLINE enScalar enFmodf(enScalar v, enScalar d)
{
	return fmodf(v, d);
}

#endif