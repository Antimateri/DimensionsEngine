#include "control/command.h"

command::~command(){
    it=_components.begin();
    for(;it!=_components.end();it++)
        delete (*it);
}

int command::action(game* _game){
    for(;it!=_components.end();it++){
        if(!(*it)->accepted(this,_game)){
            it++;
            reverseAction(_game);
            return -1;
        }
        int code=(*it)->action(this,_game);
        if(code==-1){
            it++;
            reverseAction(_game);
            return -1;
        }
        else if(code>0){
            it++;
            return code;
        }
    }
    return 0;
}
    
int command::reverseAction(game* _game){
    it--;
    for(;it!=_components.begin();it--){
        (*it)->reverseAccepted(this,_game);
        int code=(*it)->reverseAction(this,_game);
        if(code>0)
            return code;
    }
    (*it)->reverseAccepted(this,_game);
    return (*it)->reverseAction(this,_game);;
}
    
command* command::replicate(){
    command* out=new command();
    auto it2=_components.begin();
    for(;it!=_components.end();it++)
        out->addActionComponent((*it)->replicate());
    return out;
}
    
/*bool command::Accepted(game* _game){
    auto it=this->it;
    for(;it!=_components.end();it++)
        if(!(*it)->accepted(this,_game)){
            for(;it!=_components.begin();it--)
                (*it)->reverseAccepted(this,_game);
            (*it)->reverseAccepted(this,_game);
            return 0;
        }
    return 1;
}*/

void command::addActionComponent(commandComponent* _component){
    _components.push_back(_component);
}

void command::addInfoComponent(commandComponent* _component){
    _components.push_front(_component);
}