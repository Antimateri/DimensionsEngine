//Class to manage input and output
#pragma once

#include "common.h"
#include "graphic/toRender/toRender.h"


struct Renderer{
private:

    std::list<toRender*> render;    //List of layers to render
    
public:

    ~Renderer();

    void draw(SDL_Renderer* r);    //Draws the scene

    void processInput(SDL_Event& _event, control* controller); //Process input adding changes to the controller

    void addLayer(toRender* render);    //Add a layer to the Renderer

    void removeLastLayer();            //Remove the last layer from the Renderer

};