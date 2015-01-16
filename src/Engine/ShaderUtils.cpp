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

#include "ShaderUtils.h"

#include "Game.h"
#include "DriverOgl.h"
#include "Importer.h"

void enShaderUtils::Initialize(enGame *game)
{
	// Load all shaders and intialize them
	enDriverOgl *driver = game->Driver();

	enImporter importer;

	// Only the textured for the moment
	enImportedShader_s shader = importer.ImportShaders("textured1.glsl.vs", "textured1.glsl.fs");
	CreateProgram(driver, EN_TEXTURED1, shader.vs, shader.fs);
}

void enShaderUtils::CreateProgram(enDriverOgl *driver, enProgramType_e type, const enString &vsource, const enString &fsource)
{
	enProgram_s program;

	program.program = driver->CreateProgram(vsource.c_str(), fsource.c_str());

	byte textures = 1;
	switch (type)
	{
	case EN_BLINNPHONG:
	case EN_TEXTURED1:
		textures = 1; 
		break;
	case EN_TEXTURED2:
		textures = 2;
		break;
	case EN_TEXTURED3:
		textures = 3;
		break;
	case EN_BUMPED:
		textures = 2;
		break;
	}

	driver->BindProgramPoints(program, textures);

	// Add the program to the list
	PutProgram(type, program);
}

void enShaderUtils::PutProgram(enProgramType_e key, enProgram_s &program)
{
	programs.put(key, program);
}