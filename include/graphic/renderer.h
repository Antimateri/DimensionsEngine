#pragma once

#include "common.h"
#include "graphic/toRender.h"


struct Renderer{
private:

    std::list<toRender*> render;
    
public:

    ~Renderer();

    void draw(SDL_Renderer* r);

    void processInput(SDL_Event& _event);

    void addLayer(toRender* render);

    void removeLastLayer();

};