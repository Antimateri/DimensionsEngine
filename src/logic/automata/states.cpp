#include "logic/automata/states.h"
#include "logic/game.h"

state* const goalState::nextState(int input){
    if(change.count(input)) library._game->addCommand(change[input]);
    if(!conections.count(input)) return this;
    return conections[input];
}