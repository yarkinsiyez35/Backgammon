#include "Dice.h"
#include <random>

Dice::Dice(int n) : range(n)
{
}

int Dice::Roll()
{
    std::uniform_int_distribution<int> dist (1,range);
    return dist(rd);
}