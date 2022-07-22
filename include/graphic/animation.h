#pragma once

#include "common.h"
#include "graphic/textureManager.h"


//TODO search a place to die
//TODO reverse
class innerAnimation{
private:
    std::list<std::pair<int,textureManager::imgDir>> steps;
    std::list<std::pair<int,textureManager::imgDir>>::iterator it;
    int counter;
    EntityID source;
    int nsteps=0;

public:

    int const getSteps(){return nsteps;}

    void begin();

    bool step();

    void reverseBegin();

    bool reverseStep();

    void setSource(EntityID source);

    void addStep(textureManager::imgDir frame, int duration);

};