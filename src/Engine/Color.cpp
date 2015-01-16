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

#include "Color.h"

enColor::enColor()
{
	R = G = B = A = 1.0f;
}

enColor::enColor(Uint32 color)
{
	A = (float)(color >> 24 & 0xFF);
	R = (float)(color >> 16 & 0xFF);
	G = (float)(color >> 8 & 0xFF);
	B = (float)(color >> 0 & 0xFF);

	A /= 255.0f;
	R /= 255.0f;
	G /= 255.0f;
	B /= 255.0f;
}

enColor::enColor(float r, float g, float b, float a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

enColor::enColor(float r, float g, float b)
{
	R = r;
	G = g;
	B = b;
	A = 1;
}

Uint32 enColor::GetRed()
{
	return (Uint32)(R * 255);
}

Uint32 enColor::GetGreen()
{
	return (Uint32)(G * 255);
}

Uint32 enColor::GetBlue()
{
	return (Uint32)(B * 255);
}

void enColor::Clamp()
{
	R = (R < 1) ? R : 1;
	G = (G < 1) ? G : 1;
	B = (B < 1) ? B : 1;
}

Uint32 enColor::ToUint32() const
{
	Uint32 r = (Uint32)(R * 255.0f);
	Uint32 g = (Uint32)(G * 255.0f);
	Uint32 b = (Uint32)(B * 255.0f);
	Uint32 a = (Uint32)(A * 255.0f);

	return (a << 24) | (r << 16) | (g << 8) | b;
}

enColor enColor::operator+(const enColor &c) const
{
	return enColor(
		R + c.R, 
		G + c.G, 
		B + c.B, 
		A + c.A
	);
}

enColor enColor::operator-(const enColor &c) const
{
	return enColor(
		R - c.R, 
		G - c.G, 
		B - c.B, 
		A - c.A
	);
}

enColor enColor::operator*(float f) const
{
	return enColor(
		R * f, 
		G * f, 
		B * f, 
		A * f
	);
}