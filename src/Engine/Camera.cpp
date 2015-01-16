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

#include "Camera.h"

#include "Vector.h"
#include "Matrix.h"
#include "Math.h"

CLASS_FUNCTIONS(enCamera, enEntity)

enCamera::enCamera()
{
	EN_ASSERT(0);
}

enCamera::enCamera(const enString &tag) : enEntity(tag)
{
}

void enCamera::Initialize()
{
	enEntity::Initialize();

	// Camera defaults
	directions.up.Set(0, 1, 0);
	ProjectionResetup(60.0f, 800.0f / 600.0f, 0.01f, 2048.0f);
}

void enCamera::SetFov(enScalar fov)
{
	projection.fov = fov;
	ProjectionResetup(projection.fov, projection.aspect, projection.nearp, projection.farp);
}

const enScalar enCamera::GetFov() const
{
	return projection.fov;
}

enProjection_s enCamera::ProjectionData() const
{
	return projection;
}

void enCamera::ProjectionResetup(enScalar fov, enScalar aspect, enScalar nearp, enScalar farp)
{
	projection.fov = fov;
	projection.aspect = aspect;
	projection.nearp = nearp;
	projection.farp = farp;

	RecalcProjection();
}

const float *enCamera::ToProjectionPtr() const
{
	return mtxProjection.ToPtr();
}

const float *enCamera::ToLookAtPtr() const
{
	return mtxLookAt.ToPtr();
}

const enMat4x4 &enCamera::LookAt() const
{
	return mtxLookAt;
}

const enMat4x4 &enCamera::Projection() const
{
	return mtxProjection;
}

enCamera_s enCamera::GetDirections() const
{
	return directions;
}

void enCamera::RecalcProjection()
{
	mtxProjection = enMath::Perspective(projection.fov, projection.aspect, projection.nearp, projection.farp);
}

float enCamera::Yaw()
{
	return transform.rotation.axis.y;
}

float enCamera::Pitch()
{
	return transform.rotation.axis.x;
}

void enCamera::Step()
{
	enEntity::Step();

	// Don't forget about the gimbal lock problem. That's why it's Y * X not X * Y
	// Direction orientation
	enMat3x3 rot = enMath::Rotation(transform.rotation.axis.y, Y) * enMath::Rotation(transform.rotation.axis.x, X);

	enVector3 direction(rot * enVector3(0, 0, 1));
	enVector3 right(direction.Cross(directions.up));
	enVector3 center = transform.position + direction;

	mtxLookAt = enMath::LookAt(
		transform.position,
		center,
		directions.up
	);

	// Update direction
	directions.direction = direction;
	directions.right = right;
	directions.center = center;
}