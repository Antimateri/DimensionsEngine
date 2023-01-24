//main game class
#pragma once

#include "common.h"

struct controles;

struct game{
private:

    bool lockInput=false;
    control* _controlUnit=nullptr;
    IO* _IOUnit=nullptr;
    World* _world=nullptr;

public:

    enum gameState{
        Run,
        Combat,
        Stop,
        Pause
    };

    gameState _gameState;

    game();
    ~game();

    bool isLocked(){return lockInput;}
    void changeGameState(gameState state);
    bool initGame();                                    //init the game
    void gameLoop();                                    //main game loop
    void run();                                         //runs the game in the main loop
    void processInput();                                //process the input in the main loop
    
    void addControlUnit(control* c);                    //adds a control unit to the game

    void addIOUnit(IO* i){                              //adds an IO unit to the game
        _IOUnit=i;
    }

    void setWorld(World* w){                            //sets the world of the game
        _world=w;
    }

    World* getWorld(){                            //gets the world of the game
        return _world;
    }

};