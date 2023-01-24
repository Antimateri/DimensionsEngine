#include "planningParameter.h"
#include "logic/objects/components/component.h"
#include "logic/objects/world.h"
#include "logic/game.h"

namespace std
{
    template <>
    struct hash<planningParameter>
    {
        size_t operator()(const planningParameter& k) const
        {
            return hash<int>()(k.getID()); 
        }
    };
}

bool planHasAP::satisfies(planningParameter *parameter){
    if(parameter->getID()==getID() && (*parameter->getInfo())<=_ap){
        return true;
    }
    return false;
}

//TODO si no lo encuentras en la situacion lo añades, no deberiamos estar mirando la situacion sino la proyeccion
bool planHasAP::isSatisfied(std::unordered_map<int, planningParameter*>* situation, World* _world){
    int sum = 0;
    if(situation != nullptr && situation->count(getID())){
        sum+=(*(*situation)[getID()]->getInfo());
    }
    else if(_world->Get<APComponent>(_owner)!=nullptr){
        sum+=_world->Get<APComponent>(_owner)->getVal();
    }
    if(sum>=_ap){
        return true;
    }
    return false;
}

planningParameter* planHasAP::setInfo(char* data){_ap=*data;return this;}
char* planHasAP::getInfo(){return (char*)(&_ap);}

bool isNotOccupiedPlan::isSatisfied(std::unordered_map<int, planningParameter*>* situation, World* _world){
    return _world->Get<currentActionComponent>(getOwner())->current == nullptr;
}