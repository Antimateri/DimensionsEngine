#pragma once

#include "common.h"
#include "graphic/toRender.h"

struct Renderer{

    ~Renderer();

    std::list<toRender*> render;

    void draw(SDL_Renderer* r);

    void processInput(SDL_Event& _event);

    void addLayer(toRender* render);

    void removeLastLayer();
};