//classes to store animations
#pragma once

#include "common.h"
#include "graphic/textureManager.h"

//class to store animations that change the image of an entity
class innerAnimation{
private:

    World* _world;  //pointer to the world
    std::list<std::pair<float,textureManager::imgDir>> steps;   //list of steps of the animation
    std::list<std::pair<float,textureManager::imgDir>>::iterator it; //iterator to the current step
    float counter; //counter to know when to change the step
    EntityID source;   //entity to animate
    float ms=0.0;  //total time of the animation
    bool order; //0 if the animation is played in reverse, 1 otherwise
    int ntimes=1; //number of times the animation has been repeated
    int loop; //number of times the animation is repeated
    float speed=1; //speed of the animation

public:

    int const getSteps(){return std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);} //returns the number of frames in the animation

    float const getMs(){return ms;} //returns the total time of the animation in milliseconds

    void begin(World* world); //starts the animation

    bool step(); //advances the animation

    void setSpeed(float speed); 

    void setRepeats(int ntimes);

    void setSource(EntityID source);

    void addStep(textureManager::imgDir frame, float ms);   //adds a step to the animation

    void abort();  //aborts the animation

    innerAnimation* replicate();   //returns a copy of the animation

};

//class to store animations that draw directly on the window
class outerAnimation{
private:

    //struct to store the information of a step
    struct frame{
        float ms;   //time the step takes
        textureManager::imgDir img; //image to draw
        int relativeBlockX; //relative position of the image to the center of the animation in blocks
        int relativeBlockY; //relative position of the image to the center of the animation in blocks
        int relativeX; //relative position of the image to the center of the animation
        int relativeY; //relative position of the image to the center of the animation
    };

    std::list<frame> steps; //list of steps of the animation
    std::list<frame>::iterator it; //iterator to the current step
    float counter; //counter to know when to change to the step
    int centerX, centerY; //center of the animation
    float ms; //total time of the animation
    bool order; //0 if the animation is played in reverse, 1 otherwise
    int ntimes=1; //number of times the animation has been repeated
    int loop; //number of times the animation is repeated
    float speed=1; //speed of the animation

public:

    int const getSteps(){return std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);} //returns the number of frames in the animation

    float const getMs(){return ms;} //returns the total time of the animation in milliseconds

    void begin(); //starts the animation

    bool step(); //advances the animation

    void setSpeed(float speed);

    void setRepeats(int ntimes);

    void setCenter(int x, int y);

    void addStep(textureManager::imgDir img, float ms, int relativeX=0, int relativeY=0, int relativeBlockX=0, int relativeBlockY=0);

    void abort(); //aborts the animation

    void draw(); //draws the current step

    outerAnimation* replicate(); //returns a copy of the animation

};