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

#ifndef EN_DRIVER_OGL_H
#define EN_DRIVER_OGL_H

#include "types.h"
#include "ReferenceCounting.h"

class enTexture;
struct enProgram_s;

enum enShaderUtilsType
{
	EN_SHADER_VERTEX,
	EN_SHADER_FRAGMENT,
};

/**
 * All these functions must be called on the OpenGL's context thread.
 */
class enDriverOgl : public enRefObject
{
public:
	void Initalize();

	/**
	 * Binds the locations of attributes and uniforms to the provided points.
	 *
	 * @param program
	 *				Locations and program
	 * @param textures
	 *				How many textures this program defines. Defaults at 1.
	 */
	void BindProgramPoints(enProgram_s &program, byte textures = 1);

	/**
	 * Creates an array buffer with the default GL_STATIC_DRAW usage.
	 * Does not dealocate the data after use. It must be done manually. 
	 *
	 * @param bytes
	 *				Data size in bytes
	 * @param data
	 *				Pointer to data
	 *
	 * @return Buffer handle
	 */
	Uint32 CreateBuffer(Uint32 bytes, void *data);
	/**
	 * Creates an array buffer. 
	 * Does not dealocate the data after use. It must be done manually.
	 *
	 * @param bytes
	 *				Data size in bytes
	 * @param data
	 * 				Pointer to data
 	 * @param usage
 	 *				Usage of this buffer
 	 *
	 * @return Buffer handle
	 */
	Uint32 CreateBuffer(Uint32 bytes, void *data, Uint32 usage);
	
	/**
	 * Initializes a texture and returns it's handle. 
	 * After the initialization takes place it deletes and frees the provided texture.
	 */
	Uint32 InitializeTexture(enTexture &);
	/**
	 * Compiles shaders, creates and links a program.
	 *
	 * @param vsource
	 *				Vertex shader source
	 * @param fsource
	 *				Fragment shader source
	 *
	 * @return	Program handle
	 */
	Uint32 CreateProgram(const char *vsource, const char *fsource);
	// Compiles a shader and returns it's handle.
	Uint32 CompileShader(enShaderUtilsType, const char *);

	// Memory allocated in video memory for buffers
	static Uint32 Memory();
private:
	static Uint32 memory;
};

#endif