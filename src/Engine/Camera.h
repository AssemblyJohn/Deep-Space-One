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

#ifndef EN_CAMERA_H
#define EN_CAMERA_H

#include "Entity.h"

#include "Scalar.h"
#include "Vector.h"
#include "Matrix.h"

struct enProjection_s
{
	enScalar fov;
	enScalar aspect;
	enScalar nearp;
	enScalar farp;
};

struct enCamera_s
{
	enVector3 direction;
	enVector3 right;
	enVector3 up;
	// To which point we are focused
	enVector3 center;
};

class enCamera : public enEntity
{
public:
	CLASS_VARS()
	
	enCamera();
	enCamera(const enString &);

	void Initialize();

	/**
	 * Setup the projection matrix again.
	 *
	 * @param fov
	 *				Field of view
	 * @param aspect
	 *				Aspect ratio
	 * @param near 
	 *				Near plane
	 * @param far
	 *				Far plane
	 */
	void ProjectionResetup(enScalar fov, enScalar aspect, enScalar nearp, enScalar farp);
	// Projection data 
	enProjection_s ProjectionData() const;

	// Steps the camera
	void Step();

	// Set/Get FOV
	void SetFov(enScalar);
	const enScalar GetFov() const;

	/** Lookat so we can multiply it with our model matrix */
	const enMat4x4 &LookAt() const;
	/** Projection */
	const enMat4x4 &Projection() const;
	/** Updated internally */
	enCamera_s GetDirections() const;
	/** Pointer to projection matrix */
	const float *ToProjectionPtr() const;
	/** Pointer to lookat matrix */
	const float *ToLookAtPtr() const;	
	/** Rotation around y */
	float Yaw();
	/** Rotation around x */
	float Pitch();
private:
	void RecalcProjection();

	// Camera data
	enCamera_s directions;
	enMat4x4 mtxLookAt;
	
	// Projection data
	enProjection_s projection;
	enMat4x4 mtxProjection;
};

#endif