#include "logic/objects/world.h"
#include "logic/engines/behaviour/goap/goals/planningParameter.h"
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
        int code=(*it)->reverseAction(this,_game);
        if(code>0){
            it--;
            return code;
        }
    }
    (*it)->reverseAction(this,_game);
    return 0;
}
    
command* command::replicate(){
    command* out=new command();
    auto it2=_components.begin();
    for(;it2!=_components.end();it2++)
        out->push_back((*it2)->replicate());
    return out;
}

command* command::setSource(EntityIndex _source){
    source=_source;
    sourceX=library._world->Get<positionComponent>(source)->tileX;
    sourceY=library._world->Get<positionComponent>(source)->tileY;
    return this;
}

command* command::push_back(commandComponent* _component){
    _components.push_back(_component);
    this->totalTime+=_component->getTime();
    this->totalCost+=_component->getCost();
    return this;
}

command* command::push_front(commandComponent* _component){
    _components.push_front(_component);
    this->totalTime+=_component->getTime();
    this->totalCost+=_component->getCost();
    return this;
}

void command::pop_front(){
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
    
unsigned int const command::getTime(){
    return totalTime;
}

unsigned int const command::getCost(){
    return totalCost;
}

bool command::hasEffect(planningParameter *desiredEffect){
    auto it2=_components.end();
    it2--;
    for(;it2!=_components.begin();it2--)
        if((*it2)->hasEffect(this, desiredEffect))return true;
    return false;
}

std::unordered_map<int, planningParameter *>* command::getPreconditions(planningParameter *desiredEffect){
    std::unordered_map<int, planningParameter *>* out=new std::unordered_map<int, planningParameter *>();
    (*out)[desiredEffect->getID()] = desiredEffect;
    auto it2=_components.end();
    it2--;
    for(;it2!=_components.begin();it2--){
        std::unordered_map<int, planningParameter *>* aux=new std::unordered_map<int, planningParameter *>();
        for(auto [id,val]: *out){
            if((*it2)->hasEffect(this, val)){
                for(auto [id2,val2]: (*it2)->getPreconditions(this, val)){
                    if(aux->count(id2)==0){
                        (*aux)[id2]=val2;
                    }
                    else{
                        (*aux)[id2]=max((*aux)[id2],val2);
                    }
                }
            }
            else{
                (*aux)[id]=val;
            }
        }
        delete out;
        out=aux;
    }
    return out;
}