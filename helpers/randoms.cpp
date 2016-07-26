//
// Created by vtimofeev on 19/06/16.
//

#include "randoms.h"

int generateRandom0(int max)
{
    return rand() % max;
}

int generateRandom(int max)
{
    int r = rand();
    return (r % max) + 1;
}

float generateRandomFloat(float max, float min)
{
	return static_cast<float>(((max - min)*(static_cast<float>(rand()) / RAND_MAX)) + min);
}

bool generateRandomBool(int max) {
    return generateRandom(max) == 1;
}
