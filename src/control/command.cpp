#include "logic/objects/world.h"
#include "logic/engines/behaviour/goap/goals/planningParameter.h"
#include "control/command.h"
#include "logic/game.h"
#include "control/commandComponents/commandComponents.h"
#include "logic/objects/entity.h"

command::command(){
    source=INVALID_ENTITY;
    stopable=false;
}

command::~command(){
    it=_components.begin();
    for(;it!=_components.end();it++)
        delete (*it);
}

int command::action(control* _game){
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
    
int command::reverseAction(control* _game){
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
    out->setSource(source);
    return out;
}

command* command::setSource(EntityIndex _source){
    source=_source;
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

bool command::abort(control* _control){
    if(stopable){
        while(it!=_components.begin()){
            if(it!=_components.end())
                (*it)->abort(this, _control);
            it--;
        }
        (*it)->abort(this, _control);
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

bool command::hasEffect(std::unordered_map<int, planningParameter *>* goals, std::unordered_map<int, planningParameter *>* status, World* _world){
    auto it2=_components.end();
    it2--;
    for(;it2!=_components.begin();it2--)
        if((*it2)->hasEffect(this, goals, status, _world))return true;
    return false;
}

bool command::canExecute(std::unordered_map<int, planningParameter *>* status, game* _game){
    auto [pre,post]=getPrePost(status);
    for(auto [id,val] : *pre){
        if(val->isSatisfied(status, _game->getWorld())==false){
            delete pre;
            delete post;
            return false;
        }
    }
    delete pre;
    delete post;
    return true;
}

std::pair<planningState*,planningState*> command::getPrePost(std::unordered_map<int, planningParameter *>* status){
    std::unordered_map<int, planningParameter *>* pre=new std::unordered_map<int, planningParameter *>();
    std::unordered_map<int, planningParameter *>* post=new std::unordered_map<int, planningParameter *>();
    auto it2=_components.end();
    it2--;
    for(;it2!=_components.begin();it2--){
        for(auto [id,val] : (*(*it2)->getPreconditions(this, status))){
            if(pre->count(id)==0)
                (*pre)[id]=val;
            else
                (*pre)[id]->add(val);
        }
        for(auto [id,val] : (*(*it2)->getEffects(this, status))){
            if(post->count(id)==0)
                (*post)[id]=val;
            else
                (*post)[id]->add(val);
        }
    }
    std::queue<int> toDelete;
    for(auto [id,val] : *pre){
        if(post->count(id)){
            if(val->satisfies((*post)[id])){
                planningParameter* aux=val->substract((*post)[id]);
                if(aux!=nullptr){
                    delete val;
                    val=aux;
                }
                else{
                    delete val;
                    toDelete.push(id);
                }
                delete (*post)[id];
                post->erase(id);
            }
            else if((*post)[id]->satisfies(val)){
                planningParameter* aux=(*post)[id]->substract(val);
                if(aux!=nullptr){
                    delete (*post)[id];
                    (*post)[id]=aux;
                }
                else{
                    delete (*post)[id];
                    post->erase(id);
                }
                delete val;
            }
        }
    }
    while(!toDelete.empty()){
        pre->erase(toDelete.front());
        toDelete.pop();
    }
    return std::make_pair(pre,post);
}

std::string const command::getName(){
    return name;
}

command* command::setName(std::string _name){
    name=_name;
    return this;
}