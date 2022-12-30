#include "planningParameter.h"
#include "logic/objects/components/component.h"

planningParameter *max(planningParameter *a, planningParameter *b){
    if(a->satisfies(b)){
        return a;
    }
    return b;
}

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
bool planHasAP::isSatisfied(std::unordered_map<int, planningParameter*>* situation){
    if(situation != nullptr && situation->count(getID()) && (*(*situation)[getID()]->getInfo())>=_ap){
        return true;
    }
    else if(library._world->Get<APComponent>(_owner)==nullptr || library._world->Get<APComponent>(_owner)->getVal()>=_ap){
        return true;
    }
    return false;
}

planningParameter* planHasAP::setInfo(char* data){_ap=*data;return this;}
char* planHasAP::getInfo(){return (char*)(&_ap);}