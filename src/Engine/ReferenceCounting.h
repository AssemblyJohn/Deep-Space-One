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

#ifndef EN_REFERENCE_COUNTING_H
#define EN_REFERENCE_COUNTING_H

#include "types.h"
#include "Profiler.h"

/** Simple reference counted object. */
class enRefObject
{
public:
	enRefObject() : references(0) {}
	~enRefObject() { EN_ASSERT(references == 0); }

	Uint32 Retain() const
	{
		return (++references);
	}

	Uint32 Release() const
	{
		references--;
		if (references == 0)
		{
			delete this;
		}

		return references;
	}

	Uint32 GetReferenceCount() const
	{
		return references;
	}

private:
	mutable Uint32 references;
};

/** Simple pointer to reference counted objects. */
template<class T>
class enRefPtr
{
public:
	enRefPtr() : reference(NULL) {}
	enRefPtr(T *ptr, bool initRef = true)
	{
		EN_ASSERT(ptr);

		reference = ptr;
		if (initRef)
			reference->Retain();
	}
	enRefPtr(enRefPtr &other)
	{
		reference = other.reference;
		reference->Retain();
	}

	~enRefPtr() 
	{
		reference->Release();
	}

	enRefPtr &operator=(T *ptr)
	{
		// Old ref so we can release
		T *old = reference;

		// Build new reference
		reference = ptr;
		reference->Retain();

		// In case we used the default no-arg constructor the old ref might be null
		if (old)
		{
			old->Release();
		}

		return *this;
	}

	// Carefull, we just set the reference, we are not releasing anything
	enRefPtr &operator=(const enRefPtr &other)
	{
		reference = other.reference;
		return *this;
	}

	T *operator->() const
	{
		return reference;
	}

	operator T*() const
	{
		return reference;
	}

	void Release()
	{
		reference->Release();
	}

	Uint32 GetReferenceCount() const
	{
		return reference->GetReferenceCount();
	}

	T *GetReference()
	{
		return reference;
	}
private:
	T *reference;
};

#endif