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

#include "std.h"

#include "Importer.h"
#include "Profiler.h"

#include <vector>

#define BUILD

#ifdef BUILD
	#define PATH_MODEL "D:\\FastWorkspace\\C++\\Deep Space One\\media\\Models\\"
	#define PATH_TEXTURE "D:\\FastWorkspace\\C++\\Deep Space One\\media\\Textures\\"
	#define PATH_SHADER "D:\\FastWorkspace\\C++\\Deep Space One\\media\\Shaders\\"
#else
	#define PATH_MODEL "media\\Models\\"
	#define PATH_TEXTURE "media\\Textures\\"
	#define PATH_SHADER "media\\Shaders\\"
#endif

#define VERTEX_		"v"
#define NORMAL_		"vn"
#define TEXTURE_UV_	"vt"
#define OBJECT_		"o"
#define TRIANGLE_	"f"
#define COMMENT_	"#"

#define TYPE_UNKNOWN	0x000000
#define TYPE_VERTEX		0x000001
#define TYPE_TEXTURE	0x000002
#define TYPE_OBJECT		0x000003
#define TYPE_FACE		0x000004
#define TYPE_COMMENT	0x000005
#define TYPE_NORMAL		0x000006

using namespace std;

typedef struct
{
	float x, y, z;
} VEC;

typedef struct
{
	float u, v;
} UV;

typedef struct
{
	int i1, i2, i3;
	int n1, n2, n3;
	int u1, u2, u3;
} TRI;

// Prototypes
int HeaderType(char* c);
char *ExtractObjName(char *name);
void AddVertex(char *buff, vector<VEC> &vect);
void AddUv(char *buff, vector<UV> &vect);
void AddTriangle(char *buff, vector<TRI> &vect);

enString enImporter::ReadEntireCharFile(const enString &fpath)
{
	FILE * file = fopen(fpath.c_str(), "r");
	EN_ASSERT(file);

	size_t filesize;
	
	fseek(file, 0, SEEK_END);
	filesize = ftell(file);
	fseek(file, 0, SEEK_SET);

	enChar *ptr = new enChar[filesize];
	memset(ptr, '\0', filesize);
	fread(ptr, filesize, 1, file);

	return enString(ptr);
}

enImportedShader_s enImporter::ImportShaders(const enString &vertex, const enString &fragment)
{
	enString fullpathvertex = PATH_SHADER + vertex;
	enString fullpathfragment = PATH_SHADER + fragment;
	
	enImportedShader_s data;

	data.vs = ReadEntireCharFile(fullpathvertex);
	data.fs = ReadEntireCharFile(fullpathfragment);

	return data;
}

enTexture *enImporter::ParseTexture(const enString &path)
{	
	enString fullpath = PATH_TEXTURE + path;

	FILE *file = fopen(fullpath.c_str(), "r");
	EN_ASSERT(file);
	fclose(file);
	
	return enTexture::LoadTexture(fullpath.c_str());
}

