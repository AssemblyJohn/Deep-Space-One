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

#ifndef EN_MAP_H
#define EN_MAP_H

#include <map>

#include "types.h"

template<class K, class V>
class enMap
{
public:
	// Will put the value in the map or replace the value if it is already in the map
	void put(K &, V &);
	// Removes a value and key from the map
	void remove(const K &);
	// If the value is contained a reference is retrieved, else NULL or 0 or false
	V get(const K &);
	bool contains(const K &) const;
private:
	std::map<K, V> values;
};

template<class K, class V>
INLINE void enMap<K, V>::put(K &key, V &val)
{
	values[key] = val;
}

template<class K, class V>
INLINE void enMap<K, V>::remove(const K &key)
{
	values.erase(key);
}

template<class K, class V>
INLINE V enMap<K, V>::get(const K &key)
{
	return values[key];
}

template<class K, class V>
INLINE bool enMap<K, V>::contains(const K &key) const
{
	// Implement
	//EN_ASSERT(0);
	return true;
}

#endif