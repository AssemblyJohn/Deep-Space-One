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

#include "Math.h"

#include "Scalar.h"

enMat4x4 enMath::Position(const enVector3 &axis, float angle, const enVector3 &position, const enVector3 &scale)
{
	enMat3x3 rot = enMath::Rotation(angle, axis);
	enMat4x3 trans = enMath::Translation(position);
	enMat3x3 scl = enMath::Scale(scale);

	return scl.ToMat4x4() * rot.ToMat4x4() * trans.ToMat4x4();
}

enMat4x3 enMath::Camera(const enVector3 &pos, float phi, float theta)
{
	theta = DEG2RAD(theta);
	phi = DEG2RAD(phi);

	float cosT = enCos(theta);
	float sinT = enSin(theta);
	float cosP = enCos(phi);
	float sinP = enSin(phi);

	float cosTcosP = cosT * cosP;
	float cosTsinP = cosT * sinP;
	float _sinT = -sinT;
	float _sinP = -sinP;	

	return enMat4x3(
		// Rotation
		cosT,	_sinT * sinP,	_sinT * cosP,
		0,		cosP,			_sinP,
		sinT,	cosTsinP,		cosTcosP,
		// Position
		-pos.x, -pos.y,			-pos.z
	);
}

void enMath::Translate(enMat4x4 &mtx, enVector3 &t)
{
	
	mtx[3].x += mtx[0].x * t.x + mtx[1].x * t.y + mtx[2].x * t.z;
	mtx[3].y += mtx[0].y * t.x + mtx[1].y * t.y + mtx[2].y * t.z;
	mtx[3].z += mtx[0].z * t.x + mtx[1].z * t.y + mtx[2].z * t.z;
	mtx[3].w += mtx[0].w * t.x + mtx[1].w * t.y + mtx[2].w * t.z;
}

enMat4x4 enMath::LookAt(const enVector3 &eye, const enVector3 &center, const enVector3 &up)
{
	// Direction
	enVector3 d = center - eye;
	d.Normalize();

	// Right
	enVector3 r = d.Cross(up);
	r.Normalize();

	// Up perpendicular on d and r
	enVector3 u = r.Cross(d);
	
	return enMat4x4(
		r.x, u.x, -d.x, 0.0f,
		r.y, u.y, -d.y, 0.0f,
		r.z, u.z, -d.z, 0.0f,
		// Translation part		
		r.x * -eye.x + r.y * -eye.y + r.z * -eye.z,
		u.x * -eye.x + u.y * -eye.y + u.z * -eye.z,
		-d.x * -eye.x + -d.y * -eye.y + -d.z * -eye.z,
		1.0f
	);
}

enMat4x4 enMath::Perspective(float fovY, float aspect, float nPlane, float fPlane)
{
	fovY = DEG2RAD(fovY);

	float cosFov = enCos(fovY * 0.5f);
	float sinFov = enSin(fovY * 0.5f);

	float height = cosFov / sinFov;
	float width = height / aspect;

	float temp1 = (nPlane + fPlane) / (nPlane - fPlane);
	float temp2 = (2.0f * nPlane * fPlane) / (nPlane - fPlane);

	return enMat4x4(
		width, 0, 0, 0,
		0, height, 0, 0,
		0, 0, temp1, -1,
		0, 0, temp2, 0
	);
}

enMat4x4 enMath::Clip(float fovY, float aspect, float nPlane, float fPlane)
{
	fovY = DEG2RAD(fovY);

	float cosFov = enCos(fovY * 0.5f);
	float sinFov = enSin(fovY * 0.5f);

	float height = cosFov / sinFov;
	float width = height / aspect;

	float temp1 = (nPlane + fPlane) / (nPlane - fPlane);
	float temp2 = (2.0f * nPlane * fPlane) / (nPlane - fPlane);

	return enMat4x4(
		width, 0, 0, 0,
		0, height, 0, 0,
		0, 0, temp1, -1,
		0, 0, temp2, 0
	);

	/*
	// Outch... i was building a DirectX style matrix here... hehe
	fovY = DEG2RAD(fovY);
	
	float cosFov = enCos(fovY * 0.5f);
	float sinFov = enSin(fovY * 0.5f);

	float height = cosFov / sinFov;
	float width = height / aspect;

	float temp1 = fPlane / (fPlane - nPlane);
	float temp2 = nPlane * fPlane / (nPlane - fPlane);
	
	return enMat4x4(
		width, 0, 0, 0,
		0, height, 0, 0,
		0, 0, temp1, 1,
		0, 0, temp2, 0
	);
	*/
}

enVector4 enMath::ToClipSpace(const enVector3 &v, const enMat4x4 &m)
{
	enVector4 temp(
		v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
		v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
		v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2],
		v.z
	);

	float w = v.z;

	temp.x /= w;
	temp.y /= w;
	temp.z /= w;
	temp.w = w;

	return temp;
}

enVector4 enMath::ToClipSpaceNoWDiv(const enVector3 &v, const enMat4x4 &m)
{
	return enVector4(
		v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
		v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
		v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2],
		v.z
	);
}

enMat4x3 enMath::Translation(const enVector3 &v)
{
	return enMat4x3(
		1,	 0,   0,
		0,	 1,   0,
		0,	 0,	  1,
		v.x, v.y, v.z
	);
}

enMat3x3 enMath::Scale(const enVector3 &v)
{
	return enMat3x3(
		v.x, 0, 0,
		0, v.y, 0,
		0, 0, v.z
	);
}

enMat3x3 enMath::Rotation(const float angle, const enVector3 &axis)
{
	// Setup
	enScalar ang = DEG2RAD(angle);
	
	enScalar cosO = enCos(ang);
	enScalar sinO = enSin(ang);
	enScalar _cosO = (1.0f - cosO);

	return enMat3x3(
		(axis.x * axis.x) * _cosO + cosO,		   (axis.x * axis.y) * _cosO + axis.z * sinO, (axis.x * axis.z) * _cosO - axis.y * sinO,
		(axis.x * axis.y) * _cosO - axis.z * sinO, (axis.y * axis.y) * _cosO + cosO,		  (axis.y * axis.z) * _cosO + axis.x * sinO,
		(axis.x * axis.z) * _cosO + axis.y * sinO, (axis.y * axis.z) * _cosO - axis.x * sinO, (axis.z * axis.z) * _cosO + cosO
	);
}

enMat3x3 enMath::Rotation(float angle, const enAxe axe)
{
	float ang = DEG2RAD(angle);
	float cA = enCos(ang);
	float sA = enSin(ang);
	float _sA = -enSin(ang);

	switch (axe)
	{
	case X:
		return enMat3x3(
			1,  0,  0,
			0,  cA, sA,
			0, _sA, cA
		);
		break;
	case Y:
		return enMat3x3(
			cA, 0, _sA,
			0,  1,  0,
			sA, 0,  cA
		);
		break;
	case Z:
		return enMat3x3(
			cA, sA,  0,
			_sA, cA, 0,
			0,   0,  1
		);
		break;
	default: return NULL;
	}
}

enMat3x3 enMath::Orientation(const enVector3 &v)
{
	enMat3x3 tempX, tempY, tempZ;

	tempX = Rotation(v.x, X);
	tempY = Rotation(v.y, Y);
	tempZ = Rotation(v.z, Z);

	return (tempY * tempX * tempZ);
}

INLINE bool enMath::CameraFacing(const enVector3 &plane, const enVector3 &camera)
{
	if ((plane * camera) < 0)
		return true;

	return false;
}