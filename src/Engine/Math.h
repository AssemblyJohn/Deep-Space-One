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

#ifndef EN_MATH_H
#define EN_MATH_H

#include "Vector.h"
#include "Matrix.h"

typedef enum enAxe {
	X = 'x',
	Y = 'y',
	Z = 'z'
} enAxe;

class enMath
{
public:
	// Basic translation
	static enMat4x3 Translation(const enVector3 &);
	static void Translate(enMat4x4 &, enVector3 &);
	// Scale
	static enMat3x3 Scale(const enVector3 &);
	// Basic rotation around an axis
	static enMat3x3 Rotation(float, const enAxe);
	// Rotation around an arbitrary axis
	static enMat3x3 Rotation(const float, const enVector3 &);
	// Rotation around 3 axes
	static enMat3x3 Orientation(const enVector3 &);
	// Rotation around axis with the angle and position
	static enMat4x4 Position(const enVector3 &, float, const enVector3 &, const enVector3 &);

	static enMat4x3 Camera(const enVector3 &, float, float);
	static bool CameraFacing(const enVector3 &, const enVector3 &);

	static enMat4x4 LookAt(const enVector3 &eye, const enVector3 &center, const enVector3 &up);
	// Same as clip, but the name is more like GLUT
	static enMat4x4 Perspective(float fovY, float aspect, float nPlane, float fPlane);
	/**
	 * Generates a 4x4 clip matrix
	 *
	 * @param fovY
	 *				Field of view Y
	 * @param aspect
	 *				Aspect ratio
	 * @param nPlane
	 *				Near plane
	 * @param fPlane
	 *				Far plane
	 */
	static enMat4x4 Clip(float fovY, float aspect, float nPlane, float fPlane);
	
	// Transofrms a vector to clip space
	static enVector4 ToClipSpace(const enVector3 &, const enMat4x4 &);
	// Transofrm a vector to clip space without dividing with the 'w' component
	static enVector4 ToClipSpaceNoWDiv(const enVector3 &, const enMat4x4 &);
};

#endif