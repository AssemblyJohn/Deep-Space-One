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

#ifndef EN_SHADER_H
#define EN_SHADER_H

#include "glinclude.h"

#include "types.h"
#include "String.h"
#include "Map.h"

#include "ReferenceCounting.h"

#include "Profiler.h"

enum enShaderInputType
{
	// Primitives
	EN_INT		= 0,
	EN_FLOAT	= 1,

	// Vectors
	EN_VECTOR2F	= 20,
	EN_VECTOR3F	= 21,
	EN_VECTOR4F	= 22,

	// Matrix
	EN_MAT2x2	= 40,
	EN_MAT3x3	= 41,
	EN_MAT4x4	= 42,
};

enum enShaderInputTarget
{
	EN_VERTEX_ATTRIB,
	EN_UNIFORM
};

/** Shader parameters */
class enShaderParameters
{
public:
	
private:
	
};

enum enShaderResourceType
{
	EN_SHADER_UNDEFINED,
	EN_SHADER_BUFFER,
	EN_SHADER_TEXTURE,
};

// A mesh should have a lot of these shader resource dudes
// Shader resource that can be a buffer or a texture
// The handle can be shared
class enShaderResource : public enRefObject
{
public:
	enShaderResource() : type(EN_SHADER_UNDEFINED), handle(0), bound(false) {}
	enShaderResource(enShaderResourceType inType, Uint32 handle) : type(inType), handle(handle), bound(true) {}
	virtual ~enShaderResource() {} // Free any buffer data

	void Initialize();
	bool IsIntialized();

	void BindHandle(Uint32 handle)
	{
		this->handle = handle;
		bound = true;
	}
	bool IsBound()
	{
		return bound;
	}
	Uint32 GetHandle() 
	{
		EN_ASSERT(bound);
		return handle;
	}
private:
	enShaderResourceType type;
	Uint32 handle; // Optional hanle // TODO: change to a reference counted opengl buffer or texture
	bool bound;
};

// Used for a mesh'es special vertex buffer
class enShaderResourceStructuredData : public enShaderResource
{
public:
	enShaderResourceStructuredData() : enShaderResource(EN_SHADER_BUFFER, 0), size(0), stride(0), offset(0) {}
	~enShaderResourceStructuredData() {}

	void Set(Uint16, Uint16, Uint16);
private:
	Uint16 size;	// Size of data
	Uint16 stride;	// Stride of data
	Uint16 offset;	// Offset in the current buffer
};

class enShaderResourceTexture : public enShaderResource
{
public:
	enShaderResourceTexture() : enShaderResource(EN_SHADER_TEXTURE, 0) {}
	~enShaderResourceTexture() {}
private:

};

/**
 * A class representing a shader program.
 */
class enShaderProgram : public enRefObject
{
public:
	// Used to initialize the parameter map
	virtual void Initialize() = 0;
	// Used to bind a shader's parameters before rendering
	virtual void Bind() = 0;

	/**
	 * Convenience function for binding uniform data.
	 *
	 * @param name
	 *				Name of the uniform
	 * @param data
	 *				Passed data. Will be cast to the parameter's type.
	 * @param count
	 *				Number of parameters passed. Defaults to 1
	 */
	void BindUniformParam(const enChar *name, const void *data, size_t count = 1)
	{	
		/*
		enShaderInput_s input = parameters.Parameter(name);

		EN_ASSERT(input.target == EN_UNIFORM);

		switch (input.type)
		{
		case EN_INT: glUniform1iv(input.location, count, (GLint *)data); break;
		case EN_FLOAT: glUniform1fv(input.location, count, (GLfloat *)data); break;
		case EN_VECTOR2F: glUniform2fv(input.location, count, (GLfloat *)data); break;
		case EN_VECTOR3F: glUniform3fv(input.location, count, (GLfloat *)data); break;
		case EN_VECTOR4F: glUniform4fv(input.location, count, (GLfloat *)data); break;
		case EN_MAT2x2: glUniformMatrix2fv(input.location, count, false, (GLfloat *)data); break;
		case EN_MAT3x3: glUniformMatrix3fv(input.location, count, false, (GLfloat *)data); break;
		case EN_MAT4x4: glUniformMatrix4fv(input.location, count, false, (GLfloat *)data); break;
		}
		*/
	}

	// A little more complicated with buffers, we can let the ShaderInput's bind handle that
	void BindVertexAttribParam(const enChar *name)
	{
		/*
		enShaderInput_s input = parameters.Parameter(name);

		EN_ASSERT(input.target == EN_VERTEX_ATTRIB);

		// TODO:

		// glVertexAttribPointer(input.location, );
		*/
	}
private:
	Uint32 program;
	enShaderParameters parameters;
};

#endif