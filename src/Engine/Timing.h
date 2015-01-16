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

#ifndef EN_TIMING_H
#define EN_TIMING_H

#include "types.h"

class enTimer
{
public:
	enTimer();

	/**
	 * Time now. Do not use for getting milliseconds or anything, use just for timers.
	 * But instead of doing it manually, better use Mark(), and Elapsed().
	 */
	enDScalar TimeNow();

	/**
	 * Marks a point in time. Use Elapsed() after to see how much time passed.
	 */
	void Mark();
	/**
	 * @return How much time has elapsed since we called Mark(). Undefined result if we didn't called Mark(). Returned time is in seconds.
	 */
	enDScalar Elapsed();

	static Uint64 Ticks();
private:
	enDScalar Time();
	enDScalar ToSeconds(enDScalar);

	enDScalar mark;
	enDScalar frequency;
};

#endif