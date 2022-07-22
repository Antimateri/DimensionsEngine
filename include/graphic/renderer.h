#pragma once

#include "common.h"
#include "graphic/toRender.h"
#include "graphic/animation.h"

struct Renderer{
private:

    std::list<innerAnimation*> todo;

    void processAnimations();

public:

    ~Renderer();

    std::list<toRender*> render;

    void draw(SDL_Renderer* r);

    void processInput(SDL_Event& _event);

    void addLayer(toRender* render);

    void removeLastLayer();

    void addInnerAnimation(innerAnimation* in);
};