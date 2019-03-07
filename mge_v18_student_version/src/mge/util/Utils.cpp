
#include <cstdlib>
#include <iostream>
#include "Utils.h"


int Utils::RandomRange(int min, int max,bool excludeZero)
{
    if(min > max)
    {
        std::cout<<"Your min value is bigger then max!!!"<<std::endl;
        throw;
    }

    int random = rand() % (max - min + 1) + min;

    if(random == 0 && excludeZero ) random = min;

    return random;
}
