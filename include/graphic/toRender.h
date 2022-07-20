#pragma once

#include "common.h"

class toRender{
public:

    ~toRender(){};
    
    virtual void draw(SDL_Renderer* r){};

    virtual bool processInput(SDL_Event& _event){};

};

class toRenderBackground: public toRender{
public:

    ~toRenderBackground(){};

    void draw(SDL_Renderer* r);

};

class toRenderEntities: public toRender{
public:

    struct {
        //map
        SDL_Event mapUp;
        SDL_Event mapDown;
        SDL_Event mapRight;
        SDL_Event mapLeft;
        //player
    }controls;

    ~toRenderEntities(){};

    void draw(SDL_Renderer* r);

    bool processInput(SDL_Event& _event);
};