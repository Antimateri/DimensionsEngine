#pragma once
#include "generation/commonGen.h"

class biomeFactory{

public:

    biomeFactory() {}
    
    virtual void makeNew(World* world, std::vector<region>& regiones, std::vector<int>& zone, std::vector<region>& conexions, int level, randomVar& gen);
};