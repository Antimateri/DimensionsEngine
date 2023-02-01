//aplication of IO interface for SDL library
#pragma once
#include "common.h"
#include "logic/game.h"
#include "logic/interfaces/IO.h"
#include "graphic/mainWindow.h"

class SDLIO: public IO{

    virtual void processInput(game* _game, control* controller);
    virtual void presentScene(game* game);
    virtual void delay(int ms);
};