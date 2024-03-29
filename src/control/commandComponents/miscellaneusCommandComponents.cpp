
#include "control/commandComponents/commandComponents.h"
#include "control/command.h"
#include "logic/objects/world.h"
#include "logic/objects/components/component.h"
#include "control/control.h"
#include "logic/game.h"
#include "logic/engines/behaviour/goap/goals/planningParameter.h"

int const setCurrentCommandComponent::action(command* _command, control* _controller){
    if(_controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)!=nullptr){
        if(_controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)->current!=nullptr){
            if(_controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)->current->stopable==0)
                return -1;
            _controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)->current->abort(_controller);
        }
        _controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)->current=_command;
    }
    return 0;
}

std::unordered_map<int, planningParameter *>* setCurrentCommandComponent::getPreconditions(command* _command, std::unordered_map<int, planningParameter *>* status){
    std::unordered_map<int, planningParameter *>* out=new std::unordered_map<int, planningParameter *>();
    out->insert(std::make_pair(102, (new isNotOccupiedPlan())->setOwner(_command->source)));
    return out;
}

int const setCurrentCommandComponent::reverseAction(command* _command, control* _controller){
    if(_controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)!=nullptr)
        _controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)->current=nullptr;
    return 0;
}

void setCurrentCommandComponent::abort(command* _command, control* _controller){
    if(_controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)!=nullptr)
        _controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)->current=nullptr;
}

int const resetCurrentCommandComponent::reverseAction(command* _command, control* _controller){
    if(_controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)!=nullptr)
        _controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)->current=_command;
    return 0;
}
int const resetCurrentCommandComponent::action(command* _command, control* _controller){
    if(_controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)!=nullptr)
        _controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)->current=nullptr;
    return 0;
}

void resetCurrentCommandComponent::abort(command* _command, control* _controller){
    if(_controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)!=nullptr)
        _controller->getGame()->getWorld()->Get<currentActionComponent>(_command->source)->current=_command;
}

int const recoverAPCommandComponent::action(command* _command, control* _controller){
    if(_controller->getGame()->getWorld()->Get<APComponent>(_command->source)!=nullptr)
        _controller->getGame()->getWorld()->Get<APComponent>(_command->source)->addVal(this->APRecovered);
    return 0;
}
int const recoverAPCommandComponent::reverseAction(command* _command, control* _controller){
    if(_controller->getGame()->getWorld()->Get<APComponent>(_command->source)!=nullptr)
        _controller->getGame()->getWorld()->Get<APComponent>(_command->source)->subVal(this->APRecovered);
    return 0;
}
bool recoverAPCommandComponent::hasEffect(command* _command, std::unordered_map<int, planningParameter *>* goals, std::unordered_map<int, planningParameter *>* status, World* _world){
    return goals->count(101) && !goals->at(101)->isSatisfied(status, _world);
}
std::unordered_map<int, planningParameter *>* recoverAPCommandComponent::getPreconditions(command* _command, std::unordered_map<int, planningParameter *>* status){
    return new std::unordered_map<int, planningParameter *>();
}
std::unordered_map<int, planningParameter *>* recoverAPCommandComponent::getEffects(command* _command, std::unordered_map<int, planningParameter *>* status){
    std::unordered_map<int, planningParameter *>* effects=new std::unordered_map<int, planningParameter *>();
    effects->insert({101, new planHasAP(this->APRecovered)});
    return effects;
}