#pragma once

#include "common.h"

struct controles;

struct game{
private:

    std::list<std::list<command*>> waiting;
    bool lockInput=false;

public:

    enum gameState{
        Run,
        Combat,
        Stop,
        Pause
    };

    std::deque<command*> _register;

    gameState _gameState;

    game();
    ~game();

    void changeGameState(gameState state);
    bool initGame();
    void gameLoop();
    void run();
    void processInput();
    void addCommand(command* c);

};