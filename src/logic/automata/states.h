#include "common.h"

class state{
private:
    std::unordered_map<std::string, state*> conections;
    const unsigned int id;

public:

    state(unsigned int id):id(id){}

    state* const nextState(std::string input){
        if(!conections.count(input))return this;
        return conections[input];
    }

    int const getID(){
        return id;
    }

    void newConnection(std::string input, state* state){
        if(!conections.count(input))conections.insert({input,state});
        conections[input]=state;
    }

};