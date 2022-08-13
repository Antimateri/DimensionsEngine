#pragma once

#include "common.h"
#include "control/commandComponents.h"
#include "logic/game.h"

struct command{
private:

    std::list<commandComponent*>::iterator it;
    std::list<commandComponent*>::iterator currentState;

public:
    EntityID source;

    int sourceX, sourceY;

    int targetX, targetY;

    bool stopable;

    std::list<commandComponent*> _components;

    command(){source=INVALID_ENTITY;stopable=false;}

    void ready(){it=_components.begin();}

    EntityIndex getSource(){return source;}

    int action(game* _game);
    
    int reverseAction(game* _game);
    
    command* replicate();
    
    bool Accepted(game* _game);

    void addActionComponent(commandComponent* _component);

    void addInfoComponent(commandComponent* _component);

    ~command();

    bool abort();
    
};