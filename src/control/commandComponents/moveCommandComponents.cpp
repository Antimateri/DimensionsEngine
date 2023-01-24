#include "control/commandComponents/commandComponents.h"
#include "control/command.h"
#include "logic/objects/components/component.h"
#include "logic/engines/behaviour/behaviourEngine.h"
#include "logic/objects/world.h"
#include "logic/engines/behaviour/goap/goals/planningParameter.h"
#include "logic/game.h"
#include "control/control.h"

int const teleportCommandComponent::action(command* _command, control* _controller){
    prevx=_controller->getGame()->getWorld()->Get<positionComponent>(_command->source)->tileX;
    prevy=_controller->getGame()->getWorld()->Get<positionComponent>(_command->source)->tileY;
    if(_controller->getGame()->getWorld()->Get<positionComponent>(_command->source)->moveTo(_command->targetX,_command->targetY,_controller->getGame()->getWorld(),_command->source)!=positionComponent::moveError::succes)
        return -1;
    return 0;
}
int const teleportCommandComponent::reverseAction(command* _command, control* _controller){
    if(_controller->getGame()->getWorld()->Get<positionComponent>(_command->source)->moveTo(prevx, prevy ,_controller->getGame()->getWorld(),_command->source)!=positionComponent::moveError::succes)
        return -1;
    return 0;
}

commandComponent* const teleportCommandComponent::replicate(){
    return new teleportCommandComponent(this->APpT);
}

int const randomMoveCommandComponent::action(command* _command, control* _controller){
    if(_controller->getGame()->getWorld()->Get<APComponent>(_command->source)!=nullptr && _controller->getGame()->getWorld()->Get<APComponent>(_command->source)->getVal()<APCost){
        //_command->abort(_controller);
        return -1;
    }
    if(_controller->getGame()->getWorld()->Get<APComponent>(_command->source)!=nullptr)
        _controller->getGame()->getWorld()->Get<APComponent>(_command->source)->subVal(APCost);
    int tries=0;
    do{
        dirTaken=1<<rand()%4+1;
        tries++;
    }while(_controller->getGame()->getWorld()->Get<positionComponent>(_command->source)->moveInDirection(dirTaken, _controller->getGame()->getWorld(), _command->source)!=positionComponent::moveError::succes\
            && tries<10);
    return 0;
}

int const randomMoveCommandComponent::reverseAction(command* _command, control* _controller){
    _controller->getGame()->getWorld()->Get<positionComponent>(_command->source)->moveInDirection(directions::getOpposite(dirTaken), _controller->getGame()->getWorld(), _command->source);
    return 0;
}

bool randomMoveCommandComponent::hasEffect(command* _command, std::unordered_map<int, planningParameter *>* goals, std::unordered_map<int, planningParameter *>* status, World* _world){
    if(goals->count(100) && !(*goals)[100]->isSatisfied(status, _world))return true;
    return false;
}

std::unordered_map<int, planningParameter *>* randomMoveCommandComponent::getPreconditions(command* _command, std::unordered_map<int, planningParameter *>* status){
    std::unordered_map<int, planningParameter *>* out = new std::unordered_map<int, planningParameter *>();
    out->insert({101, (new planHasAP(10))->setOwner(_command->source)});
    return out;
}

std::unordered_map<int, planningParameter *>* randomMoveCommandComponent::getEffects(command* _command, std::unordered_map<int, planningParameter *>* status){
    std::unordered_map<int, planningParameter *>* out = new std::unordered_map<int, planningParameter *>();
    out->insert({100, (new planMove())->setOwner(_command->source)});
    return out;
}