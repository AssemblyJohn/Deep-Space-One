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

#ifndef EN_SHADER_UTILS_H
#define EN_SHADER_UTILS_H

#include "String.h"
#include "Map.h"
#include "ReferenceCounting.h"

#include "Program.h"

class enGame;
class enDriverOgl;

class enShaderUtils : public enRefObject
{
public:
	void Initialize(enGame *);
	
	enProgram_s GetProgram(enProgramType_e key)
	{
		return programs.get(key);
	}
private:
	void CreateProgram(enDriverOgl *, enProgramType_e, const enString &, const enString &);
	void PutProgram(enProgramType_e, enProgram_s &);

	enMap<enProgramType_e, enProgram_s> programs;
};

#endif