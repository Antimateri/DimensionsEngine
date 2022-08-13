#include "control/command.h"

command::~command(){
    it=_components.begin();
    for(;it!=_components.end();it++)
        delete (*it);
}

int command::action(game* _game){
    currentState=_components.end();
    for(;it!=_components.end();it++){
        if(!(*it)->accepted(this,_game)){
            return -1;
        }
        int code=(*it)->action(this,_game);
        if(code==-1){
            return -1;
        }
        else if(code>0){
            currentState=it;
            it++;
            return code;
        }
    }
    return 0;
}
    
int command::reverseAction(game* _game){
    for(;it!=_components.begin();it--){
        (*it)->reverseAccepted(this,_game);
        int code=(*it)->reverseAction(this,_game);
        if(code>0){
            it--;
            return code;
        }
    }
    (*it)->reverseAccepted(this,_game);
    (*it)->reverseAction(this,_game);
    return 0;
}
    
command* command::replicate(){
    command* out=new command();
    auto it2=_components.begin();
    for(;it2!=_components.end();it2++)
        out->addActionComponent((*it2)->replicate());
    return out;
}
    
bool command::Accepted(game* _game){
    bool out=1;
    auto it=_components.begin();
    for(;it!=_components.end();it++)
        if(!(*it)->accepted(this,_game)){
            out=0;
            break;
        }
    it--;
    for(;it!=_components.begin();it--)
        (*it)->reverseAccepted(this,_game);
    (*it)->reverseAccepted(this,_game);
    return 1;
}

void command::addActionComponent(commandComponent* _component){
    _components.push_back(_component);
}

void command::addInfoComponent(commandComponent* _component){
    _components.push_front(_component);
}

bool command::abort(){
    if(stopable){
        it=_components.end();
        if(library._world->Get<currentActionComponent>(source)!=nullptr && library._world->Get<currentActionComponent>(source)->current==this)
            library._world->Get<currentActionComponent>(source)->current=nullptr;
        (*currentState)->abort();
        return 1;
    }
    return 0;
}