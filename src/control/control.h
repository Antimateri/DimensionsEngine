//aplication of the control interface of logic to a command architecture
#pragma once

#include "common.h"
#include "logic/interfaces/control.h"

class commandControl: public control{
private:
    std::list<std::list<command*>> waiting; //queue of commands to apply, each list is a turn, when the turn ends the first list is removed

public:

    std::deque<command*> _register; //list of commands that have been applied

    commandControl(){}
    ~commandControl();
    void applyTurn(game* game);
    void addCommand(command* c);
};