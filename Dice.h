#ifndef TAVLA_DICE_H
#define TAVLA_DICE_H

#include <random>

class Dice {
public:
    Dice(int n =6);                     //constructor
    int Roll();                         //returns the dice value as int
private:
    int range;
    std::random_device rd;

};

#endif //TAVLA_DICE_H
