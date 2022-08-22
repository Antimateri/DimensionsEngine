#pragma once

#include "common.h"
#include "logic/game.h"

struct command{
private:

    std::list<commandComponent*>::iterator it;
    std::list<commandComponent*>::iterator currentState;
    int totalTime=0;
    unsigned int effect=0;

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

    bool ReverseAccepted(game* _game);

    command* addActionComponent(commandComponent* _component);

    command* addInfoComponent(commandComponent* _component);

    void removeInfoComponent();

    ~command();

    bool abort(game* _game);

    unsigned int const getEffect();
    
    unsigned int const getTime();
};