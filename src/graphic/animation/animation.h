#pragma once

#include "common.h"
#include "graphic/textureManager.h"


//TODO search for a place to die
class innerAnimation{
private:
    std::list<std::pair<float,textureManager::imgDir>> steps;
    std::list<std::pair<float,textureManager::imgDir>>::iterator it;
    float counter;
    EntityID source;
    float ms;
    bool order;
    int ntimes=1;
    int loop;
    float speed=1;

public:

    int const getSteps(){return std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);}

    void begin();

    bool step();

    void setSpeed(float speed);

    void setRepeats(int ntimes);

    void setSource(EntityID source);

    void addStep(textureManager::imgDir frame, float ms);

    void abort();

    innerAnimation* replicate();

};