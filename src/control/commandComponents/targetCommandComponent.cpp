#include "control/commandComponents.h"
#include "control/command.h"
#include "logic/objects/component.h"

const void targetCommandComponent::action(command* _command, game* _game){
    prevx=_command->targetX;
    prevy=_command->targetY;
    _command->targetY=targetY;
    _command->targetX=targetX;
}
const void targetCommandComponent::reverseAction(command* _command, game* _game){
    _command->targetY=prevy;
    _command->targetX=prevx;
}