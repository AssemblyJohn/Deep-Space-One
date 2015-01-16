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

#include "DriverOgl.h"

#include "glinclude.h"

#include "Profiler.h"
#include "String.h"
#include "Texture.h"
#include "Program.h"

#include "SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#define TAG "DRIVER_OGL"

Uint32 enDriverOgl::memory = 0;

void enDriverOgl::Initalize()
{
	glEnable(GL_DEPTH_TEST);

	// Culling
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glClearColor(0, 0, 0, 0);	
	
	// Blending for various effects
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void enDriverOgl::BindProgramPoints(enProgram_s &program, byte textures)
{
	glUseProgram(program.program);

	program.attributeVertex = glGetAttribLocation(program.program, ATTR_VERTEX_NAME);
	program.attributeNormal = glGetAttribLocation(program.program, ATTR_NORMAL_NAME);
	program.attributeUv = glGetAttribLocation(program.program, ATTR_UV_NAME);

	program.uniformModelView = glGetUniformLocation(program.program, UNI_MODELVIEW_NAME);
	program.uniformProjection = glGetUniformLocation(program.program, UNI_PROJECTION_NAME);

	std::string texture;
	
	for (byte i = 0; i < textures; i++)
	{
		texture.clear();
		texture += UNI_TEXTURE_NAME;

		char buff[10];
		_itoa(i, buff, 10);
		texture.append(buff);
		
		program.uniformTextures.add(glGetUniformLocation(program.program, texture.c_str()));
	}

	glUseProgram(0);
}

Uint32 enDriverOgl::CreateBuffer(Uint32 bytes, void *data)
{
	return CreateBuffer(bytes, data, GL_STATIC_DRAW);
}

Uint32 enDriverOgl::CreateBuffer(Uint32 bytes, void *data, Uint32 usage)
{
	Uint32 buffer;
	glGenBuffers(1, &buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, bytes, data, usage);

	// Add to the memory used
	memory += bytes;

	return buffer;
}

Uint32 enDriverOgl::CreateProgram(const char *vsource, const char *fsource)
{
	Uint32 vertex = CompileShader(EN_SHADER_VERTEX, vsource);
	Uint32 fragment = CompileShader(EN_SHADER_FRAGMENT, fsource);

	Uint32 program = glCreateProgram();

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);

	GLint status;
	glValidateProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status == 0)
	{	
		std::string log;
		GLint len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
		log.reserve(len);

		glGetProgramInfoLog(program, len, NULL, &log[0]);

		TELOG(TAG, "Program link log: %s\n", log.c_str());
		glDeleteProgram(program);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}

Uint32 enDriverOgl::CompileShader(enShaderUtilsType type, const char *source)
{
	Uint32 shader;
	
	switch (type)
	{
	case EN_SHADER_VERTEX:
		shader = glCreateShader(GL_VERTEX_SHADER);		
		break;
	case EN_SHADER_FRAGMENT:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint status;	
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == 0)
	{
		std::string log;
		GLint len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		log.reserve(len);

		glGetShaderInfoLog(shader, len, NULL, &log[0]);

		TELOG(TAG, "Shader log: %s\n", log.c_str());
		glDeleteShader(shader);
	}

	return shader;
}

Uint32 enDriverOgl::InitializeTexture(enTexture &texture)
{
	Uint32 handle;
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, GL_TRUE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);	
	
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture.Width(), texture.Height(),
		GL_RGB, GL_UNSIGNED_BYTE, texture.ToPtr());	

	enTexture::Dealloc(&texture);

	return handle;
}

Uint32 enDriverOgl::Memory()
{
	return memory;
}