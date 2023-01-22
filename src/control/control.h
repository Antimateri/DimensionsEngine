#pragma once

#include "common.h"
#include "logic/interfaces/control.h"

class commandControl: public control{
private:
    std::list<std::list<command*>> waiting;

public:

    std::deque<command*> _register;

    commandControl(){}
    ~commandControl();
    void applyTurn(game* game);
    void addCommand(command* c);
};