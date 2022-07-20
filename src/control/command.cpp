#include "control/command.h"

command::~command(){
    auto it=_components.begin();
    for(;it!=_components.end();it++)
        delete (*it);
}

void command::action(game* _game){
    auto it=_components.begin();
    for(;it!=_components.end();it++)
        (*it)->action(this,_game);
}
    
void command::reverseAction(game* _game){
    auto it=_components.begin();
    for(;it!=_components.end();it++)
        (*it)->reverseAction(this,_game);
}
    
command* command::replicate(){
    /*command* out=new command();
    auto it=_components.begin();
    for(;it!=_components.end();it++)
        out->addComponent((*it)->replicate());
    return out;*/
    return this;
}
    
bool command::Accepted(game* _game){
    auto it=_components.begin();
    for(;it!=_components.end();it++)
        if(!(*it)->accepted(this,_game)){
            for(;it!=_components.begin();it--)
                (*it)->reverseAccepted(this,_game);
            (*it)->reverseAccepted(this,_game);
            return 0;
        }
    return 1;
}

void command::addActionComponent(commandComponent* _component){
    _components.push_back(_component);
}

void command::addInfoComponent(commandComponent* _component){
    _components.push_front(_component);
}