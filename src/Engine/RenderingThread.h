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

#ifndef EN_RENDERING_THREAD_H
#define EN_RENDERING_THREAD_H

#include "Threading.h"

#include "ReferenceCounting.h"

#include "ShaderUtils.h"
#include "DriverOgl.h"

void InitializeRendering();
bool IsRenderingThread();

class enRenderingThread : public enThread
{
	void Run();


	enRefPtr<enDriverOgl> driver;
	enRefPtr<enShaderUtils> shaders;


	enDriverOgl *Driver() const;
	enShaderUtils *Shaders() const;
};

#endif