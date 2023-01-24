#pragma once

#include "common.h"

class toRender{
public:

    ~toRender(){};
    
    virtual void draw(SDL_Renderer* r){};

    virtual bool processInput(SDL_Event& _event, control* controller){return 0;};

};

class toRenderBackground: public toRender{
private:

    const int speed=1;
    World* _world;
    int up=0,down=0,left=0,right=0;

public:

    struct {
        //map
        SDL_Scancode mapUp;
        SDL_Scancode mapDown;
        SDL_Scancode mapRight;
        SDL_Scancode mapLeft;
        //player
    }controls;

    toRenderBackground(World* _world){
        this->_world=_world;
        controls.mapUp=SDL_SCANCODE_UP;
        controls.mapDown=SDL_SCANCODE_DOWN;
        controls.mapLeft=SDL_SCANCODE_LEFT;
        controls.mapRight=SDL_SCANCODE_RIGHT;
    }

    ~toRenderBackground(){};

    void draw(SDL_Renderer* r);

    bool processInput(SDL_Event& _event, control* controller);

};

class toRenderEntities: public toRender{
private:

    game* _game;

public:

    struct {
        //map
        SDL_Event mapUp;
        SDL_Event mapDown;
        SDL_Event mapRight;
        SDL_Event mapLeft;
        //player
    }controls;

    toRenderEntities(game* _game){
        this->_game=_game;
    }

    ~toRenderEntities(){};

    void draw(SDL_Renderer* r);

    bool processInput(SDL_Event& _event, control* controller);
};

class toRenderInnerAnimation: public toRender{
private:

    std::list<innerAnimation*> todo;
    bool running=1;
public:

    ~toRenderInnerAnimation(){};
    
    void draw(SDL_Renderer* r);

    bool processInput(SDL_Event& _event, control* controller){return 0;};

    void addInnerAnimation(innerAnimation* in);

    void pause();

    void start();
};

class toRenderOuterAnimation: public toRender{
private:

    std::list<outerAnimation*> todo;
    bool running=1;
public:

    ~toRenderOuterAnimation(){};
    
    void draw(SDL_Renderer* r);

    bool processInput(SDL_Event& _event, control* controller){return 0;};

    void addOuterAnimation(outerAnimation* in);

    void pause();

    void start();
};