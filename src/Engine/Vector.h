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

#ifndef EN_VECTOR_H
#define EN_VECTOR_H

#include "Scalar.h"

// All vectors are column, OpenGL convention

/**
 * Begin enVector2
 */

class enVector2
{
public:
	float x, y;

	enVector2();
	enVector2(float, float);
	enVector2(const enVector2 &);

	void Set(float, float);
	void Zero();

	bool Equals(enVector2);
	bool Equals(enVector2, float);

	float Distance(enVector2 &);
	void Normalize();
	float Magnitude();

	const float *ToPtr() const;
	float *ToPtr();
	
	// Usefull for matrices
	float operator[](size_t) const;
	float &operator[](size_t);
	// Dot product between this vector and the other
	float operator*(const enVector2 &) const;
	// Negate operation
	enVector2 operator-() const;
	enVector2 operator*(float) const;
	enVector2 operator/(float) const;
	enVector2 operator+(const enVector2 &) const;
	enVector2 operator-(const enVector2 &) const;
	enVector2 &operator+=(const enVector2 &);
	enVector2 &operator-=(const enVector2 &);
	enVector2 &operator/=(const enVector2 &);
	enVector2 &operator/=(float);
	enVector2 &operator*=(float);

	static float Dot(enVector2 &, enVector2 &);
	static float Distance(enVector2 &, enVector2 &);
};

INLINE enVector2::enVector2() { }

INLINE enVector2::enVector2(const enVector2 &v)
{
	x = v.x; y = v.y;
}

INLINE enVector2::enVector2(float x, float y)
{
	this->x = x; this->y = y;
}

INLINE float enVector2::operator[](size_t i) const {
	return (&x)[i];
}

INLINE float &enVector2::operator[](size_t i) {
	return (&x)[i];
}

INLINE enVector2 enVector2::operator-() const
{
	return enVector2(-x, -y);
}

INLINE float enVector2::operator*(const enVector2 &v) const
{
	return x * v.x + y * v.y;
}

INLINE enVector2 enVector2::operator*(float v) const
{
	return enVector2(x * v, y * v);
}

INLINE enVector2 enVector2::operator/(float v) const
{
	float val = 1.0f / v;
	return enVector2(x * val, y * val);
}

INLINE enVector2 enVector2::operator+(const enVector2 &v) const
{
	return enVector2(x + v.x, y + v.y);
}

INLINE enVector2 enVector2::operator-(const enVector2 &v) const
{
	return enVector2(x - v.x, y - v.y);
}

INLINE enVector2 &enVector2::operator+=(const enVector2 &v)
{
	x += v.x;
	y += v.y;

	return *this;
}

INLINE enVector2 &enVector2::operator-=(const enVector2 &v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}

INLINE enVector2 &enVector2::operator/=(const enVector2 &v)
{
	x /= v.x;
	y /= v.y;

	return *this;
}

INLINE enVector2 &enVector2::operator/=(float v)
{
	float val = 1.0f / v;
	x *= val;
	y *= val;

	return *this;
}

INLINE enVector2 &enVector2::operator*=(float v)
{
	x *= v;
	y *= v;

	return *this;
}

INLINE void enVector2::Normalize()
{
	float magSq = x * x + y * y;
	if (magSq > 0.0f)
	{
		// Don't use sqrt, use our one
		float oneOverMag = (float)(1.0f / enSqrt(magSq));
		x *= oneOverMag;
		y *= oneOverMag;
	}
}

INLINE float enVector2::Magnitude()
{
	return enSqrt(x * x + y * y);
}

INLINE const float *enVector2::ToPtr(void) const
{
	return &x;
}

INLINE float *enVector2::ToPtr(void)
{
	return &x;
}

INLINE float enVector2::Dot(enVector2 &a, enVector2 &b)
{
	return a.x * b.x + a.y * b.y;
}

INLINE float enVector2::Distance(enVector2 &a, enVector2 &b)
{
	return enSqrt(
		(a.x - b.x) * (a.x - b.x) +
		(a.y - b.y) * (a.y - b.y)
	);
}

