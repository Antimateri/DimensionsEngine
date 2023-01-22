
#include "control/commandComponents/commandComponents.h"
#include "control/command.h"
#include "logic/objects/world.h"
#include "logic/objects/components/component.h"

int const setCurrentCommandComponent::action(command* _command, game* _game){
    if(library._world->Get<currentActionComponent>(_command->source)!=nullptr){
        if(library._world->Get<currentActionComponent>(_command->source)->current!=nullptr){
            if(library._world->Get<currentActionComponent>(_command->source)->current->stopable==0)
                return -1;
            library._world->Get<currentActionComponent>(_command->source)->current->abort(_game);
        }
        library._world->Get<currentActionComponent>(_command->source)->current=_command;
    }
    return 0;
}

std::unordered_map<int, planningParameter *>* setCurrentCommandComponent::getPreconditions(command* _command, std::unordered_map<int, planningParameter *>* status){
    std::unordered_map<int, planningParameter *>* out=new std::unordered_map<int, planningParameter *>();
    out->insert(std::make_pair(102, (new isNotOccupiedPlan())->setOwner(_command->source)));
    return out;
}

int const setCurrentCommandComponent::reverseAction(command* _command, game* _game){
    if(library._world->Get<currentActionComponent>(_command->source)!=nullptr)
        library._world->Get<currentActionComponent>(_command->source)->current=nullptr;
    return 0;
}

void setCurrentCommandComponent::abort(command* _command, const game* _game){
    if(library._world->Get<currentActionComponent>(_command->source)!=nullptr)
        library._world->Get<currentActionComponent>(_command->source)->current=nullptr;
}

int const resetCurrentCommandComponent::reverseAction(command* _command, game* _game){
    if(library._world->Get<currentActionComponent>(_command->source)!=nullptr)
        library._world->Get<currentActionComponent>(_command->source)->current=_command;
    return 0;
}
int const resetCurrentCommandComponent::action(command* _command, game* _game){
    if(library._world->Get<currentActionComponent>(_command->source)!=nullptr)
        library._world->Get<currentActionComponent>(_command->source)->current=nullptr;
    return 0;
}

void resetCurrentCommandComponent::abort(command* _command, const game* _game){
    if(library._world->Get<currentActionComponent>(_command->source)!=nullptr)
        library._world->Get<currentActionComponent>(_command->source)->current=_command;
}

int const recoverAPCommandComponent::action(command* _command, game* _game){
    if(library._world->Get<APComponent>(_command->source)!=nullptr)
        library._world->Get<APComponent>(_command->source)->addVal(this->APRecovered);
    return 0;
}
int const recoverAPCommandComponent::reverseAction(command* _command, game* _game){
    if(library._world->Get<APComponent>(_command->source)!=nullptr)
        library._world->Get<APComponent>(_command->source)->subVal(this->APRecovered);
    return 0;
}
bool recoverAPCommandComponent::hasEffect(command* _command, std::unordered_map<int, planningParameter *>* goals, std::unordered_map<int, planningParameter *>* status){
    return goals->count(101) && !goals->at(101)->isSatisfied(status);
}
std::unordered_map<int, planningParameter *>* recoverAPCommandComponent::getPreconditions(command* _command, std::unordered_map<int, planningParameter *>* status){
    return new std::unordered_map<int, planningParameter *>();
}
std::unordered_map<int, planningParameter *>* recoverAPCommandComponent::getEffects(command* _command, std::unordered_map<int, planningParameter *>* status){
    std::unordered_map<int, planningParameter *>* effects=new std::unordered_map<int, planningParameter *>();
    effects->insert({101, new planHasAP(this->APRecovered)});
    return effects;
}