#include "control/commandComponents.h"
#include "control/command.h"
#include "logic/objects/component.h"

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
bool const teleportCommandComponent::accepted(command* _command, const game* _game){
    APComponent* ap=library._world->Get<APComponent>(_command->source);
    if(ap==nullptr)
        return 1;
    this->APtaken=APpT*(abs(_command->sourceX-_command->targetX)+abs(_command->sourceY-_command->targetY));
    ap->subVal(this->APtaken);
    if(library._world->map[_command->targetX][_command->targetY]!=INVALID_ENTITY || library._world->map[_command->sourceX][_command->sourceY]!=_command->source)
        return 0;
    if(ap->getVal()>=0)
        return 1;
    return 0;
}
void const teleportCommandComponent::reverseAccepted(command* _command, const game* _game){
    APComponent* ap=library._world->Get<APComponent>(_command->source);
    if(ap==nullptr)
        return;
    this->APtaken=APpT*(abs(_command->sourceX-_command->targetX)+abs(_command->sourceY-_command->targetY));
    ap->addVal(this->APtaken);
}
commandComponent* const teleportCommandComponent::replicate(){
    return new teleportCommandComponent(this->APpT);
}