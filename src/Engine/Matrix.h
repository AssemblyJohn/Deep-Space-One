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

#ifndef EN_MATRIX_H
#define EN_MATRIX_H

#include "Scalar.h"
#include "Memory.h"

#include "Vector.h"

// TODO: clean up pronto

/**
 * Begin enMat3x3
 */

class enMat4x4
{
public:
	enMat4x4();
	enMat4x4(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
	enMat4x4(const float[4][4]);
	enMat4x4(const enVector4 &, const enVector4 &, const enVector4 &, const enVector4 &);

	void Zero();
	void Identity();

	// Operators
	const enVector4 &operator[](size_t) const;
	enVector4 &operator[](size_t);
	enMat4x4 operator-() const;
	enMat4x4 operator*(float) const;
	enVector3 operator*(const enVector3 &) const;
	enVector4 operator*(const enVector4 &) const;
	enMat4x4 operator*(const enMat4x4 &) const;
	enMat4x4 operator+(const enMat4x4 &) const;
	enMat4x4 operator-(const enMat4x4 &) const;
	enMat4x4 &operator*=(float);
	enMat4x4 &operator*=(const enMat4x4 &);
	enMat4x4 &operator+=(const enMat4x4 &);
	enMat4x4 &operator-=(const enMat4x4 &);

	enMat4x4 ToTranspose() const;

	const float *ToPtr(void) const;
	float *ToPtr(void);
private:
	enVector4 mtx[4];
};

/**
* Special matrix that holds rotation aswell as translation.
* Not really valid in the math world but we can trick it in the programming world :)
* Last row represents translation.
*/
class enMat4x3
{
public:
	enMat4x3();
	enMat4x3(float, float, float, float, float, float, float, float, float, float, float, float);
	enMat4x3(const float[4][3]);
	enMat4x3(const enVector3 &, const enVector3 &, const enVector3 &, const enVector3 &);

	void Zero();
	void Identity();

	// Operators
	const enVector3 &operator[](size_t) const;
	enVector3 &operator[](size_t);
	enMat4x3 operator-() const;
	enMat4x3 operator*(float) const;
	// This is going to be tricked
	enVector3 operator*(const enVector3 &) const;
	// This is also going to be tricked
	enMat4x3 operator*(const enMat4x3 &) const;
	enMat4x3 operator+(const enMat4x3 &) const;
	enMat4x3 operator-(const enMat4x3 &) const;
	enMat4x3 &operator*=(float);
	enMat4x3 &operator*=(const enMat4x3 &);
	enMat4x3 &operator+=(const enMat4x3 &);
	enMat4x3 &operator-=(const enMat4x3 &);

	//friend enVector3 operator*(const enVector3 &, const enMat4x3 &);

	enMat4x4 ToMat4x4() const;

private:
	enVector3 mtx[4];
};

class enMat3x3
{
public:
	enMat3x3();
	enMat3x3(float, float, float, float, float, float, float, float, float);
	enMat3x3(const float[3][3]);
	enMat3x3(const enVector3 &, const enVector3 &, const enVector3 &);

	void Zero();
	void Identity();	

	// Operators
	const enVector3 &operator[](size_t) const;
	enVector3 &operator[](size_t);
	enMat3x3 operator-() const;
	enMat3x3 operator*(float) const;
	enVector3 operator*(const enVector3 &) const;
	enMat3x3 operator*(const enMat3x3 &) const;
	enMat3x3 operator+(const enMat3x3 &) const;
	enMat3x3 operator-(const enMat3x3 &) const;
	enMat3x3 &operator*=(float);
	enMat3x3 &operator*=(const enMat3x3 &);
	enMat3x3 &operator+=(const enMat3x3 &);
	enMat3x3 &operator-=(const enMat3x3 &);

	// Needa 'friend' because we have too many parameters
	//friend enMat3x3 operator*(float, const enMat3x3 &);
	//friend enVector3 operator*(const enVector3 &, const enMat3x3 &);
	//friend enVector3 &operator*=(enVector3 &, const enMat3x3 &);

	enMat4x3 ToMat4x3() const;
	enMat4x4 ToMat4x4() const;	

	enMat3x3 ToTranspose() const;

