#pragma once
#include "generation/biomeFactory.h"

class caveFactory: public biomeFactory {
protected:
    int _wallPercentage;
    int _evaluations;

    int getSurrounding(int x, int y, std::vector<std::vector<int>> map);

public:
    caveFactory(int wallPercentage, int evaluations): _evaluations(evaluations), _wallPercentage(wallPercentage){};
    
    virtual void makeNew(World* world, std::vector<region>& regiones, std::vector<int>& zone, std::vector<region>& conexions, int level, randomVar& gen);
};