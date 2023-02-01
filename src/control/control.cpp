#include "control/command.h"
#include "control/control.h"
#include "logic/engines/behaviour/behaviourEngine.h"

void commandControl::applyTurn(game* game){
    behaviourEngine(game, this);    //Apply the behaviour engine

    if(waiting.empty())return;    //If there are no commands to apply, return

    for(auto c : waiting.front()){  //Apply all the commands in the first list
        int code=c->action(this);
        //when the command ends (returns 0)
        if(code==0){
            _register.push_back(c);
            if(_register.size()>NUMBER_COMMANDS_REMEMBERED){
                delete _register.front();
                _register.pop_front();
            }
        }
        //when the command is waiting for something (returns > 0)
        else if(code>0){
            while(waiting.size()<=code)
                //adds the command again inte the queue in the correct position to run it again when the waiting is over
                waiting.push_back(std::list<command*>());   
            auto it=waiting.begin();
            std::advance(it,code);
            (*it).push_back(c);
        }
    }
    waiting.pop_front();
}

void commandControl::addCommand(command* c){
    c->ready();
    if(waiting.empty())
        waiting.push_front(std::list<command*>());
    waiting.front().push_back(c);
}

commandControl::~commandControl(){
    for(auto c : _register)
        delete c;
    for(auto l : waiting)
        for(auto c : l)
            delete c;
}