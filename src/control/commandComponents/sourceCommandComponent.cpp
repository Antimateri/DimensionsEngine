#include "control/commandComponents.h"
#include "control/command.h"
#include "logic/objects/component.h"

const void EntitySourceCommandComponent::action(command* _command, game* _game){
    prevx=_command->sourceX;
    prevy=_command->sourceY;
    prevent=_command->source;
    _command->source=ent;
    positionComponent* pos=library._world->Get<positionComponent>(ent);
    if(pos==nullptr)return;
    _command->targetY=pos->tileY;
    _command->targetX=pos->tileX;
}
const void EntitySourceCommandComponent::reverseAction(command* _command, game* _game){
    _command->sourceX=prevx;
    _command->sourceY=prevy;
    _command->source=prevent;
}