//modules of Renderer which manage input and output
#pragma once

#include "common.h"

//interface
class toRender{
public:

    ~toRender(){};
    
    virtual void draw(SDL_Renderer* r){};

    virtual bool processInput(SDL_Event& _event, control* controller){return 0;};

};

//class to manage the background, draws it and moves camera
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

//draws the entities and provisionally manages the input of the player actions
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

//Manages the animations which change the image of the entities
class toRenderInnerAnimation: public toRender{
private:

    std::list<innerAnimation*> todo;
    bool running=1;
public:

    ~toRenderInnerAnimation(){};
    
    void draw(SDL_Renderer* r);

    bool processInput(SDL_Event& _event, control* controller){return 0;};

    void addInnerAnimation(innerAnimation* in);  //add a new animation to the list

    void pause();   //pause the animations

    void start();   //start the animations
};

//Manages the animations which draw directly on the screen
class toRenderOuterAnimation: public toRender{
private:

    std::list<outerAnimation*> todo;
    bool running=1;
public:

    ~toRenderOuterAnimation(){};
    
    void draw(SDL_Renderer* r);

    bool processInput(SDL_Event& _event, control* controller){return 0;};

    void addOuterAnimation(outerAnimation* in); //add a new animation to the list

    void pause();   //pause the animations

    void start();   //start the animations
};