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

#ifndef EN_IMPORTER_H
#define EN_IMPORTER_H

#include "Vector.h"
#include "AABB.h"
#include "String.h"

template<class T> class enList;
class enTexture;

// Will be packed
struct enImportedData_s
{
	enList<enVector3> *vertex;
	enList<enVector3> *normal;
	enList<enVector2> *uv;

	enAABB aabb;
};

struct enImportedShader_s
{
	enString vs;
	enString fs;
};

class enImporter
{
public:
	enImporter() {}

	// Plain names will do since the importer will take care of setting the path to the shaders location
	enImportedShader_s ImportShaders(const enString &vertex, const enString &fragment);
	// Plain name will do since the importer will take care of setting the path to the models location
	enImportedData_s ParseObjFile(const enString &);
	// Plain name will do since the importer will take care of setting the path to the textures location
	enTexture *ParseTexture(const enString &);
private:
	enString ReadEntireCharFile(const enString &fpath);
};

#endif