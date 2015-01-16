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

#include "String.h"

enString::enString()
{
}

enString::enString(const enChar *str)
{
	inner = std::string(str);
}

enString::enString(const enString &other)
{
	inner = other.inner;
}

enString::enString(const std::string &other)
{
	inner = other;
}

void enString::Clear()
{
	inner.clear();	
}

void enString::Reserve(size_t i)
{
	inner.reserve(i);
}

void enString::Append(const enChar *ptr)
{
	inner.append(ptr);
}

void enString::Append(Int32 v)
{	
	char buff[10];
	enMemory::Memset(buff, 0, sizeof(buff));

	itoa(v, buff, 10);

	inner.append(buff);
}

void enString::Append(Int64 v)
{
	char buff[20];
	enMemory::Memset(buff, 0, sizeof(buff));

	ltoa(v, buff, 10);

	inner.append(buff);
}

void enString::Append(enString &other)
{
	inner.append(other.inner);
}

const enChar *enString::c_str() const
{
	return inner.c_str();
}

enChar *enString::c_str()
{
	return const_cast<enChar *>(inner.c_str());
}

enChar &enString::operator[](const size_t i)
{
	return inner[i];
}

const enChar &enString::operator[](const size_t i) const
{
	return inner[i];
}

void enString::operator=(const enString &other)
{
	inner = other.inner;
}

void enString::operator=(const enChar *ptr)
{
	inner = ptr;
}

enString enString::operator+(const enChar *ptr)
{
	return enString(inner + ptr);
}

enString enString::operator+(const enString &other)
{
	return enString(inner + other.inner);
}

enString &enString::operator+=(const enChar *ptr)
{	
	inner.append(ptr);

	return *this;
}

bool enString::operator==(const enString &other) const
{
	return (inner == other.inner);
}

// Static

// TODO:

enString enString::toString(Int32 v)
{
	return enString();
}

enString enString::toString(Uint32 v)
{
	return enString();
}

// Friend

enString operator+(const enChar *ptr, const enString &other)
{	
	return enString(ptr) + other;
}