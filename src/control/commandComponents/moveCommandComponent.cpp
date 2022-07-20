#include "control/commandComponents.h"
#include "control/command.h"
#include "logic/objects/component.h"

const void teleportCommandComponent::action(command* _command, game* _game){
    prevx=library._world->Get<positionComponent>(_command->source)->tileX;
    prevy=library._world->Get<positionComponent>(_command->source)->tileY;
    library._world->Get<positionComponent>(_command->source)->moveTo(_command->targetX,_command->targetY,library._world,_command->source);
}
const void teleportCommandComponent::reverseAction(command* _command, game* _game){
    library._world->Get<positionComponent>(_command->source)->moveTo(prevx, prevy ,library._world,_command->source);
}
const bool teleportCommandComponent::accepted(command* _command, const game* _game){
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
const void teleportCommandComponent::reverseAccepted(command* _command, const game* _game){
    APComponent* ap=library._world->Get<APComponent>(_command->source);
    if(ap==nullptr)
        return;
    this->APtaken=APpT*(abs(_command->sourceX-_command->targetX)+abs(_command->sourceY-_command->targetY));
    ap->addVal(this->APtaken);
}
const commandComponent* teleportCommandComponent::replicate(){
    return new teleportCommandComponent(this->APpT);
}