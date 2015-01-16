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

#ifndef EN_PROGRAM_H
#define EN_PROGRAM_H

#include "types.h"
#include "List.h"

// Be sure to use these names in the shader
#define ATTR_VERTEX_NAME "att_vertex"
#define ATTR_NORMAL_NAME "att_normal"
#define ATTR_UV_NAME "att_uv"

#define UNI_MODELVIEW_NAME "uni_mv"
#define UNI_PROJECTION_NAME "uni_proj"

// Append 0 - N here
#define UNI_TEXTURE_NAME "texture"

/**
 * A shader should have all these attributes/uniforms to make things easy
 */
struct enProgram_s
{
public:
	// Program
	Uint32 program;

	// Standard attribute positions
	Int32 attributeVertex;
	Int32 attributeNormal;
	Int32 attributeUv;

	// Standard uniform positions
	Int32 uniformModelView;
	Int32 uniformProjection;

	// Texture positions. Should be named "texture0" - "textureN"
	enList<Int32> uniformTextures;
};

enum enProgramType_e
{
	EN_SIMPLE,
	EN_TEXTURED1,
	EN_TEXTURED2,
	EN_TEXTURED3,
	EN_BLINNPHONG,
	EN_BUMPED,
};

#endif