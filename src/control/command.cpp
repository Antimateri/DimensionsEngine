#include "control/command.h"
#include "control/commandComponents/commandComponents.h"

command::~command(){
    it=_components.begin();
    for(;it!=_components.end();it++)
        delete (*it);
}

int command::action(game* _game){
    currentState=_components.end();
    for(;it!=_components.end();it++){
        if(!(*it)->accepted(this,_game)){
            bool prev=stopable;
            stopable=1;
            it--;
            abort(_game);
            stopable=prev;
            return -1;
        }
        int code=(*it)->action(this,_game);
        if(code==-1){
            bool prev=stopable;
            stopable=1;
            it--;
            abort(_game);
            stopable=prev;
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
    if(_components.size()==0)return 0;
    bool out=1;
    it=_components.begin();
    for(;it!=_components.end();it++)
        if(!(*it)->accepted(this,_game)){
            out=0;
            break;
        }
    return out;
}

bool command::ReverseAccepted(game* _game){
    it--;
    for(;it!=_components.begin();it--)
        (*it)->reverseAccepted(this,_game);
    (*it)->reverseAccepted(this,_game);
    return 1;
}

command* command::addActionComponent(commandComponent* _component){
    _components.push_back(_component);
    this->totalTime+=_component->getTime();
    if(_component->getEffect()!=0){
        effect=_component->getEffect();
    }
    return this;
}

command* command::addInfoComponent(commandComponent* _component){
    _components.push_front(_component);
    return this;
}

void command::removeInfoComponent(){
    _components.pop_front();
}

bool command::abort(game* _game){
    if(stopable){
        while(it!=_components.begin()){
            (*it)->abort(this, _game);
            it--;
        }
        (*it)->abort(this, _game);
        it=_components.end();
        return 1;
    }
    return 0;
}

unsigned int const command::getEffect(){
    return effect;
}
    
unsigned int const command::getTime(){
    return totalTime;
}