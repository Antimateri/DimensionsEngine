#pragma once

#include "common.h"
#include "graphic/textureManager.h"


class innerAnimation{
private:
    std::list<std::pair<float,textureManager::imgDir>> steps;
    std::list<std::pair<float,textureManager::imgDir>>::iterator it;
    float counter;
    EntityID source;
    float ms=0.0;
    bool order;
    int ntimes=1;
    int loop;
    float speed=1;

public:

    int const getSteps(){return std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);}

    float const getMs(){return ms;}

    void begin();

    bool step();

    void setSpeed(float speed);

    void setRepeats(int ntimes);

    void setSource(EntityID source);

    void addStep(textureManager::imgDir frame, float ms);

    void abort();

    innerAnimation* replicate();

};

class outerAnimation{
private:

    struct frame{
        float ms;
        textureManager::imgDir img;
        int relativeBlockX;
        int relativeBlockY;
        int relativeX;
        int relativeY;
    };

    std::list<frame> steps;
    std::list<frame>::iterator it;
    float counter;
    int centerX, centerY;
    float ms;
    bool order;
    int ntimes=1;
    int loop;
    float speed=1;

public:

    int const getSteps(){return std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);}

    float const getMs(){return ms;}

    void begin();

    bool step();

    void setSpeed(float speed);

    void setRepeats(int ntimes);

    void setCenter(int x, int y);

    void addStep(textureManager::imgDir img, float ms, int relativeX=0, int relativeY=0, int relativeBlockX=0, int relativeBlockY=0);

    void abort();

    void draw();

    outerAnimation* replicate();

};