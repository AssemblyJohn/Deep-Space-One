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

#include "Mesh.h"

#include "Texture.h"
#include "Vector.h"

#include "Memory.h"
#include "Profiler.h"

const size_t enMesh::VERTEX_COORDS	= 3;
const size_t enMesh::NORMAL_COORDS	= 3;
const size_t enMesh::UV_COORDS		= 2;
const size_t enMesh::BYTE_PER_COORD = sizeof(float);

const size_t enMesh::VERTEX_STRIDE = enMesh::VERTEX_COORDS * enMesh::BYTE_PER_COORD;
const size_t enMesh::NORMAL_STRIDE = enMesh::NORMAL_COORDS * enMesh::BYTE_PER_COORD;
const size_t enMesh::UV_STRIDE = enMesh::UV_COORDS * enMesh::BYTE_PER_COORD;

enMesh::enMesh()
{}

enMesh::enMesh(const enGeometryData_s &data, const enProgram_s &program, const enAABB &aabb) 
{
	this->data = data;
	this->program = program;
	this->aabb = aabb;
}

void enMesh::SetGeometryData(const enGeometryData_s &data)
{
	this->data = data;
}

void enMesh::SetProgram(const enProgram_s &program)
{
	this->program = program;
}

void enMesh::SetAABB(const enAABB &aabb)
{

	this->aabb = aabb;
}

const enGeometryData_s &enMesh::GetGeometryData() const
{
	return data;
}

const enProgram_s &enMesh::GetProgram() const
{
	return program;
}

const enAABB &enMesh::GetAABB() const
{
	return aabb;
}