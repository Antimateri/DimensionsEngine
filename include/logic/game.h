#pragma once

#include "common.h"
#include "graphic/mainWindow.h"
#include "control/command.h"

struct controles;

struct game{
public:

    enum gameState{
        Run,
        Stop,
        Pause
    };

    std::deque<command*> _register;

    gameState _gameState;

    game();
    ~game();

    bool initGame();
    void gameLoop();
    void run();
    void processInput();
    void executeCommand(command* c);

};