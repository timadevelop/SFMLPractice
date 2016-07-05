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

bool generateRandomBool(int max) {
    return generateRandom(max) == 1;
}