enImportedData_s enImporter::ParseObjFile(const enString &path)
{
	enString fullpath = PATH_MODEL + path;

	FILE *file = fopen(fullpath.c_str(), "r");
		
	EN_ASSERT(file);

	char *name;
	vector<VEC> vertices;
	vector<VEC> normals;
	vector<UV>  textures;

	// Will pack based on this
	vector<TRI>  faces;
	
	char buff[100];
	char parseBuff[100];

	char *header;
	int header_code;
	
	// TODO: read bigger chunks
	while(fgets(buff, 100, file))
	{
		strcpy(parseBuff, buff);
		header = strtok(buff, " ");

		header_code = HeaderType(header);
		switch(header_code)
		{
		case TYPE_UNKNOWN:
			continue;
		case TYPE_COMMENT:
			continue;
		case TYPE_OBJECT:
			name = ExtractObjName(parseBuff);
			break;
		case TYPE_VERTEX:
			AddVertex(parseBuff, vertices);
			break;
		case TYPE_NORMAL:
			AddVertex(parseBuff, normals);
			break;
		case TYPE_TEXTURE:
			AddUv(parseBuff, textures);
			break;
		case TYPE_FACE:
			AddTriangle(parseBuff, faces);
			break;
		}
	}

	fclose(file);

	enImportedData_s data;
	
	// TODO: set the AABB

	data.vertex = new enList<enVector3>();
	data.normal = new enList<enVector3>();
	data.uv = new enList<enVector2>();

	// Pack everything
	for (size_t i = 0; i < faces.size(); i++)
	{
		TRI &tri = faces[i];

		data.vertex->add(enVector3(vertices[tri.i1].x, vertices[tri.i1].y, vertices[tri.i1].z));
		data.vertex->add(enVector3(vertices[tri.i2].x, vertices[tri.i2].y, vertices[tri.i2].z));
		data.vertex->add(enVector3(vertices[tri.i3].x, vertices[tri.i3].y, vertices[tri.i3].z));
		
		data.normal->add(enVector3(normals[tri.n1].x, normals[tri.n1].y, normals[tri.n1].z));
		data.normal->add(enVector3(normals[tri.n2].x, normals[tri.n2].y, normals[tri.n2].z));
		data.normal->add(enVector3(normals[tri.n3].x, normals[tri.n3].y, normals[tri.n3].z));
		
		data.uv->add(enVector2(textures[tri.u1].u, textures[tri.u1].v));
		data.uv->add(enVector2(textures[tri.u2].u, textures[tri.u2].v));
		data.uv->add(enVector2(textures[tri.u3].u, textures[tri.u3].v));
	}
	
	
	// Scan for min/max vertices
	data.aabb = enAABB(&(data.vertex->get(0)), data.vertex->size());

	return data;
}

int HeaderType(char* c)
{
	int code = 0;

	if (strcmp(c, VERTEX_) == 0)
		code = TYPE_VERTEX;
	else if (strcmp(c, NORMAL_) == 0)
		code = TYPE_NORMAL;
	else if(strcmp(c, TEXTURE_UV_) == 0)
		code = TYPE_TEXTURE;
	else if(strcmp(c, OBJECT_) == 0)
		code = TYPE_OBJECT;
	else if(strcmp(c, TRIANGLE_) == 0)
		code = TYPE_FACE;
	else if(strcmp(c, COMMENT_) == 0)
		code = TYPE_COMMENT;
	else
		code = TYPE_UNKNOWN;

	return code;
}

char *ExtractObjName(char *name)
{
	// Skip header
	strtok(name, " ");
	return strtok(NULL, " ");
}

void AddVertex(char *buff, vector<VEC> &vect)
{
	// Skipp header
	strtok(buff, " ");

	VEC tmp;

	tmp.x = (float)atof(strtok(NULL, " "));
	tmp.y = (float)atof(strtok(NULL, " "));
	tmp.z = (float)atof(strtok(NULL, " "));

	vect.push_back(tmp);
}

void AddUv(char *buff, vector<UV> &vect)
{
	// Skip header
	strtok(buff, " ");

	UV tmp;

	tmp.u = (float)atof(strtok(NULL, " "));
	tmp.v = (float)atof(strtok(NULL, " "));

	vect.push_back(tmp);
}

void AddTriangle(char *buff, vector<TRI> &vect)
{
	// Skip header
	strtok(buff, " ");

	TRI tmp;

	// vertex 1
	tmp.i1 = atoi(strtok(NULL, " /"));
	// texture 1
	tmp.u1 = atoi(strtok(NULL, " /"));
	// normal 1
	tmp.n1 = atoi(strtok(NULL, " /"));

	// vertex 2
	tmp.i2 = atoi(strtok(NULL, " /"));
	// texture 2
	tmp.u2 = atoi(strtok(NULL, " /"));
	// normal 2
	tmp.n2 = atoi(strtok(NULL, " /"));

	// vertex 3
	tmp.i3 = atoi(strtok(NULL, " /"));
	// texture 3
	tmp.u3 = atoi(strtok(NULL, " /"));
	// normal 3
	tmp.n3 = atoi(strtok(NULL, " /"));
	
	// Dec eveything by one
	tmp.i1 -= 1;
	tmp.i2 -= 1;
	tmp.i3 -= 1;

	tmp.n1 -= 1;
	tmp.n2 -= 1;
	tmp.n3 -= 1;

	tmp.u1 -= 1;
	tmp.u2 -= 1;
	tmp.u3 -= 1;

	vect.push_back(tmp);
}