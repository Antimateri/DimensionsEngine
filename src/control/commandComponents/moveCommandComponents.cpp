#include "control/commandComponents/commandComponents.h"
#include "control/command.h"
#include "logic/objects/components/component.h"
#include "logic/engines/behaviour/behaviourEngine.h"

int const teleportCommandComponent::action(command* _command, game* _game){
    prevx=library._world->Get<positionComponent>(_command->source)->tileX;
    prevy=library._world->Get<positionComponent>(_command->source)->tileY;
    if(library._world->Get<positionComponent>(_command->source)->moveTo(_command->targetX,_command->targetY,library._world,_command->source)!=positionComponent::moveError::succes)
        return -1;
    return 0;
}
int const teleportCommandComponent::reverseAction(command* _command, game* _game){
    if(library._world->Get<positionComponent>(_command->source)->moveTo(prevx, prevy ,library._world,_command->source)!=positionComponent::moveError::succes)
        return -1;
    return 0;
}

commandComponent* const teleportCommandComponent::replicate(){
    return new teleportCommandComponent(this->APpT);
}

int const randomMoveCommandComponent::action(command* _command, game* _game){
    if(library._world->Get<APComponent>(_command->source)!=nullptr && library._world->Get<APComponent>(_command->source)->getVal()<10){
        //_command->abort(_game);
        return -1;
    }
    if(library._world->Get<APComponent>(_command->source)!=nullptr)
        library._world->Get<APComponent>(_command->source)->subVal(10);
    do{
        dirTaken=1<<rand()%10;
    }while(library._world->Get<positionComponent>(_command->source)->moveInDirection(dirTaken, library._world, _command->source)!=positionComponent::moveError::succes);
    return 0;
}

int const randomMoveCommandComponent::reverseAction(command* _command, game* _game){
    library._world->Get<positionComponent>(_command->source)->moveInDirection(directions::getOpposite(dirTaken), library._world, _command->source);
    return 0;
}

bool randomMoveCommandComponent::hasEffect(command* _command, std::unordered_map<int, planningParameter *>* goals, std::unordered_map<int, planningParameter *>* status){
    if(goals->count(100) && !(*goals)[100]->isSatisfied(status))return true;
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