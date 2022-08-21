#pragma once

#include "logic/automata/states.h"

template <typename T>
class FSM{
protected:
    state* currentState;
    std::vector<T*> states;

public:

    FSM(){
        states.push_back(new T(0));
        currentState=states[0];
    }

    T* const getCurrentState(){
        return static_cast<T*>(currentState);
    }

    T* const getState(int id){
        if(id>=states.size())return nullptr;
        return states[id];
    }

    void setCurrentState(T* state){
        currentState=state;
    }

    T* createState(){
        T* out = new T(states.size());
        states.push_back(out);
        return out;
    }

    void nextState(int input){
        currentState = currentState->nextState(input);
    }

    ~FSM(){
        for(T* i : states)
            delete i;
    }

    FSM<T>* const practicalReplicate(){
        FSM<T>* out=new FSM<T>();
        out->currentState=currentState;
        return out;
    }
};