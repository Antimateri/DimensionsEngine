#include "control/commandComponents.h"
#include "control/command.h"
#include "logic/objects/component.h"

int const EntitySourceCommandComponent::action(command* _command, game* _game){
    prevx=_command->sourceX;
    prevy=_command->sourceY;
    prevent=_command->source;
    _command->source=ent;
    positionComponent* pos=library._world->Get<positionComponent>(ent);
    if(pos==nullptr)return 0;
    _command->sourceY=pos->tileY;
    _command->sourceX=pos->tileX;
    return 0;
}
int const EntitySourceCommandComponent::reverseAction(command* _command, game* _game){
    _command->sourceX=prevx;
    _command->sourceY=prevy;
    _command->source=prevent;
    return 0;
}