INLINE void enVector2::Set(float x, float y)
{
	this->x = x; this->y = y;
}

INLINE void enVector2::Zero()
{
	x = y = 0;
}

INLINE float enVector2::Distance(enVector2 &v)
{
	return enSqrt(
		(x - v.x) * (x - v.x) +
		(y - v.y) * (y - v.y)
	);
}

INLINE bool enVector2::Equals(enVector2 v)
{
	return (x == v.x) && (x == v.y);
}

INLINE bool enVector2::Equals(enVector2 v, float epsilon)
{
	return (enFabs(x - v.x) < epsilon) && (enFabs(y - v.y) < epsilon);
}

/**
 * End enVector2
 */


/**
 * Begin enVector3
 */

class enVector3
{
public:
	float x, y, z;

	enVector3();
	enVector3(float);
	enVector3(float, float, float);
	enVector3(const enVector3 &);
	/**
	 * Builds the vector from a pointer to 3 floats
	 */
	enVector3(const float *);

	void Set(float, float, float);
	void Zero();

	bool Equals(enVector3);
	bool Equals(enVector3, float);

	enVector3 Cross(const enVector3 &);
	float Distance(const enVector3 &);
	void Normalize();
	float Magnitude();

	const float *ToPtr(void) const;
	float *ToPtr(void);

	// Usefull for matrices
	float operator[](size_t) const;
	float &operator[](size_t);
	// Dot product between this vector and the other
	float operator*(const enVector3 &) const;
	// Negate operation
	enVector3 operator-() const;
	enVector3 operator*(float) const;
	enVector3 operator/(float) const;
	enVector3 operator+(const enVector3 &) const;
	enVector3 operator-(const enVector3 &) const;
	enVector3 &operator+=(const enVector3 &);
	enVector3 &operator-=(const enVector3 &);
	enVector3 &operator/=(const enVector3 &);
	enVector3 &operator/=(float);
	enVector3 &operator*=(float);

	static float Dot(const enVector3 &, const enVector3 &);
	/**
	 * Computes the angle between two vectors. The vectors will be normalized.
	 *
	 * @return The angle between the two provided vectors.
	 */
	static float Angle(enVector3 &, enVector3 &);
	static enVector3 Cross(const enVector3 &, const enVector3 &);
	static float Distance(const enVector3 &, const enVector3 &);
};

INLINE enVector3::enVector3() { }

INLINE enVector3::enVector3(const enVector3 &v)
{
	x = v.x; y = v.y; z = v.z;
}

INLINE enVector3::enVector3(float v)
{
	x = y = z = v;
}

INLINE enVector3::enVector3(float x, float y, float z)
{
	this->x = x; this->y = y; this->z = z;
}

INLINE enVector3::enVector3(const float *v)
{
	x = v[0]; y = v[1]; z = v[2];
}

INLINE float enVector3::operator[](size_t i) const {
	return (&x)[i];
}

// So we can use vector[i] += something. In case the expresion must be an modifiable lvalue
INLINE float &enVector3::operator[](size_t i) {
	return (&x)[i];
}

INLINE enVector3 enVector3::operator-() const
{
	return enVector3(-x, -y, -z);
}

INLINE float enVector3::operator*(const enVector3 &v) const
{
	return x * v.x + y * v.y + z * v.z;
}

INLINE enVector3 enVector3::operator*(float v) const
{
	return enVector3(x * v, y * v, z * v);
}

INLINE enVector3 enVector3::operator/(float v) const
{
	float val = 1.0f / v;
	return enVector3(x * val, y * val, z * val);
}

INLINE enVector3 enVector3::operator+(const enVector3 &v) const
{
	return enVector3(x + v.x, y + v.y, z + v.z);
}

INLINE enVector3 enVector3::operator-(const enVector3 &v) const
{
	return enVector3(x - v.x, y - v.y, z - v.z);
}

