#pragma once
#include <random>

class Random {

    static std::mt19937 random;

public:

    static int Int(int min, int max); //static means not related to instance; exists as is for all instances of class
    static float Float(float min, float max);

};