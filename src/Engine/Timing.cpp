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

#include "Timing.h"

#include <Windows.h>

enTimer::enTimer()
{
	LARGE_INTEGER temp;
	QueryPerformanceFrequency(&temp);

	frequency = (enDScalar) temp.QuadPart;
}

enDScalar enTimer::TimeNow()
{
	return ToSeconds(Time());
}

void enTimer::Mark()
{
	mark = TimeNow();
}

enDScalar enTimer::Elapsed()
{
	return (TimeNow() - mark);
}

enDScalar enTimer::Time()
{
	LARGE_INTEGER temp;
	QueryPerformanceCounter(&temp);
	
	return (enDScalar) temp.QuadPart;
}

enDScalar enTimer::ToSeconds(enDScalar time)
{
	return (time / frequency);
}

Uint64 enTimer::Ticks()
{
	return GetTickCount64();
}