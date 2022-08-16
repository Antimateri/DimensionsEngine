#include "control/commandComponents/commandComponents.h"
#include "control/command.h"
#include "logic/objects/components/component.h"

int const targetCommandComponent::action(command* _command, game* _game){
    prevx=_command->targetX;
    prevy=_command->targetY;
    _command->targetY=targetY;
    _command->targetX=targetX;
    return 0;
}
int const targetCommandComponent::reverseAction(command* _command, game* _game){
    _command->targetY=prevy;
    _command->targetX=prevx;
    return 0;
}