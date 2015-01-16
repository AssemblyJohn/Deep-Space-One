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

#ifndef EN_TYPES_H
#define EN_TYPES_H

#define INLINE __forceinline

typedef __w64 unsigned int size_t;

typedef unsigned __int64 Uint64;
typedef __int64 Int64;

typedef unsigned int Uint32;
typedef int Int32;

typedef unsigned short Uint16;
typedef short Int16;

typedef float enScalar;
typedef double enDScalar;

typedef __int64 enLongLong;
typedef unsigned __int64 enULongLong;

typedef unsigned char byte;
typedef char enChar;

enum {
	EN_FALSE = 0,
	EN_TRUE = 1,
};

typedef char enBool;

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#endif