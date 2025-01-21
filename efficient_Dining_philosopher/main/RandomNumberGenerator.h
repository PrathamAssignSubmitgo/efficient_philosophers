#pragma once
using namespace std;
#include <time.h>
#include <random>

#define INT_MAX 2147483647

class RandomNumberGenerator
{
public:
	static unsigned int Get()
	{
		static default_random_engine generator;
		static uniform_int_distribution<unsigned int> distribution(5, 20);
		unsigned int number = distribution(generator);
		return number;
	}
};