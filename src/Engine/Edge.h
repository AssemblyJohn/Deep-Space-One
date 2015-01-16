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

#ifndef EN_EDGE_H
#define EN_EDGE_H

class enEdge
{
public:
	// Indexes in a list of triangles
	size_t a, b;

	enEdge()
	{
		a = b = 0;
	}

	enEdge(size_t a, size_t b)
	{
		this->a = b; this->b = b;
	}
};

#endif