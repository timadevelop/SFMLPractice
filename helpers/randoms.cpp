//
// Created by vtimofeev on 19/06/16.
//

#include "randoms.h"

#include <random>
std::random_device rd;
std::mt19937 mt(rd());
int generateRandom0(int max)
{
	std::uniform_int_distribution<int> dist(0, max);
	return dist(mt);
}

int generateRandom(int max)
{
	std::uniform_int_distribution<int> dist(0, max);
	return dist(mt);
}

int generateRandomInt(int min ,int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

float generateRandomFloat(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(mt);
}

bool generateRandomBool(int max) {
    return generateRandom(max) == 1;
}
