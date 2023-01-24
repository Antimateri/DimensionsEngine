//interface for an input/output module
#pragma once
#include "common.h"

class IO{
public:
    IO(){};
    ~IO(){};
    virtual void processInput(game* game, control* controller)=0;
    virtual void presentScene(game* game)=0;
    virtual void delay(int ms)=0;
};