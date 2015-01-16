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

#ifndef EN_CLASS_H
#define EN_CLASS_H

class enType;
class enClass; 
template <class T> class enList;

#define CLASS_VARS()					\
public:									\
	static enType Type;					\
	virtual enType *GetType() const;	\
	static enClass *NewObject();

#define CLASS_FUNCTIONS(clazz, superclass)						\
	enType clazz::Type(#clazz, #superclass, clazz::NewObject);	\
	enType *clazz::GetType() const {							\
		return &(clazz::Type);									\
	}															\
	enClass *clazz::NewObject() {								\
		return new clazz;										\
	}

class enType {
public:
	const char *classname;
	const char *superclassname;

	// Constructor that receives the classname and superclass name
	enType(const char *, const char *, enClass* (*newCallback)());
	~enType();	

	// In case we are NOT enClass. In that case it will be null.
	enType *superclass;
	// If we have classes that are derived from us. If nobody derives from this it can be empty.
	enList<enType*> *derived;

	// New instance callback
	enClass* (*newCallback)();

	static void Initialize();
private:
	static bool initialized;
};

class enClass {
	CLASS_VARS()

	virtual ~enClass();

	// Returns the class's visible name
	const char *GetClassname() const { return GetType()->classname; };
	// Returns the superclasses visible name
	const char *GetSuperclassname() const { return GetType()->superclassname; };
		
	// If the instance is a instance of the provided type
	bool InstanceOf(enType &);

	// New, delete
	void *operator new(size_t size);
	void operator delete(void *ptr, size_t size);

	// Searches for a class type by the name
	static enType *GetClass(const char *);
	// Returns a new instance for the class found with that name
	static enClass *NewObject(const char *);

	// Must be called to build the object graph
	static void Initialize();

	friend class Profiler;
private:
	// Memory leak detection
	static int instances;
	static int size;
	static int memused;

	static bool initialized;
};

#endif