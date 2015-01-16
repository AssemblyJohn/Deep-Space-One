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

#ifndef EN_COLOR_H
#define EN_COLOR_H

#include "types.h"

class enColor
{
public:
	float R, G, B, A;

	enColor();
	enColor(Uint32 color);
	enColor(float r, float g, float b, float a);
	enColor(float r, float g, float b);
	
	Uint32 GetRed();
	Uint32 GetGreen();
	Uint32 GetBlue();
	Uint32 GetAlfa();

	void Clamp();
	Uint32 ToUint32() const;

	enColor operator+(const enColor &) const;
	enColor operator-(const enColor &) const;
	enColor operator*(float f) const;
};

#endif