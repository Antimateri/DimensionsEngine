#pragma once

#include "common.h"

//state of a finite state machine
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