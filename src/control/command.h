#pragma once

#include "common.h"

class command{
private:

    std::list<commandComponent*>::iterator it;
    std::list<commandComponent*>::iterator currentState;
    std::list<commandComponent*> _components;
    int totalTime=0;
    int totalCost=0;
    unsigned int effect=0;

    void endAction(game* _game);

public:
    EntityID source;

    int targetX, targetY;

    bool stopable;

    command();

    void ready(){it=_components.begin();}

    EntityIndex getSource(){return source;}

    command* setSource(EntityIndex _source);

    int action(game* _game);
    
    int reverseAction(game* _game);
    
    command* replicate();
    
    bool hasEffect(std::unordered_map<int, planningParameter *>* goals, std::unordered_map<int, planningParameter *>* status);

    bool canExecute(std::unordered_map<int, planningParameter *>* status);

    std::pair<planningState*,planningState*> getPrePost(std::unordered_map<int, planningParameter *>* status);

    command* push_back(commandComponent* _component);

    command* push_front(commandComponent* _component);

    void pop_front();

    ~command();

    bool abort(game* _game);
    
    unsigned int const getTime();

    unsigned int const getCost();
};