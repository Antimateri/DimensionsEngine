#include "logic/automata/states.h"

template <typename T>
class FSM{
private:
    state* currentState;
    std::vector<T*> states;

public:

    FSM(){}
    FSM(int nstates){
        states.reserve(nstates);
        for(int i=0;i<nstates;i++){
            states[i] = new T(i);
        }
        FSM();
    }

    T* const getCurrentState(){
        return static_cast<T>(currentState);
    }

    T* const getState(int id){
        if(id>=states.size())return nullptr;
        return states[id];
    }

    T* createState(){
        T* out = new T(states.size());
        states.push_back(out);
        return out;
    }

    void nextState(std::string input){
        currentState = currentState->nextState(input);
    }

    ~FSM(){
        for(T* i : states)
            delete i;
    }
};