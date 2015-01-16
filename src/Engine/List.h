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

#ifndef EN_LIST_H
#define EN_LIST_H

#include <vector>
#include <algorithm>

#include "types.h"

/**
 * Basic wrapper for a list so we are not dependant on the std::vector. We could modify the implementation any time.
 */
template<class T>
class enList
{
public:
	void add(const T&);
	void insert(size_t, const T&);
	void erase(size_t);

	const T &get(size_t) const;
	T &get(size_t);

	bool isEmpty() const;
	bool isNotEmpty() const;

	size_t size() const;
	const T &operator[](size_t) const;
	T &operator[](size_t);

	void clear();

	void sort(bool (*)(T &, T &));
private:
	std::vector<T> list;
};

template<class T>
INLINE void enList<T>::sort(bool (*cmp)(T&, T&))
{
	std::sort(list.begin(), list.end(), cmp);
}

template<class T>
INLINE void enList<T>::add(const T &val)
{
	this->list.push_back(val);
}

template<class T>
INLINE void enList<T>::insert(size_t index, const T &val)
{		
	this->list.insert(list.begin() + index, val);	
}

template<class T>
INLINE void enList<T>::erase(size_t index)
{
	this->list.erase(list.begin() + index);
}

template<class T>
INLINE void enList<T>::clear()
{
	this->list.clear();
}

template<class T>
INLINE size_t enList<T>::size() const
{
	return list.size();
}

template<class T>
INLINE const T &enList<T>::operator[](size_t index) const
{
	return list[index];
}

template<class T>
INLINE T &enList<T>::operator[](size_t index)
{
	return list[index];
}

template<class T>
INLINE const T &enList<T>::get(size_t index) const
{
	return list[index];
}

template<class T>
INLINE T &enList<T>::get(size_t index)
{
	return list[index];
}

template<class T>
INLINE bool enList<T>::isEmpty() const
{
	return (list.size() == 0);
}

template<class T>
INLINE bool enList<T>::isNotEmpty() const
{
	return (list.size() != 0);
}

#endif