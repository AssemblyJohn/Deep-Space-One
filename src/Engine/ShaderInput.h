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

#ifndef EN_SHADER_INPUT
#define EN_SHADER_INPUT

#include "ShaderBase.h"

class enShaderInput
{
public:
	void Initialize();
	void Bind(const enShaderParameters &map, const enChar *name, enShaderResource &resource)
	{
		

		
	}
private:
	bool locationBound; // Location has been bound and it's ready for use

	enString name;
	Int16 location;

	// If it's for a uniform or attrib
	enShaderInputTarget target;
	// It's type (int, float, vec2, mat2x2 etc...)
	enShaderInputType type;
};

#endif