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

#ifndef EN_MT_RANDOM_H
#define EN_MT_RANDOM_H

#include "types.h"
#include "Timing.h"

#define EN_MT_LENGTH 624

/**
 * Mersene Twister implmentation
 */
class enMtRandom
{
public:
	enMtRandom() 
	{
		idx = 0;
		Seed(enTimer::Ticks());
	}

	/**
	 * Seeds the random generator with the provided seed.
	 */
	void Seed(Uint32 seed)
	{
		mt[0] = seed;
		int i;

		for (i = 1; i < EN_MT_LENGTH; i++)
		{
			mt[i] = (1812433253 * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i) & bitMask_32;
		}
	}

	/**
	 * Returns a 'random' unsigned integer number.
	 */
	Uint32 Rand()
	{
		if (idx == 0)
		{
			InnerGeneration();
		}

		unsigned int y = mt[idx];

		y ^= y >> 11;
		y ^= (y << 7) & 2636928640;
		y ^= (y << 15) & 4022730752;
		y ^= y >> 18;
		idx = (idx + 1) % EN_MT_LENGTH;

		return y;
	}

	/**
	 * Same as 'Rand' but it returns the number within (0, range)
	 */
	Uint32 Rand(Uint32 range)
	{
		return (Rand() % range);
	}

private:
	void InnerGeneration()
	{
		int i;
		unsigned int y;

		for (i = 0; i < EN_MT_LENGTH; i++)
		{
			y = (mt[i] & bitPow_31) + (mt[(i + 1) % EN_MT_LENGTH] & (bitPow_31 - 1));

			mt[i] = mt[(i + 397) % EN_MT_LENGTH] ^ (y >> 1);

			if (y % 2)
			{
				mt[i] ^= 2567483615;
			}
		}
	}

	static const unsigned int bitMask_32 = 0xffffffff;
	static const unsigned int bitPow_31 = 1 << 31;

	unsigned int mt[EN_MT_LENGTH];
	unsigned int idx;
};



#endif