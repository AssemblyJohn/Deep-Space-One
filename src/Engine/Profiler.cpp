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

#include "Profiler.h"

#include <stdarg.h>
#include <stdio.h>

void dprintf(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	printf("[DEBUG] "); vprintf(fmt, args);
	va_end(args);
}

void eprintf(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	printf("[ERROR] "); vprintf(fmt, args);
	va_end(args);
}

void tdprintf(const char * tag, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	printf("[DEBUG"); printf("|TAG: %s] ", tag); vprintf(fmt, args);
	va_end(args);
}

void teprintf(const char *tag, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	printf("[ERROR"); printf("|TAG: %s] ", tag); vprintf(fmt, args);
	va_end(args);
}

size_t Profiler::MemoryTextureUsed()
{	
	size_t memused = enTexture::memused;

	dprintf("Memory used by textures: %d\n", memused);

	return memused;
}

size_t Profiler::MemoryRuntimeClassesUsed()
{
	size_t memused = enClass::memused;

	dprintf("Memory used by runtime classes: %d\n", memused);

	return memused;
}