INLINE enVector3 &enVector3::operator+=(const enVector3 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

INLINE enVector3 &enVector3::operator-=(const enVector3 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

INLINE enVector3 &enVector3::operator/=(const enVector3 &v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;

	return *this;
}

INLINE enVector3 &enVector3::operator/=(float v)
{
	float val = 1.0f / v;
	x *= val;
	y *= val;
	z *= val;

	return *this;
}

INLINE enVector3 &enVector3::operator*=(float v)
{
	x *= v;
	y *= v;
	z *= v;

	return *this;
}

INLINE void enVector3::Normalize()
{
	float magSq = x * x + y * y + z * z;
	if (magSq > 0.0f)
	{
		// Don't use sqrt, use our one
		float oneOverMag = (float)(1.0f / enSqrt(magSq));
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
	}
}

INLINE float enVector3::Magnitude()
{
	return enSqrt(x * x + y * y + z * z);
}

INLINE const float *enVector3::ToPtr(void) const
{
	return &x;
}

INLINE float *enVector3::ToPtr(void)
{
	return &x;
}

INLINE float enVector3::Dot(const enVector3 &a, const enVector3 &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

INLINE float enVector3::Angle(enVector3 &a, enVector3 &b)
{
	a.Normalize();
	b.Normalize();

	return RAD2DEG(enAcos(a * b));
}

INLINE enVector3 enVector3::Cross(const enVector3 &a, const enVector3 &b)
{
	return enVector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

INLINE float enVector3::Distance(const enVector3 &a, const enVector3 &b)
{
	return enSqrt(
		(a.x - b.x) * (a.x - b.x) +
		(a.y - b.y) * (a.y - b.y) +
		(a.z - b.z) * (a.z - b.z)
	);
}

INLINE void enVector3::Set(float x, float y, float z)
{
	this->x = x; this->y = y; this->z = z;
}

INLINE void enVector3::Zero()
{
	x = y = z = 0;
}

INLINE enVector3 enVector3::Cross(const enVector3 &v)
{
	return enVector3(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}

INLINE float enVector3::Distance(const enVector3 &v)
{
	return enSqrt(
		(x - v.x) * (x - v.x) +
		(y - v.y) * (y - v.y) +
		(z - v.z) * (z - v.z)
	);
}

INLINE bool enVector3::Equals(enVector3 v)
{
	return (x == v.x) && (x == v.y) && (z == v.z);
}

INLINE bool enVector3::Equals(enVector3 v, float epsilon)
{
	return (enFabs(x - v.x) < epsilon) && (enFabs(y - v.y) < epsilon) && (enFabs(z - v.z) < epsilon);
}

/**
 * End enVector3
 */

/**
 * Begin enVector4
 */

// About the same as vector3...
class enVector4
{
public:
	float x, y, z, w;

	enVector4();
	enVector4(float);
	enVector4(float, float, float, float);
	enVector4(const enVector4 &);

	void Set(float, float, float, float);
	void Zero();

	bool Equals(enVector4);
	bool Equals(enVector4, float);

	enVector4 Cross(const enVector4 &);
	float Distance(const enVector4 &);
	void Normalize();
	float Magnitude();

	const float *ToPtr(void) const;
	float *ToPtr(void);

	// Usefull for matrices
	float operator[](size_t) const;
	float &operator[](size_t);
	// Dot product between this vector and the other
	float operator*(const enVector4 &) const;
	enVector4 operator-() const;
	enVector4 operator*(float) const;
	enVector4 operator/(float) const;
	enVector4 operator+(const enVector4 &) const;
	enVector4 operator-(const enVector4 &) const;
	enVector4 &operator+=(const enVector4 &);
	enVector4 &operator-=(const enVector4 &);
	enVector4 &operator/=(const enVector4 &);
	enVector4 &operator/=(float);
	enVector4 &operator*=(float);
	operator enVector3() const;

	static float Dot(enVector4 &, enVector4 &);
	// Only uses 3 parts (no w)
	static enVector4 Cross(enVector4 &, enVector4 &);
	// Only uses 3 parts (no w)
	static float Distance(enVector4 &, enVector4 &);
};



INLINE enVector4::enVector4() { }

INLINE enVector4::enVector4(const enVector4 &v)
{
	x = v.x; y = v.y; z = v.z; w = v.w;
}

INLINE enVector4::enVector4(float v)
{
	x = y = z = w = v;
}

INLINE enVector4::enVector4(float x, float y, float z, float w)
{
	this->x = x; this->y = y; this->z = z; this->w = w;
}

INLINE float enVector4::operator[](size_t i) const {
	return (&x)[i];
}

INLINE float &enVector4::operator[](size_t i) {
	return (&x)[i];
}

INLINE enVector4 enVector4::operator-() const
{
	return enVector4(-x, -y, -z, -w);
}

INLINE float enVector4::operator*(const enVector4 &v) const
{
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

INLINE enVector4 enVector4::operator*(float v) const
{
	return enVector4(x * v, y * v, z * v, w * v);
}

INLINE enVector4 enVector4::operator/(float v) const
{
	float val = 1.0f / v;
	return enVector4(x * val, y * val, z * val, w * val);
}

INLINE enVector4 enVector4::operator+(const enVector4 &v) const
{
	return enVector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

INLINE enVector4 enVector4::operator-(const enVector4 &v) const
{
	return enVector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

INLINE enVector4 &enVector4::operator+=(const enVector4 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;

	return *this;
}

INLINE enVector4 &enVector4::operator-=(const enVector4 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;

	return *this;
}

INLINE enVector4 &enVector4::operator/=(const enVector4 &v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;

	return *this;
}

INLINE enVector4 &enVector4::operator/=(float v)
{
	float val = 1.0f / v;
	x *= val;
	y *= val;
	z *= val;
	w *= val;

	return *this;
}

INLINE enVector4 &enVector4::operator*=(float v)
{
	x *= v;
	y *= v;
	z *= v;
	w *= v;

	return *this;
}

INLINE enVector4::operator enVector3() const
{
	return enVector3(
		x, y, z
	);
}

INLINE void enVector4::Normalize()
{
	float magSq = x * x + y * y + z * z;
	if (magSq > 0.0f)
	{
		// Don't use sqrt, use our one
		float oneOverMag = (float)(1.0f / enSqrt(magSq));
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
		w *= oneOverMag;
	}
}

INLINE float enVector4::Magnitude()
{
	return enSqrt(x * x + y * y + z * z + w * w);
}

INLINE const float *enVector4::ToPtr(void) const
{
	return &x;
}

INLINE float *enVector4::ToPtr(void)
{
	return &x;
}

INLINE float enVector4::Dot(enVector4 &a, enVector4 &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

INLINE enVector4 enVector4::Cross(enVector4 &a, enVector4 &b)
{
	// Take only 3 parts of it
	return enVector4(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
		1.0f
	);
}

INLINE float enVector4::Distance(enVector4 &a, enVector4 &b)
{
	// Take only the 3 parts of it
	return enSqrt(
		(a.x - b.x) * (a.x - b.x) +
		(a.y - b.y) * (a.y - b.y) +
		(a.z - b.z) * (a.z - b.z)
	);
}

INLINE void enVector4::Set(float x, float y, float z, float w)
{
	this->x = x; this->y = y; this->z = z; this->w = w;
}

INLINE void enVector4::Zero()
{
	x = y = z = w = 0;
}

INLINE enVector4 enVector4::Cross(const enVector4 &v)
{
	// Take only 3 parts of it
	return enVector4(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x,
		1.0f
	);
}

INLINE float enVector4::Distance(const enVector4 &v)
{
	return enSqrt(
		(x - v.x) * (x - v.x) +
		(y - v.y) * (y - v.y) +
		(z - v.z) * (z - v.z)
	);
}

INLINE bool enVector4::Equals(enVector4 v)
{
	return (x == v.x) && (x == v.y) && (z == v.z) && (w == v.w);
}

INLINE bool enVector4::Equals(enVector4 v, float epsilon)
{	
	return (enFabs(x - v.x) < epsilon) && (enFabs(y - v.y) < epsilon) && (enFabs(z - v.z) < epsilon) && (enFabs(w - v.w) < epsilon);
}

/**
* End enVector4
*/

#endif 