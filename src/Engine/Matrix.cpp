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

#include "Matrix.h"

enMat3x3 identity3x3(enVector3(1, 0, 0), enVector3(0, 1, 0), enVector3(0, 0, 1));
enMat4x3 identity4x3(enVector3(1, 0, 0), enVector3(0, 1, 0), enVector3(0, 0, 1), enVector3(0, 0, 0));
enMat4x4 identity4x4(enVector4(1, 0, 0, 0), enVector4(0, 1, 0, 0), enVector4(0, 0, 1, 0), enVector4(0, 0, 0, 1));