#pragma once

#include "common.h"
#include "control/commandComponents.h"
#include "logic/game.h"

struct command{

    EntityID source;

    int sourceX, sourceY;

    int targetX, targetY;

    std::list<commandComponent*> _components;

    void action(game* _game);
    
    void reverseAction(game* _game);
    
    command* replicate();
    
    bool Accepted(game* _game);

    void addActionComponent(commandComponent* _component);

    void addInfoComponent(commandComponent* _component);

    ~command();
    
};