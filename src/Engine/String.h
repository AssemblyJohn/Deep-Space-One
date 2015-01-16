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

#ifndef EN_STRING_H
#define EN_STRING_H

#include <string>
#include "types.h"
#include "Memory.h"

INLINE int enStrCmp(const char *s1, const char *s2)
{
	return strcmp(s1, s2);
}

// Should make a string pool for this class.
class enString
{
public:
	enString();
	enString(const enChar *);
	enString(const enString &);
	enString(const std::string &);

	void Clear();
	void Reserve(size_t);

	void Append(const enChar *);
	void Append(Int32);
	void Append(Int64);
	void Append(enString &);	

	const enChar *c_str() const;
	enChar *c_str();

	enChar &operator[](const size_t);
	const enChar &operator[](const size_t) const;
	void operator=(const enString &);
	void operator=(const enChar *);
	enString operator+(const enChar *);
	enString operator+(const enString &);
	enString &operator+=(const enChar *);

	friend enString operator+(const enChar *, const enString &);

	bool operator==(const enString&) const;

	static enString toString(Int32);
	static enString toString(Uint32);
private:
	std::string inner;
};

#endif