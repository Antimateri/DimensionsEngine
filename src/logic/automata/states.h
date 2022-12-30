#pragma once

#include "common.h"

class state{
protected:
    std::unordered_map<int, state*> conections;
    const unsigned int id;

public:

    state(unsigned int id):id(id){}

    state* const nextState(int input){
        if(!conections.count(input))return this;
        return conections[input];
    }

    int const getID(){
        return id;
    }

    void newConnection(int input, state* state){
        if(!conections.count(input))conections.insert({input,state});
        conections[input]=state;
    }

};

/*class goalState: public state{
private:

    std::unordered_map<int, command*> change;
    std::unordered_set<int> goals;

public:

    using state::state;

    state* const nextState(int input);

    bool const isGoal(int goal){
        return goals.count(goal);
    }

    void addGoal(int goal){
        goals.insert(goal);
    }

    void newConnection(int input, state* state){
        if(!conections.count(input))conections.insert({input,state});
        conections[input]=state;
    }

};*/