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
    float ms;
    bool order;

public:

    int const getSteps(){return std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);}

    void begin();

    bool step();

    void reverseBegin();

    void setSource(EntityID source);

    void addStep(textureManager::imgDir frame, float ms);

};