	const float *ToPtr(void) const;
	float *ToPtr(void);
private:
	enVector3 mtx[3];
};




extern enMat3x3 identity3x3;

INLINE enMat3x3::enMat3x3() { }

INLINE enMat3x3::enMat3x3(float n00, float n01, float n02, float n10, float n11, float n12, float n20, float n21, float n22)
{
	mtx[0][0] = n00; mtx[0][1] = n01; mtx[0][2] = n02;
	mtx[1][0] = n10; mtx[1][1] = n11; mtx[1][2] = n12;
	mtx[2][0] = n20; mtx[2][1] = n21; mtx[2][2] = n22;
}

INLINE enMat3x3::enMat3x3(const enVector3 &a, const enVector3 &b, const enVector3 &c)
{
	mtx[0][0] = a.x; mtx[0][1] = a.y; mtx[0][2] = a.z;
	mtx[1][0] = b.x; mtx[1][1] = b.y; mtx[1][2] = b.z;
	mtx[2][0] = c.x; mtx[2][1] = c.y; mtx[2][2] = c.z;
}

INLINE enMat3x3::enMat3x3(const float src[3][3])
{
	enMemory::Memcpy(mtx, src, 3 * 3 * sizeof(float));
}

INLINE void enMat3x3::Zero()
{
	enMemory::Memset(mtx, 0, sizeof(enMat3x3));
}

INLINE void enMat3x3::Identity()
{
	*this = identity3x3;
}

INLINE const enVector3 &enMat3x3::operator[](size_t i) const
{
	return mtx[i];
}

INLINE enVector3 &enMat3x3::operator[](size_t i)
{
	return mtx[i];
}

INLINE enMat3x3 enMat3x3::operator-() const
{
	return enMat3x3(
		-mtx[0][0], -mtx[0][1], -mtx[0][2],
		-mtx[1][0], -mtx[1][1], -mtx[1][2],
		-mtx[2][0], -mtx[2][1], -mtx[2][2]
	);
}

INLINE enMat3x3 enMat3x3::operator*(float v) const
{	
	return enMat3x3(
		v * mtx[0][0], v * mtx[0][1], v * mtx[0][2],
		v * mtx[1][0], v * mtx[1][1], v * mtx[1][2],
		v * mtx[2][0], v * mtx[2][1], v * mtx[2][2]
	);
}

INLINE enVector3 enMat3x3::operator*(const enVector3 &v) const
{
	return enVector3(
		mtx[0][0] * v.x + mtx[0][1] * v.y + mtx[0][2] * v.z,
		mtx[1][0] * v.x + mtx[1][1] * v.y + mtx[1][2] * v.z,
		mtx[2][0] * v.x + mtx[2][1] * v.y + mtx[2][2] * v.z
	);
}

INLINE enMat3x3 enMat3x3::operator*(const enMat3x3 &v) const
{
	return enMat3x3(
		mtx[0][0] * v[0][0] + mtx[0][1] * v[1][0] + mtx[0][2] * v[2][0],
		mtx[0][0] * v[0][1] + mtx[0][1] * v[1][1] + mtx[0][2] * v[2][1],
		mtx[0][0] * v[0][2] + mtx[0][1] * v[1][2] + mtx[0][2] * v[2][2],

		mtx[1][0] * v[0][0] + mtx[1][1] * v[1][0] + mtx[1][2] * v[2][0],
		mtx[1][0] * v[0][1] + mtx[1][1] * v[1][1] + mtx[1][2] * v[2][1],
		mtx[1][0] * v[0][2] + mtx[1][1] * v[1][2] + mtx[1][2] * v[2][2],

		mtx[2][0] * v[0][0] + mtx[2][1] * v[1][0] + mtx[2][2] * v[2][0],
		mtx[2][0] * v[0][1] + mtx[2][1] * v[1][1] + mtx[2][2] * v[2][1],
		mtx[2][0] * v[0][2] + mtx[2][1] * v[1][2] + mtx[2][2] * v[2][2]
	);
}

INLINE enMat3x3 enMat3x3::operator+(const enMat3x3 &v) const
{
	return enMat3x3(
		mtx[0][0] + v[0][0], mtx[0][1] + v[0][1], mtx[0][2] + v[0][2],
		mtx[1][0] + v[1][0], mtx[1][1] + v[1][1], mtx[1][2] + v[1][2],
		mtx[2][0] + v[2][0], mtx[2][1] + v[2][1], mtx[2][2] + v[2][2]
	);
}

INLINE enMat3x3 enMat3x3::operator-(const enMat3x3 &v) const
{
	return enMat3x3(
		mtx[0][0] - v[0][0], mtx[0][1] - v[0][1], mtx[0][2] - v[0][2],
		mtx[1][0] - v[1][0], mtx[1][1] - v[1][1], mtx[1][2] - v[1][2],
		mtx[2][0] - v[2][0], mtx[2][1] - v[2][1], mtx[2][2] - v[2][2]
	);
}

INLINE enMat3x3 &enMat3x3::operator*=(float v)
{
	mtx[0][0] *= v; mtx[0][1] *= v; mtx[0][2] *= v;
	mtx[1][0] *= v; mtx[1][1] *= v; mtx[1][2] *= v;
	mtx[2][0] *= v; mtx[2][1] *= v; mtx[2][2] *= v;

	return *this;
}

INLINE enMat3x3 &enMat3x3::operator*=(const enMat3x3 &v)
{
	float src[3][3];

	// First row
	src[0][0] = mtx[0][0] * v[0][0] + mtx[0][1] * v[1][0] + mtx[0][2] * v[2][0];
	src[0][1] = mtx[0][0] * v[0][1] + mtx[0][1] * v[1][1] + mtx[0][2] * v[2][1];
	src[0][2] = mtx[0][0] * v[0][2] + mtx[0][1] * v[1][2] + mtx[0][2] * v[2][2];

	// Second row
	src[1][0] = mtx[1][0] * v[0][0] + mtx[1][1] * v[1][0] + mtx[1][2] * v[2][0];
	src[1][1] = mtx[1][0] * v[0][1] + mtx[1][1] * v[1][1] + mtx[1][2] * v[2][1];
	src[1][2] = mtx[1][0] * v[0][2] + mtx[1][1] * v[1][2] + mtx[1][2] * v[2][2];

	// Third row
	src[2][0] = mtx[2][0] * v[0][0] + mtx[2][1] * v[1][0] + mtx[2][2] * v[2][0];
	src[2][1] = mtx[2][0] * v[0][1] + mtx[2][1] * v[1][1] + mtx[2][2] * v[2][1];
	src[2][2] = mtx[2][0] * v[0][2] + mtx[2][1] * v[1][2] + mtx[2][2] * v[2][2];

	enMemory::Memcpy(mtx, src, 3 * 3 * sizeof(float));

	return *this;
}

INLINE enMat3x3 &enMat3x3::operator+=(const enMat3x3 &v)
{
	mtx[0][0] += v[0][0]; mtx[0][1] += v[0][1]; mtx[0][2] += v[0][2];
	mtx[1][0] += v[1][0]; mtx[1][1] += v[1][1]; mtx[1][2] += v[1][2];
	mtx[2][0] += v[2][0]; mtx[2][1] += v[2][1]; mtx[2][2] += v[2][2];

	return *this;
}

INLINE enMat3x3 &enMat3x3::operator-=(const enMat3x3 &v)
{
	mtx[0][0] -= v[0][0]; mtx[0][1] -= v[0][1]; mtx[0][2] -= v[0][2];
	mtx[1][0] -= v[1][0]; mtx[1][1] -= v[1][1]; mtx[1][2] -= v[1][2];
	mtx[2][0] -= v[2][0]; mtx[2][1] -= v[2][1]; mtx[2][2] -= v[2][2];

	return *this;
}

INLINE enMat4x3 enMat3x3::ToMat4x3() const
{
	return enMat4x3(
		mtx[0][0], mtx[0][1], mtx[0][2],
		mtx[1][0], mtx[1][1], mtx[1][2],
		mtx[2][0], mtx[2][1], mtx[2][2],
		0.0f,	   0.0f,	  0.0f
	);
}

INLINE enMat4x4 enMat3x3::ToMat4x4() const
{
	return enMat4x4(
		mtx[0][0], mtx[0][1], mtx[0][2], 0.0f,
		mtx[1][0], mtx[1][1], mtx[1][2], 0.0f,
		mtx[2][0], mtx[2][1], mtx[2][2], 0.0f,
		0.0f,	   0.0f,	  0.0f,		 1.0f
	);
}

INLINE enMat3x3 enMat3x3:: ToTranspose() const
{
	return enMat3x3(
		mtx[0][0], mtx[1][0], mtx[2][0],
		mtx[0][1], mtx[1][1], mtx[2][1],
		mtx[0][2], mtx[1][2], mtx[2][2]
	);
}

INLINE const float *enMat3x3::ToPtr(void) const
{
	return mtx[0].ToPtr();
}

INLINE float *enMat3x3::ToPtr(void)
{
	return mtx[0].ToPtr();
}

/**
 * End enMat3x3
 */



/**
 * Begin enMat4x3
 */

extern enMat4x3 identity4x3;

INLINE enMat4x3::enMat4x3() { }

INLINE enMat4x3::enMat4x3(float n00, float n01, float n02, float n10, float n11, float n12, float n20, float n21, float n22, float n30, float n31, float n32)
{
	mtx[0][0] = n00; mtx[0][1] = n01; mtx[0][2] = n02;
	mtx[1][0] = n10; mtx[1][1] = n11; mtx[1][2] = n12;
	mtx[2][0] = n20; mtx[2][1] = n21; mtx[2][2] = n22;
	mtx[3][0] = n30; mtx[3][1] = n31; mtx[3][2] = n32;
}

INLINE enMat4x3::enMat4x3(const enVector3 &a, const enVector3 &b, const enVector3 &c, const enVector3 &d)
{
	mtx[0][0] = a.x; mtx[0][1] = a.y; mtx[0][2] = a.z;
	mtx[1][0] = b.x; mtx[1][1] = b.y; mtx[1][2] = b.z;
	mtx[2][0] = c.x; mtx[2][1] = c.y; mtx[2][2] = c.z;
	mtx[3][0] = d.x; mtx[3][1] = d.y; mtx[3][2] = d.z;
}

INLINE enMat4x3::enMat4x3(const float src[4][3])
{
	enMemory::Memcpy(mtx, src, 4 * 3 * sizeof(float));
}

INLINE void enMat4x3::Zero()
{
	enMemory::Memset(mtx, 0, sizeof(enMat4x3));
}

INLINE void enMat4x3::Identity()
{
	*this = identity4x3;
}

INLINE const enVector3 &enMat4x3::operator[](size_t i) const
{
	return mtx[i];
}

INLINE enVector3 &enMat4x3::operator[](size_t i)
{
	return mtx[i];
}

INLINE enMat4x3 enMat4x3::operator-() const
{
	return enMat4x3(
		-mtx[0][0], -mtx[0][1], -mtx[0][2],
		-mtx[1][0], -mtx[1][1], -mtx[1][2],
		-mtx[2][0], -mtx[2][1], -mtx[2][2],
		-mtx[3][0], -mtx[3][1], -mtx[3][2]
	);
}

INLINE enMat4x3 enMat4x3::operator*(float v) const
{
	return enMat4x3(
		v * mtx[0][0], v * mtx[0][1], v * mtx[0][2],
		v * mtx[1][0], v * mtx[1][1], v * mtx[1][2],
		v * mtx[2][0], v * mtx[2][1], v * mtx[2][2],
		v * mtx[3][0], v * mtx[3][1], v * mtx[3][2]
	);
}

INLINE enVector3 enMat4x3::operator*(const enVector3 &v) const
{
	// Tricked it :)
	return enVector3(
		mtx[0][0] * v.x + mtx[0][1] * v.y + mtx[0][2] * v.z + mtx[3][0],
		mtx[1][0] * v.x + mtx[1][1] * v.y + mtx[1][2] * v.z + mtx[3][1],
		mtx[2][0] * v.x + mtx[2][1] * v.y + mtx[2][2] * v.z + mtx[3][2]
	);
}

INLINE enMat4x3 enMat4x3::operator*(const enMat4x3 &v) const
{
	// This too
	return enMat4x3(
		mtx[0][0] * v[0][0] + mtx[0][1] * v[1][0] + mtx[0][2] * v[2][0],
		mtx[0][0] * v[0][1] + mtx[0][1] * v[1][1] + mtx[0][2] * v[2][1],
		mtx[0][0] * v[0][2] + mtx[0][1] * v[1][2] + mtx[0][2] * v[2][2],

		mtx[1][0] * v[0][0] + mtx[1][1] * v[1][0] + mtx[1][2] * v[2][0],
		mtx[1][0] * v[0][1] + mtx[1][1] * v[1][1] + mtx[1][2] * v[2][1],
		mtx[1][0] * v[0][2] + mtx[1][1] * v[1][2] + mtx[1][2] * v[2][2],

		mtx[2][0] * v[0][0] + mtx[2][1] * v[1][0] + mtx[2][2] * v[2][0],
		mtx[2][0] * v[0][1] + mtx[2][1] * v[1][1] + mtx[2][2] * v[2][1],
		mtx[2][0] * v[0][2] + mtx[2][1] * v[1][2] + mtx[2][2] * v[2][2],

		mtx[3][0] * v[0][0] + mtx[3][1] * v[1][0] + mtx[3][2] * v[2][0] + v[3][0],
		mtx[3][0] * v[0][1] + mtx[3][1] * v[1][1] + mtx[3][2] * v[2][1] + v[3][1],
		mtx[3][0] * v[0][2] + mtx[3][1] * v[1][2] + mtx[3][2] * v[2][2] + v[3][2]
	);
}

INLINE enMat4x3 enMat4x3::operator+(const enMat4x3 &v) const
{
	return enMat4x3(
		mtx[0][0] + v[0][0], mtx[0][1] + v[0][1], mtx[0][2] + v[0][2],
		mtx[1][0] + v[1][0], mtx[1][1] + v[1][1], mtx[1][2] + v[1][2],
		mtx[2][0] + v[2][0], mtx[2][1] + v[2][1], mtx[2][2] + v[2][2],
		mtx[3][0] + v[3][0], mtx[3][1] + v[3][1], mtx[3][2] + v[3][2]
	);
}

INLINE enMat4x3 enMat4x3::operator-(const enMat4x3 &v) const
{
	return enMat4x3(
		mtx[0][0] - v[0][0], mtx[0][1] - v[0][1], mtx[0][2] - v[0][2],
		mtx[1][0] - v[1][0], mtx[1][1] - v[1][1], mtx[1][2] - v[1][2],
		mtx[2][0] - v[2][0], mtx[2][1] - v[2][1], mtx[2][2] - v[2][2],
		mtx[3][0] - v[3][0], mtx[3][1] - v[3][1], mtx[3][2] - v[3][2]
	);
}

INLINE enMat4x3 &enMat4x3::operator*=(float v)
{
	mtx[0][0] *= v; mtx[0][1] *= v; mtx[0][2] *= v;
	mtx[1][0] *= v; mtx[1][1] *= v; mtx[1][2] *= v;
	mtx[2][0] *= v; mtx[2][1] *= v; mtx[2][2] *= v;
	mtx[3][0] *= v; mtx[3][1] *= v; mtx[3][2] *= v;

	return *this;
}

INLINE enMat4x3 &enMat4x3::operator*=(const enMat4x3 &v)
{
	float src[4][3];

	// First row
	src[0][0] = mtx[0][0] * v[0][0] + mtx[0][1] * v[1][0] + mtx[0][2] * v[2][0];
	src[0][1] = mtx[0][0] * v[0][1] + mtx[0][1] * v[1][1] + mtx[0][2] * v[2][1];
	src[0][2] = mtx[0][0] * v[0][2] + mtx[0][1] * v[1][2] + mtx[0][2] * v[2][2];

	// Second row
	src[1][0] = mtx[1][0] * v[0][0] + mtx[1][1] * v[1][0] + mtx[1][2] * v[2][0];
	src[1][1] = mtx[1][0] * v[0][1] + mtx[1][1] * v[1][1] + mtx[1][2] * v[2][1];
	src[1][2] = mtx[1][0] * v[0][2] + mtx[1][1] * v[1][2] + mtx[1][2] * v[2][2];

	// Third row
	src[2][0] = mtx[2][0] * v[0][0] + mtx[2][1] * v[1][0] + mtx[2][2] * v[2][0];
	src[2][1] = mtx[2][0] * v[0][1] + mtx[2][1] * v[1][1] + mtx[2][2] * v[2][1];
	src[2][2] = mtx[2][0] * v[0][2] + mtx[2][1] * v[1][2] + mtx[2][2] * v[2][2];

	// Fourth row
	src[3][0] = mtx[3][0] * v[0][0] + mtx[3][1] * v[1][0] + mtx[3][2] * v[2][0] + v[3][0];
	src[3][1] = mtx[3][0] * v[0][1] + mtx[3][1] * v[1][1] + mtx[3][2] * v[2][1] + v[3][1];
	src[3][2] = mtx[3][0] * v[0][2] + mtx[3][1] * v[1][2] + mtx[3][2] * v[2][2] + v[3][2];
	
	enMemory::Memcpy(mtx, src, 4 * 3 * sizeof(float));

	return *this;
}

INLINE enMat4x3 &enMat4x3::operator+=(const enMat4x3 &v)
{
	mtx[0][0] += v[0][0]; mtx[0][1] += v[0][1]; mtx[0][2] += v[0][2];
	mtx[1][0] += v[1][0]; mtx[1][1] += v[1][1]; mtx[1][2] += v[1][2];
	mtx[2][0] += v[2][0]; mtx[2][1] += v[2][1]; mtx[2][2] += v[2][2];
	mtx[3][0] += v[3][0]; mtx[3][1] += v[3][1]; mtx[3][2] += v[3][2];

	return *this;
}

INLINE enMat4x3 &enMat4x3::operator-=(const enMat4x3 &v)
{
	mtx[0][0] -= v[0][0]; mtx[0][1] -= v[0][1]; mtx[0][2] -= v[0][2];
	mtx[1][0] -= v[1][0]; mtx[1][1] -= v[1][1]; mtx[1][2] -= v[1][2];
	mtx[2][0] -= v[2][0]; mtx[2][1] -= v[2][1]; mtx[2][2] -= v[2][2];
	mtx[3][0] -= v[3][0]; mtx[3][1] -= v[3][1]; mtx[3][2] -= v[3][2];

	return *this;
}

INLINE enMat4x4 enMat4x3::ToMat4x4() const
{
	return enMat4x4(
		mtx[0][0], mtx[0][1], mtx[0][2], 0.0f,
		mtx[1][0], mtx[1][1], mtx[1][2], 0.0f,
		mtx[2][0], mtx[2][1], mtx[2][2], 0.0f,
		mtx[3][0], mtx[3][1], mtx[3][2], 1.0f
	);
}

/**
 * End enMat4x3
 */


/**
 * Begin enMat4x4
 */

extern enMat4x4 identity4x4;

INLINE enMat4x4::enMat4x4() { }

INLINE enMat4x4::enMat4x4(float n00, float n01, float n02, float n03, float n10, float n11, float n12, float n13, float n20, float n21, float n22, float n23, float n30, float n31, float n32, float n33)
{
	mtx[0][0] = n00; mtx[0][1] = n01; mtx[0][2] = n02; mtx[0][3] = n03;
	mtx[1][0] = n10; mtx[1][1] = n11; mtx[1][2] = n12; mtx[1][3] = n13;
	mtx[2][0] = n20; mtx[2][1] = n21; mtx[2][2] = n22; mtx[2][3] = n23;
	mtx[3][0] = n30; mtx[3][1] = n31; mtx[3][2] = n32; mtx[3][3] = n33;
}

INLINE enMat4x4::enMat4x4(const enVector4 &a, const enVector4 &b, const enVector4 &c, const enVector4 &d)
{
	mtx[0][0] = a.x; mtx[0][1] = a.y; mtx[0][2] = a.z; mtx[0][3] = a.w;
	mtx[1][0] = b.x; mtx[1][1] = b.y; mtx[1][2] = b.z; mtx[1][3] = b.w;
	mtx[2][0] = c.x; mtx[2][1] = c.y; mtx[2][2] = c.z; mtx[2][3] = c.w;
	mtx[3][0] = d.x; mtx[3][1] = d.y; mtx[3][2] = d.z; mtx[3][3] = d.w;
}

INLINE void enMat4x4::Zero()
{
	enMemory::Memset(mtx, 0, sizeof(enMat4x4));
}

INLINE void enMat4x4::Identity()
{
	*this = identity4x4;
}

INLINE enMat4x4::enMat4x4(const float src[4][4])
{
	enMemory::Memcpy(mtx, src, 4 * 4 * sizeof(float));
}

INLINE const enVector4 &enMat4x4::operator[](size_t i) const
{
	return mtx[i];
}

INLINE enVector4 &enMat4x4::operator[](size_t i)
{
	return mtx[i];
}

INLINE enMat4x4 enMat4x4::operator-() const
{
	return enMat4x4(
		-mtx[0][0], -mtx[0][1], -mtx[0][2], -mtx[0][3],
		-mtx[1][0], -mtx[1][1], -mtx[1][2], -mtx[1][3],
		-mtx[2][0], -mtx[2][1], -mtx[2][2], -mtx[2][3],
		-mtx[3][0], -mtx[3][1], -mtx[3][2], -mtx[3][3]
	);
}

INLINE enMat4x4 enMat4x4::operator*(float v) const
{
	return enMat4x4(
		v * mtx[0][0], v * mtx[0][1], v * mtx[0][2], v * mtx[0][3],
		v * mtx[1][0], v * mtx[1][1], v * mtx[1][2], v * mtx[1][3],
		v * mtx[2][0], v * mtx[2][1], v * mtx[2][2], v * mtx[2][3],
		v * mtx[3][0], v * mtx[3][1], v * mtx[3][2], v * mtx[3][3]
	);
}

INLINE enVector3 enMat4x4::operator*(const enVector3 &v) const
{
	return enVector3(
		mtx[0][0] * v.x + mtx[0][1] * v.y + mtx[0][2] * v.z + mtx[3][0],
		mtx[1][0] * v.x + mtx[1][1] * v.y + mtx[1][2] * v.z + mtx[3][1],
		mtx[2][0] * v.x + mtx[2][1] * v.y + mtx[2][2] * v.z + mtx[3][2]
	);
}

INLINE enVector4 enMat4x4::operator*(const enVector4 &v) const
{
	return enVector4(
		mtx[0][0] * v.x + mtx[0][1] * v.y + mtx[0][2] * v.z + mtx[0][3] * v.w,
		mtx[1][0] * v.x + mtx[1][1] * v.y + mtx[1][2] * v.z + mtx[1][3] * v.w,
		mtx[2][0] * v.x + mtx[2][1] * v.y + mtx[2][2] * v.z + mtx[2][3] * v.w,
		mtx[3][0] * v.x + mtx[3][1] * v.y + mtx[3][2] * v.z + mtx[3][3] * v.w
	);
}

INLINE enMat4x4 enMat4x4::operator*(const enMat4x4 &v) const
{
	return enMat4x4(
		mtx[0][0] * v[0][0] + mtx[0][1] * v[1][0] + mtx[0][2] * v[2][0] + mtx[0][3] * v[3][0],
		mtx[0][0] * v[0][1] + mtx[0][1] * v[1][1] + mtx[0][2] * v[2][1] + mtx[0][3] * v[3][1],
		mtx[0][0] * v[0][2] + mtx[0][1] * v[1][2] + mtx[0][2] * v[2][2] + mtx[0][3] * v[3][2],
		mtx[0][0] * v[0][3] + mtx[0][1] * v[1][3] + mtx[0][2] * v[2][3] + mtx[0][3] * v[3][3],

		mtx[1][0] * v[0][0] + mtx[1][1] * v[1][0] + mtx[1][2] * v[2][0] + mtx[1][3] * v[3][0],
		mtx[1][0] * v[0][1] + mtx[1][1] * v[1][1] + mtx[1][2] * v[2][1] + mtx[1][3] * v[3][1],
		mtx[1][0] * v[0][2] + mtx[1][1] * v[1][2] + mtx[1][2] * v[2][2] + mtx[1][3] * v[3][2],
		mtx[1][0] * v[0][3] + mtx[1][1] * v[1][3] + mtx[1][2] * v[2][3] + mtx[1][3] * v[3][3],

		mtx[2][0] * v[0][0] + mtx[2][1] * v[1][0] + mtx[2][2] * v[2][0] + mtx[2][3] * v[3][0],
		mtx[2][0] * v[0][1] + mtx[2][1] * v[1][1] + mtx[2][2] * v[2][1] + mtx[2][3] * v[3][1],
		mtx[2][0] * v[0][2] + mtx[2][1] * v[1][2] + mtx[2][2] * v[2][2] + mtx[2][3] * v[3][2],
		mtx[2][0] * v[0][3] + mtx[2][1] * v[1][3] + mtx[2][2] * v[2][3] + mtx[2][3] * v[3][3],

		mtx[3][0] * v[0][0] + mtx[3][1] * v[1][0] + mtx[3][2] * v[2][0] + mtx[3][3] * v[3][0],
		mtx[3][0] * v[0][1] + mtx[3][1] * v[1][1] + mtx[3][2] * v[2][1] + mtx[3][3] * v[3][1],
		mtx[3][0] * v[0][2] + mtx[3][1] * v[1][2] + mtx[3][2] * v[2][2] + mtx[3][3] * v[3][2],
		mtx[3][0] * v[0][3] + mtx[3][1] * v[1][3] + mtx[3][2] * v[2][3] + mtx[3][3] * v[3][3]
	);
}

INLINE enMat4x4 enMat4x4::operator+(const enMat4x4 &v) const
{
	return enMat4x4(
		mtx[0][0] + v[0][0], mtx[0][1] + v[0][1], mtx[0][2] + v[0][2], mtx[0][3] + v[0][3],
		mtx[1][0] + v[1][0], mtx[1][1] + v[1][1], mtx[1][2] + v[1][2], mtx[1][3] + v[1][3],
		mtx[2][0] + v[2][0], mtx[2][1] + v[2][1], mtx[2][2] + v[2][2], mtx[2][3] + v[2][3],
		mtx[3][0] + v[3][0], mtx[3][1] + v[3][1], mtx[3][2] + v[3][2], mtx[3][3] + v[3][3]
	);
}

INLINE enMat4x4 enMat4x4::operator-(const enMat4x4 &v) const
{
	return enMat4x4(
		mtx[0][0] - v[0][0], mtx[0][1] - v[0][1], mtx[0][2] - v[0][2], mtx[0][3] - v[0][3],
		mtx[1][0] - v[1][0], mtx[1][1] - v[1][1], mtx[1][2] - v[1][2], mtx[1][3] - v[1][3],
		mtx[2][0] - v[2][0], mtx[2][1] - v[2][1], mtx[2][2] - v[2][2], mtx[2][3] - v[2][3],
		mtx[3][0] - v[3][0], mtx[3][1] - v[3][1], mtx[3][2] - v[3][2], mtx[3][3] - v[3][3]
	);
}

INLINE enMat4x4 &enMat4x4::operator*=(float v)
{
	mtx[0][0] *= v; mtx[0][1] *= v; mtx[0][2] *= v; mtx[0][3] *= v;
	mtx[1][0] *= v; mtx[1][1] *= v; mtx[1][2] *= v; mtx[1][3] *= v;
	mtx[2][0] *= v; mtx[2][1] *= v; mtx[2][2] *= v; mtx[2][3] *= v;
	mtx[3][0] *= v; mtx[3][1] *= v; mtx[3][2] *= v; mtx[3][3] *= v;

	return *this;
}

INLINE enMat4x4 &enMat4x4::operator*=(const enMat4x4 &v)
{
	float src[4][4];

	src[0][0] = mtx[0][0] * v[0][0] + mtx[0][1] * v[1][0] + mtx[0][2] * v[2][0] + mtx[0][3] * v[3][0];
	src[0][1] = mtx[0][0] * v[0][1] + mtx[0][1] * v[1][1] + mtx[0][2] * v[2][1] + mtx[0][3] * v[3][1];
	src[0][2] = mtx[0][0] * v[0][2] + mtx[0][1] * v[1][2] + mtx[0][2] * v[2][2] + mtx[0][3] * v[3][2];
	src[0][3] = mtx[0][0] * v[0][3] + mtx[0][1] * v[1][3] + mtx[0][2] * v[2][3] + mtx[0][3] * v[3][3];

	src[1][0] = mtx[1][0] * v[0][0] + mtx[1][1] * v[1][0] + mtx[1][2] * v[2][0] + mtx[1][3] * v[3][0];
	src[1][1] = mtx[1][0] * v[0][1] + mtx[1][1] * v[1][1] + mtx[1][2] * v[2][1] + mtx[1][3] * v[3][1];
	src[1][2] = mtx[1][0] * v[0][2] + mtx[1][1] * v[1][2] + mtx[1][2] * v[2][2] + mtx[1][3] * v[3][2];
	src[1][3] = mtx[1][0] * v[0][3] + mtx[1][1] * v[1][3] + mtx[1][2] * v[2][3] + mtx[1][3] * v[3][3];

	src[2][0] = mtx[2][0] * v[0][0] + mtx[2][1] * v[1][0] + mtx[2][2] * v[2][0] + mtx[2][3] * v[3][0];
	src[2][1] = mtx[2][0] * v[0][1] + mtx[2][1] * v[1][1] + mtx[2][2] * v[2][1] + mtx[2][3] * v[3][1];
	src[2][2] = mtx[2][0] * v[0][2] + mtx[2][1] * v[1][2] + mtx[2][2] * v[2][2] + mtx[2][3] * v[3][2];
	src[2][3] = mtx[2][0] * v[0][3] + mtx[2][1] * v[1][3] + mtx[2][2] * v[2][3] + mtx[2][3] * v[3][3];

	src[3][0] = mtx[3][0] * v[0][0] + mtx[3][1] * v[1][0] + mtx[3][2] * v[2][0] + mtx[3][3] * v[3][0];
	src[3][1] = mtx[3][0] * v[0][1] + mtx[3][1] * v[1][1] + mtx[3][2] * v[2][1] + mtx[3][3] * v[3][1];
	src[3][2] = mtx[3][0] * v[0][2] + mtx[3][1] * v[1][2] + mtx[3][2] * v[2][2] + mtx[3][3] * v[3][2];
	src[3][3] = mtx[3][0] * v[0][3] + mtx[3][1] * v[1][3] + mtx[3][2] * v[2][3] + mtx[3][3] * v[3][3];

	enMemory::Memcpy(mtx, src, 4 * 4 * sizeof(float));

	return *this;
}

INLINE enMat4x4 &enMat4x4::operator+=(const enMat4x4 &v)
{
	mtx[0][0] += v[0][0]; mtx[0][1] += v[0][1]; mtx[0][2] += v[0][2]; mtx[0][3] += v[0][3];
	mtx[1][0] += v[1][0]; mtx[1][1] += v[1][1]; mtx[1][2] += v[1][2]; mtx[1][3] += v[1][3];
	mtx[2][0] += v[2][0]; mtx[2][1] += v[2][1]; mtx[2][2] += v[2][2]; mtx[2][3] += v[2][3];
	mtx[3][0] += v[3][0]; mtx[3][1] += v[3][1]; mtx[3][2] += v[3][2]; mtx[3][3] += v[3][3];

	return *this;
}

INLINE enMat4x4 &enMat4x4::operator-=(const enMat4x4 &v)
{
	mtx[0][0] -= v[0][0]; mtx[0][1] -= v[0][1]; mtx[0][2] -= v[0][2]; mtx[0][3] -= v[0][3];
	mtx[1][0] -= v[1][0]; mtx[1][1] -= v[1][1]; mtx[1][2] -= v[1][2]; mtx[1][3] -= v[1][3];
	mtx[2][0] -= v[2][0]; mtx[2][1] -= v[2][1]; mtx[2][2] -= v[2][2]; mtx[2][3] -= v[2][3];
	mtx[3][0] -= v[3][0]; mtx[3][1] -= v[3][1]; mtx[3][2] -= v[3][2]; mtx[3][3] -= v[3][3];

	return *this;
}

INLINE enMat4x4 enMat4x4::ToTranspose() const
{
	return enMat4x4(
		mtx[0][0], mtx[1][0], mtx[2][0], mtx[3][0],
		mtx[0][1], mtx[1][1], mtx[2][1], mtx[3][1],
		mtx[0][2], mtx[1][2], mtx[2][2], mtx[3][2],
		mtx[0][3], mtx[1][3], mtx[2][3], mtx[3][3]
	);
}

INLINE const float *enMat4x4::ToPtr(void) const
{
	return mtx[0].ToPtr();
}

INLINE float *enMat4x4::ToPtr(void)
{
	return mtx[0].ToPtr();
}

/**
* End enMat4x4
*/

#endif